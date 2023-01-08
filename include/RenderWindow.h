#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* loadTexture(const char* filePath);
	void cleanup();
	void clear();
	void render(Entity& entity);
	void display();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};