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
	void update(float deltaTime);
	void updateComponents(float deltaTime);
	virtual void updateActor(float deltaTime);
	State getState() const { return state; }
	void setState(State state) { this->state = state; }
	const Vector2& getPosition() const { return position; }
	void setPosition(const Vector2& position) { this->position = position; }
	float getScale() const { return scale; }
	void setScale(float scale) { this->scale = scale; }
	float getRotation() const { return rotation; }
	void setRotation(float rotation) { this->rotation = rotation; }
	class Game* getGame() { return game; }
	void addComponent(class Component* component);
	void removeComponent(class Component* component);
};

