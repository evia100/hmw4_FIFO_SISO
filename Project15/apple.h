#ifndef APPLE_H
#define APPLE_H

#include "drawable.h"

class Apple : public Drawable {

	// The gfx of the apple
	const char* gfx;

public:

	/**
	 * @brief Initiate a level 1 monster in x,y
	 */
	Apple(unsigned short x, unsigned short y);

	/**
	 * @brief Draw the object
	 */
	virtual void draw();

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



#endif 



