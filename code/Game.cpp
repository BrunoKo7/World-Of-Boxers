#include "Game.h"
#include "config.h"
#include "graphics.h" 

Game::Game()
{
}

Game::~Game()
{
	if (player) {
		delete player;
		player = nullptr;
	}
}

//Determines which one of the game's screens will be updated
//based on the current state's status and calls the appropriate update method.
void Game::update()
{
	switch (status) {
	case STATUS_START:
		updateStartScreen();
		break;
	case STATUS_PLAYING:
		updatePlayingScreen();
		break;
	case STATUS_END:
		updateEndScreen();
		break;
	}
}

//Like Game::update(), based on the current state's status
//calls the appropriate draw() method.
void Game::draw()
{
	switch (status) {
	case STATUS_START:
		drawStartScreen();
		break;
	case STATUS_PLAYING:
		drawPlayingScreen();
		break;
	case STATUS_END:
		drawEndScreen();
		break;
	}
}

//Initialises the font and background music theme.
//Also initialises the creation time of the Game object.
void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "norton.ttf");
	creation_time = graphics::getGlobalTime();
	graphics::playMusic(std::string(ASSET_PATH) + "Entertainer.mp3", 0.3f, true, 10000);
}

/*
* Creates a new  GameObject.
* This is done based on a probability to create a specific
* and desired amount of each object Class.
* Classes are Goodies, Enemies, SuperEnemy.
* Each created GameObject gets inserted in the vector.
* Also updates game's creation time.
*/
void Game::spawn() {
	if (graphics::getGlobalTime() - creation_time > 2000) {
		float prob = rand0to1();
		if (prob < 1 / float(8))
			vec.push_back(new Goodies());
		else if (prob < 3 / float(8))
			vec.push_back(new SuperEnemy());
		else
			vec.push_back(new Enemies());

		creation_time = graphics::getGlobalTime();
	}
}

/*
* Plays a specific sound effect based on the int parameter passed.
* 0: sound effect for the moment when player collides with an enemy.
* 1: sound effect for the moment when player collides with a goody.
* 2: sound effect for the moment when player destroys a superEnemy with his weapon.
* Also checks that these 3 sounds will not overlap.
*/

void Game::soundPlay(int track) {
	if (graphics::getGlobalTime() - sound_creation_time > 2000) {
		switch (track) {
		case 0:
			graphics::playSound(std::string(ASSET_PATH) + "enemyHit.mp3", 0.5, false);
			break;
		case 1:
			graphics::playSound(std::string(ASSET_PATH) + "snackTime.mp3", 0.5, false);
			break;
		case 2:
			graphics::playSound(std::string(ASSET_PATH) + "balooKill.mp3", 0.5, false);
			break;
		}
		sound_creation_time = graphics::getGlobalTime();
	}
}

/*
* Spawns player's weapon after checking that:
* -There aren't any other weapons inside the playing screen.
* -SPACEBAR has been pressed.
* -650ms have passed since the last creation.
* These are checked to increase the level of difficulty of the game.
*/
void Game::spawnWeapon() {
	if (!wp && graphics::getKeyState(graphics::SCANCODE_SPACE) && (graphics::getGlobalTime() - tongue_creation_time > 650)) {
		wp = new Weapon();
		graphics::playSound(std::string(ASSET_PATH) + "spit.mp3", 0.5, false);
		wp->setCausedDamage(player->isSuper());
		wp->setParams(player->isSuper(), player->getXCoord(), player->getYCoord(), player->getSize());
		tongue_creation_time = graphics::getGlobalTime();
	}
}

void Game::checkWeapon() {
	if (wp && !(wp->isActive())) {
		delete wp;
		wp = nullptr;
	}
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		another_creation_time = graphics::getGlobalTime();
		tongue_creation_time = graphics::getGlobalTime();
		sound_creation_time = graphics::getGlobalTime();
	}
}

