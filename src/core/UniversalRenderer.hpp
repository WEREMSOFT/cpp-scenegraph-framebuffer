#pragma once
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <arpa/inet.h>

#ifndef UR_MALLOC
#define UR_MALLOC malloc
#endif

#ifndef UR_REALLOC
#define UR_REALLOC realloc
#endif

#ifndef UR_FREE
#define UR_FREE free
#endif

#define UR_SCREEN_WIDTH 320
#define UR_SCREEN_HEIGHT 200
namespace weremsoft
{


	typedef struct tagBITMAPFILEHEADER
	{
		uint16_t bfType;
		uint32_t bfSize;
		uint16_t bfReserved1;
		uint16_t bfReserved2;
		uint32_t bfOffBits;
	} __attribute__((packed)) BITMAPFILEHEADER;

	typedef struct tagBITMAPINFOHEADER
	{
		uint32_t biSize;
		int32_t biWidth;
		int32_t biHeight;
		uint16_t biPlanes;
		uint16_t biBitCount;
		uint32_t biCompression;
		uint32_t biSizeImage;
		int32_t biXPixPerMeter;
		int32_t biYPixPerMeter;
		uint32_t biClrUsed;
		uint32_t biClrImporant;
	} __attribute__((packed)) BITMAPINFOHEADER;

	unsigned char Fonts[][5] =
		{
			// 0
			{0b011100,
			 0b110010,
			 0b101010,
			 0b100110,
			 0b011100},
			// 1
			{0b001000,
			 0b011000,
			 0b001000,
			 0b001000,
			 0b011100},
			// 2
			{0b011100,
			 0b100010,
			 0b001100,
			 0b010000,
			 0b111110},
			// 3
			{0b011100,
			 0b100010,
			 0b001100,
			 0b100010,
			 0b011100},
			// 4
			{0b001010,
			 0b010010,
			 0b100010,
			 0b111110,
			 0b000010},
			// 5
			{0b111110,
			 0b100000,
			 0b111100,
			 0b000010,
			 0b111100},
			// 6
			{0b011110,
			 0b100000,
			 0b111100,
			 0b100010,
			 0b011100},
			// 7
			{0b111110,
			 0b000010,
			 0b000100,
			 0b001000,
			 0b010000},
			// 8
			{0b011100,
			 0b100010,
			 0b011100,
			 0b100010,
			 0b011100},
			// 9
			{0b011100,
			 0b100010,
			 0b011110,
			 0b000010,
			 0b011100},
			// A
			{0b111100,
			 0b100100,
			 0b100100,
			 0b111100,
			 0b100100},
			// B
			{0b111000,
			 0b100100,
			 0b111000,
			 0b100100,
			 0b111000},
			// C
			{0b111100,
			 0b100100,
			 0b100000,
			 0b100100,
			 0b111100},
			// D
			{0b111000,
			 0b100100,
			 0b100100,
			 0b100100,
			 0b111000},
			// E
			{0b111100,
			 0b100000,
			 0b111100,
			 0b100000,
			 0b111100},
			// F
			{0b111100,
			 0b100000,
			 0b111000,
			 0b100000,
			 0b100000},
			// G
			{0b011000,
			 0b100000,
			 0b101100,
			 0b100100,
			 0b011000},
			// H
			{0b100100,
			 0b100100,
			 0b111100,
			 0b100100,
			 0b100100},
			// I
			{0b011100,
			 0b001000,
			 0b001000,
			 0b001000,
			 0b011100},
			// J
			{0b111100,
			 0b000100,
			 0b000100,
			 0b100100,
			 0b011000},
			// K
			{0b100100,
			 0b101000,
			 0b110000,
			 0b101000,
			 0b100100},
			// L
			{0b100000,
			 0b100000,
			 0b100000,
			 0b100000,
			 0b111000},
			// M
			{0b100010,
			 0b110110,
			 0b101010,
			 0b100010,
			 0b100010},
			// N
			{0b010010,
			 0b011010,
			 0b010110,
			 0b010010,
			 0b010010},
			// O
			{0b111100,
			 0b100100,
			 0b100100,
			 0b100100,
			 0b111100},
			// P
			{0b111000,
			 0b100100,
			 0b111000,
			 0b100000,
			 0b100000},
			// Q
			{0b111100,
			 0b100100,
			 0b100100,
			 0b101100,
			 0b111100},
			// R
			{0b111000,
			 0b100100,
			 0b111000,
			 0b100100,
			 0b100100},
			// S
			{0b011100,
			 0b100000,
			 0b011000,
			 0b000100,
			 0b111000},
			// T
			{0b111000,
			 0b010000,
			 0b010000,
			 0b010000,
			 0b010000},
			// U
			{0b100100,
			 0b100100,
			 0b100100,
			 0b100100,
			 0b011000},
			// V
			{0b100100,
			 0b100100,
			 0b100100,
			 0b011000,
			 0b010000},
			// W
			{0b100010,
			 0b100010,
			 0b101010,
			 0b110110,
			 0b100010},
			// X
			{0b100100,
			 0b100100,
			 0b011000,
			 0b100100,
			 0b100100},
			// Y
			{0b100010,
			 0b100010,
			 0b010100,
			 0b001000,
			 0b001000},
			// Z
			{0b111110,
			 0b000100,
			 0b001000,
			 0b010000,
			 0b111110},
			// %
			{0b110001,
			 0b110010,
			 0b001100,
			 0b010011,
			 0b100011},
			// .
			{0b000000,
			 0b000000,
			 0b000000,
			 0b001100,
			 0b001100}};

