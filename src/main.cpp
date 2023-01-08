#include <iostream>
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>	
#include <SDL_image.h>
#include "Log.h"
#include "RenderWindow.h"
#include "Entity.h"

// https://lazyfoo.net/tutorials/SDL/index.php#Optimized%20Surface%20Loading%20and%20Soft%20Stretching

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
	SDL_Texture* grassTexture = window.loadTexture("res/Textures/ground_grass_1.png");
	
	Entity entitees[3] = 
	{
		Entity(69, 100, grassTexture), 
		Entity(42, 100, grassTexture),
		Entity(100, 100, grassTexture)
	};


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

		window.clear();
		for (Entity& ent : entitees)
		{
			window.render(ent);
		}

		window.display();
	}

	window.cleanup();
	SDL_Quit();
	return 0;
}