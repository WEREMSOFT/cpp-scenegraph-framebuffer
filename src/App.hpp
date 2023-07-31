#include "UniversalRenderer/Renderer.hpp"
#include "Game/GameObject.hpp"
#include <string>

using namespace UR;
class App
{
	Uint32 oldTime = SDL_GetTicks();
	Uint32 newTime;
	double delta;
	bool isRunning = true;
	Renderer ur;
	game::GameObject go; 
public:
	App()
	{
		printf("creating app\n");
		game::GameObject child;
		go.AddChild(&child);

		printf("Vector Size %d\n", go.children.size());
		printf("Child name %s\n", go.children[0]->name.c_str());
		printf("Child id %d\n", go.children[0]->id);

		go.Update(0);
	}

	~App()
	{
		printf("destroying app\n");
	}

	void Run()
	{

		SpriteAnimated s = SpriteAnimated(std::string("assets/running-man2.bmp").c_str());

		s.animations.reserve(3);
		s.animations.emplace_back(Animation{.frameWidth = 51, .frameHeight = 66, .frameCount = 6, .frameRate = 12});
		s.animations.emplace_back(Animation{.frameWidth = 51, .frameHeight = 66, .frameCount = 8, .frameRate = 12});
		s.animations.emplace_back(Animation{.frameWidth = 51, .frameHeight = 66, .frameCount = 8, .frameRate = 3});

		while (isRunning)
		{
			newTime = SDL_GetTicks();
			delta = (double)(newTime - oldTime) / 1000.;
			ur.StartFrame();

			ur.DrawDemo(delta);

			s.DrawTransparentAnimatedClipped(delta, 0);

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