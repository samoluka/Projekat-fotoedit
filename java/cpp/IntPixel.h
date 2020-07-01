#pragma once


class Pixel;

class IntPixel{
	int red, blue, green, alpha;
	static int maxchar;

	int mid();

public:


	IntPixel() { red = 0; green = 0; blue = 0; alpha = 0; }
	IntPixel(int r, int b, int g, int a) :red(r), blue(b), green(g), alpha(a) {};
	IntPixel(const Pixel& p);


	int GetRed()const { return red; }
	void SetRed(int red) { this->red = red; }

	int GetBlue()const { return blue; }
	void SetBlue(int blue) { this->blue = blue; }

	int GetGreen()const { return green; }
	void SetGreen(int green) { this->green = green; }

	int GetAlpha()const { return alpha; }
	void SetAlpha(int alpha) { this->alpha = alpha; }

	void SetAll(const int);
	void saberi(const int);
	void oduzmi(const int);
	void inverzno_oduzmi(const int);
	void pomnozi(const int);
	void podeli(const int);
	void inverzno_podeli(const int);
	void power(const double);
	void logarithm(const double);
	void min(const int);
	void max(const int);
	void invers();
	void greyscale();
	void black_white();
	void abs();

};
