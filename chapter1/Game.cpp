#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
: window(nullptr)
, renderer(nullptr)
, ticksCount(0)
, isRunning(true)
, paddleDir(0)
, paddlePos({ 10.0f, 768.0f / 2.0f })
, ballPos({ 1024.0f / 2.0f, 768.0f / 2.0f })
, ballVel({ -200.0f, 235.0f })
{}

bool Game::Initialize() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Game", 1024, 768, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Game::RunLoop() {
    while (isRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
    }
    const auto state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }
    paddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        paddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        paddleDir += 1;
    }
}

void Game::UpdateGame() {
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	ticksCount = SDL_GetTicks();
	if (paddleDir != 0) {
		paddlePos.y += paddleDir * 300.0f * deltaTime;
		if (paddlePos.y < (paddleH / 2.0f + thickness)) {
			paddlePos.y = paddleH / 2.0f + thickness;
		} else if (paddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
			paddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
	ballPos.x += ballVel.x * deltaTime;
	ballPos.y += ballVel.y * deltaTime;
	float diff = paddlePos.y - ballPos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	if (diff <= paddleH / 2.0f && ballPos.x <= 25.0f && ballPos.x >= 20.0f && ballVel.x < 0.0f) {
		ballVel.x *= -1.0f;
	}
	else if (ballPos.x <= 0.0f) {
		isRunning = false;
	}
	else if (ballPos.x >= (1024.0f - thickness) && ballVel.x > 0.0f) {
		ballVel.x *= -1.0f;
	}
	if (ballPos.y <= thickness && ballVel.y < 0.0f) {
		ballVel.y *= -1;
	}
	else if (ballPos.y >= (768 - thickness) && ballVel.y > 0.0f) {
		ballVel.y *= -1;
	}
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_FRect wall { 0, 0, 1024, thickness };
	SDL_RenderFillRect(renderer, &wall);
	wall.y = 768 - thickness;
	SDL_RenderFillRect(renderer, &wall);
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(renderer, &wall);
	SDL_FRect paddle{
		paddlePos.x,
		paddlePos.y - paddleH / 2,
		thickness,
		paddleH
	};
	SDL_RenderFillRect(renderer, &paddle);
	SDL_FRect ball{
		ballPos.x - thickness / 2,
		ballPos.y - thickness / 2,
		thickness,
		thickness
	};
	SDL_RenderFillRect(renderer, &ball);
	SDL_RenderPresent(renderer);
}
