#pragma once
#include "Entity.h"
#include <SDL.h>
#include <SDL_image/SDL_image.h>

class RenderWindow
{
public:
    RenderWindow(const char *title, int width, int height);
    SDL_Texture *loadTexture(const char *filePath);
    void cleanup();
    void clear();
    void render(Entity &entity);
    void display();

    SDL_Window *GetWindow()
    {
        return m_Window;
    }
    SDL_Renderer *GetRenderer()
    {
        return m_Renderer;
    }

private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
};
