#pragma once
#include <SDL2/SDL.h>
#include "Types.hpp"

namespace UR
{

	void putPixel(int x, int y, char r, char g, char b)
	{
		SDL_SetRenderDrawColor(RendererCore::renderer, r, g, b, 255);
		SDL_RenderDrawPoint(RendererCore::renderer, x, y);
	}
#define UR_PUT_PIXEL putPixel

#define UR_KEY_PRESS SDL_KEYDOWN

	int getButtonState(int mouseButton)
	{
		return 0;
	}

#define UR_GET_BUTTON_STATE

}