//Updates all visible items - the player and its weapon, all enemies, and the superEnemy.
void Game::updatePlayingScreen()
{
	graphics::Brush br;
	if (!playerExists) {
		player = new Player();
		playerExists = 1;
	}

	if (player) {
		player->update();
	}
	
	if (player && graphics::getGlobalTime() - another_creation_time > 5000 && status == STATUS_PLAYING) {

		spawn();
		checkCollision();
		checkGameObject();
		spawnWeapon();
		checkWeapon();
		checkCollisionTongue();

		if (player->isSuper()) {
			player -> decXP(0.00035f);	//Constantly decrease superTitan's XP.
		}

		if (wp) {
			wp->update();
		}

		//Iterates the vector, determines the type of each one of its contents 
		//and calls the appropriate update() method.
		for (it = vec.begin(); it != vec.end(); it++) {

			if ((*it)->getType() == CHOCO || (*it)->getType() == CRYPTO || (*it)->getType() == APPLE) {
				enemy = dynamic_cast<Enemies*>((*it));
				enemy->update();
			}

			else if ((*it)->getType() == PILL || (*it)->getType() == SCOOBY || (*it)->getType() == STEAK) {
				g = dynamic_cast<Goodies*>((*it));
				g->update();
			}
			else{
				se = dynamic_cast<SuperEnemy*>((*it));
				se->update();
			}
		}
	}
	/*
	* When player loses, play sound FX,
	* delete all allocated memory created with new.
	* In order to do so, vector gets iterated and
	* all its items get deleted. After that, vector gets cleared.
	*/
	if (player->getRemainingLife() <= 0) {
		graphics::playSound(std::string(ASSET_PATH) + "Lost.mp3", 0.5, false);
		if (wp) {
			delete wp;
			wp = nullptr;
		}
		delete player;
		player = nullptr;
		playerExists = false;
		for (it = vec.begin(); it != vec.end(); ++it) {
		
			if ((*it)->getType() == CHOCO || (*it)->getType() == CRYPTO || (*it)->getType() == APPLE) {
				enemy = dynamic_cast<Enemies*>(*it);
				delete enemy;
				enemy = nullptr;
			}

			else if ((*it)->getType() == PILL || (*it)->getType() == SCOOBY || (*it)->getType() == STEAK) {
				g = dynamic_cast<Goodies*>(*it);
				delete g;
				g = nullptr;
			}

			else{
				se = dynamic_cast<SuperEnemy*>(*it);
				delete se;
				se = nullptr;
			}
		}
		vec.clear();
		status = STATUS_END;
	}
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_I)) {
		status = STATUS_START;
	}
}

//Iterates through the vector that contains all active or inactive gameObjects and
//checks if each and every one of them has collided with player.
//If so, deletes the gameObject and affects the player's life/xp.
void Game::checkCollision()
{
	Col_Disk player_disk; 
	for (it = vec.begin();it != vec.end();) {
		
		Enemies* enemy = nullptr;
		Goodies* g = nullptr;
		SuperEnemy* se = nullptr;
		
		if ((*it)->getType() == CHOCO || (*it)->getType() == CRYPTO || (*it)->getType() == APPLE) {
			enemy = dynamic_cast<Enemies*>((*it));
			Col_Disk go_disk = enemy->getCollisionDisk(enemy);
			player_disk = player->getCollisionDisk(player);
			float dx = abs(player_disk.center_x - go_disk.center_x);
			float dy = abs(player_disk.center_y - go_disk.center_y);
			if (sqrt(dx * dx + dy * dy) < player_disk.r + go_disk.r) {
				player->drainLife(enemy->getCausedDamage());
				it = vec.erase(it);
				soundPlay(0);
				delete enemy;
				enemy = nullptr;				
			}
			else
				++it;
		}

		else if ((*it)->getType() == PILL || (*it)->getType() == SCOOBY || (*it)->getType() == STEAK) {
			g = dynamic_cast<Goodies*>(*it);
			Col_Disk go_disk = g->getCollisionDisk(g);
			player_disk = player->getCollisionDisk(player);
			float dx = abs(player_disk.center_x - go_disk.center_x);
			float dy = abs(player_disk.center_y - go_disk.center_y);
			if (sqrt(dx * dx + dy * dy) < player_disk.r + go_disk.r) {
				player->drainLife(g->getBoost());
				it = vec.erase(it);
				soundPlay(1);
				delete g;
				g = nullptr;
			}
			else 
				++it;
		}

		else if((*it)->getType() == SUPER){
			se = dynamic_cast<SuperEnemy*>(*it);
			Col_Disk go_disk = se->getCollisionDisk(se);
			player_disk = player->getCollisionDisk(player);
			float dx = abs(player_disk.center_x - go_disk.center_x);
			float dy = abs(player_disk.center_y - go_disk.center_y);
			if (sqrt(dx * dx + dy * dy) < player_disk.r + go_disk.r) {
				player->drainLife(se->getCausedDamage());
				it = vec.erase(it);
				soundPlay(0);
				delete se;
				se = nullptr;
			}
			else
				++it;
		}
	}
}

