#pragma once
#include "Actor.h"

class Ship : public Actor {
	float rightSpeed;
	float downSpeed;
public:
	Ship(class Game* game);
	virtual ~Ship() = default;
	void updateActor(float deltaTime) override;
	void processKeyboard(const uint8_t* state);
	float getRightSpeed() const { return rightSpeed; }
	float getDownSpeed() const { return downSpeed; }
};

