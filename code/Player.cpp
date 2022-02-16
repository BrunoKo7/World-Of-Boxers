#include "graphics.h"
#include "Player.h"

Player::Player() {}
Player::~Player() {}

/*
* Updates the position of the Player's 
* based on the keys pressed by the user.
* Makes sure that the visible player objects
* always remains inside the CANVAS.
*/
void Player::update() {

	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		x_coord -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		x_coord += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		y_coord -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		y_coord += speed * graphics::getDeltaTime() / 10.0f;
	}

	if (x_coord < 0) x_coord = 0;
	if (x_coord > CANVAS_WIDTH) x_coord = CANVAS_WIDTH;
	if (y_coord < 0) y_coord = 0;
	if (y_coord > CANVAS_HEIGHT) y_coord = CANVAS_HEIGHT;
}

void Player::draw() {
	
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	graphics::setScale(size, size);

	//If the player is Super (XP == 1) we make him glowing.
	if (super) {
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 30);
		br.fill_color[0] = 0.3f + 0.5f * glow;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		br.fill_secondary_color[0] = 0.45f;
		br.fill_secondary_color[1] = 0.05f;
		br.fill_secondary_color[2] = 0.05f;
		br.fill_opacity = 0.7f;
		br.fill_secondary_opacity = 0.3f;
		br.gradient = true;
		br.outline_opacity = 0.0f;
		graphics::drawDisk(x_coord, y_coord, 2 * size, br);
	}

	br.texture = std::string(ASSET_PATH) + "titan_shadow.png";
	br.fill_opacity = 0.5f;
	graphics::drawRect(x_coord+size/2.0f, y_coord + 10 * size, 100, 100, br);

	br.fill_opacity = 1.0f;
	br.texture = std::string(ASSET_PATH) + "titan_normal.png";
	graphics::drawRect(x_coord, y_coord, 100, 100, br);

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

void Player::init() {}

void Player::incrXP(float amount) {
	xp = std::max<float>(0.0f, std::min<float>(xp + amount, 1.0f));
	//If Titan becomes Super (XP == 1), its size and its Col_Disk radius become twice as big.
	if (xp == 1.0f) {
		super = true;
		size *= 2.0f;
		radius *= 2.0f;
	}
}

void Player::decXP(float amount) {
	xp = std::max<float>(0.0f, std::min<float>(xp - amount, 1.0f));
	//When SuperTitan mode ends(XP == 0), both the radius and size get restored.
	if (xp == 0.0f) {
		super = false;
		size /= 2.0f;
		radius /= 2.0f;
	}
}