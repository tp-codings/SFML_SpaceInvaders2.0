#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;

class Player
{
public:
	//Con / Des
	Player();
	virtual ~Player();

	//Functions
	void move(const float dirX, const float dirY);

	void update();
	void render(RenderTarget &target);


	//Accessor
	const Vector2f& getPos() const;
	const Sprite getShape() const;
	const bool canAttack();
	const int getHp() const;
	const int getHpMax() const;


	//Modifier
	void setPosition(Vector2f pos);
	void setPosition(float x, float y);
	void loseHp(const int hp);

private:
	//Shape
	Sprite sprite;
	Texture texture;

	//Variables
	float movementSpeed;
	float coolDown;
	float coolDownMax;
	int health;
	int hpMax;

	//private Functions
	void initTexture();
	void initSprite();
	void initVariables();
	void updateAttack();
};

