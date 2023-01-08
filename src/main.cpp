#include <iostream>
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>	
#include <SDL_image.h>
#include "Log.h"
#include "RenderWindow.h"

// https://lazyfoo.net/tutorials/SDL/index.php#Optimized%20Surface%20Loading%20and%20Soft%20Stretching

// Window size constants
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

enum KeyPressSurface
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_TOTAL
};

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		Log("Failed to initialize SDL2. SDL_ERROR: %s", SDL_GetError());
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		Log("Failed to initialize SDL_image. ERROR: %s", SDL_GetError());
	}

	RenderWindow window("Avolute", 1280, 720);
	
	bool running = true;
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
	}

	window.cleanup();
	SDL_Quit();
	return 0;
}