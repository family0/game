#pragma once
#include <SDL/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

class Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 ticksCount;
	bool isRunning;
	bool updatingActors;
	std::vector<class Actor*> actors;
	std::vector<class Actor*> pendingActors;
	std::vector<class SpriteComponent*> sprites;
	std::unordered_map<std::string, SDL_Texture*> textures;
	class Ship* ship;
public:
	Game();
	virtual ~Game() = default;
	bool initialize();
	void runLoop();
	void shutdown();

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	SDL_Texture* getTexture(const std::string& fileName);
private:
	void processInput();
	void updateGame();
	void generateOutput();
	void loadData();
	void unloadData();
};