//Iterates through the vector that contains all active or inactive gameObjects and
//deletes the inactive ones.
void Game::checkGameObject() {

	for (it = vec.begin();it != vec.end();) {

		Enemies* enemy = nullptr;
		Goodies* g = nullptr;
		SuperEnemy* se = nullptr;

		if ((*it)->getType() == CHOCO || (*it)->getType() == CRYPTO || (*it)->getType() == APPLE) {
			enemy = dynamic_cast<Enemies*>((*it));
			if (!(enemy->isActive())) {
				it = vec.erase(it);
				delete enemy;
				enemy = nullptr;
			}
			else
				++it;
		}

		else if ((*it)->getType() == PILL || (*it)->getType() == SCOOBY || (*it)->getType() == STEAK) {
			g = dynamic_cast<Goodies*>(*it);

			if (!(g->isActive())) {
				it = vec.erase(it);
				delete g;
				g = nullptr;
			}
			else
				++it;
		}

		else if ((*it)->getType() == SUPER) {
			se = dynamic_cast<SuperEnemy*>(*it);
			if (!(se->isActive())) {
				it = vec.erase(it);
				delete se;
				se = nullptr;
			}
			else if (se->getRemainingLife() <= 0.0f) {
				if (player && !(player->isSuper())) {
					player->incrXP(0.2);
				}
				player->updateScore(30);	
				soundPlay(2);
				it = vec.erase(it);
				delete se;
				se = nullptr;
			}
			else
				++it;
		}
	}
}

