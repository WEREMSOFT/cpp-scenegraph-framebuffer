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

			if(UR::keysJustPressed[SDL_SCANCODE_SPACE])
			{
				currentAnimation++;
				currentAnimation %= 3;
			}

			if (parent != NULL) 
			{
				if (UR::isBitSet(parent->tags, game::GameObjectType::DRAWABLE) || UR::isBitSet(parent->tags, game::GameObjectType::ANIMATED))
				sprite.isFlipped = ((GameObjectDrawable*)parent)->sprite.isFlipped;
				return;
			}
			if(UR::keys[SDL_SCANCODE_LEFT])
			{
				localPosition.x -= velocity.x * deltaTime;
				sprite.isFlipped = true;
			}

			if(UR::keys[SDL_SCANCODE_RIGHT])
			{
				localPosition.x += velocity.x * deltaTime;
				sprite.isFlipped = false;
			}
			if(UR::keys[SDL_SCANCODE_UP])
			{
				localPosition.y -= velocity.y * deltaTime;
			}

			if(UR::keys[SDL_SCANCODE_DOWN])
			{
				localPosition.y += velocity.y * deltaTime;
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

	RunningMan CreateRunningMan()
	{
		RunningMan goa(std::string("assets/running-man2.bmp").c_str());
		goa.sprite.animations.reserve(3);
		goa.AddAnimation(Animation{.frameSize = {51, 66}, .frameCount = 6, .frameRate = 12});
		goa.AddAnimation(Animation{.frameSize = {51, 66}, .frameCount = 8, .frameRate = 12});
		goa.AddAnimation(Animation{.frameSize = {51, 66}, .frameCount = 8, .frameRate = 3});

		goa.sprite.center = (PointI){.x = 25, .y = 33};
		return goa;
	}

	void Run()
	{

		auto goa = CreateRunningMan();
		auto goa2 = CreateRunningMan();

		goa2.localPosition.x += 10;
		goa2.localPosition.y += 10;

		goa.AddChild(&goa2);


		while (UR_PROCESS_INPUT())
		{
			ur.StartFrame();

			ur.DrawDemo(ur.delta);
			
			goa.Update(ur.delta);
			goa.Draw();

			ur.EndFrame();
		}
	}
};