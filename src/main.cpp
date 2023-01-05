#include <iostream>
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Log.h"

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

// Window
SDL_Window* gWindow = nullptr;
// Surface
SDL_Surface* gScreenSurface = nullptr;
// images that correspond to keypress
SDL_Surface* gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
// displayed image
SDL_Surface* gCurrentSurface = nullptr;

bool onInit()
{
	bool success = true;

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create Window
		gWindow = SDL_CreateWindow("Avolute", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			Log("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

// Loads individual image
SDL_Surface* loadSurface(std::string path)
{
	// Final, optimized image
	SDL_Surface* optimizedSurface = nullptr;

	// Load image at specific path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		Log("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		// Convert Surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == nullptr)
		{
			Log("Unable to optimize image % s!SDL Error : % s\n", path.c_str(), SDL_GetError())
		}

		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

bool loadMedia()
{
	bool success = true;
	
	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("res/press.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
	{
		Log("Failed to load default image!");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("res/up.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == nullptr)
	{
		Log("Failed to load default image!");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("res/down.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == nullptr)
	{
		Log("Failed to load default image!");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("res/left.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == nullptr)
	{
		Log("Failed to load default image!");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("res/right.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == nullptr)
	{
		Log("Failed to load default image!");
		success = false;
	}

	return success;
}

void cleanup()
{
	// Dealloc the Surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = nullptr;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// Quit the Subsystem
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	bool quit = false;
	// Hacky way to get the window to stay up
	SDL_Event e;

	// Start SDL and create window
	if (!onInit())
	{
		Log("Failed to initialize");
	}
	else
	{
		// Load media
		if (!loadMedia())
		{
			Log("Failed to load media");
		}
		else
		{	
			gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
							break;

						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;

						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;

						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;

						default:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				// Apply image
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = WINDOW_WIDTH;
				stretchRect.h = WINDOW_HEIGHT;
				SDL_BlitScaled(gCurrentSurface, nullptr, gScreenSurface, &stretchRect);

				// Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	
	cleanup();

	return 0;
}