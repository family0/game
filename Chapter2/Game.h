#pragma once
#include <SDL/SDL.h>

class Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 ticksCount;
	bool isRunning;
public:
	Game() = default;
	virtual ~Game() = default;
	bool initialize();
	void runLoop();
	void shutdown();
};
