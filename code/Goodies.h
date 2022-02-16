#pragma once
#include "Collidable.h"

class Goodies : virtual public Collidable {
	
	float x_coord;
	float y_coord;
	float size = 0.8f;
	float radius;
	float boost;	//Used to store the amount of boost that main player gets after colliding ("eating") with Goodies objects.
	
	bool active;	
	
	type_t type;
public:
	
	void update() override;
	void draw() override;
	void init() override;
	
	inline float getBoost() { return -boost; }
	inline float getXCoord() { return x_coord; }
	inline float getYCoord() { return y_coord; }
	inline float getSize() { return size; }
	inline float getRadius() { return radius; }
	inline bool isActive() {return active;}
	inline type_t getType() const override { return type; }

	Goodies();
	~Goodies();
};