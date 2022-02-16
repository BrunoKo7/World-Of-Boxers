#include "Enemies.h"
#include "utils.h"
#include "graphics.h"
#include "config.h"
#include <random>

/*Specifies the type of the current Enemies object.
* This is done based on a probability to create an almost equal 
* amount of each type. 
* Types are CHOCO, CRYPTO, APPLE.
*/
void Enemies::setType()
{
	float prob = rand0to1();

	if (prob < (float(1) / 3)) {
		type = CHOCO;
		caused_damage = 0.2f;
		radius = size * 0.6f;
	}
	else if (prob >= (float(1) / 3) && prob < (float(2) / 3)) {
		type = CRYPTO;
		caused_damage = 0.25f;
		radius = size * 0.6f;
	}
	else {
		type = APPLE;
		caused_damage = 0.1f;
		radius = size * 0.55f;
	}
}

/*
* Updates the position, rotation and 
* checks if the Enemies object is still inside the canvas
* in order to deactivate it if necessary.
*/
void Enemies::update()
{
	x_coord -= speed * graphics::getDeltaTime();
	rotation += 0.05f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);
	if (x_coord < -size) {
		active = false;
	}
}

void Enemies::draw()
{
	graphics::setOrientation(rotation);
	graphics::Brush brush;
	graphics::Brush br;
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.f;

	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 50.0f);

	switch (type)
	{
	case CHOCO:
		brush.texture = std::string(ASSET_PATH) + "choco.png";
		break;

	case CRYPTO:
		br.texture = "";
		br.fill_color[0] = 0.1f;
		br.fill_color[1] = 0.5f + 0.5f * glow;
		br.fill_color[2] = 0.1f;
		br.fill_secondary_color[0] = 0.05f;
		br.fill_secondary_color[1] = 0.5f;
		br.fill_secondary_color[2] = 0.05f;
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.3f;
		br.gradient = true;
		br.outline_opacity = 0.0f;
		graphics::drawDisk(x_coord, y_coord, size / float(1.55f), br);
		graphics::resetPose();
		brush.texture = std::string(ASSET_PATH) + "crypto.png";
		break;

	case APPLE:
		brush.texture = std::string(ASSET_PATH) + "apple.png";
		break;
	}
	graphics::drawRect(x_coord, y_coord, size, size, brush);
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

//Initialises some of the Enemies object's fields.
void Enemies::init()
{
	active = true;
	speed = 0.2f + 0.6f * rand0to1();
	size = 50 + 30 * rand0to1();
	x_coord = CANVAS_WIDTH + 1.1f * size;
	y_coord = rand0to1() * CANVAS_HEIGHT;
	rotation = rand0to1() * 360;
	setType();
}

Enemies::Enemies() {
	init();
}

Enemies::~Enemies() {}