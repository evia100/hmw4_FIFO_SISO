#include "drawable.h"
#include "drawable_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/* typedefs */
typedef struct Node* PNode;
typedef struct Node Node;

// DrawableList constructor
DrawableList::DrawableList() :
	head(nullptr),
	tail(nullptr),
	size(0) {};

DrawableList::~DrawableList()
{
	if (size == 0) {
		return;
	}
	PNode curr;
	// deletes all nodes in drawablelist
	while (size != 0)
	{
		curr = head->next;
		delete head->item;
		delete head;
		head = curr;
		size--;
	}
}

void DrawableList::push_front(Drawable& item)
{
	PNode new_node = new Node;
	// no need to check if the allocation succsseded.

	// if the list is empty
	if (size == 0)
	{
		new_node->item = &item;
		new_node->valid = true;
		head = new_node;
		tail = new_node;
		size++;

	}
	else
	{
		// new node prev is set to nullptr
		new_node->next = head;
		head->prev = new_node;

		new_node->item = &item;
		new_node->valid = true;
		head = new_node;
		size++;



		// new_node prev is initalized already to nullptr by ctor
		// iterator counter initalized to 0 
	}
}

void DrawableList::push_back(Drawable& item)
{
	PNode new_node = new Node;

	if (size == 0)
	{
		new_node->item = &item;
		new_node->valid = true;
		head = new_node;
		tail = new_node;
		size++;
	}
	else
	{
		// new node next is set to nullptr
		new_node->prev = tail;
		tail->next = new_node;

		new_node->item = &item;
		new_node->valid = true;
		tail = new_node;
		size++;

		// new_node next is initalized already to nullptr by ctor
		// iterator counter initalized to 0 
	}
}

