#pragma once
#include <SDL.h>
#include <SDL_image.h>


class RenderWindow
{
public:
	RenderWindow(const char* title, int width, int height);
	void cleanup();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};