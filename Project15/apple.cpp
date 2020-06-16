#include "apple.h"
#include "ascii_objects.h"
#include "drawable.h"

Apple::Apple(unsigned short x, unsigned short y) : Drawable({x, y, 1, 1}), gfx(APPLE) {};

void Apple::move() {
	return;
}

void Apple::draw() {
	mini_gui_print_rect(mg, bounding_box, gfx);
};

void Apple::remove() {
	mini_gui_clear_rect(this->mg, this->bounding_box);
};

int Apple::id() {
	return APPLE_ID;
}

void Apple::refresh() {
	return;
}





