#include "Player.h"
#include <iostream>

//Con / Des
Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

Player::~Player()
{
}


void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::updateAttack()
{
	if (this->coolDown < this->coolDownMax)
	{
		this->coolDown +=1.f;
	}
}

//Functions
void Player::update()
{
	this->updateAttack();
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}



const Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const Sprite Player::getShape() const
{
	return this->sprite;
}

const bool Player::canAttack()
{
	if (this->coolDown >= this->coolDownMax)
	{
		this->coolDown = 0.f;
		return true;
	}
	else {
		return false;
	}
}

const int Player::getHp() const
{
	return this->health;
}

const int Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Player::loseHp(const int hp)
{
	this->health -= hp;
	if (this->health < 0)
	{
		this->health = 0;
	}
}


//private Functions
void Player::initTexture()
{
	//Load Texture
	if (!this->texture.loadFromFile("Texture/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE:: LOADING TEXTURE FAILED" << std::endl;
	}
}

void Player::initSprite()
{
	//set Texture to Sprite (Shape)
	this->sprite.setPosition(465, 480);
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.05f, 0.05f);
}

void Player::initVariables()
{
	this->movementSpeed = 15.f;
	this->coolDownMax = 10.f;
	this->coolDown = this->coolDownMax;
	this->hpMax = 50;
	this->health = this->hpMax;
}
