#include "drawable.h"
#include "drawable_list.h"

/*** typedefs ***/
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
		head = new_node;
		size++;
		// next,prev,item,iterator counter,valid is set by node c'tor ? 
	}
	else
	{
		new_node->next = head;
		head->prev = new_node;

		head = new_node;

		// new_node prev is initalized already to nullptr by ctor
		// iterator counter initalized to 0 , valid is false.
		new_node->item = &item;
	}
}

void DrawableList::push_back(Drawable& item)
{
	PNode new_node = new Node;

	// new_node next is initalized already to nullptr by ctor
	// iterator counter initalized to 0 , valid is false.
	tail->next = new_node;
	new_node->prev = tail;

	tail = new_node;
}


void DrawableList::erase(Iterator& it)
{
	it.invalidate();

}