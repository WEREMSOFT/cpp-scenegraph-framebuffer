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

		GameObjectAnimated(const char *bmpFile = nullptr) : GameObjectDrawable(bmpFile)
		{
			UR::setBit(tags, GameObjectType::ANIMATED);
		}

		void AddAnimation(UR::Animation animation)
		{
			sprite.animations.emplace_back(animation);
		}

		void Update(float deltaTime)
		{
			GameObjectDrawable::Update(deltaTime);
			sprite.CalculateCurrentFrame(deltaTime);
			sprite.currentAnimationId = currentAnimation;
		}

		void Draw()
		{
			sprite.DrawTransparentAnimatedClipped();

			for (auto child : children)
			{
				if(UR::isBitSet(child->tags, GameObjectType::DRAWABLE))
				{
					((GameObjectDrawable*)child)->Draw();
				}
			}
		}
	};
} // END Game namespace