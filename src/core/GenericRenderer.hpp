#pragma once
#include <SDL2/SDL.h>
#include <assert.h>

#define UR_SCREEN_WIDTH 320
#define UR_SCREEN_HEIGHT 200




namespace RendererCore
{
	SDL_Renderer* renderer;
	SDL_Window* window;
};


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

#include "universal_renderer.h"

class GenericRenderer
{
	public:
	
		GenericRenderer()
		{
			printf("creating renderer\n");
			assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "Error initializing SDL\n");

			SDL_DisplayMode displayMode;
			SDL_GetCurrentDisplayMode(0, &displayMode);

			RendererCore::window = SDL_CreateWindow(
				NULL,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				800,
				600,
				0);

			assert(RendererCore::window != NULL && "Error creating SDL window");

			RendererCore::renderer = SDL_CreateRenderer(RendererCore::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			assert(RendererCore::renderer != NULL && "Error creating renderer");
			
			SDL_RenderSetScale(RendererCore::renderer, 2., 2.);
			printf("renderer initialized\n");
		}

		void StartFrame(void)
		{
			SDL_SetRenderDrawColor(RendererCore::renderer, 0, 0, 0, 0);
    		SDL_RenderClear(RendererCore::renderer);
		}

		void EndFrame(void)
		{
			SDL_RenderPresent(RendererCore::renderer);
		}

		~GenericRenderer()
		{
			printf("destroying renderer\n");
			// SDL_DestroyRenderer(RendererCore::renderer);
			// SDL_DestroyWindow(RendererCore::window);
			SDL_Quit();
		}
};
