#include "Entity.h"

Entity::Entity(Vector2f pos, SDL_Texture* tex, float scaleX, float scaleY)
	:m_pos(pos), m_tex(tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32 * scaleX;
	currentFrame.h = 32 * scaleY;
}

SDL_Texture* Entity::GetTexture()
{
	return m_tex;
}

SDL_Rect Entity::GetCurrentFrame()
{
	return currentFrame;
}

