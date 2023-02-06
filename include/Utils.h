#include <SDL.h>
#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#define Log(...) printf(__VA_ARGS__); printf("\n");
#else
#define Log(...) ;
#endif

namespace Utils
{
	inline float hireTimeInSeconds()
	{
		float t = (float)SDL_GetTicks();
		t *= 0.001f;

		return t;
	}
}