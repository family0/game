#include "Actor.h"
#include <algorithm>

using namespace std;

Actor::Actor(Game* game)
	: state(Active)
	, position(Vector2::Zero)
	, scale(1.0f)
	, rotation(0.0f)
	, game(game)
{
	game->addActor(this);
}

Actor::~Actor() {
	game->removeActor(this);
	while (!components.empty()) {
		delete components.back();
	}
}

void Actor::update(float deltaTime) {
	if (state == Active) {
		updateComponents(deltaTime);
		updateActor(deltaTime);
	}
}

void Actor::updateComponents(float deltaTime) {
	for (auto comp : components) {
		comp->update(deltaTime);
	}
}

void Actor::updateActor(float deltaTime) {}

void Actor::addComponent(Component* component) {
	int order = component->getUpdateOrder();
	auto iter = components.begin();
	for (; iter != components.end(); iter++) {
		if (order < (*iter)->getUpdateOrder())
			break;
	}
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component) {
	auto iter = find(components.begin(), components.end(), component);
	if (iter != components.end())
		components.erase(iter);
}
