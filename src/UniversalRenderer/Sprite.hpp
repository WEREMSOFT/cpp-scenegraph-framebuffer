#pragma once

#include <vector>
#include "Types.hpp"
#include "Utils.hpp"
#include "ImplementationSDL2.hpp"
#include "Config.hpp"

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

	class Sprite
	{
	public:
		bool animated = false;
		bool isFlipped = false;
		std::vector<Animation> animations;
		PointI position = {0};
		PointI center = {0};
		PointI size = {0};
		Color *imageData;

		Sprite(const char *file)
		{
			int nrChannels;
			imageData = (Color *)BMPLoad(file, &size.x, &size.y);
			if (imageData == NULL)
			{
				printf("Error loading image %s\n", file);
				exit(-1);
			}
		}

		~Sprite()
		{
			UR_FREE(imageData);
		}

		void Draw()
		{
			for (int i = 0; i < size.x; i++)
			{
				for (int j = 0; j < size.y; j++)
				{
					Color color = imageData[j * size.x + i];
					UR_PUT_PIXEL(position.x + i, position.y + j, color.r, color.g, color.b);
				}
			}
		}

		void DrawClipped()
		{
			if (isFlipped)
			{
				PointI adjustedPosition = {position.x - center.x, position.y + center.y};

				int clippedWidth = fmin(adjustedPosition.x, size.x);
				int clippedHeight = fmin(size.y,
										 fmax(0, size.y - (size.y - UR_SCREEN_HEIGHT)));

				int clippedX = 0;
				int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i];
						UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
					}
				}
			}
			else
			{
				PointI adjustedPosition = {position.x + center.x, position.y + center.y};

				int clippedWidth = fmin(size.x,
										fmax(0, size.x - (size.x + adjustedPosition.x - UR_SCREEN_WIDTH)));
				int clippedHeight = fmin(size.y,
										 fmax(0, size.y - (size.y + adjustedPosition.y - UR_SCREEN_HEIGHT)));

				int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
				int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i];
						UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
					}
				}
			}
		}

		void DrawTransparent()
		{
			if (isFlipped)
				for (int j = 0; j < size.y; j++)
				{
					for (int i = 0; i < size.x; i++)
					{
						Color color = imageData[j * size.x + i];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(position.x + size.x - i, position.y + j, color.r, color.g, color.b);
					}
				}
			else
				for (int j = 0; j < size.y; j++)
				{
					for (int i = 0; i < size.x; i++)
					{
						Color color = imageData[j * size.x + i];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(position.x + i, position.y + j, color.r, color.g, color.b);
					}
				}
		}

		void DrawTransparentClipped()
		{
			if (isFlipped)
			{
				PointI adjustedPosition = {position.x - center.x, position.y + center.y};

				int clippedWidth = fmin(adjustedPosition.x, size.x);
				int clippedHeight = fmin(size.y,
										 fmax(0, size.y - (size.y - UR_SCREEN_HEIGHT)));

				int clippedX = 0;
				int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
					}
				}
			}
			else
			{
				PointI adjustedPosition = {position.x + center.x, position.y + center.y};

				int clippedWidth = fmin(size.x,
										fmax(0, size.x - (size.x + adjustedPosition.x - UR_SCREEN_WIDTH)));
				int clippedHeight = fmin(size.y,
										 fmax(0, size.y - (size.y + adjustedPosition.y - UR_SCREEN_HEIGHT)));

				int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
				int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
					}
				}
			}
		}

		void DrawTransparentClippedLowerLine(int lowerLineHeight)
		{
			int clippedWidth = fmin(size.x,
									fmax(0, size.x - (size.x + position.x - UR_SCREEN_WIDTH)));
			int clippedHeight = fmin(size.y,
									 fmax(0, size.y - (size.y + position.y - lowerLineHeight)));
			int clippedX = position.x < 0 ? -position.x : 0;
			int clippedY = position.y < 0 ? -position.y : 0;

			if (isFlipped)
				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(position.x + size.x - i, position.y + j, color.r, color.g, color.b);
					}
				}
			else
				for (int j = clippedY; j < clippedHeight; j++)
				{
					for (int i = clippedX; i < clippedWidth; i++)
					{
						Color color = imageData[j * size.x + i];
						if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
							UR_PUT_PIXEL(position.x + i, position.y + j, color.r, color.g, color.b);
					}
				}
		}

		void CreateCkeckerBoard(PointI size, int checkerWidth, Color color1, Color color2)
		{
			Color currentColor = color1;
			imageData = (Color *)UR_MALLOC(sizeof(Color) * size.x * size.y);
			size = size;
			for (int y = 0; y < size.y; y++)
			{
				for (int x = 0; x < size.x; x++)
				{
					if ((y / checkerWidth + x / checkerWidth) % 2)
					{
						currentColor = color1;
					}
					else
					{
						currentColor = color2;
					}
					imageData[x + y * size.x] = currentColor;
				}
			}
		}

		void DrawTransparentAnimatedClipped2(double deltaTime, int animationId = 0)
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
										 fmax(0, animations[animationId].frameHeight - (animations[animationId].frameHeight - UR_SCREEN_HEIGHT)));

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
																	UR_SCREEN_WIDTH)));

			int clippedHeight = fmin(animations[animationId].frameHeight,
									 fmax(0, animations[animationId].frameHeight - (animations[animationId].frameHeight + adjustedPosition.y - UR_SCREEN_HEIGHT)));

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

		// void DrawTransparentAnimatedClipped(double deltaTime)
		// {
		// 	if (!animations[animationId].isPlaying)
		// 	{
		// 		animations[animationId].isPlaying = true;
		// 	}

		// 	animations[animationId].frameIncrement += deltaTime * animations[animationId].frameRate;
		// 	int lastFrame = animations[animationId].currentFrame;
		// 	animations[animationId].currentFrame = animations[animationId].frameIncrement;
		// 	animations[animationId].currentFrame %= animations[animationId].frameCount;
		// 	if (animations[animationId].currentFrame < lastFrame)
		// 	{
		// 		animations[animationId].isPlaying = false;
		// 	}

		// 	if (isFlipped)
		// 	{
		// 		PointI adjustedPosition = {position.x - center.x, position.y + center.y};

		// 		int clippedWidth = fmin(position.x + size.y, animations[animationId].frameWidth);

		// 		int clippedHeight = fmin(size.y,
		// 								 fmax(0, size.y - (size.y - UR_SCREEN_HEIGHT)));

		// 		int clippedX = 0;
		// 		int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

		// 		for (int j = clippedY; j < clippedHeight; j++)
		// 		{
		// 			for (int i = clippedX; i < clippedWidth; i++)
		// 			{
		// 				Color color = imageData[j * size.x + i +
		// 										animations[animationId].currentFrame * animations[animationId].frameWidth];
		// 				if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
		// 					UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
		// 			}
		// 		}
		// 		return;
		// 	}

		// 	PointI adjustedPosition = {position.x + center.x, position.y + center.y};

		// 	int clippedWidth = fmin(animations[animationId].frameWidth,
		// 							fmax(0, animations[animationId].frameWidth - (animations[animationId].frameWidth + adjustedPosition.x -
		// 															UR_SCREEN_WIDTH)));

		// 	int clippedHeight = fmin(size.y,
		// 							 fmax(0, size.y - (size.y + adjustedPosition.y - UR_SCREEN_HEIGHT)));

		// 	int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
		// 	int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

		// 	for (int j = clippedY; j < clippedHeight; j++)
		// 	{
		// 		for (int i = clippedX; i < clippedWidth; i++)
		// 		{
		// 			Color color = imageData[j * size.x + i +
		// 									animation[animationId].currentFrame * animations[animationId].frameWidth];
		// 			if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
		// 				UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
		// 		}
		// 	}
		// }

	}; // END Sprite class
}