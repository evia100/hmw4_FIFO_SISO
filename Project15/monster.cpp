#include "monster.h"
#include "ascii_objects.h"

class Monster : public Drawable {

	// The level of the monster
	int level = 1;

	// The velocity of the monster
	int vel = 1;

	// The direction the moster is moving right now
	direction_t current_direction = left;

	// How much to keep the last direction
	int direction_hold = 0;

	// Direction counter
	int direction_counter = 0;

	// The next bounding box
	struct rect next_bb = this->bounding_box;

	// The gfx of the monster
	const char* gfx = MONSTER0;

public:

	/**
	 * @brief Initiate a level 1 monster in x,y
	 */
	Monster(unsigned short x, unsigned short y, int direction_hold) {
		this->bounding_box.x = x;
		this->bounding_box.y = y;
		this->direction_hold = direction_hold;
	};

	/**
	 * @brief Move the object in the direction
	 */
	virtual void move(direction_t direction) {

		//checking if the object already move all the direction hold steps.
		if (this->direction_counter >= this->direction_hold) {
			this->direction_counter = 0;
			this->current_direction = direction;
		};

		//get screen size
		rect screen_size = mini_gui_get_screen_size(this->mg);

		//check if the next movement is pushing the monster out of bounds.
		//if not - set next step to this position
		switch (this->current_direction) {
		case left:
			if (this->bounding_box.x + vel < screen_size.x) {
				this->next_bb.x = this->bounding_box.x + vel;
			};
			break;
		case right:
			if (this->bounding_box.x - this->bounding_box.width - vel > screen_size.x - screen_size.width) {
				this->next_bb.x = this->bounding_box.x - vel;
			};
			break;
		case up:
			if (this->bounding_box.y + vel < screen_size.y) {
				this->next_bb.y = this->bounding_box.y + vel;
			};
			break;
		case down:
			if (this->bounding_box.y - this->bounding_box.height - vel > screen_size.y - screen_size.height) {
				this->next_bb.y = this->bounding_box.y - vel;
			};
			break;
		};
		this->direction_counter++;
	}
	/**
	 * @brief Draw the object
	 */
	virtual void draw() {
		mini_gui_clear_rect(this->mg, this->bounding_box);
		mini_gui_print_rect(this->mg, next_bb, gfx);
	};

	/**
	 * @brief Return an ID that is unique to
	 * the dynamid type of the drawable object.
	 */
	virtual int id();

	/**
	 * @brief Is called whenever any refresh is required
	 */
	virtual void refresh() {
		if (this->level < 5) {
			this->vel = 1;
			this->gfx = MONSTER0;
		}
		else if (this->level >= 5 and this->level < 15) {
			this->vel = 1;
			this->gfx = MONSTER1;
			this->next_bb.height = 5
		}
		else if (this->level >= 15 and this->level < 25) {
			this->vel = 1;
			this->gfx = MONSTER2;
			this->next_bb.height = 5
		}
		else {
			this->vel = 2;
			this->gfx = MONSTER3;
			this->next_bb.height = 5;
		};
	};

	/**
	 * @brief Do a step in the 'game of life'
	 * @param lst A list of all drawable objects in the world
	 */
	virtual void step(DrawableList& lst) {
		for (int i = 0; i < len(lst), i++) {
			if collide(this, lst[i]) {
				if (lst[i]->id == APPLE) {
					lst[i].remove();
					this->level++;
				}
				else if (lst[i]->id == MONSTER) {
					if (lst[i]->level > this->level) {
						mini_gui_clear_rect(this->mg, this->bounding_box);
						this->level += lst[i]->level;
					}
				}
				refresh();
			}


		};
	};
};