	typedef struct
	{
		unsigned char r, g, b;
	} URColor;

#define UR_RED     \
	(URColor)      \
	{              \
		0xFF, 0, 0 \
	}
#define UR_WHITE         \
	(URColor)            \
	{                    \
		0xFF, 0xFF, 0xFF \
	}
#define UR_BLUE    \
	(URColor)      \
	{              \
		0, 0, 0xFF \
	}
#define UR_GREEN   \
	(URColor)      \
	{              \
		0, 0xFF, 0 \
	}
#define UR_PURPLE     \
	(URColor)         \
	{                 \
		0xFF, 0, 0xFF \
	}
#define UR_YELLOW     \
	(URColor)         \
	{                 \
		0xFF, 0xFF, 0 \
	}
#define UR_BLACK \
	(URColor)    \
	{            \
		0, 0, 0  \
	}

	struct URPointI
	{
		int x, y;
	};

	struct URRectI
	{
		URPointI position;
		URPointI size;
	};

	namespace RendererCore
	{
		SDL_Renderer *renderer;
		SDL_Window *window;
	};

	void putPixel(int x, int y, char r, char g, char b)
	{
		SDL_SetRenderDrawColor(RendererCore::renderer, r, g, b, 255);
		SDL_RenderDrawPoint(RendererCore::renderer, x, y);
	}
#define UR_PUT_PIXEL putPixel

#define UR_KEY_PRESS SDL_KEYDOWN

	int getButtonState(int mouseButton)
	{
		return 0;
	}

#define UR_GET_BUTTON_STATE

	// #include "universal_renderer.h"

	class UniversalRenderer
	{
	public:
		// --- KEYBOARD
		bool keys[256];
		bool keysJustPressed[256];
		// --- MOUSE
		int mouseButtons[5] = {0};

		UniversalRenderer()
		{
			printf("creating renderer\n");
			assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "Error initializing SDL\n");

			SDL_DisplayMode displayMode;
			SDL_GetCurrentDisplayMode(0, &displayMode);

			RendererCore::window = SDL_CreateWindow(
				NULL,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				800,
				600,
				0);

			assert(RendererCore::window != NULL && "Error creating SDL window");

			RendererCore::renderer = SDL_CreateRenderer(RendererCore::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			assert(RendererCore::renderer != NULL && "Error creating renderer");

			SDL_RenderSetScale(RendererCore::renderer, 2., 2.);
			printf("renderer initialized\n");
		}

		void StartFrame(void)
		{
			SDL_SetRenderDrawColor(RendererCore::renderer, 0, 0, 0, 0);
			SDL_RenderClear(RendererCore::renderer);
		}

		void EndFrame(void)
		{
			SDL_RenderPresent(RendererCore::renderer);
		}

		~UniversalRenderer()
		{
			printf("destroying renderer\n");
			SDL_DestroyRenderer(RendererCore::renderer);
			SDL_DestroyWindow(RendererCore::window);
			SDL_Quit();
		}

		void ClearScreen(URColor clearColor)
		{
			for (int x = 0; x < UR_SCREEN_WIDTH; x++)
				for (int y = 0; y < UR_SCREEN_HEIGHT; y++)
				{
					URPointI p = (URPointI){x, y};
					UR_PUT_PIXEL(p.x, p.y, clearColor.r, clearColor.g, clearColor.b);
				}
		}

