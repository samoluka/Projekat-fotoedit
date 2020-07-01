#pragma once
#include <cmath>
#include <functional>
#include <iostream>
#include "IntPixel.h";


class Pixel {
private:
	unsigned char red = 0, green = 0, blue = 0;
	unsigned char alpha = 0;
	static const unsigned char max_char = 255;
public:

	Pixel() {};
	Pixel(unsigned char red, unsigned char green, unsigned char blue,unsigned char alpha) :red(red), green(green), blue(blue),alpha(alpha) {};
	Pixel(unsigned char red, unsigned char green, unsigned char blue):Pixel(red,green,blue,0) {};
	Pixel(const IntPixel&);

	const unsigned char GetRed()const { return red; }
	const unsigned char GetGreen()const { return green; }
	const unsigned char GetBlue()const { return blue; }
	const unsigned char GetAlpha()const { return alpha; }
	void SetRed(unsigned char red) { this->red = red; }
	void SetGreen(unsigned char green) { this->green = green; }
	void SetBlue(unsigned char blue) { this->blue = blue; }
	void SetAlpha(unsigned char alpha) { this->alpha = alpha; }

	friend std::ostream& operator<<(std::ostream&, const Pixel&);
};

