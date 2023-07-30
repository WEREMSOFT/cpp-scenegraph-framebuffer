#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Types.hpp"

namespace UR
{
#pragma pack(push, 1)
	struct BITMAPFILEHEADER
	{
		uint16_t bfType;
		uint32_t bfSize;
		uint16_t bfReserved1;
		uint16_t bfReserved2;
		uint32_t bfOffBits;
	} __attribute__((packed));

	struct BITMAPINFOHEADER
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
	};
#pragma pack(pop)

#define BITMAPINFOHEADER_SIZE 40
#define BITMAPFILEHEADER_SIZE 14

	unsigned char *BMPLoad(const char *fileName, int *imageWidth, int *imageHeight)
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
}