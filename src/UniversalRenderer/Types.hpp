#pragma once
#include <SDL2/SDL.h>

namespace UR
{

#ifndef UR_MALLOC
#define UR_MALLOC malloc
#endif

#ifndef UR_REALLOC
#define UR_REALLOC realloc
#endif

#ifndef UR_FREE
#define UR_FREE free
#endif

	namespace RendererCore
	{
		SDL_Renderer *renderer;
		SDL_Window *window;
	};

	struct PointI
	{
		int x, y;
	};

	struct RectI
	{
		PointI position;
		PointI size;
	};

	struct Color
	{
		unsigned char r, g, b;
	};
}