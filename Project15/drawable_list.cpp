#include "drawable.h"
#include "drawable_list.h"
#include "mini_gui.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

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
		/*
		curr->next = nullptr;
		curr->prev = nullptr;
		*/
		size--;
	}
	else if (it.ptr == tail) // the node is the tail of the list
	{
		PNode curr = it.ptr;

		tail = curr->prev;
		curr->prev->next = nullptr;
		/*
		curr->next = nullptr;
		curr->prev = nullptr;
		*/
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
		/*
		curr->next = nullptr;
		curr->prev = nullptr;
		*/
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
	if (curr != nullptr)
	{
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

}

Iterator DrawableList::end()
{
	PNode curr = tail;
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

Iterator::Iterator(const Iterator& other)
{
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
	if (this->ptr->iterator_counter == 0 && this->ptr->valid == false)
	{
		delete this->ptr->item;
		delete this->ptr;
		ptr = nullptr;
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


Iterator& Iterator::next() {
	if (ptr != nullptr) {
		bool found_valid = false;
		while ((found_valid == false) && (ptr != nullptr)) {
			Node* next_node = ptr->next;
			this->decrease_counter();
			ptr = next_node;
			if (ptr != nullptr) {
				increase_counter();
				found_valid = ptr->valid;
			}
		}
	}
	return (*this);
}

Iterator& Iterator::prev() {
	if (ptr != nullptr) {
		bool found_valid = false;
		while ((found_valid == false) && (ptr != nullptr)) {
			Node* prev_node = ptr->prev;
			this->decrease_counter();
			ptr = prev_node;
			if (ptr != nullptr) {
				increase_counter();
				found_valid = ptr->valid;
			}
		}
	}
	return (*this);
}



// my functions------------------------------------
/*
Iterator& Iterator::next()
{
	if (ptr != nullptr)
	{
		PNode curr = ptr;
		bool is_valid = false;
		while ((is_valid == false) && (ptr != nullptr))
		{
			if (ptr->iterator_counter == 1) // going to be deleted
			{
				while ((is_valid == false) && (ptr != nullptr))
				{
					ptr = ptr->next;
					if (ptr != nullptr)
					{
						increase_counter();
						is_valid = ptr->valid;
					}
				}
				return *this;
			}
			this->decrease_counter();
			if (ptr == nullptr && curr->next!=nullptr)
			{
				ptr = curr->next;
			}
			else //(ptr != nullptr)
			{
				ptr = ptr->next;
				if (ptr != nullptr)
				{
					increase_counter();
					is_valid = ptr->valid;
				}

			}
		return *this;
		}
	}
	else {
		// invalid_itr points to nullptr.
		Iterator invalid_itr = Iterator();
		return invalid_itr;
	}
}

*/

/*
Iterator& Iterator::prev()
{
	if (ptr != nullptr)
	{
		bool is_valid = false;
		while ((is_valid == false) && (ptr != nullptr))
		{
			if (ptr->iterator_counter == 1) // going to be deleted
			{
				while ((is_valid == false) && (ptr != nullptr))
				{
					ptr = ptr->prev;
					if (ptr != nullptr)
					{
						increase_counter();
						is_valid = ptr->valid;
					}
				}
				return *this;
			}
			this->decrease_counter();
			ptr = ptr->prev;
			if (ptr != nullptr)
			{
				increase_counter();
				is_valid = ptr->valid;
			}
		}
		return *this;
	}
	else {
		// invalid_itr points to nullptr.
		Iterator invalid_itr = Iterator();
		return invalid_itr;
	}
}
*/


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



















/***** TESTING *****/
int A::ID_ = 11;
int A::get_ID() {
	return ID_;
}

void DrawableList::print() {
	if (size == 0) {
		cout << "List Empty" << endl;
		return;
	}

	for (Iterator it = begin(); it.valid(); it.next()) {
		if (it.valid()) {
			cout << "Valid and ";
		}
		else {
			cout << "Not Valid and ";
		}
		it.get_object()->print();
		cout << "it count is: " << it.ptr->iterator_counter << endl;
	}

}

A::A(struct rect bb) :Drawable(bb), next_bb{ 0 } {}

A::~A() {}

void A::print() {
	//cout << "my ID is:" << get_ID() << endl;
	cout << "obj is: " << bounding_box.x << endl; //"my bb is: (x,y,w,h):" << "(" << bounding_box.x << ", " << bounding_box.y << ", ";
	//cout << bounding_box.width << ", " << bounding_box.height << ")" << endl;
	//cout << "my next bb is: (x,y,w,h):" << "(" << next_bb.x << ", " << next_bb.y <<", ";
	//cout << next_bb.width << ", " << next_bb.height << ")" << endl;
}

void A::move(direction_t direction) {
	next_bb = bounding_box;
	switch (direction) {
	case 0:
		next_bb.x--;
		break;
	case 1:
		next_bb.x++;
		break;
	case 2:
		next_bb.y++;
		break;
	case 3:
		next_bb.y--;
		break;
	default:
		break;
	}
}

void A::draw() {
	mini_gui_clear_rect(mg, bounding_box);
	bounding_box = next_bb;
	mini_gui_print_rect(mg, bounding_box, MONSTER0);
	next_bb = { 0 };
}

void A::refresh() {
	next_bb.x -= 2;
}

int A::id() {
	return A::get_ID();
}

void A::step(DrawableList& lst) {
	for (Iterator it = lst.begin(); it.valid(); it.next()) {
		if (collide(*(it.get_object()))) {
			cout << "collide!" << endl;
		}
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
	A *a1 = new A(b1), *a2 = new A(b2), *a3 = new A(b3), *a4 = new A(b4), *a5 = new A(b5);
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
	cout << endl;
	t1.set(L.begin());
	t2.set(L.begin());
	t3.set(L.begin());
	t4.set(L.begin());
	cout << endl << "List is:" << endl;
	L.print();

	t4.next();
	t4.next(); // t4 now points to third node (third node iterator counter should be 2)
	t2.next();
	t2.next(); // t2 now points to third node (third node iterator counter should be 3)
	cout << endl << "List before is:" << endl;
	L.print();
	cout << endl << "List after erase is:" << endl;
	L.erase(t2); // pointed to node 3
	L.print();
	cout << endl;
	cout << endl;
	t2.get_object()->print(); // points to the erased node
	t4.get_object()->print(); // points to the erased node
	cout << endl;
	cout << endl;
	t4.prev(); // points to third node and now points to second node.
	t4.get_object()->print();
	L.print();
	cout << endl;
	t2.get_object()->print();
	t4.get_object()->print();
	cout << endl;
	// problems here (not anymore)
	t3.next(); // from node 1 points to node 2
	L.print();
	cout << endl;
	t3.get_object()->print();
	cout << endl;
	t3.next(); // from node 2 to node 4 (node 3 deleted)
	L.print();
	cout << endl;
	t3.get_object()->print();
	cout << "t2 is at" << endl;
	///

	// next from a invalid Iterator
	t2.get_object()->print();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	t2.next();
	t2.get_object()->print();
	t2.prev();
	t2.get_object()->print();
	t4.get_object()->print();
	cout << endl;
	L.print();



	L.erase(t1);
	cout << endl;
	L.print();
	cout << endl;
	t1.get_object()->print();
	t3.get_object()->print();
	cout << endl;
	t1.next(); // now points to node 2
	t3.next();
	t1.get_object()->print();
	t3.get_object()->print();
	t1.prev(); // no node prev


	if (t1.valid()) {
		t1.get_object()->print();
	}
	else {
		cout << "iterator not valid!" << endl;
	}

	return 0;
}
