#pragma once
#include "Collidable.h"

class Weapon : virtual public Collidable {
	
	float x_coord;
	float y_coord;
	float speed = 0.8f;
	float size;
	float rotation;
	float radius;
	float caused_damage = 1.0f;

	bool active = false;

	type_t type = WEAPON;

public:
	void update() override;
	void draw() override;
	void init() override;

	void setCausedDamage(bool);
	void setParams(bool, float, float, float);

	inline float getRadius() const { return radius; }	
	inline float getCausedDamage() const { return caused_damage; }
	inline float getXCoord() const { return x_coord; }
	inline float getYCoord() const { return y_coord; }
	inline float getSize() const { return size; }
	
	inline bool isActive() const { return active; }
	
	inline type_t getType() const override { return type; }
	 
	Weapon();
	~Weapon();
};