		void DrawCircle(URPointI center, double radious, URColor color)
		{
			for (int i = center.x - radious; i <= center.x + radious; i++)
			{
				for (int j = center.y - radious; j <= center.y + radious; j++)
				{
					URPointI p = (URPointI){i, j};
					if (floor(sqrt(pow(center.x - i, 2) + pow(center.y - j, 2))) == radious)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawCircleFill(URPointI center, double radious, URColor color)
		{

			for (int i = center.x - radious; i <= center.x + radious; i++)
			{
				for (int j = center.y - radious; j <= center.y + radious; j++)
				{
					URPointI p = (URPointI){i, j};
					if (floor(sqrt(pow(center.x - i, 2) + pow(center.y - j, 2))) <= radious)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawSquare(URPointI topLeftCorner, URPointI size, URColor color)
		{
			for (int i = fmax(topLeftCorner.x, 0); i <= topLeftCorner.x + size.x; i++)
			{
				for (int j = fmax(topLeftCorner.y, 0); j <= topLeftCorner.y + size.y; j++)
				{
					URPointI p = (URPointI){i, j};
					if (j == topLeftCorner.y || j == topLeftCorner.y + size.y || i == topLeftCorner.x || i == topLeftCorner.x + size.x)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawSquareFill(URPointI topLeftCorner, URPointI size, URColor color)
		{
			for (int i = topLeftCorner.x; i <= topLeftCorner.x + size.x; i++)
			{
				for (int j = topLeftCorner.y; j <= topLeftCorner.y + size.y; j++)
				{
					URPointI p = (URPointI){i, j};
					if (j >= topLeftCorner.y || j <= topLeftCorner.y + size.y || i >= topLeftCorner.x || i <= topLeftCorner.x + size.x)
						UR_PUT_PIXEL(p.x, p.y, color.r, color.g, color.b);
				}
			}
		}

		void DrawLine(URPointI pointA, URPointI pointB, URColor color)
		{
			int dx = abs(pointB.x - pointA.x), sx = pointA.x < pointB.x ? 1 : -1;
			int dy = abs(pointB.y - pointA.y), sy = pointA.y < pointB.y ? 1 : -1;
			int err = (dx > dy ? dx : -dy) / 2, e2;

			for (;;)
			{
				UR_PUT_PIXEL(pointA.x, pointA.y, color.r, color.g, color.b);

				if (pointA.x == pointB.x && pointA.y == pointB.y)
					break;
				e2 = err;

				if (e2 > -dx)
				{
					err -= dy;
					pointA.x += sx;
				}

				if (e2 < dy)
				{
					err += dx;
					pointA.y += sy;
				}
			}
		}

		bool IsMouseButtonJustPressed(int mouseButton)
		{
			int currentMouseState = UR_GET_BUTTON_STATE(mouseButton);

			if (mouseButtons[mouseButton] && currentMouseState)
				return false;

			mouseButtons[mouseButton] = currentMouseState;

			return currentMouseState;
		}

		void PrintString(URPointI topLeftCorner, const char *string, URColor color)
		{
			size_t stringLen = strlen(string);

			for (size_t i = 0; i < stringLen; i++)
			{
				if (string[i] == '.')
				{
					int charOffset = 'z' - 'a' + 12;
					DrawCharacter((URPointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, charOffset, color);
					continue;
				}

				if (string[i] == '%')
				{
					int charOffset = 'z' - 'a' + 11;
					DrawCharacter((URPointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, charOffset, color);
					continue;
				}

				if (string[i] >= '0' && string[i] <= '9')
				{
					DrawCharacter((URPointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, string[i] - '0', color);
					continue;
				}

				if (string[i] >= 'a' && string[i] <= 'z')
				{
					int charOffset = string[i] - 'a' + 10;
					DrawCharacter((URPointI){topLeftCorner.x + (int)i * 6, topLeftCorner.y}, charOffset, color);
					continue;
				}
			}
		}

		void DrawCharacter(URPointI topLeftCorner, unsigned int letter, URColor color)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j <= 8; j++)
				{
					if (Fonts[letter][i] & (0b1000000 >> j))
						UR_PUT_PIXEL(topLeftCorner.x + j, topLeftCorner.y + i, color.r, color.g, color.b);
				}
			}
		}

		void PrintFPS(double deltaTime)
		{

#define FPS_HISTORY 10
			static double fpsHistory[FPS_HISTORY] = {0};
			static int counter = 1;
			counter++;
			counter %= FPS_HISTORY;
			fpsHistory[counter] = (1 / deltaTime);

			int sum = 0;
			for (int i = 0; i < FPS_HISTORY; i++)
			{
				sum += fpsHistory[i];
			}

			float avg = sum / FPS_HISTORY;

			{
				char text[1000] = {0};
				snprintf(text, 1000, "fps: %d", (int)floor(avg));
				PrintString((URPointI){230, 220}, text, (URColor){0, 0xff, 0xff});
			}

			{
				char text[1000] = {0};
				snprintf(text, 1000, "ftime:%.4f", deltaTime);
				PrintString((URPointI){230, 230}, text, (URColor){0, 0xff, 0xff});
			}
		}

#define BITMAPINFOHEADER_SIZE 40
#define BITMAPFILEHEADER_SIZE 14

		unsigned char *urBMPLoad(char *fileName, int *imageWidth, int *imageHeight)
		{
			BITMAPFILEHEADER fileHeader;
			BITMAPINFOHEADER infoHeader;

			FILE *fp;
			int downToUp = 1;
			unsigned char *Data;
			unsigned int size;

			int w, h, width, height;
			int lineSize;
			unsigned char *lineData;

			if (sizeof(fileHeader) != BITMAPFILEHEADER_SIZE || sizeof(infoHeader) != BITMAPINFOHEADER_SIZE)
			{
				printf("16bit width alighment required. %ld\n", sizeof(fileHeader));
				exit(-1);
			}

			if ((fp = fopen(fileName, "rb")) == NULL)
			{
				printf("No such file. (%s)\n", fileName);
				exit(-1);
			}

			if (fread(&fileHeader, sizeof(fileHeader), 1, fp) != 1)
			{
				printf("Not BMP file (filesize under 14Bytes)\n");
				exit(-1);
			}

			if (fileHeader.bfType != htons(0x424d))
			{
				printf("%s: Not BMP file type (magc number = '%04x')\n", fileName, fileHeader.bfType);
				exit(-1);
			}

			if (fread(&infoHeader.biSize, sizeof(infoHeader.biSize), 1, fp) != 1)
			{
				printf("%s: No infoHeader field (too small filesize)\n", fileName);
				exit(-1);
			}

			if (infoHeader.biSize != 40)
			{
				printf("%s: Not Windows BMP file type (header size = %d)\n", fileName, infoHeader.biSize);
				exit(-1);
			}

			if (fread(&infoHeader.biWidth, sizeof(infoHeader) - sizeof(infoHeader.biSize), 1, fp) != 1)
			{
				printf("%s: Not enough infoHeader field (too small filesize)\n", fileName);
				exit(-1);
			}

			width = infoHeader.biWidth;
			height = infoHeader.biHeight;
			printf("width = %d, height = %d\n", infoHeader.biWidth, infoHeader.biHeight);
			if (height < 0)
			{
				downToUp = 0;
				height *= -1;
				printf("(up to down scanned data)\n");
			}

			if (infoHeader.biPlanes != 1)
			{
				printf("Number of plain is not 1 (%d)\n", infoHeader.biPlanes);
				exit(-1);
			}
			printf("planes = %d\n", infoHeader.biPlanes);

			if ((infoHeader.biBitCount != 24) && (infoHeader.biBitCount != 32))
			{
				printf("%s: only 24 or 32 bits per pixel format is acceptable (%d)\n", fileName, infoHeader.biBitCount);
				exit(-1);
			}
			printf("bits/pixel = %d\n", infoHeader.biBitCount);

			fseek(fp, fileHeader.bfOffBits, SEEK_SET);

			if (infoHeader.biBitCount != 24)
			{
				printf("only 24 bit RGB bmp images are supported\n");
				exit(-1);
			}

			int pixSize = infoHeader.biBitCount / 8;
			size = width * height * pixSize;
			Data = (unsigned char *)UR_MALLOC(size);
			if (Data == NULL)
			{
				printf("cannot alocate memory for the picture (%d bytes)\n", size);
				exit(-1);
			}
			printf("Data %p (%d bytes allocated)\n", Data, size);

			lineSize = width * pixSize;
			if ((lineSize % 4) != 0)
				lineSize = ((lineSize / 4) + 1) * 4;

			lineData = (unsigned char *)UR_MALLOC(lineSize);
			if (Data == NULL)
			{
				printf("cannot alocate memory for line buffer (%d bytes)\n", lineSize);
				exit(-1);
			}

			for (h = 0; h < height; h++)
			{
				if (fread(lineData, lineSize, 1, fp) != 1)
				{
					printf("cannot read data body\n");
					exit(-1);
				}
				unsigned char *target;
				if (downToUp)
				{
					target = Data + (height - 1 - h) * width * pixSize;
				}
				else
				{
					target = Data + h * width * pixSize;
				}

				for (w = 0; w < width; w++)
				{
					target[w * pixSize] = lineData[w * pixSize + 2];	 // Red
					target[w * pixSize + 1] = lineData[w * pixSize + 1]; // Green
					target[w * pixSize + 2] = lineData[w * pixSize];	 // Blue
					if (pixSize == 4)
						target[w * pixSize + 3] = lineData[w * pixSize + 3]; // Alpha
				}
			}

			UR_FREE(lineData);
			fclose(fp);

			*imageWidth = width;
			*imageHeight = height;
			return Data;
		}
	};
}
