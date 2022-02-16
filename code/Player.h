#pragma once
#include "Collidable.h"
#include "config.h"

class Player : virtual public Collidable {

	float x_coord = CANVAS_WIDTH / 2, y_coord = CANVAS_HEIGHT / 2;
	float speed = 5.0f;
	float size = 1.0f;
	float life = 1.0f;
	float xp = 0.0f;
	float radius = size * 53.0f;
	float score = 0;
	
	bool super = false;	//SuperTitan mode. The player gets bigger and its hits deal 3x original damage.
	bool active = true;

	type_t type = PLAYER;

public:

	Player();
	~Player();

	void update() override;
	void draw() override;
	void init() override;

	inline float getYCoord() const  { return y_coord; }
	inline float getXCoord() const { return x_coord; }
	inline float getRemainingLife() const { return life; }
	inline float getXP() const { return xp; }
	inline float getSize() const { return size; }
	inline float getRadius() const { return radius; }
	inline float getScore() const { return score; }
	
	inline bool isSuper() const { return super; }
	inline bool isActive() const { return active; }

	inline type_t getType() const override { return type; }
	
	
	inline void updateScore(int points) { score += points; }
	inline void drainLife(float amount) { life = std::max<float>(0.0f, std::min<float>(life - amount / size, 1.0f)); }
	void incrXP(float);
	void decXP(float);
};