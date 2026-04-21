#ifndef GAME_H
#define GAME_H


#include<iostream>
#include <vector>
#include"player.h"
#include"enemie.h"
#include"boss.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
using namespace sf;

class game
{
private:
	//game win
		RenderWindow win;
		void initWin();
		Event ev;

	//game background
		//backgrout textures
		Texture backgroundTex1;
		Texture backgroundTex2;

		//backgroud sprits
		Sprite background1;
		Sprite background2;
		void initBackground();

	//game objects 
		player P;
		boss Mbooss;
		std::vector<enemie> enemies;
		void initEnemies();
		void iniBoss();


public:
	game();
	void checkPattack();
	void checkEAttack();
	void checkBAttack();
	bool isRunnig();
	void getEvet();


	void update();
	void render();

};



#endif // !GAME_H