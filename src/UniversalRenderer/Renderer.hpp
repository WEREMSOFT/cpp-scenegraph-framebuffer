#pragma once
#include <SDL2/SDL.h>
#include <assert.h>
#include <string>
#include <stdbool.h>
#include <stdint.h>
#include <arpa/inet.h>

#include "Types.hpp"
#include "Data.hpp"
#include "Sprite.hpp"
#include "SpriteAnimated.hpp"
#include "ImplementationSDL2.hpp"
#include "Config.hpp"

namespace UR
{
	class Renderer
	{
	public:
		Renderer()
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

		~Renderer()
		{
			printf("destroying renderer\n");
			SDL_DestroyRenderer(RendererCore::renderer);
			SDL_DestroyWindow(RendererCore::window);
			SDL_Quit();
		}

		void ClearScreen(Color clearColor)
		{
			for (int x = 0; x < UR_SCREEN_WIDTH; x++)
				for (int y = 0; y < UR_SCREEN_HEIGHT; y++)
				{
					PointI p = (PointI){x, y};
					UR_PUT_PIXEL(p.x, p.y, clearColor.r, clearColor.g, clearColor.b);
				}
		}

		void DrawCircle(PointI center, double radious, Color color)
		{
			for (int i = center.x - radious; i <= center.x + radious; i++)
			{
				for (int j = center.y - radious; j <= center.y + radious; j++)
				{
					PointI p = (PointI){i, j};
					if (floor(sqrt(pow(center.x - i, 2) + pow(center.y - j, 2))) == radious)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawCircleFill(PointI center, double radious, Color color)
		{

			for (int i = center.x - radious; i <= center.x + radious; i++)
			{
				for (int j = center.y - radious; j <= center.y + radious; j++)
				{
					PointI p = (PointI){i, j};
					if (floor(sqrt(pow(center.x - i, 2) + pow(center.y - j, 2))) <= radious)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawSquare(PointI topLeftCorner, PointI size, Color color)
		{
			for (int i = fmax(topLeftCorner.x, 0); i <= topLeftCorner.x + size.x; i++)
			{
				for (int j = fmax(topLeftCorner.y, 0); j <= topLeftCorner.y + size.y; j++)
				{
					PointI p = (PointI){i, j};
					if (j == topLeftCorner.y || j == topLeftCorner.y + size.y || i == topLeftCorner.x || i == topLeftCorner.x + size.x)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawSquareFill(PointI topLeftCorner, PointI size, Color color)
		{
			for (int i = topLeftCorner.x; i <= topLeftCorner.x + size.x; i++)
			{
				for (int j = topLeftCorner.y; j <= topLeftCorner.y + size.y; j++)
				{
					PointI p = (PointI){i, j};
					if (j >= topLeftCorner.y || j <= topLeftCorner.y + size.y || i >= topLeftCorner.x || i <= topLeftCorner.x + size.x)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawLine(PointI pointA, PointI pointB, Color color)
		{
			int dx = abs(pointB.x - pointA.x), sx = pointA.x < pointB.x ? 1 : -1;
			int dy = abs(pointB.y - pointA.y), sy = pointA.y < pointB.y ? 1 : -1;
			int err = (dx > dy ? dx : -dy) / 2, e2;

			for (;;)
			{
				UR_PUT_PIXEL(pointA.x, pointA.y, color.r, color.g, color.b);

				if (pointA.x == pointB.x && pointA.y == pointB.y)
					break;
				e2 = err;

				if (e2 > -dx)
				{
					err -= dy;
					pointA.x += sx;
				}

				if (e2 < dy)
				{
					err += dx;
					pointA.y += sy;
				}
			}
		}

		bool IsMouseButtonJustPressed(int mouseButton)
		{
			int currentMouseState = UR_GET_BUTTON_STATE(mouseButton);

			if (mouseButtons[mouseButton] && currentMouseState)
				return false;

			mouseButtons[mouseButton] = currentMouseState;

			return currentMouseState;
		}

		void PrintString(PointI topLeftCorner, const char *string, Color color)
		{
			size_t stringLen = strlen(string);

			for (size_t i = 0; i < stringLen; i++)
			{
				if (string[i] == '.')
				{
					int charOffset = 'z' - 'a' + 12;
					DrawCharacter((PointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, charOffset, color);
					continue;
				}

				if (string[i] == '%')
				{
					int charOffset = 'z' - 'a' + 11;
					DrawCharacter((PointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, charOffset, color);
					continue;
				}

				if (string[i] >= '0' && string[i] <= '9')
				{
					DrawCharacter((PointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, string[i] - '0', color);
					continue;
				}

				if (string[i] >= 'a' && string[i] <= 'z')
				{
					int charOffset = string[i] - 'a' + 10;
					DrawCharacter((PointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, charOffset, color);
					continue;
				}
			}
		}

		void DrawCharacter(PointI topLeftCorner, unsigned int letter, Color color)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j <= 8; j++)
				{
					if (Fonts[letter][i] & (0b1000000 >> j))
						UR_PUT_PIXEL(topLeftCorner.x + j, topLeftCorner.y + i, color.r, color.g, color.b);
				}
			}
		}

		void PrintFPS(double deltaTime)
		{

#define FPS_HISTORY 10
			static double fpsHistory[FPS_HISTORY] = {0};
			static int counter = 1;
			counter++;
			counter %= FPS_HISTORY;
			fpsHistory[counter] = (1 / deltaTime);

			int sum = 0;
			for (int i = 0; i < FPS_HISTORY; i++)
			{
				sum += fpsHistory[i];
			}

			float avg = sum / FPS_HISTORY;

			{
				char text[1000] = {0};
				snprintf(text, 1000, "fps: %d", (int)floor(avg));
				PrintString((PointI){230, 220}, text, (Color){0, 0xff, 0xff});
			}

			{
				char text[1000] = {0};
				snprintf(text, 1000, "ftime:%.4f", deltaTime);
				PrintString((PointI){230, 230}, text, (Color){0, 0xff, 0xff});
			}
		}

		void DrawDemo(double deltaTime)
		{
			for (int i = 0; i < 800; ++i)
				putPixel(i, i, 0, 255, 0);

			if (keysJustPressed[SDL_SCANCODE_SPACE])
				DrawCircleFill((PointI){100, 100}, 100, (Color){255, 0, 0});
			else
				DrawCircleFill((PointI){100, 100}, 100, (Color){0, 255, 0});

			if (IsMouseButtonJustPressed(SDL_BUTTON_LEFT))
				DrawCircle((PointI){150, 100}, 50, UR_RED);
			else
				DrawCircleFill((PointI){150, 100}, 50, UR_PURPLE);

			DrawSquare({100, 100}, {30, 30}, UR_RED);
			DrawSquareFill({130, 130}, {30, 30}, UR_RED);

			DrawLine({320, 0}, {0, 240}, UR_BLUE);
			PrintString((PointI){100, 100}, std::string("hello world!!").c_str(), (Color){255, 255, 0});

			PrintFPS(deltaTime);
		}
	}; // END RENDERER CLASS
}
