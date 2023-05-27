#include "Bullet.h"


//Con / Des
Bullet::Bullet(Texture* texture, Sprite pl, float posX, float posY, float dirX, float dirY, float movementSpeed)
{
	this->initShape(texture, pl, posX, posY);
	this->initProperties(dirX, dirY, movementSpeed);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->shape);
}

const FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}


//private Function
void Bullet::initShape(Texture* texture, Sprite pl, float posX, float  posY)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(Vector2f(posX + pl.getGlobalBounds().width/2 - this->shape.getGlobalBounds().width/33, posY));
	this->shape.scale(0.05f, 0.05f);
}

void Bullet::initProperties(float dirX, float dirY, float movementSpeed)
{
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;
}
