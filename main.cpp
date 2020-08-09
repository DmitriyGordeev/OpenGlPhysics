#include <ctime>
#include "MainGame.h"

int main(int argc, char** argv)
{
	srand(time(NULL));

	MainGame mainGame;
	mainGame.run();

	return 0;
}