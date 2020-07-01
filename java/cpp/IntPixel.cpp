#include "IntPixel.h"
#include "Pixel.h"
#include <cmath>
int IntPixel::maxchar = 255;

IntPixel::IntPixel(const Pixel & p) {
	red = (p.GetRed());
	blue = (p.GetBlue());
	green = (p.GetGreen());
	alpha = (p.GetAlpha());
}

void IntPixel::SetAll(const int c) {
	this->red = c;
	this->green = c;
	this->blue = c;
}
int IntPixel::mid() {
	return (red + green + blue) / 3;
}

void IntPixel::saberi(const int operand) {
	red += operand;
	blue += operand;
	green += operand;
}
void IntPixel::oduzmi(const int operand) {
	red -= operand;
	blue -= operand;
	green -= operand;
}
void IntPixel::inverzno_oduzmi(const int operand) {
	red = operand - red;
	blue = operand - blue;
	green = operand - green;
}
void IntPixel::pomnozi(const int operand) {
	red *= operand;
	blue *= operand;
	green *= operand;
}
void IntPixel::podeli(const int operand) {
	red /= operand;
	blue /= operand;
	green /= operand;
}
void IntPixel::inverzno_podeli(const int operand) {
	red = operand / red;
	blue = operand / blue;
	green = operand / green;
}

void IntPixel::power(const double operand) {
	red = pow(red, operand);
	blue = pow(blue, operand);
	green = pow(green, operand);
}

void IntPixel::logarithm(const double operand) {
	red = log(red) / log(operand);
	blue = log(red) / log(operand);
	green = log(red) / log(operand);

}

void IntPixel::min(const int operand) {
	if (red < operand) red = operand;
	if (blue < operand) blue = operand;
	if (green < operand) green = operand;
}

void IntPixel::max(const int operand) {
	if (red > operand) red = operand;
	if (blue > operand) blue = operand;
	if (green > operand) green = operand;
}

void IntPixel::invers() {
	inverzno_oduzmi(maxchar);
}

void IntPixel::greyscale() {
	SetAll(mid());
}

void IntPixel::black_white() {
	int s = mid() > 127 ? 255 : 0;
	SetAll(s);
}

void IntPixel::abs(){
	red = std::abs(red);
	green = std::abs(green);
	blue = std::abs(blue);
	alpha = std::abs(alpha);
}
