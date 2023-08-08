#pragma once

#include <vector>
#include <string>
#include "GameObject.hpp"

namespace game
{
	class GameObjectAnimated : public GameObjectDrawable
	{
	public:
		int currentAnimation = 0;

		GameObjectAnimated(const char* bmpFile = nullptr) : GameObjectDrawable(bmpFile)
		{
			UR::setBit(tags, GameObjectType::ANIMATED);
		}

		void Draw(double deltaTime)
		{
			sprite.currentAnimationId = currentAnimation;
			sprite.DrawTransparentAnimatedClipped(deltaTime);
		}
	};
} // END Game namespace