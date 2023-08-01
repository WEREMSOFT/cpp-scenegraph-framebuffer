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


	struct PointI
	{
		int x, y;
	};
	
	namespace RendererCore
	{
		SDL_Renderer *renderer;
		SDL_Window *window;
		PointI screenSize;
	};

	struct PointF
	{
		float x, y;
	};

	struct PointD
	{
		double x, y;
	};

	struct RectI
	{
		PointI position;
		PointI size;
	};

	struct ScreenInfo
	{
		PointI size;
	};

	struct Color
	{
		unsigned char r, g, b;
	};
}