#pragma once
#include "Component.h"
#include "SDL/SDL.h"

class SpriteComponent : public Component {
	SDL_Texture* texture;
	int drawOrder;
	int texWidth;
	int texHeight;
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	virtual ~SpriteComponent();
	virtual void draw(SDL_Renderer* renderer);
	virtual void setTexture(SDL_Texture* texture);
	int getDrawOrder() const { return drawOrder; }
	int getTexWidth() const { return texWidth; }
	int getTexHeight() const { return texHeight; }
};

