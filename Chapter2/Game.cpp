#include "Game.h"
#include <SDL/SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

using namespace std;

Game::Game()
	: window(nullptr)
	, renderer(nullptr)
	, isRunning(true)
	, updatingActors(false)
{}

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
	loadData();
	ticksCount = SDL_GetTicks();
	return true;
}

void Game::runLoop() {
	while (isRunning) {
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::shutdown() {
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::addActor(Actor* actor) {
	if (updatingActors) {
		pendingActors.emplace_back(actor);
	} else {
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor) {
	auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
	}
	iter = std::find(actors.begin(), actors.end(), actor);
	if (iter != actors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, actors.end() - 1);
		actors.pop_back();
	}
}

void Game::addSprite(SpriteComponent* sprite) {
	int order = sprite->getDrawOrder();
	auto iter = sprites.begin();
	for (;
		iter != sprites.end();
		++iter) {
		if (order < (*iter)->getDrawOrder()) {
			break;
		}
	}
	sprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent* sprite) {
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	sprites.erase(iter);
}

SDL_Texture* Game::getTexture(const std::string& fileName) {
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = textures.find(fileName);
	if (iter != textures.end()) {
		tex = iter->second;
	} else {
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		textures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE])
		isRunning = false;
	ship->processKeyboard(state);
}

void Game::updateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)) {}
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
	ticksCount = SDL_GetTicks();

	updatingActors = true;
	for (auto actor : actors) {
		actor->update(deltaTime);
	}
	updatingActors = false;

	for (auto actor : pendingActors) {
		actors.emplace_back(actor);
	}
	pendingActors.clear();

	vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors) {
		delete actor;
	}
}

void Game::generateOutput() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (auto sprite : sprites) {
		sprite->draw(renderer);
	}
	SDL_RenderPresent(renderer);
}

void Game::loadData() {
	ship = new Ship(this);
	ship->setPosition(Vector2(100.0f, 384.0f));
	ship->setScale(1.5f);
	Actor* temp = new Actor(this);
	temp->setPosition(Vector2(512.0f, 384.0f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->setScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		getTexture("Assets/Farback01.png"),
		getTexture("Assets/Farback02.png")
	};
	bg->setBGTextures(bgtexs);
	bg->setScrollSpeed(-100.0f);
	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->setScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		getTexture("Assets/Stars.png"),
		getTexture("Assets/Stars.png")
	};
	bg->setBGTextures(bgtexs);
	bg->setScrollSpeed(-200.0f);
}

void Game::unloadData() {
	while (!actors.empty()) {
		delete actors.back();
	}

	// Destroy textures
	for (auto i : textures) {
		SDL_DestroyTexture(i.second);
	}
	textures.clear();
}
