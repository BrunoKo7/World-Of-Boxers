#pragma once
#include "utils.h"
#include "GameObject.h"

class Collidable : public GameObject{
public:
	//Returns the disk that surrounds the passed GameObject.
	//Col_Disk struct's definition can be found in utils.h file.
	Col_Disk getCollisionDisk(GameObject*) const;
};
