#include "apple.h"
#include "ascii_objects.h"
#include "drawable.h"
#include "monster.h"


Apple::Apple(unsigned short x, unsigned short y) : Drawable({x, y, 1, 1}), gfx(APPLE) {};

void Apple::move(direction_t direction) {
	return;
}

void Apple::draw() {
	if (!is_drawn) {
		mini_gui_print_rect(mg, bounding_box, gfx);
		is_drawn = true;
	}
}

void Apple::step(DrawableList& lst)
{
	return;
}

int Apple::id() {
	return APPLE_ID;
}

void Apple::refresh() {
	return;
}
