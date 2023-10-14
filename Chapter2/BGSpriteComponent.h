#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class BGSpriteComponent : public SpriteComponent {
	struct BGTexture {
		SDL_Texture* texture;
		Vector2 offset;
	};
	std::vector<BGTexture> bgTextures;
	Vector2 screenSize;
	float scrollSpeed;
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;
	void setBGTextures(const std::vector<SDL_Texture*>& textures);
	void setScreenSize(const Vector2& size) { screenSize = size; }
	void setScrollSpeed(float speed) { scrollSpeed = speed; }
	float GetScrollSpeed() const { return scrollSpeed; }
};

