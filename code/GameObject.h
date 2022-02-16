#pragma once
#include "utils.h"

class GameObject {
public:
	
	typedef enum { CHOCO, CRYPTO, APPLE, SUPER, SCOOBY, STEAK, PILL, WEAPON, PLAYER } type_t; //Used to refer to various specific GameObject types faster.
	
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;

	virtual type_t getType() const = 0;
	
	GameObject() {};
	~GameObject() {};
};