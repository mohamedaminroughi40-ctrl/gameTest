
#include "game.h"
#include <iostream>

int main()
{
	game G;
	while (G.isRunnig()) {
		G.update();


		G.render();

	}
}