void DrawableList::erase(Iterator& it)
{
	if (it.ptr == nullptr)
		return;
	if (size == 0) // no nodes at all
	{
		return;
	}
	if (size == 1) // only one node in the list.
	{
		// head/tail->next and head/tail->prev is already nullptr.
		PNode curr = it.ptr;
		curr->next = nullptr;
		curr->prev = nullptr;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	else if (it.ptr == head) // the node is the head of the list
	{
		PNode curr = it.ptr;
		
		head = curr->next;
		curr->next->prev = nullptr;
		curr->next = nullptr;
		curr->prev = nullptr;
		size--;
	}
	else if (it.ptr==tail) // the node is the tail of the list
	{
		PNode curr = it.ptr;

		tail = curr->prev;
		curr->prev->next = nullptr;

		curr->next = nullptr;
		curr->prev = nullptr;
		size--;
	}
	else // somewhere in the middle.
	{
		PNode curr_next, curr_prev, curr;
		curr = it.ptr;
		curr_next = curr->next;
		curr_prev = curr->prev;
		// disconnect the curr node
		curr_prev->next = curr_next;
		curr_next->prev = curr_prev;
		curr->next = nullptr;
		curr->prev = nullptr;
		size--;
	}
	it.invalidate();
}
int DrawableList::get_size() const
{
	return size;
}
Iterator DrawableList::begin()
{
	PNode curr = head;
	int temp_size = size;
	if (curr->valid == true) {
		Iterator new_itr = Iterator(*curr);
		return new_itr;
	}
	else
	{
		while (temp_size != 1) // already checked the head
		{
			curr = curr->next;
			if (curr->valid == true)
			{
				Iterator new_itr = Iterator(*curr);
				return new_itr;
			}
			temp_size--;
		}
	}
	// invalid_itr points to nullptr.
	Iterator invalid_itr = Iterator();
	return invalid_itr;
	
}

Iterator DrawableList::end()
{
	PNode curr=tail;
	int temp_size = size;
	if (curr->valid == true) {
		Iterator new_itr = Iterator(*curr);
		return new_itr;
	}
	else
	{
		while (temp_size != 1) // already checked the head
		{
			curr = curr->prev;
			if (curr->valid == true)
			{
				Iterator new_itr = Iterator(*curr);
				return new_itr;
			}
			temp_size--;
		}
	}

	Iterator invalid_itr = Iterator();
	return invalid_itr;
}




///* iterator functions *///
// no param ctor,initalize the iterator with nullptr.
Iterator::Iterator() : ptr(nullptr) {};
Iterator::Iterator(Node& n) : ptr(&n) {
	this->increase_counter();
}
Iterator::Iterator(const Iterator& other) {
	ptr = other.ptr;
	this->increase_counter();
}
Iterator::~Iterator()
{
		this->decrease_counter();
}
void Iterator::invalidate()
{
	if (this->ptr == nullptr)
		return;
	else {
		this->ptr->valid = false;
	}
}

void Iterator::decrease_counter()
{
	if (this->ptr == nullptr)
		return;
	this->ptr->iterator_counter--;
	if (this->ptr->iterator_counter == 0 && this->ptr->valid==false)
	{
		delete this->ptr->item;
		delete this->ptr;
	}

}

void Iterator::increase_counter()
{
	if (this->ptr == nullptr)
		return;
	else 
	{ 
		// should i increase by one only if the node is valid?
		if (this->ptr->valid == true)
		{
			this->ptr->iterator_counter++;
		}
		else
			return;
	}
}

Drawable* Iterator::get_object()
{
	if (this->ptr == nullptr)
		return nullptr;
	return this->ptr->item;
}

Iterator& Iterator::set(const Iterator& other)
{
	if (this == &other)
	{
		this->increase_counter();
		return *this;
	}
	else
	{
		this->decrease_counter();
		this->ptr = other.ptr;
		this->increase_counter();
		return *this;
	}
}

Iterator& Iterator::next()
{
	PNode curr_ptr = this->ptr;
	this->decrease_counter();
	while (curr_ptr->next->valid == false && curr_ptr!=nullptr)
	{
		curr_ptr = curr_ptr->next;
	}
	if (curr_ptr != nullptr)
	{
		this->ptr = curr_ptr;
		this->increase_counter();
	}
	return *this;
}

Iterator& Iterator::prev()
{
	PNode curr_ptr = this->ptr;
	this->decrease_counter();
	while (curr_ptr->prev->valid == false && curr_ptr != nullptr)
	{
		curr_ptr = curr_ptr->prev;
	}
	if (curr_ptr != nullptr)
	{
		this->ptr = curr_ptr;
		this->increase_counter();
	}
	return *this;
}

bool Iterator::valid() const
{
	if (this->ptr == nullptr)
		return false;
	else
	{
		if (this->ptr->valid == true)
			return true;
		else
			return false;
	}
}


int main() {
	// Test1: A Objects Only:
	cout << "Test1 - Objects Only:" << endl;
	struct rect b1 = { 1,1,1,1 };
	struct rect b2 = { 2,2,2,2 };
	struct rect b3 = { 3,3,3,3 };
	struct rect b4 = { 4,4,4,4 };
	struct rect b5 = { 5,5,5,5 };
	A* a1 = new A(b1), * a2 = new A(b2), * a3 = new A(b3), * a4 = new A(b4), * a5 = new A(b5);
	a1->print();
	a3->print();
	a5->print();


	// Test2: pointers:
	cout << endl << endl << "Test2: pointers:" << endl;
	A* a = new A(b1);
	a->print();
	delete a;
	Drawable* d;
	d = new A(b2);
	d->print();
	delete d;


	//Test3: List push
	cout << endl << endl << "Test3 - List push elem:" << endl;
	DrawableList L;
	L.push_back(*a3);
	L.push_front(*a2);
	L.push_back(*a4);
	L.push_front(*a1);
	L.push_back(*a5);
	L.print();
	cout << " list size is: " << L.get_size() << endl;


	//Test4: Iterators print
	cout << endl << endl << "Test4 - Iterators print" << endl;
	cout << "List is:" << endl;
	L.print();
	Iterator t1 = L.begin(), t2 = L.end(), t3 = L.begin();
	cout << "t1 is at: ";
	t1.get_object()->print();
	cout << "t2 is at: ";
	t2.get_object()->print();
	cout << "t3 is at: ";
	t3.get_object()->print();
	t3.next();
	t3.next();
	t2.next();
	t1.prev();
	t3.next();
	t3.prev();

	cout << "t1 is at: ";
	if (t1.valid()) {
		t1.get_object()->print();
	}
	else {
		cout << "iterator not valid!" << endl;
	}

	cout << "t2 is at: ";
	if (t2.valid()) {
		t2.get_object()->print();
	}
	else {
		cout << "iterator not valid!" << endl;
	}

	cout << "t3 is at: ";
	if (t3.valid()) {
		t3.get_object()->print();
	}
	else {
		cout << "iterator not valid!" << endl;
	}
	cout << " list size is: " << L.get_size() << endl;
	L.print();


	//Test5: Empty List
	cout << endl << endl << "Test5 - Empty list" << endl;
	cout << "List is:" << endl;
	DrawableList L2;
	L2.print();
	Iterator t4 = L2.begin();
	if (t4.valid()) {
		t4.get_object()->print();
	}
	else {
		cout << "iterator not valid!" << endl;
	}


	//Test6: Iterator invalidate
	cout << endl << endl << "Test6 - Iterator invalidate" << endl;

	t1.set(L.begin());
	t2.set(L.begin());
	t3.set(L.begin());
	t4.set(L.begin());
	cout << endl << "List is:" << endl;
	L.print();

	t4.next();
	t4.next();
	t2.next();
	t2.next();
	cout << endl << "List is:" << endl;
	L.erase(t2);
	L.print();

	cout << endl;
	t2.get_object()->print();
	t4.get_object()->print();
	cout << endl;
	t4.prev();
	t2.get_object()->print();
	t4.get_object()->print();
	cout << endl;
	t2.next();
	t2.prev();
	t2.get_object()->print();
	t4.get_object()->print();

	L.erase(t1);
	L.print();
	cout << endl;
	t1.get_object()->print();
	t3.get_object()->print();
	cout << endl;
	t1.next();
	t3.next();
	t1.get_object()->print();
	t3.get_object()->print();
	t1.prev();


	if (t1.valid()) {
		t1.get_object()->print();
	}
	else {
		cout << "iterator not valid!" << endl;
	}
	return 0;
}
