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

		printf("Vector Size %ld\n", go.children.size());
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

		game::GameObjectAnimated goa(std::string("assets/running-man2.bmp").c_str());

		goa.sprite.animations.reserve(3);
		goa.sprite.animations.emplace_back(Animation{.frameWidth = 51, .frameHeight = 66, .frameCount = 6, .frameRate = 12});
		goa.sprite.animations.emplace_back(Animation{.frameWidth = 51, .frameHeight = 66, .frameCount = 8, .frameRate = 12});
		goa.sprite.animations.emplace_back(Animation{.frameWidth = 51, .frameHeight = 66, .frameCount = 8, .frameRate = 3});

		while (UR_PROCESS_INPUT())
		{
			newTime = SDL_GetTicks();
			delta = (double)(newTime - oldTime) / 1000.;
			ur.StartFrame();

			ur.DrawDemo(delta);

			if(UR::keysJustPressed[SDL_SCANCODE_SPACE])
			{
				goa.currentAnimation++;
				goa.currentAnimation %= 3;
			}

			goa.Update(delta);

			ur.EndFrame();
			oldTime = newTime;
		}
	}
};