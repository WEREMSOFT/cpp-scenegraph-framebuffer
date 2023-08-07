#include "UniversalRenderer/Renderer.hpp"
#include "Game/GameObject.hpp"
#include "Game/GameObjectAnimated.hpp"
#include <string>

using namespace UR;


class RunningMan: public game::GameObjectAnimated
{
	public:
		RunningMan(std::string fileName): GameObjectAnimated(fileName.c_str())
		{
			velocity.x = 100.;
			velocity.y = 100.;
		}

		void Update(double deltaTime)
		{
			GameObjectAnimated::Update(deltaTime);
			if(UR::keys[SDL_SCANCODE_LEFT])
			{
				position.x -= velocity.x * deltaTime;
			}

			if(UR::keys[SDL_SCANCODE_RIGHT])
			{
				position.x += velocity.x * deltaTime;
			}
			if(UR::keys[SDL_SCANCODE_UP])
			{
				position.y -= velocity.y * deltaTime;
			}

			if(UR::keys[SDL_SCANCODE_DOWN])
			{
				position.y += velocity.y * deltaTime;
			}
		}
};

class App
{
	Renderer ur;
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

		RunningMan goa(std::string("assets/running-man2.bmp").c_str());
		goa.sprite.animations.reserve(3);
		goa.sprite.animations.emplace_back(Animation{.frameSize = {51, 66}, .frameCount = 6, .frameRate = 12});
		goa.sprite.animations.emplace_back(Animation{.frameSize = {51, 66}, .frameCount = 8, .frameRate = 12});
		goa.sprite.animations.emplace_back(Animation{.frameSize = {51, 66}, .frameCount = 8, .frameRate = 3});

		while (UR_PROCESS_INPUT())
		{
			ur.StartFrame();

			ur.DrawDemo(ur.delta);

			if(UR::keysJustPressed[SDL_SCANCODE_SPACE])
			{
				goa.currentAnimation++;
				goa.currentAnimation %= 3;
			}

			goa.Update(ur.delta);
			goa.Draw(ur.delta);

			ur.EndFrame();
		}
	}
};