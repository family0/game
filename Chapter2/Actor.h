#pragma once
#include <vector>
#include "Math.h"
#include "Game.h"
#include "Component.h"

class Actor {
public:
	enum State {
		Active,
		Paused,
		Dead,
	};
private:
	State state;
	Vector2 position;
	float scale;
	float rotation;
	std::vector<Component*> components;
	Game* game;
public:
	Actor(Game* game);
	virtual ~Actor();
};

