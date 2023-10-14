#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game)
:Actor(game)
, rightSpeed(0.0f)
, downSpeed(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->getTexture("Assets/Ship01.png"),
		game->getTexture("Assets/Ship02.png"),
		game->getTexture("Assets/Ship03.png"),
		game->getTexture("Assets/Ship04.png"),
	};
	asc->setAnimTextures(anims);
}

void Ship::updateActor(float deltaTime) {
	Actor::updateActor(deltaTime);
	Vector2 pos = getPosition();
	pos.x += rightSpeed * deltaTime;
	pos.y += downSpeed * deltaTime;
	if (pos.x < 25.0f) {
		pos.x = 25.0f;
	} else if (pos.x > 500.0f) {
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f) {
		pos.y = 25.0f;
	} else if (pos.y > 743.0f) {
		pos.y = 743.0f;
	}
	setPosition(pos);
}

void Ship::processKeyboard(const uint8_t* state) {
	rightSpeed = 0.0f;
	downSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D]) {
		rightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		rightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S]) {
		downSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W]) {
		downSpeed -= 300.0f;
	}
}
