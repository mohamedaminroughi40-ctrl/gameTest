#include "enemie.h"

void enemie::initEnemie()
{
	this->idleTex.loadFromFile("assets/gost/Idle.png");
	this->chaseTex.loadFromFile("assets/gost/Chase.png");
	this->chaseBTex.loadFromFile("assets/gost/ChaseB.png");
	this->apearTex.loadFromFile("assets/gost/Appear.png");
	this->vanishTex.loadFromFile("assets/gost/Vanish.png");

	//heath init
	this->maxHp = 20;
	this->hp = maxHp;
}

enemie::enemie() 
{
	this->initEnemie();
	this->enemieSprite.setTexture(this->idleTex);
	//animation
	this->currentFrame = 0;
	this->animationTimeLimit = 0.5f;
	}

void enemie::setposition(float posX, float poseY)
{
	this->enemieSprite.setPosition(posX, poseY);
}

void enemie::animation()
{
	if (this->state == dead && this->currentFrame == 3)
	{
		this->currentFrame = 3;
		return;
	}
	if ( this->animationTimer.getElapsedTime().asSeconds() >= this->animationTimeLimit )
	{
		if (this->currentFrame < this->maxFrame)
		{
			this->currentFrame++;
		}
		else
		{
			this->currentFrame = 0;
		}
		this->animationTimer.restart();
		this->enemieSprite.setTextureRect(IntRect(this->currentFrame * this->widthFrame, 0, this->widthFrame, this->hightFrame));
	}
}

void enemie::stateHundling(float playerPosX)
{
	if (this->hp <= 0 )
	{
		this->state = dead;
		return;
	}
	float distance = abs(playerPosX - this->enemieSprite.getPosition().x);
	if (distance < 700) {
		if (distance < 100)
		{
			this->state = Eidle;
		}
		else if (playerPosX < this->enemieSprite.getPosition().x)
		{
			this->state = Echase;
		}
		else
		{
			this->state = EshaseB;
		}
	}

	else this->state = Eidle;
}

void enemie::movUp(float playerPosX)
{
	if (this->state == Echase)
	{
		 this->enemieSprite.move(-2.f, 0.f);
	}
	else if(this->state == EshaseB )
	{
		this->enemieSprite.move(2.f, 0.f);
	}
	
	
}


void enemie::spriteUp()
{
	switch (this->state) {
	case Eidle:
		this->maxFrame = 6;
		this->enemieSprite.setTexture(this->idleTex);
		break;
	case Echase:
		this->maxFrame = 3;
		this->enemieSprite.setTexture(this->chaseTex);
		break;
	case EshaseB:
		this->maxFrame = 3;
		this->enemieSprite.setTexture(this->chaseBTex);
		break;
	case dead:
		this->maxFrame = 3;
		this->enemieSprite.setTexture(this->vanishTex);
		break;
	}
}


void enemie::update(float playerPosX)
{
	this->stateHundling(playerPosX);
	this->movUp(playerPosX);
	this->spriteUp();
	this->animation();
}

void enemie::takeDamage(int damage)
{
	this->hp -= damage;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

Sprite enemie::getSprite()
{
	return this->enemieSprite;
}

int enemie::getHeah()
{
	return this->hp;
}


