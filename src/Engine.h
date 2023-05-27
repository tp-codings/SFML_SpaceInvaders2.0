#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include<map>
#include<vector>

using namespace sf;

class Engine
{
public:
	//Constructor / Deconstructor
	Engine();
	virtual ~Engine();

	//Accessors
	const bool running() const;

	//Functions
	void run();

	
	void update();
	void render();

private:

	//window
	RenderWindow* window;
	VideoMode videomode;
	Event ev;
	 
	//Game objects
	Player *player;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;

	//Game logic
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int points;
	bool endGame;

	//GUI
	Font font;
	Text text;
	Text endGameText;
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;

	//World
	Sprite worldBackground;

	//Resources
	std::map<std::string, Texture*> textures;
	

	//private Functions
	void initWindow();
	void initVariables();
	void initPlayer();
	void initEnemy();
	void pollEvent();
	void movePlayer();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateEndGame();
	void renderGUI(RenderTarget *target);
	void renderEndGameScreen(RenderTarget* target);
	void renderWorld();
	void initTextures();
	void initGUI();
	void initWorld();
};

