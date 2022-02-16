#include "Collidable.h"
#include "GameObject.h"
#include "Enemies.h"
#include "SuperEnemy.h"
#include "Goodies.h"
#include "Player.h"
#include "Weapon.h"

//Defines and returns the Col_Disk for the GameObject passed as a parameter.
Col_Disk Collidable::getCollisionDisk(GameObject* obj) const {
	
	Enemies* enemy = nullptr;
	SuperEnemy* se = nullptr;
	Goodies* g = nullptr;
	Weapon* wp = nullptr;
	Player* pl = nullptr;
	type_t type = obj->getType();
	
	Col_Disk disk;

	//Used to check the specific type of the passed parameter
	//and downcast it to access its methods and initialise 
	//the Col_Disk to be returned.
	switch (type) {

	case CHOCO:
	case APPLE:
	case CRYPTO: 
		enemy = dynamic_cast<Enemies*>(obj);
		disk.center_x = enemy->getXCoord();
		disk.center_y = enemy->getYCoord();
		disk.r = enemy->getRadius();
		break;

	case STEAK:
	case PILL:
	case SCOOBY:
		g = dynamic_cast<Goodies*>(obj);
		disk.center_x = g->getXCoord();
		disk.center_y = g->getYCoord();
		disk.r = g->getRadius();
		break;

	case PLAYER:
		pl = dynamic_cast<Player*>(obj);
		disk.center_x = pl->getXCoord();
		disk.center_y = pl->getYCoord();
		disk.r = pl->getRadius();
		break;

	case SUPER:
		se = dynamic_cast<SuperEnemy*>(obj);
		disk.center_x = se->getXCoord();
		disk.center_y = se->getYCoord();
		disk.r = se->getRadius();
		break;

	case WEAPON:
		wp = dynamic_cast<Weapon*>(obj);
		disk.center_x = wp->getXCoord();
		disk.center_y = wp->getYCoord();
		disk.r = wp->getRadius();
		break;
	}
	
	return disk;
}
