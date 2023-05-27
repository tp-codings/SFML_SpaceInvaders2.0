#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Bullet
{
public:
	//Con / Des
	Bullet(Texture* texture, Sprite pl, float posX, float posY, float dirX, float dirY, float movementSpeed);
	virtual ~Bullet();

	//Functions
	void update();
	void render(RenderTarget *target);

	//Accessor
	const FloatRect getBounds() const;

private:
	//Shape
	Sprite shape;

	//Properties
	Vector2f direction;
	float movementSpeed;

	//private Functions
	void initShape(Texture* texture, Sprite pl, float posX, float posY);
	void initProperties(float dirX, float dirY, float movementSpeed);
};

