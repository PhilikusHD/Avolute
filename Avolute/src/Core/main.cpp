#include <iostream>
//#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image/SDL_image.h>
#include <vector>
#include <memory>


#include "Utils.h"
#include "RenderWindow.h"
#include "Entity.h"
#include "Avolute.h"

// https://lazyfoo.net/tutorials/SDL/index.php#Optimized%20Surface%20Loading%20and%20Soft%20Stretching

enum KeyPressSurfaces
{
	KEY_PRESS_DEFAULT,
	KEY_PRESS_UP,
	KEY_PRESS_DOWN,
	KEY_PRESS_LEFT,
	KEY_PRESS_RIGHT,
	KEY_PRESS_TOTAL
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
	SDL_Texture* grassTexture = window.loadTexture("../assets/textures/ground_grass_1.png");
	SDL_Texture* bob = window.loadTexture("../assets/textures/ground_grass_1.png");

	Entity test;

	std::vector<Entity> entities =
	{
		Entity(Vector2f(0, 0), grassTexture, 1.0f, 1.0f),
		Entity(Vector2f(30, 0), grassTexture, 1.0f, 1.0f),
		Entity(Vector2f(30, 30), grassTexture, 1.0f, 1.0f),
		Entity(Vector2f(30, 60), grassTexture, 1.0f, 1.0f),
		Entity(Vector2f(30, 90), grassTexture, 1.0f, 1.0f)
	};


	Entity Bob(Vector2f(30, 100), bob, 1.0f, 1.0f);

	bool running = true;
	SDL_Event event;

	const float deltaTime = 1.0f / 60.0f;
	const int tileSize = 32;
	float velocity = 1.0f;
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
				else if(event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_d:
						Bob.getPos().m_x += tileSize * accumulator * velocity;
						break;
					case SDLK_a:
						Bob.getPos().m_x -= tileSize * accumulator * velocity;
						break;
					case SDLK_w:
						Bob.getPos().m_y -= tileSize * accumulator * velocity;
						break;
					case SDLK_s:
						Bob.getPos().m_y += tileSize * accumulator * velocity;
						break;
					default:
						Bob.getPos().print();
						break;
					}
				}
			}

			accumulator -= deltaTime;
		}

		const float alpha = accumulator / deltaTime;

		window.clear();

		for (Entity& ent : entities)
		{
			window.render(ent);
			window.render(Bob);
		}

		window.display();
	}

	window.cleanup();
	SDL_Quit();
	return 0;
}
