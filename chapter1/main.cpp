#include <iostream>
#include "Game.h"

using namespace std;

int main(int arpc, char* argv[]) {
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}