#include "Weapon.h"
#include "graphics.h"
#include "config.h"

void Weapon::update()
{
	x_coord += speed * graphics::getDeltaTime();
	rotation -= 0.05f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);
	if (x_coord > size + CANVAS_WIDTH) {
		active = false;
	}
}

void Weapon::draw()
{
	graphics::setOrientation(rotation);
	graphics::Brush brush;
	brush.texture = std::string(ASSET_PATH) + "tongue.png";
	brush.outline_opacity = 0.0f;
	brush.fill_opacity = 1.0f;
	graphics::drawRect(x_coord, y_coord, size, size, brush);
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

void Weapon::setCausedDamage(bool super) {
	active = true;
	caused_damage = super ? 3.0f : 1.0f;
}

void Weapon::init()
{
}

void Weapon::setParams(bool super, float x, float y, float sz)
{
	x_coord = x + sz*60;
	y_coord = y;
	size = 35*sz;
	radius = size / 2.f;
}

Weapon::Weapon(){}
Weapon::~Weapon() {}