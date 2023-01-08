#include "RenderWindow.h"
#include "Log.h"

RenderWindow::RenderWindow(const char* title, int width, int height)
	: m_Window(nullptr), m_Renderer(nullptr)
{
	m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (m_Window == nullptr)
	{
		Log("Failed to initialize Window: %s", SDL_GetError());
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::cleanup()
{
	SDL_DestroyWindow(m_Window);
}