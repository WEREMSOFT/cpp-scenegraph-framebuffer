#pragma once

#include "Sprite.hpp"

namespace UR
{
	struct Animation
	{
		// configuration
		PointI frameSize;
		int frameCount;
		float frameRate;
		// state
		bool isPlaying;
		int t;
		int currentFrame;
		float frameIncrement;
	};

	class SpriteAnimated: public Sprite
	{
	public:
		uint32_t currentAnimationId = 0;
		bool isFlipped = false;
		std::vector<Animation> animations;

		SpriteAnimated(const char *file = nullptr): Sprite(file)
		{
			printf("creating AnimatedSprite\n");
		}

		~SpriteAnimated()
		{
			printf("destruyendo SpriteAnimated\n");
		}

		void DrawTransparentAnimatedClipped(double deltaTime)
		{
			if (!animations[currentAnimationId].isPlaying)
			{
				animations[currentAnimationId].isPlaying = true;
			}

			int animationStartingY = currentAnimationId * animations[currentAnimationId].frameSize.y;

			animations[currentAnimationId].frameIncrement += deltaTime * animations[currentAnimationId].frameRate;
			int lastFrame = animations[currentAnimationId].currentFrame;
			animations[currentAnimationId].currentFrame = animations[currentAnimationId].frameIncrement;
			animations[currentAnimationId].currentFrame %= animations[currentAnimationId].frameCount;
			if (animations[currentAnimationId].currentFrame < lastFrame)
			{
				animations[currentAnimationId].isPlaying = false;
			}

			if (isFlipped)
			{
				PointI adjustedPosition = {position.x - center.x, position.y + center.y};

				int clippedWidth = fmin(position.x + size.y, animations[currentAnimationId].frameSize.x);

				int clippedHeight = fmin(animations[currentAnimationId].frameSize.y,
										 fmax(0, animations[currentAnimationId].frameSize.y - (animations[currentAnimationId].frameSize.y - RendererCore::screenSize.y)));

				int clippedX = 0;
				int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i +
												animations[currentAnimationId].currentFrame * animations[currentAnimationId].frameSize.x];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
					}
				}
				return;
			}

			PointI adjustedPosition = {position.x + center.x, position.y + center.y};

			int clippedWidth = fmin(animations[currentAnimationId].frameSize.x,
									fmax(0, animations[currentAnimationId].frameSize.x - (animations[currentAnimationId].frameSize.x + adjustedPosition.x -
																	RendererCore::screenSize.y)));

			int clippedHeight = fmin(animations[currentAnimationId].frameSize.y,
									 fmax(0, animations[currentAnimationId].frameSize.y - (animations[currentAnimationId].frameSize.y + adjustedPosition.y - RendererCore::screenSize.y)));

			int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = imageData[(animationStartingY + j) * size.x + i +
											animations[currentAnimationId].currentFrame * animations[currentAnimationId].frameSize.x];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
		}

	}; // END class
}