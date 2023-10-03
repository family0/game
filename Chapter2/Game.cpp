#include "Game.h"
#include <SDL/SDL_image.h>

bool Game::initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
	if (!window) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	ticksCount = SDL_GetTicks();
	return true;
}

void Game::runLoop() {}

void Game::shutdown() {}
