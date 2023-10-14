#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent {
	// All textures in the animation
	std::vector<SDL_Texture*> animTextures;
	// Current frame displayed
	float currFrame;
	// Animation frame rate
	float animFPS;
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// Update animation every frame (overridden from component)
	void update(float deltaTime) override;
	// Set the textures used for animation
	void setAnimTextures(const std::vector<SDL_Texture*>& textures);
	// Set/get the animation FPS
	float getAnimFPS() const { return animFPS; }
	void setAnimFPS(float fps) { animFPS = fps; }
};

