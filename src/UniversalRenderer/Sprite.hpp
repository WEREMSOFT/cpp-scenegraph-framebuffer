#pragma once

#include "Types.hpp"
#include "Utils.hpp"

namespace UR
{
	class Sprite
	{
	public:
		bool animated;
		bool isFlipped;
		Animation animation;
		PointI position;
		PointI center;
		PointI size;
		Color *imageData;

		Sprite(char *file)
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
					UR_PUT_PIXEL(_this.position.x + i, _this.position.y + j, color.r, color.g, color.b);
				}
			}
		}
	};
	/*

typedef

	void urSpriteDraw(URSprite _this)
	{
		for (int i = 0; i < _this.size.x; i++)
		{
			for (int j = 0; j < _this.size.y; j++)
			{
				Color color = _this.imageData[j * _this.size.x + i];
				UR_PUT_PIXEL(_this.position.x + i, _this.position.y + j, color.r, color.g, color.b);
			}
		}
	}

	void urSpriteDrawClipped(URSprite _this)
	{
		if (_this.isFlipped)
		{
			PointI adjustedPosition = {_this.position.x - _this.center.x, _this.position.y + _this.center.y};

			int clippedWidth = fmin(adjustedPosition.x, _this.size.x);
			int clippedHeight = fmin(_this.size.y,
									 fmax(0, _this.size.y - (_this.size.y - UR_SCREEN_HEIGHT)));

			int clippedX = 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
		}
		else
		{
			PointI adjustedPosition = {_this.position.x + _this.center.x, _this.position.y + _this.center.y};

			int clippedWidth = fmin(_this.size.x,
									fmax(0, _this.size.x - (_this.size.x + adjustedPosition.x - UR_SCREEN_WIDTH)));
			int clippedHeight = fmin(_this.size.y,
									 fmax(0, _this.size.y - (_this.size.y + adjustedPosition.y - UR_SCREEN_HEIGHT)));

			int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
		}
	}

	void urSpriteDrawTransparent(URSprite _this)
	{
		if (_this.isFlipped)
			for (int j = 0; j < _this.size.y; j++)
			{
				for (int i = 0; i < _this.size.x; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(_this.position.x + _this.size.x - i, _this.position.y + j, color.r, color.g, color.b);
				}
			}
		else
			for (int j = 0; j < _this.size.y; j++)
			{
				for (int i = 0; i < _this.size.x; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(_this.position.x + i, _this.position.y + j, color.r, color.g, color.b);
				}
			}
	}

	void urSpriteDrawTransparentClipped(URSprite _this)
	{
		if (_this.isFlipped)
		{
			PointI adjustedPosition = {_this.position.x - _this.center.x, _this.position.y + _this.center.y};

			int clippedWidth = fmin(adjustedPosition.x, _this.size.x);
			int clippedHeight = fmin(_this.size.y,
									 fmax(0, _this.size.y - (_this.size.y - UR_SCREEN_HEIGHT)));

			int clippedX = 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
		}
		else
		{
			PointI adjustedPosition = {_this.position.x + _this.center.x, _this.position.y + _this.center.y};

			int clippedWidth = fmin(_this.size.x,
									fmax(0, _this.size.x - (_this.size.x + adjustedPosition.x - UR_SCREEN_WIDTH)));
			int clippedHeight = fmin(_this.size.y,
									 fmax(0, _this.size.y - (_this.size.y + adjustedPosition.y - UR_SCREEN_HEIGHT)));

			int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
		}
	}

	void urSpriteDrawTransparentClippedLowerLine(URSprite _this, int lowerLineHeight)
	{
		int clippedWidth = fmin(_this.size.x,
								fmax(0, _this.size.x - (_this.size.x + _this.position.x - UR_SCREEN_WIDTH)));
		int clippedHeight = fmin(_this.size.y,
								 fmax(0, _this.size.y - (_this.size.y + _this.position.y - lowerLineHeight)));
		int clippedX = _this.position.x < 0 ? -_this.position.x : 0;
		int clippedY = _this.position.y < 0 ? -_this.position.y : 0;

		if (_this.isFlipped)
			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(_this.position.x + _this.size.x - i, _this.position.y + j, color.r, color.g, color.b);
				}
			}
		else
			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(_this.position.x + i, _this.position.y + j, color.r, color.g, color.b);
				}
			}
	}


	URSprite urSpriteCreateCkeckerBoard(PointI size, int checkerWidth, Color color1, Color color2)
	{
		URSprite _this = {0};
		Color currentColor = color1;
		_this.imageData = (Color *)UR_MALLOC(sizeof(Color) * size.x * size.y);
		_this.size = size;
		for (int y = 0; y < _this.size.y; y++)
		{
			for (int x = 0; x < _this.size.x; x++)
			{
				if ((y / checkerWidth + x / checkerWidth) % 2)
				{
					currentColor = color1;
				}
				else
				{
					currentColor = color2;
				}
				_this.imageData[x + y * size.x] = currentColor;
			}
		}
		return _this;
	}

	URSprite urSpriteDrawTransparentAnimatedClipped(URSprite _this, double deltaTime)
	{
		if (!_this.animation.isPlaying)
		{
			_this.animation.isPlaying = true;
		}

		_this.animation.frameIncrement += deltaTime * _this.animation.frameRate;
		int lastFrame = _this.animation.currentFrame;
		_this.animation.currentFrame = _this.animation.frameIncrement;
		_this.animation.currentFrame %= _this.animation.frameCount;
		if (_this.animation.currentFrame < lastFrame)
		{
			_this.animation.isPlaying = false;
		}

		if (_this.isFlipped)
		{
			PointI adjustedPosition = {_this.position.x - _this.center.x, _this.position.y + _this.center.y};

			int clippedWidth = fmin(_this.position.x + _this.size.y, _this.animation.frameWidth);

			int clippedHeight = fmin(_this.size.y,
									 fmax(0, _this.size.y - (_this.size.y - UR_SCREEN_HEIGHT)));

			int clippedX = 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i +
													_this.animation.currentFrame * _this.animation.frameWidth];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(adjustedPosition.x - i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
			return _this;
		}

		{
			PointI adjustedPosition = {_this.position.x + _this.center.x, _this.position.y + _this.center.y};

			int clippedWidth = fmin(_this.animation.frameWidth,
									fmax(0, _this.animation.frameWidth - (_this.animation.frameWidth + adjustedPosition.x -
																		  UR_SCREEN_WIDTH)));

			int clippedHeight = fmin(_this.size.y,
									 fmax(0, _this.size.y - (_this.size.y + adjustedPosition.y - UR_SCREEN_HEIGHT)));

			int clippedX = adjustedPosition.x < 0 ? -adjustedPosition.x : 0;
			int clippedY = adjustedPosition.y < 0 ? -adjustedPosition.y : 0;

			for (int j = clippedY; j < clippedHeight; j++)
			{
				for (int i = clippedX; i < clippedWidth; i++)
				{
					Color color = _this.imageData[j * _this.size.x + i +
													_this.animation.currentFrame * _this.animation.frameWidth];
					if (!(color.r == 0xFF && color.b == 0xFF && color.g == 0))
						UR_PUT_PIXEL(adjustedPosition.x + i, adjustedPosition.y + j, color.r, color.g, color.b);
				}
			}
			return _this;
		}
	}

	*/
}