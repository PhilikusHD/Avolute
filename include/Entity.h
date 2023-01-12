#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "AMath.h"

class Entity
{
public:
	// Leave scale empty for default values
	Entity(Vector2f pos, SDL_Texture* tex, float scaleX, float scaleY);
	Vector2f& getPos()
	{
		return m_pos;
	}

	SDL_Texture* GetTexture();
	SDL_Rect GetCurrentFrame();
private:

	Vector2f m_pos;
	SDL_Rect currentFrame;
	SDL_Texture* m_tex;
};