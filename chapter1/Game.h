#pragma once
#include <SDL3/SDL.h>
#include "Vector2.h"

class Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 ticksCount;
	bool isRunning;
	int paddleDir;
	Vector2 paddlePos;
	Vector2 ballPos;
	Vector2 ballVel;
public:
	Game();
	virtual ~Game() = default;
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
};

