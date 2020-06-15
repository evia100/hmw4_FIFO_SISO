#include "drawable.h"
#include "drawable_list.h"

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
/*
Iterator::Iterator(const Iterator& other)
{

}
*/
