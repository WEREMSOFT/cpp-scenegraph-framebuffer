#pragma once

#include "Sprite.hpp"

namespace UR
{
	struct Animation
	{
		// configuration
		int frameWidth;
		int frameHeight;
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
		bool isFlipped = false;
		std::vector<Animation> animations;

		SpriteAnimated(const char *file): Sprite(file)
		{
		}

		void DrawTransparentAnimatedClipped(double deltaTime, int animationId = 0)
		{
			if (!animations[animationId].isPlaying)
			{
				animations[animationId].isPlaying = true;
			}

			int animationStartingY = animationId * animations[animationId].frameHeight;

			animations[animationId].frameIncrement += deltaTime * animations[animationId].frameRate;
			int lastFrame = animations[animationId].currentFrame;
			animations[animationId].currentFrame = animations[animationId].frameIncrement;
			animations[animationId].currentFrame %= animations[animationId].frameCount;
			if (animations[animationId].currentFrame < lastFrame)
			{
				animations[animationId].isPlaying = false;
			}

			if (isFlipped)
			{
				PointI adjustedPosition = {position.x - center.x, position.y + center.y};

				int clippedWidth = fmin(position.x + size.y, animations[animationId].frameWidth);

				int clippedHeight = fmin(animations[animationId].frameHeight,
										 fmax(0, animations[animationId].frameHeight - (animations[animationId].frameHeight - RendererCore::screenSize.y)));

				int clippedX = 0;
				int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i +
												animations[animationId].currentFrame * animations[animationId].frameWidth];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
					}
				}
				return;
			}

			PointI adjustedPosition = {position.x + center.x, position.y + center.y};

			int clippedWidth = fmin(animations[animationId].frameWidth,
									fmax(0, animations[animationId].frameWidth - (animations[animationId].frameWidth + adjustedPosition.x -
																	RendererCore::screenSize.y)));

			int clippedHeight = fmin(animations[animationId].frameHeight,
									 fmax(0, animations[animationId].frameHeight - (animations[animationId].frameHeight + adjustedPosition.y - RendererCore::screenSize.y)));

			int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = imageData[(animationStartingY + j) * size.x + i +
											animations[animationId].currentFrame * animations[animationId].frameWidth];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
		}

	}; // END class
}