//Iterates through the vector that contains all active or inactive gameObjects and
//checks if weapon (tongue) collides with superEnemies (Baloo's).
//If so decreases superEnemy's remaining life and deletes the weapon, 
//making it disappear after the collision.
void Game::checkCollisionTongue()
{
	if (wp) {
		Col_Disk wp_disk = wp->getCollisionDisk(wp);
		for (it = vec.begin();it != vec.end();) {
			if ((*it)->getType() == SUPER) {
				se = dynamic_cast<SuperEnemy*>(*it);
				Col_Disk se_disk = se->getCollisionDisk(se);
				float dx = abs(wp_disk.center_x - se_disk.center_x);
				float dy = abs(wp_disk.center_y - se_disk.center_y);
				if (sqrt(dx * dx + dy * dy) < wp_disk.r + se_disk.r) {
					se->decreaseLife(wp->getCausedDamage());
					delete wp;
					wp = nullptr;
					++it;
				}
				else
					++it;
			}
			else {
				++it;
			}
		}
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	
	//Intro + start prompt
	br.fill_color[0] = 1.0f;
	char mainText[27];
	char prompt[32];
	sprintf_s(mainText, "Welcome to WorldOfBoxers!");
	sprintf_s(prompt, "Hit ENTER to start playing! :D");
	graphics::drawText(CANVAS_WIDTH / 10.0f, CANVAS_HEIGHT / 4.0f, 30, mainText, br);
	graphics::drawText(CANVAS_WIDTH / 2.0f + 30.0f, CANVAS_HEIGHT / 2 + 20.0f, 40, prompt, br);
	
	//Info
	char instr1[20], instr2[28], instr3[25], instr4[40], instr5[50];
	sprintf_s(instr1, "Rules are simple:");
	graphics::drawText(CANVAS_WIDTH/2 + 275.0f, CANVAS_HEIGHT/2+110.0f, 19, instr1, br);
	sprintf_s(instr2, "Move Titan with WASD keys.");
	graphics::drawText(CANVAS_WIDTH / 2 + 90.0f, CANVAS_HEIGHT / 2 + 155.0f, 19, instr2, br);
	sprintf_s(instr3, "Avoid all sweets!");
	graphics::drawText(CANVAS_WIDTH / 2 + 90.0f, CANVAS_HEIGHT / 2 + 175.0f, 19, instr3, br);
	sprintf_s(instr4, "Drown cousin Baloo in Titan's drool.");
	graphics::drawText(CANVAS_WIDTH / 2 + 90.0f, CANVAS_HEIGHT / 2 + 195.0f, 19, instr4, br);
	sprintf_s(instr5, "Press SPACEBAR to spit drool towards enemies.");
	graphics::drawText(CANVAS_WIDTH / 2 + 90.0f, CANVAS_HEIGHT / 2 + 215.0f, 19, instr5, br);

	br.texture = std::string(ASSET_PATH) + "titan_intro.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 4 + 175.0f, 300, 200, br);
}

void Game::drawPlayingScreen()
{
	//Background illustration
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "back.png";
	graphics::drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//Draw unique player and unique player's weapon (tongue).
	if (player)
		player->draw();
	
	if (player && wp) {
		wp->draw();
	}

	//Draw all active gameObjects that appear on the playing screen.
	for (it = vec.begin(); it != vec.end(); ++it) {
		
		if ((*it)->getType() == CHOCO || (*it)->getType() == CRYPTO || (*it)->getType() == APPLE) {
			enemy = dynamic_cast<Enemies*>(*it);
			enemy->draw();
		}

		else if ((*it)->getType() == PILL || (*it)->getType() == SCOOBY || (*it)->getType() == STEAK) {
			g = dynamic_cast<Goodies*>(*it);
			g->draw();
		}

		else{
			se = dynamic_cast<SuperEnemy*>(*it);
			se->draw();
		}
	}

	//INFO FOR THE PLAYER
	//Health bar
	float p_life = 0.0f;
	player? p_life = player->getRemainingLife(): 0.0f;
	br.texture = "";
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.8f;
	br.fill_color[1] = 0.03f;
	br.fill_color[2] = 0.03f;
	graphics::drawRect(CANVAS_WIDTH - 76 - (1.0f - p_life) * 150 / 2, 10, float(150)*p_life, 18.0f, br);
	
	//HEALTH text over bar
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0;
	char health[16];
	sprintf_s(health, "H E A L T H");
	graphics::drawText(CANVAS_WIDTH - 123, 18.0f, 20, health, br);

	//XP bar
	//Fills after killing SuperEnemy objects.
	float p_xp = 0.0f;
	player ? p_xp = player->getXP() : 0.0f;
	br.texture = "";
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.16f;
	br.fill_color[1] = 0.19f;
	br.fill_color[2] = 0.55f;
	graphics::drawRect(CANVAS_WIDTH - 151.5f + (p_xp) * 150 / 2, 28.65f, float(150)*p_xp, 18.0f, br);
	
	//XP text over bar
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	char XP[6];
	sprintf_s(XP, "X P ");
	graphics::drawText(CANVAS_WIDTH - 100, 37.0f, 20, XP, br);

	//Score text
	char score[30];
	int p_score = player ? player->getScore() : 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	sprintf_s(score, "Score: %d", p_score);
	graphics::drawText(10.0f, 25.0f, 20, score, br);
}

void Game::drawEndScreen()
{
	graphics::Brush br;
	char info[26];
	char info2[51];
	char exit[21];
	
	sprintf_s(info, "Titan  got  diabetes :(");
	graphics::drawText(CANVAS_WIDTH / 3.0f + 10.0f, CANVAS_HEIGHT / 2 - 30.0f, 30.0f, info, br);
	
	sprintf_s(info2, "Press  I  to  inject  insulin  and  play  again!");
	graphics::drawText(CANVAS_WIDTH / 4.0f, CANVAS_HEIGHT / 2 + 15.0f, 30.0f, info2, br);
	
	sprintf_s(exit, "Press Esc to exit.");
	graphics::drawText(CANVAS_WIDTH - 230.0f, CANVAS_HEIGHT - 18.0f, 30, exit, br);
}