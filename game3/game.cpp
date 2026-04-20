#include "game.h"
using namespace sf;

void game::initWin()
{
	this->win.create(VideoMode(1400, 700), "Game", Style::Close | Style::Resize);
	this->win.setFramerateLimit(60);
}

void game::initBackground()
{
	//load the textures
	this->backgroundTex1.loadFromFile("assets/bg1.png");
	this->backgroundTex2.loadFromFile("assets/bg2.png");

	//set the textures to the sprites
	this->background1.setTexture(this->backgroundTex1);
	this->background2.setTexture(this->backgroundTex2);

	Vector2u winSize = this->win.getSize();

	//dividing the size of the size winddow by the image size to get the right scale
		//back1
		float Back1scaleX = (float)winSize.x / this->backgroundTex1.getSize().x;
		float Back1scaleY = (float)(winSize.y / this->backgroundTex1.getSize().y);
		//back2
		float Back2scaleX =  (float) winSize.x / this->backgroundTex2.getSize().x;
		float Back2scaleY =  (float) winSize.y / this->backgroundTex2.getSize().y;

	//apply the scale to the sprite
		this->background1.setScale(Back1scaleX, Back1scaleY);
		this->background2.setScale(Back2scaleX, Back2scaleY);

}



void game::initEnemies()
{
	enemie e1;
	e1.setposition((float)this->win.getSize().x - 600, (float)this->win.getSize().y - 190);
	e1.getSprite().scale(1.5f, 1.5f);
	this->enemies.push_back(e1);

	enemie e2;
	e2.setposition((float)this->win.getSize().x - 400, (float)this->win.getSize().y - 190);
	e2.getSprite().scale(1.5f, 1.5f);
	this->enemies.push_back(e2);

	enemie e3;
	e3.setposition((float)this->win.getSize().x - 200, (float)this->win.getSize().y - 190);
	e3.getSprite().scale(1.5f, 1.5f);
	this->enemies.push_back(e3);
}

game::game()
{
	this->initWin();
	this->initBackground();
	//player
	this->P.setPosition(100.f, (float)this->win.getSize().y - 280);
	this->P.setGround((float)this->win.getSize().y - 280);
	this->P.getSrite().scale(2.f, 2.f);
	this->initEnemies();
}

void game::checkPattack()
{
	FloatRect playerHitBox = this->P.getHitBox();
	for (int i = 0; i < this->enemies.size(); i++)
	{
		if (playerHitBox.intersects(this->enemies[i].getSprite().getGlobalBounds()))
		{
			if (this->P.isAttakFrame() && !this->P.getAttakeDealt())
			{
				this->enemies[i].takeDamage(10);
				this->P.setAttakeDealt(true);
				std::cout << "the player attake \n";
				std::cout << "the enemy " <<i <<" heath is " << this->enemies[i].getHeah() << std::endl;
			}
		}
	}
}

void game::checkEAttack()
{
	for (int i = 0; i < this->enemies.size(); i++)
	{
		FloatRect enemieHitBox = this->enemies[i].getHitBox();

		if (enemieHitBox.intersects(this->P.getSrite().getGlobalBounds()) )  
		{
			if (this->enemies[i].isAttaking() && !this->enemies[i].getAttackDealt() && this->enemies[i].getAttackFarme() )
			{
				this->enemies[i].setAttackDealt(true);
				this->P.takeDamage(10);
				std::cout << "the player got damaged";
			}
			
		}
	}
	

}



bool game::isRunnig()
{
	return this->win.isOpen();
}

void game::getEvet()
{
	while (this->win.pollEvent(this->ev)) {
		if (this->ev.type == Event::KeyPressed && this->ev.key.code == Keyboard::Escape)
		{
			this->win.close();
		}
	}
}

void game::update()
{
	this->getEvet();
	this->checkPattack();
	this->checkEAttack();
	this->P.update();
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].update(this->P.getPosition().x);
		if (this->enemies[i].death())
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void game::render()
{
	this->win.clear();
	this->win.draw(this->background1);
	this->win.draw(this->background2);
	
  //   Draw player's hit box for debugging.
	 //If the hit box is empty (width/height == 0) draw the sprite bounds instead.
	//FloatRect hb = this->P.getHitBox();
	//if (hb.width > 0.f && hb.height > 0.f)
	//{
	//	RectangleShape box;
	//	box.setPosition(hb.left, hb.top);
	//	box.setSize(Vector2f(hb.width, hb.height));
	//	box.setFillColor(Color::Transparent);
	//	box.setOutlineColor(Color::Red);
	//	box.setOutlineThickness(1.f);
	//	this->win.draw(box);
	//}
	//else
	//{
	//	FloatRect gb = this->P.getSrite().getGlobalBounds();
	//	RectangleShape box;
	//	box.setPosition(gb.left, gb.top);
	//	box.setSize(Vector2f(gb.width, gb.height));
	//	box.setFillColor(Color::Transparent);
	//	box.setOutlineColor(Color::Green);
	//	box.setOutlineThickness(1.f);
	//	this->win.draw(box);
	//}
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->win.draw(this->enemies[i].getSprite());
	}
	this->win.draw(this->P.getSrite());
	
	this->win.display();
}


