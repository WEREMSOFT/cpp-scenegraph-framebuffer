#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Types.hpp"
#include "Data.hpp"

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

#define UR_GET_BUTTON_STATE getButtonState

	bool processInput()
	{
		memset(UR::keysJustPressed, 0, sizeof(bool) * 256);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// Handle SDL events
			switch (event.type)
			{
			case SDL_QUIT:
				return false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					return false;
					break;
				}
				UR::keysJustPressed[event.key.keysym.scancode] = true;
				UR::keys[event.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				UR::keys[event.key.keysym.scancode] = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				UR::mouseButtons[event.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				UR::mouseButtons[event.button.button] = false;
				break;
			}
		}
		return true;
	}

	#define UR_PROCESS_INPUT processInput

	#define UR_GET_ELAPSED_MILLISENCONDS SDL_GetTicks

	void clearFrame()
	{
		SDL_SetRenderDrawColor(RendererCore::renderer, 0, 0, 0, 0);
		SDL_RenderClear(RendererCore::renderer);
	}

	#define UR_CLEAR_FRAME clearFrame

	void drawFrame()
	{
		SDL_RenderPresent(RendererCore::renderer);
	}

	#define UR_DRAW_FRAME drawFrame
}