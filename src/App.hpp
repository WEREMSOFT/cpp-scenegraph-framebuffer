#include "core/UniversalRenderer.hpp"
#include <string>

using namespace weremsoft;
class App
{
	Uint32 oldTime = SDL_GetTicks();
	Uint32 newTime;
	double delta;
	bool isRunning = true;
	UniversalRenderer ur;

public:
	App()
	{
		printf("creating app\n");
	}

	~App()
	{
		printf("destroying app\n");
	}

	void Run()
	{
		while (isRunning)
		{
			newTime = SDL_GetTicks();
			delta = (double)(newTime - oldTime) / 1000.;
			ur.StartFrame();

			for (int i = 0; i < 800; ++i)
				putPixel(i, i, 0, 255, 0);

			if (ur.keysJustPressed[SDL_SCANCODE_SPACE])
				ur.DrawCircleFill((PointI){100, 100}, 100, (Color){255, 0, 0});
			else
				ur.DrawCircleFill((PointI){100, 100}, 100, (Color){0, 255, 0});

			if (ur.IsMouseButtonJustPressed(SDL_BUTTON_LEFT))
				ur.DrawCircleFill((PointI){150, 100}, 100, (Color){255, 0, 0});
			else
				ur.DrawCircleFill((PointI){150, 100}, 100, (Color){0, 255, 0});

			// s = urSpriteDrawTransparentAnimatedClipped(s, delta);

			ur.PrintString((PointI){100, 100}, std::string("hello world!!").c_str(), (Color){255, 255, 0});

			ur.PrintFPS(delta);

			ur.EndFrame();

			memset(ur.keysJustPressed, 0, sizeof(bool) * 256);
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{

				// Handle SDL events
				switch (event.type)
				{
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						isRunning = false;
						break;
					}
					ur.keysJustPressed[event.key.keysym.scancode] = true;
					ur.keys[event.key.keysym.scancode] = true;
					break;
				case SDL_KEYUP:
					ur.keys[event.key.keysym.scancode] = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					ur.mouseButtons[event.button.button] = true;
					break;
				case SDL_MOUSEBUTTONUP:
					ur.mouseButtons[event.button.button] = false;
					break;
				}
			}
			oldTime = newTime;
		}
	}
};