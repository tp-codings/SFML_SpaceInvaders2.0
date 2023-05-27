#include "Engine.h"
#include<iostream>
#include<sstream>

//Constructor / Deconstructor
Engine::Engine()
{
	this->initWindow();
	this->initVariables();
	this->initPlayer();
	this->initEnemy();
	this->initTextures();
	this->initGUI();
	this->initWorld();
}

Engine::~Engine()
{
	delete this->window;
	delete this->player;

	//Delete Textures
	for (auto & i : this->textures)
	{
		delete i.second;
	}
	//Delete Bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
	//Delete Enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

//Accessors
const bool Engine::running() const
{
	return this->window->isOpen();
}


//------------------------------------------------------------------------------------------------------------------------------

//Functions
void Engine::run()
{
	while (this->running())
	{
		this->update();
		this->render();
	}
}


void Engine::update()
{
	this->pollEvent();
	if (endGame == false)
	{
		this->updateInput();
		this->updateEnemies();
		this->updateEndGame();
		this->player->update();
		this->updateCollision();
	}
	this->updateBullets();
	this->updateCombat();
	this->updateGUI();
}

void Engine::render()
{
	this->window->clear();

	this->renderWorld();

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	
	if (this->endGame == false) this->player->render(*this->window);

	this->renderGUI(this->window);

	this->renderEndGameScreen(this->window);

	this->window->display();
	
}



//-------------------------------------------------------------------------------------------------------------------------------

//private Functions
void Engine::initWindow()
{
	this->videomode.height = 667;
	this->videomode.width = 1000;
	this->window = new RenderWindow(this->videomode, "Space Invaders 3.0", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Engine::initVariables()
{
	this->points = 0;
	this->endGame = false;
}

void Engine::initPlayer()
{
	this->player = new Player();
}

void Engine::initEnemy()
{
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
}

void Engine::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape) this->window->close();
			break;
		}
	}
}

void Engine::movePlayer()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}

}

void Engine::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (Otimization)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

		}
		++counter;
		std::cout << this->bullets.size() << std::endl;
	}
}

void Engine::updateEnemies()
{
	//Spawning
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
	{
		this->enemies.push_back(new Enemy(this->textures["Enemy"], rand() % (this->window->getSize().x - 20), -30));
		this->enemySpawnTimer = 0.f;
	}
	else
	{
		this->enemySpawnTimer += 1.f;
	}

	//Updating
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;

		}
		//Enemy player Collision
		else if (enemy->getBounds().intersects(this->player->getShape().getGlobalBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Engine::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool enemyDead = false;
		for (size_t k = 0; k < this->bullets.size() && enemyDead == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemyDead = true;
			}
		}
	}
}

void Engine::updateInput()
{
	this->movePlayer();
	if (this->player->canAttack())
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			this->bullets.push_back(new Bullet(
				this->textures["BULLET"], 
				this->player->getShape(), 
				this->player->getPos().x, 
				this->player->getPos().y, 
				0.f, -1.f, 10.f));
		}
	}
}

void Engine::updateGUI()
{
	
	std::stringstream ss;
	ss << "Points: " << this->points << std::endl << this->player->getHp();
	this->text.setString(ss.str());

	//Player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
	
}

void Engine::updateWorld()
{
}

void Engine::updateCollision()
{
	//left side
	if (this->player->getPos().x <= 0.f)
	{
		this->player->setPosition(0.f, this->player->getPos().y);
	}

	//right side
	if (this->player->getPos().x + this->player->getShape().getGlobalBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getShape().getGlobalBounds().width, this->player->getPos().y);
	}

	//top
	if (this->player->getPos().y  <= 0.f)
	{
		this->player->setPosition(this->player->getPos().x, 0.f);
	}

	//bottom
	if (this->player->getPos().y + this->player->getShape().getGlobalBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getPos().x, this->window->getSize().y - this->player->getShape().getGlobalBounds().height);
	}
}

void Engine::updateEndGame()
{
	if (this->player->getHp() == 0)
	{
		this->endGame = true;
	}
}

void Engine::renderGUI(RenderTarget *target)
{
	target->draw(this->text);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Engine::renderEndGameScreen(RenderTarget* target)
{
	if (this->endGame) target->draw(this->endGameText);
}

void Engine::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Engine::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["Enemy"] = new Texture();
	this->textures["World"] = new Texture();
	if (!this->textures["BULLET"]->loadFromFile("Texture/penis.png"))
	{
		std::cout << "ERROR::ENGINE::INITTEXTURE::FAILED LOAD FROM FILE";
	}

	if (!this->textures["Enemy"]->loadFromFile("Texture/bullet.png"))
	{
		std::cout << "ERROR::ENGINE::INITTEXTURE::FAILED LOAD FROM FILE";
	}
	if (!this->textures["World"]->loadFromFile("Texture/space.png"))
	{
		std::cout << "ERROR::ENGINE::INITTEXTURE::FAILED LOAD FROM FILE";
	}
}

void Engine::initGUI()
{
	//Load Font
	if (!this->font.loadFromFile("Fonts/1942.ttf"))
	{
		std::cout << "Fuck it lil niggaa";
	}

	//Init text
	this->text.setFont(font);
	this->text.setCharacterSize(30);
	this->text.setFillColor(Color::White);
	this->text.setString("none");
	
	//Init endGameText
	this->endGameText.setFont(font);
	this->endGameText.setCharacterSize(80);
	this->endGameText.setFillColor(Color::Red);
	this->endGameText.setString("YOU ARE DEAD");
	this->endGameText.setPosition(
		this->window->getSize().x / 2.f - this->endGameText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->endGameText.getGlobalBounds().height / 2.f);

	//Init HealthBar
	this->playerHpBar.setSize(Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(Color(0, 192, 217, 150));
	this->playerHpBar.setPosition(Vector2f(350.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(Color(25, 25, 25, 200));
}

void Engine::initWorld()
{
	this->worldBackground.setTexture(*textures["World"]);
}
