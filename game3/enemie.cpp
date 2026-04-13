#include "enemie.h"

void enemie::initEnemie()
{
	this->idleTex.loadFromFile("assets/gost/Idle.png");
	this->chaseTex.loadFromFile("assets/gost/Chase.png");
	this->apearTex.loadFromFile("assets/gost/Appear.png");
	this->vanishTex.loadFromFile("assets/gost/Vanish.png");
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
	float distance = abs(playerPosX - this->enemieSprite.getPosition().x);
	if (distance > 700) this->state = Eidle;
	else this->state = Echase;
}

void enemie::movUp(float playerPosX)
{
	if (this->state == Echase)
	{
		if (playerPosX < this->enemieSprite.getPosition().x) this->enemieSprite.move(-1.f, 0.f);
		else this->enemieSprite.move(1.f, 0.f);
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

	}
}








void enemie::update(float playerPosX)
{
	this->stateHundling(playerPosX);
	this->movUp(playerPosX);
	this->spriteUp();
	this->animation();
}

Sprite enemie::getSprite()
{
	return this->enemieSprite;
}







