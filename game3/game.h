#ifndef GAME_H
#define GAME_H

#include"player.h"
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


public:
	game();
	bool isRunnig();
	void getEvet();


	void update();
	void render();

};




#endif // !GAME_H