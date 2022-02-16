#include "SuperEnemy.h"

void SuperEnemy::update()
{
	x_coord -= speed/4 * graphics::getDeltaTime();
	if (x_coord < -size) {
		active = false;
	}
}

void SuperEnemy::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	switch (hits) {
	case 0:
		br.fill_opacity = 1.0f;
		break;
	case 1:
		br.fill_opacity = 0.65f;
		break;
	case 2:
		br.fill_opacity = 0.3f;
		break;
	}
	
	br.texture = std::string(ASSET_PATH) + "baloo.png";
	graphics::drawRect(x_coord, y_coord, 2 * size, 2 * size, br);
	graphics::resetPose();

#ifdef DEBUGGING
	graphics::Brush br1;
	br1.outline_opacity = 1;
	br1.texture = "";
	br1.fill_opacity = 0.0f;
	br1.gradient = false;
	Col_Disk hull = getCollisionDisk(this);
	graphics::drawDisk(hull.center_x, hull.center_y, hull.r, br1);
#endif
}

SuperEnemy::SuperEnemy()
{
	init();
	speed *= 3;
	radius = size * 1.1f;
	type = SUPER;
}

SuperEnemy::~SuperEnemy() {}