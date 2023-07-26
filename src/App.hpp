#include "core/GenericRenderer.hpp"

class App
{
	GenericRenderer ur;
	Uint32 oldTime = SDL_GetTicks();
	Uint32 newTime;
	double delta;
	bool isRunning = true;

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

			if (keysJustPressed[SDL_SCANCODE_SPACE])
				urDrawCircleFill((URPointI){100, 100}, 100, (URColor){255, 0, 0});
			else
				urDrawCircleFill((URPointI){100, 100}, 100, (URColor){0, 255, 0});

			if (urIsMouseButtonJustPressed(SDL_BUTTON_LEFT))
				urDrawCircleFill((URPointI){150, 100}, 100, (URColor){255, 0, 0});
			else
				urDrawCircleFill((URPointI){150, 100}, 100, (URColor){0, 255, 0});

			// s = urSpriteDrawTransparentAnimatedClipped(s, delta);

			urPrintString((URPointI){100, 100}, "hello world!!", (URColor){255, 255, 0});

			urPrintFPS(delta);

			ur.EndFrame();

			memset(keysJustPressed, 0, sizeof(bool) * 256);
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
					keysJustPressed[event.key.keysym.scancode] = true;
					keys[event.key.keysym.scancode] = true;
					break;
				case SDL_KEYUP:
					keys[event.key.keysym.scancode] = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouseButtons[event.button.button] = true;
					break;
				case SDL_MOUSEBUTTONUP:
					mouseButtons[event.button.button] = false;
					break;
				}
			}
			oldTime = newTime;
		}
	}
};