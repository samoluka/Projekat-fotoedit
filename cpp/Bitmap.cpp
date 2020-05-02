#define _CRT_SECURE_NO_WARNINGS
#include "Bitmap.h"
#include <vector>
#include "Pixel.h"
#include <ctime>

void BMP::ReadBMP(const std::string& file, Layer & l, int StartX, int StartY) {
	int i;
	FILE* f = fopen(file.c_str(), "rb");
	if (!f) return;
	unsigned char info[54];

	fread(info, sizeof(unsigned char), 54, f);

	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	if (height > l.GetHeight() || width > l.GetWidth()) {
		std::cout << l.GetWidth() << " " << width << " " << l.GetHeight() << " " << height << std::endl;
		l.resize(height, width);
		std::cout << l.GetWidth() << " " << width << " " << l.GetHeight() << " " << height << std::endl;
	}
	
	int size = 4 * width * height;
	unsigned char* data = new unsigned char[size];

	fread(data, sizeof(unsigned char), size, f);
	fclose(f);

	int br = 0;
	for (i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int r = data[br + 2];
			int g = data[br + 1];
			int b = data[br + 0];
			int a = data[br + 3] * 100 / 255;
			br += 4;
			int ii = i + StartY;
			int jj = j + StartX;
			if (ii >= l.GetHeight() || jj >= l.GetWidth()) continue;
			l.SetPixel(ii, jj, Pixel(r, g, b, a));
		}
	}
}

const int bytesPerPixel = 4;
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;
unsigned char* createBitmapFileHeader(int height, int width, int pitch, int paddingSize);
unsigned char* createBitmapInfoHeader(int height, int width);

void BMP::ExportBMP(const std::string& file, Layer & l) {

	int pitch = l.GetWidth() * 4;
	unsigned char padding[3] = { 0, 0, 0 };
	int paddingSize = (4 - (pitch) % 4) % 4;

	int height = l.GetHeight();
	int width = l.GetWidth();
	unsigned char* image = new unsigned char[l.GetMatrix().size()*4];
	int it = 0;
	for (auto& x : l.GetMatrix()) {
		float a = x.GetAlpha() / 100.0;
		image[it++] = x.GetBlue() * a;
		image[it++] = x.GetGreen() * a;
		image[it++] = x.GetRed() * a;
		image[it++] = x.GetAlpha() * 255 / 100;
	}

	unsigned char* fileHeader = createBitmapFileHeader(height, width, pitch, paddingSize);
	unsigned char* infoHeader = createBitmapInfoHeader(height, width);

	FILE* imageFile = fopen(file.c_str(), "wb");

	fwrite(fileHeader, 1, fileHeaderSize, imageFile);
	fwrite(infoHeader, 1, infoHeaderSize, imageFile);

	int i;
	for (i = 0; i < height; i++) {
		fwrite(image + (i*pitch), bytesPerPixel, width, imageFile);
		fwrite(padding, 1, paddingSize, imageFile);
	}
	delete[] image;
	fclose(imageFile);
}

unsigned char* createBitmapFileHeader(int height, int width, int pitch, int paddingSize) {
	int fileSize = fileHeaderSize + infoHeaderSize + (/*bytesPerPixel*width*/pitch + paddingSize) * height;

	static unsigned char fileHeader[] = {
		0,0, /// signature
		0,0,0,0, /// image file size in bytes
		0,0,0,0, /// reserved
		0,0,0,0, /// start of pixel array
	};

	fileHeader[0] = (unsigned char)('B');
	fileHeader[1] = (unsigned char)('M');
	fileHeader[2] = (unsigned char)(fileSize);
	fileHeader[3] = (unsigned char)(fileSize >> 8);
	fileHeader[4] = (unsigned char)(fileSize >> 16);
	fileHeader[5] = (unsigned char)(fileSize >> 24);
	fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

	return fileHeader;
}

unsigned char* createBitmapInfoHeader(int height, int width) {
	static unsigned char infoHeader[] = {
		0,0,0,0, /// header size
		0,0,0,0, /// image width
		0,0,0,0, /// image height
		0,0, /// number of color planes
		0,0, /// bits per pixel
		0,0,0,0, /// compression
		0,0,0,0, /// image size
		0,0,0,0, /// horizontal resolution
		0,0,0,0, /// vertical resolution
		0,0,0,0, /// colors in color table
		0,0,0,0, /// important color count
	};

	infoHeader[0] = (unsigned char)(infoHeaderSize);
	infoHeader[4] = (unsigned char)(width);
	infoHeader[5] = (unsigned char)(width >> 8);
	infoHeader[6] = (unsigned char)(width >> 16);
	infoHeader[7] = (unsigned char)(width >> 24);
	infoHeader[8] = (unsigned char)(height);
	infoHeader[9] = (unsigned char)(height >> 8);
	infoHeader[10] = (unsigned char)(height >> 16);
	infoHeader[11] = (unsigned char)(height >> 24);
	infoHeader[12] = (unsigned char)(1);
	infoHeader[14] = (unsigned char)(bytesPerPixel * 8);

	return infoHeader;
}