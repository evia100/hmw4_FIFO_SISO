#include "apple.h"
#include "ascii_objects.h"
#include "drawable.h"

class Apple : public Drawable {

	// The gfx of the apple
	const char* gfx = APPLE;

public:

	/**
	 * @brief Initiate an apple
	 */
	Apple(unsigned short x, unsigned short y) {
		this->bounding_box.x = x;
		this->bounding_box.y = y;
	};

	/**
	 * @brief Draw the object
	 */
	virtual void draw() {
		mini_gui_print_rect(this->mg, this->bounding_box, this->gfx);
	};

	virtual void remove() {
		mini_gui_clear_rect(this->mg, this->bounding_box);
	};

	/**
	 * @brief Return an ID that is unique to
	 * the dynamid type of the drawable object.
	 */
	virtual int id();

	/**
	 * @brief Is called whenever any refresh is required
	 */
	virtual void refresh();

};




