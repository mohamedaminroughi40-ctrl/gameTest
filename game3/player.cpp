 #include "player.h"

using namespace sf;

void player::initPlayer()
{
	//get the texturs
	this->playerIdleTex.loadFromFile("assets/player/idle.png");
	this->playerAttakTex.loadFromFile("assets/player/attack.png");
	this->playerDeathTex.loadFromFile("assets/player/death.png");
	this->playerRunTex.loadFromFile("assets/player/run.png");
	this->playerRunBackTex.loadFromFile("assets/player/runB.png");
	this->playerJumpTex.loadFromFile("assets/player/jump.png");
	//initialse the state
	this->playerState = idle;
	this->playerSprite.setTexture(this->playerIdleTex);
	//initialse the speed
	this->currentFrame = 0;
	this->animationSpeed = 0.1f;

	//jump init
	this->gravity = 0.8f;
	this->groud = 200.f;
	this->upSpeed = 0.f;
	this->isJumping = false;

	//heath init
	this->hp = this->maxHealth;

	//cooldown attake init
	this->canAttak = true;
	this->attakCooldown = 3.f;

}


player::player()
{
	this->initPlayer();
	
}


void player::takeDamage(int damage)
{
	this->hp -= damage;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}


void player::setPosition(float positionX, float positionY)
{
	this->playerSprite.setPosition(positionX, positionY);
}

void player::setGround(float g)
{
	this->groud = g;

}


void player::updateState()
{
	this->playerState = idle;
	this->maxFrame = 3;
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->playerState = run;
		this->maxFrame = 5;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->playerState = runB;
		this->maxFrame = 5;
	}
	//attake logice

	
	if (Keyboard::isKeyPressed(Keyboard::N) && this->canAttak)
	{
		this->playerState = attak;
		this->maxFrame = 4;
		
	}



	if (Keyboard::isKeyPressed(Keyboard::W) && !this->isJumping) // not jumping for the case we we click space while jumping 
	{
		this->playerState = jump;
		this->upSpeed = -10.f;
		this->isJumping = true;
		this->maxFrame = 4;
	}
}
void player::updatePlayersprite()
{
	if (this->playerLastState != this->playerState)
	{
		switch (this->playerState) {
		case jump:
			this->playerSprite.setTexture(this->playerJumpTex);
			break;
		case run:
			this->playerSprite.setTexture(this->playerRunTex);
			break;
		case runB:
			this->playerSprite.setTexture(this->playerRunBackTex);
			break;
		case idle:
			this->playerSprite.setTexture(this->playerIdleTex);
			break;
		case attak:
			this->playerSprite.setTexture(this->playerAttakTex);
			break;
		}
		this->playerLastState = this->playerState;
	}
}



void player::updateJump()
{
	this->upSpeed += this->gravity;
	this->playerSprite.move(0, this->upSpeed);

	if (this->playerSprite.getPosition().y >= this->groud )
	{
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, this->groud);
		this->upSpeed = 0;
		this->isJumping = false;
	}

}

void player::updatePlayeranimation()
{
	if (this->animationClock.getElapsedTime().asSeconds() >= this->animationSpeed)
	{
		if (this->currentFrame < maxFrame)
		{
			currentFrame++;
		}
		else
		{
			currentFrame = 0;
			
		}
		this->playerSprite.setTextureRect(IntRect(this->widthFrame * currentFrame, 0, this->widthFrame, this->hightFrame));
		this->animationClock.restart();
	}


}

FloatRect player::getHitBox()
{
	if (this->playerState == attak)
	{
		return FloatRect(
			(float)this->playerSprite.getPosition().x + 80.f,//position infront of the player
			(float)this->playerSprite.getPosition().y, //the ground as the player 
			60.f, 40.f);
	}
	return FloatRect(0, 0, 0, 0); // no attak
}


Sprite& player::getSrite(){
	return this->playerSprite;
}

Vector2f player::getPosition()
{
	return this->playerSprite.getPosition();
}

void player::update()
{
	this->updateState();
	if (this->playerState == run)
	{
		this->playerSprite.move(5.f, 0);
	}
	if (this->playerState == runB)
	{
		this->playerSprite.move(-5.f, 0);
	}
	if (this->isJumping) this->updateJump();
	this->updatePlayersprite();
	this->updatePlayeranimation();
}
