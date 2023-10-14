#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
:Component(owner)
,texture(nullptr)
,drawOrder(drawOrder)
,texWidth(0)
,texHeight(0)
{
	owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent() {
	owner->getGame()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer* renderer) {
	if (texture) {
		SDL_Rect r;
		r.w = static_cast<int>(texWidth * owner->getScale());
		r.h = static_cast<int>(texHeight * owner->getScale());
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2);
		SDL_RenderCopyEx(renderer, texture, nullptr, &r, -Math::ToDegrees(owner->getRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::setTexture(SDL_Texture* texture) {
	this->texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
}
