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
	else {
		it.ptr->valid = false;
	}

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

void Iterator::decrease_counter()
{
	this->ptr->iterator_counter--;

}

/*
Iterator::Iterator(const Iterator& other)
{

}
*/
