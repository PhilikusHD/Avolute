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

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(m_Renderer, filePath);

	if (texture == nullptr)
	{
		Log("Failed to load texture. Error: %s", SDL_GetError());
	}

	return texture;
}

void RenderWindow::cleanup()
{
	SDL_DestroyWindow(m_Window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(m_Renderer);
}

void RenderWindow::render(Entity& entity)
{
	SDL_Rect src;
	src.x = entity.GetCurrentFrame().x;
	src.y = entity.GetCurrentFrame().y;
	src.w = entity.GetCurrentFrame().w;
	src.h = entity.GetCurrentFrame().h;

	SDL_Rect dst;
	dst.x = entity.GetX() * 4;
	dst.y = entity.GetY() * 4;
	dst.w = entity.GetCurrentFrame().w * 4;
	dst.h = entity.GetCurrentFrame().h * 4;

	SDL_RenderCopy(m_Renderer, entity.GetTexture(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(m_Renderer);
}