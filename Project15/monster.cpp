#include "monster.h"
#include "drawable.h"
#include "drawable_list.h"
#include "ascii_objects.h"

Monster::Monster(unsigned short x, unsigned short y, int direction_hold) : Drawable({ x, y, 1, 1 }),
level(1),
vel(1),
current_direction(left),
direction_counter(0), gfx(MONSTER0),
next_bb({ x, y, 1, 1 }) {};

void Monster::move(direction_t direction) {

	//checking if the object already move all the direction hold steps.
	if (direction_counter >= direction_hold) {
		direction_counter = 0;
		current_direction = direction;
	};

	//get screen size
	struct rect screen_size = mini_gui_get_screen_size(this->mg);

	//check if the next movement is pushing the monster out of bounds.
	//if not - set next step to this position
	switch (current_direction) {
	case left:
		if (bounding_box.x - vel > screen_size.x) {
			next_bb.x = bounding_box.x - vel;
		};
		break;
	case right:
		if (bounding_box.x + bounding_box.width + vel < screen_size.x + screen_size.width) {
			next_bb.x = bounding_box.x + vel;
		};
		break;
	case up:
		if (bounding_box.y + vel < screen_size.y) {
			next_bb.y = bounding_box.y + vel;
		};
		break;
	case down:
		if (bounding_box.y + bounding_box.height - vel > screen_size.y + screen_size.height) {
			next_bb.y = bounding_box.y - vel;
		};
		break;
	};
	direction_counter++;
}


void Monster::draw() {
	mini_gui_clear_rect(mg, bounding_box);
	mini_gui_print_rect(mg, next_bb, gfx);
};

int Monster::id() {
	return MONSTER_ID;
}

void Monster::refresh() {
	if (level < 5) {
		gfx = MONSTER0;
		vel = 1;
		next_bb.width = 1;
		next_bb.height = 1;
	}
	else if (level < 15) {
		gfx = MONSTER1;
		vel = 1;
		next_bb.width = 3;
		next_bb.height = 1;
	}
	else if (level < 25) {
		gfx = MONSTER2;
		vel = 1;
		next_bb.width = 3;
		next_bb.height = 2;
	}
	else {
		gfx = MONSTER3;
		vel = 2;
		next_bb.width = 8;
		next_bb.height = 3;
	}
	// Get world size
	struct rect world_size = mini_gui_get_screen_size(mg);
	// Fix position in case of screen overflow
	if (next_bb.x + next_bb.width >= world_size.width) {
		next_bb.x = world_size.width - next_bb.width;
	}
	if (next_bb.y + next_bb.height >= world_size.height) {
		next_bb.y = world_size.height - next_bb.height;
	}
}

void Monster::step(DrawableList &lst) 
{
	
	for (Iterator it = lst.begin(); it.valid(); it.next) 
	{
		Drawable* object = dynamic_cast<Drawable*>(it.get_object());
		if (collide(it.get_object)) 
		{
			if ((int)object->id==APPLE_ID) 
			{
				this->level++;

			}
			else if ((int)object->id == MONSTER_ID)
			{
				Monster* object = dynamic_cast<Monster*>(it.get_object());
				if ( object->level >= this->level) {
					object->level += this->level;
					
					mini_gui_clear_rect(mg, bounding_box);
				}
				else if (object->level < this->level)
				{
					this->level += object->level;
					mini_gui_clear_rect(object->mg, object->bounding_box);
				}
			}
			refresh();
		}


	};
};
