#pragma once
#include "Enemies.h"
#include "config.h"

class SuperEnemy : virtual public Enemies {
	
	int hits = 0; //Used to count the number of hits taken from player weapon. 3 hits make SuperEnemy "die".
	float life = 3.0f;
	float caused_damage = 0.5f;
	float radius;
	
	type_t type = SUPER;

public:

	void update();
	void draw();
	
	inline float getCausedDamage() const {return caused_damage;}
	inline float getRemainingLife() const { return life; }
	inline float getRadius() const { return radius; }
	
	inline type_t getType() const override { return type; }
	
	inline bool isActive() const { return active; }
	
	inline void decreaseLife(float damage) {
		life = std::max<float>(0.0f, std::min<float>(life - damage, 3.0f));
		hits += 1;
	}
	
	SuperEnemy();
	~SuperEnemy();

};