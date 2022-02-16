#pragma once
#include "Player.h"
#include "Enemies.h"
#include "Goodies.h"
#include "SuperEnemy.h"
#include "Weapon.h"
#include <Vector>

class Game {

	typedef enum { CHOCO, CRYPTO, APPLE, SUPER, SCOOBY, STEAK, PILL, WEAPON, PLAYER } type_t;
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_END } status_t; //Will be used to determine the current game's state.
	status_t status = STATUS_START;
	
	Player* player = nullptr;	
	Enemies* enemy = nullptr; 
	Goodies* g = nullptr; 
	SuperEnemy* se = nullptr;
	Weapon* wp = nullptr;

	bool playerExists = false;

	float creation_time;			//Used to spawn Enemies objects every 2 seconds.
	float another_creation_time;	//Used to begin spawning Enemies objects after 5 seconds in the playing screen. 
	float tongue_creation_time;		//Used to control that only 1 weapon (tongue) can be created every 0.65 seconds.
	float sound_creation_time;		//Used to control that no sound effects overlap.

	/*
	* Using a vector to store all visible GameObject's apart from the player and weapon.
	* These are created by spawn() function.
	*/
	std::vector<GameObject*> vec;
	std::vector<GameObject*>::iterator it; //Vector's iterator.

	void updateStartScreen();
	void updatePlayingScreen();
	void updateEndScreen();
	
	void drawStartScreen();
	void drawPlayingScreen();
	void drawEndScreen();
	
	void spawn();
	void spawnWeapon();
	
	void checkWeapon();
	void checkCollision();
	void checkGameObject();
	void checkCollisionTongue();
	void soundPlay(int);
	
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();
};