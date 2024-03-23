#include "Enemy.h"

Enemy::Enemy(Texture *texture, float posX, float posY)
{
	this->initVariables();
	this->initShape(texture, posX, posY);
}

Enemy::~Enemy()
{
	 
}


//Functions
void Enemy::update()
{
	this->shape.move(0.f, speed);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->shape);
}

const FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int Enemy::getPoints() const
{
	return this->points;
}

const int Enemy::getHealth() const
{
	return this->hp;
}

const int Enemy::getDamage() const
{
	return this->damage;
}


//private Functions
void Enemy::initVariables()
{
	this->pointCount = rand() % 40 + 10;
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = static_cast<int>(this->pointCount / 10);
	this->points = static_cast<int>(this->pointCount / 10);
	this->speed = this->pointCount / 10;
}

void Enemy::initShape(Texture* texture, float posX, float posY)
{
	this->shape.setPosition(posX, posY);
	this->shape.setRadius(this->pointCount);
	//this->shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
	this->shape.setTexture(texture);
}
