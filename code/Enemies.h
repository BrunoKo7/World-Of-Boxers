#pragma once
#include "Collidable.h"
#include "graphics.h"

class Enemies : virtual public Collidable { 

protected:
	
	 //The two following declarations define the coordinates of Enemies objects inside the CANVAS.
	float x_coord;
	float y_coord;
	
	float speed;
	float size;
	float rotation;
	float caused_damage;	//Used to store the amount of damage that each Enemies object deals.
	bool active = false;	//Used to check if the Enemies objects remain inside the CANVAS.
	type_t type;			//Used to store the type of Enemies objects, based on the enumeration inside GameObject.h
	float radius;

public:

	inline type_t getType() const override { return type; } 

	inline float getXCoord() const { return x_coord; }
	
	inline float getYCoord() const { return y_coord; }

	inline float getSize() const { return size; }

	inline float getRadius() const { return radius; }
	
	inline float getCausedDamage() const { return caused_damage; }
	
	virtual inline bool isActive() const { return active;	}
	
	virtual void setType();
	
	virtual void update() override;
	virtual void draw() override;
	virtual void init() override;

	Enemies();
	~Enemies();

};