#pragma once

namespace UR
{
#ifndef UR_MALLOC
#define UR_MALLOC malloc
#endif

#ifndef UR_REALLOC
#define UR_REALLOC realloc
#endif

#ifndef UR_FREE
#define UR_FREE free
#endif

	struct PointI
	{
		int x, y;
	};

	struct RectI
	{
		PointI position;
		PointI size;
	};

	struct Color
	{
		unsigned char r, g, b;
	};

	struct Animation
	{
		bool isPlaying;
		int frameWidth;
		int frameHeight;
		int t;
		int currentFrame;
		int frameCount;
		float frameIncrement;
		float frameRate;
	};
}