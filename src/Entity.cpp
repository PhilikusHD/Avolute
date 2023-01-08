#include "Entity.h"

Entity::Entity(float x, float y, SDL_Texture* tex)
	: x(x), y(y), tex(tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

float Entity::GetX()
{
	return x;
}

float Entity::GetY()
{
	return y;
}

SDL_Texture* Entity::GetTexture()
{
	return tex;
}

SDL_Rect Entity::GetCurrentFrame()
{
	return currentFrame;
}
