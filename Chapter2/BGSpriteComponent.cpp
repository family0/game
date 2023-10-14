#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder) 
	, scrollSpeed(0.0f)
{}

void BGSpriteComponent::update(float deltaTime) {
	SpriteComponent::update(deltaTime);
	for (auto& tex : bgTextures) {
		// Update the x offset
		tex.offset.x += scrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (tex.offset.x < -screenSize.x) {
			tex.offset.x = (bgTextures.size() - 1) * screenSize.x - 1;
		}
	}
}

void BGSpriteComponent::draw(SDL_Renderer* renderer) {
	for (auto& bg : bgTextures) {
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(screenSize.x);
		r.h = static_cast<int>(screenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2 + bg.offset.x);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2 + bg.offset.y);

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.texture,
			nullptr,
			&r
		);
	}
}

void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures) {
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.texture = tex;
		// Each texture is screen width in offset
		temp.offset.x = count * screenSize.x;
		temp.offset.y = 0;
		bgTextures.emplace_back(temp);
		count++;
	}
}
