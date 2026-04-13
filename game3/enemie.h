

#ifndef ENEMIE_H
#define ENEMIE_H

#include <math.h>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
using namespace sf;



enum stateMov
{
	Eidle,Echase
};

class enemie
{	
	private:
		stateMov state;
		Texture idleTex;
		Texture apearTex;
		Texture chaseTex;
		Texture vanishTex;
		Sprite enemieSprite;
		void initEnemie();

		//animation logic
		int currentFrame;
		int maxFrame;
		float widthFrame = 64;
		float hightFrame = 80;
			//animation timer
			Clock animationTimer;
			float animationTimeLimit;
		

	public:
		enemie();
		void setposition(float posX , float poseY);
		void animation();
		void stateHundling(float playerPosX);
		void movUp(float playerPosX);
		void spriteUp();


		void update(float playerPosX);

		Sprite getSprite();

		
};



#endif 