#include <iostream>
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>	
#include <SDL_image.h>
#include <vector>

#include "Utils.h"
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
	SDL_Texture* bob = window.loadTexture("res/Textures/bob.png");
	
	//Entity entitees[3] =
	//{
	//	Entity(69, 100, grassTexture), 
	//	Entity(42, 100, grassTexture),
	//	Entity(100, 100, grassTexture)
	//};

	std::vector<Entity> entities = 
	{
		Entity(Vector2f(0, 0), grassTexture),
		Entity(Vector2f(30, 0), grassTexture),
		Entity(Vector2f(30, 30), grassTexture),
		Entity(Vector2f(30, 60), grassTexture),
		Entity(Vector2f(30, 90), grassTexture)
	};

	Entity Bob(Vector2f(100, 50), bob);
	entities.emplace_back(Bob);

	bool running = true;
	SDL_Event event;

	const float deltaTime = 0.01f;
	float accumulator = 0.0f;
	float currentTime = Utils::hireTimeInSeconds();

	while (running)
	{
		float newTime = Utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		
		while (accumulator >= deltaTime)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
			}

			accumulator -= deltaTime;
		}

		const float alpha = accumulator / deltaTime;

		window.clear();

		for (Entity& ent : entities)
		{
			window.render(ent);
		}

		window.display();
	}

	window.cleanup();
	SDL_Quit();
	return 0;
}