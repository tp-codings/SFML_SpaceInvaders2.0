#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;

class Enemy
{
public:
	Enemy(Texture *texture, float posX, float posY);
	virtual ~Enemy();

	void update();
	void render(RenderTarget *target);

	//Accessor
	const FloatRect getBounds() const;
	const int getPoints() const;
	const int getHealth() const;
	const int getDamage() const;

private:

	//Shape
	CircleShape shape;
	unsigned pointCount;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;
	float speed;

	void initVariables();
	void initShape(Texture* texture, float posX, float posY);
};

