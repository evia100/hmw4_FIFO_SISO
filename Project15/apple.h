#ifndef APPLE_H
#define APPLE_H
#define APPLE_ID 2;
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
	 * @brief Move the object in the direction
	 */
	virtual void move();

	/**
	 * @brief Draw the object
	 */
	virtual void draw();

	/**
	* @brief remove the object from the map
	*/
	void remove();

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



