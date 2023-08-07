#pragma once

#include <vector>
#include <string>
#include "GameObject.hpp"

namespace game
{
	class GameObjectAnimated : public GameObjectDrawable
	{
	public:
		UR::SpriteAnimated sprite;
		int currentAnimation = 0;

		GameObjectAnimated(const char* bmpFile = nullptr) : sprite(bmpFile)
		{
			UR::setBit(tags, GameObjectType::ANIMATED);
		}

		void Update(double deltaTime)
		{
			sprite.position.x = position.x;
			sprite.position.y = position.y;
		}

		void Draw(double deltaTime)
		{
			sprite.currentAnimationId = currentAnimation;
			sprite.DrawTransparentAnimatedClipped(deltaTime);
		}
	};
} // END Game namespace