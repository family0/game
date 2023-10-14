#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, currFrame(0.0f)
	, animFPS(24.0f) 
{}

void AnimSpriteComponent::update(float deltaTime) {
	SpriteComponent::update(deltaTime);
	if (animTextures.size() > 0) {
		currFrame += animFPS * deltaTime;
		while (currFrame >= animTextures.size()) {
			currFrame -= animTextures.size();
		}
		setTexture(animTextures[static_cast<int>(currFrame)]);
	}
}

void AnimSpriteComponent::setAnimTextures(const std::vector<SDL_Texture*>& textures) {
	animTextures = textures;
	if (animTextures.size() > 0) {
		// Set the active texture to first frame
		currFrame = 0.0f;
		setTexture(animTextures[0]);
	}
}
