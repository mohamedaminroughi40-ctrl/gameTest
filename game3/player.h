
#ifndef PLAYER_H
#define PLAYER_H


#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
using namespace sf;

//stats
enum state
{
	idle,
	run,
	runB,
	jump,
	death,
	attak
};


class player
{
	Event ev;
	
	//texturs and sprite
		Texture playerIdleTex;
		Texture playerAttakTex;
		Texture playerJumpTex;
		Texture playerRunTex;
		Texture playerRunBackTex;
		Texture playerDeathTex;
		Sprite playerSprite;
		state playerState;
		state playerLastState;
		void initPlayer();


	//jump logic
		bool isJumping;
		float gravity;
		float upSpeed;
		float groud;

	//animation logic
		int currentFrame;
		int maxFrame;
		float widthFrame = 160.f;
		float hightFrame = 90.f;
		//time
		Clock animationClock;
		float animationSpeed;

		//hit box
		FloatRect hitBox;
		FloatRect getHitBox();

	//health sys
		int maxHealth;
		int hp;
		void takeDamage(int damage);
	//couldown attak
		Clock cooldown;
		float attakCooldown;
		bool canAttak;

public:
	player();

	void setPosition(float positionX , float positionY);
	void setGround(float g);

	void updateState();

	void updateJump();

	void updatePlayersprite();

	void updatePlayeranimation();

	void update();

	Sprite& getSrite() ;

	Vector2f getPosition();


};



#endif 