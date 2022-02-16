#include "Goodies.h"
#include "graphics.h"
#include "config.h"
#include "utils.h"

void Goodies::update()
{
}

void Goodies::draw()
{
	graphics::Brush brush;
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;
	switch (type)
	{
	case SCOOBY:
		brush.texture = std::string(ASSET_PATH) + "scooby_snacks.png";
		break;

	case STEAK:
		brush.texture = std::string(ASSET_PATH) + "steak.png";
		break;

	case PILL:
		brush.texture = std::string(ASSET_PATH) + "pill.png";
		break;
	}
	graphics::drawRect(x_coord, y_coord, 100*size, 100*size, brush);
	graphics::resetPose();


#ifdef DEBUGGING
	graphics::Brush br1;
	br1.outline_opacity = 1;
	br1.texture = "";
	br1.fill_opacity = 0.0f;
	br1.gradient = false;
	Col_Disk hull = getCollisionDisk((GameObject*)this);
	graphics::drawDisk(hull.center_x, hull.center_y, hull.r, br1);
#endif
}

/*
* Specifies the type of the current Goodies object.
* This is done based on a probability to create a specific
* and desired amount of each type.
* Types are SCOOBY, PILL, STEAK.
* Also initialises some of the object's fields.
*/
void Goodies::init()
{
	active = true;
	x_coord = rand0to1() * CANVAS_WIDTH;
	y_coord = rand0to1() * CANVAS_HEIGHT;
	float prob = rand0to1();
	if (prob < (float(1) / 6)) {
		type = PILL;
		radius = size * 55;
		boost = 0.65f;
	}
	else if (prob >= (float(1) / 6) && prob < (float(4) / 6)) {
		type = STEAK;
		radius = size * 53;
		boost = 0.25f;
	}
	else {
		type = SCOOBY;
		radius = size * 55;
		boost = 0.4f;
	}
}

Goodies::Goodies() {
	init();
}
Goodies::~Goodies() {}