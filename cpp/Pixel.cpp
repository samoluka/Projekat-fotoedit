#include "Pixel.h"

Pixel::Pixel(const IntPixel& p) {
	red = p.GetRed();
	if (p.GetRed() > 255) red = 255;
	else if (p.GetRed() < 0) red = 0;
	blue = p.GetBlue();
	if (p.GetBlue() > 255) blue = 255;
	else if (p.GetBlue() < 0) blue = 0;
	green = p.GetGreen();
	if (p.GetGreen() > 255) green = 255;
	else if (p.GetGreen() < 0) green = 0;
	alpha = p.GetAlpha();
	if (p.GetAlpha() > 100) alpha = 100;
	else if (p.GetAlpha() < 0) alpha = 0;
}
std::ostream & operator<<(std::ostream &os, const Pixel &p) {
	os << "(" << (int)p.GetRed() << "," << (int)p.GetGreen() << "," << (int)p.GetBlue() << "," << (int)p.GetAlpha() << ")";
	return os;
}
