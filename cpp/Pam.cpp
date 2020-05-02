#include "Pam.h"
#include <regex>
#include <fstream>

void Pam::load(const std::string & path, Layer & l) {
	std::ifstream f(path, std::ios::binary);
	std::string input;
	std::getline(f, input);
	std::regex opt1("WIDTH ([0-9]*)");
	std::regex opt2("HEIGHT ([0-9]*)");
	std::regex opt3("DEPTH ([0-9]*)");
	std::regex opt4("MAXVAL ([0-9]*)");
	std::regex opt5("TUPLTYPE ([0-9]*)");
	std::smatch res;
	std::getline(f, input);
	std::regex_match(input, res, opt1);
	input = res[1];
	int w = std::atoi(input.c_str());
	std::getline(f, input);
	std::regex_match(input, res, opt2);
	input = res[1];
	int h = std::atoi(input.c_str());
	std::getline(f, input);
	std::getline(f, input);
	std::getline(f, input);
	std::getline(f, input);

	l.resize(h, w);

	int size = 4 * w * h;
	unsigned char* buff = new unsigned char[size];

	using uchar = unsigned char;
	f.read((char*)buff, size);
	int x = 0;
	int y = h - 1;
	for (int i = 0; i < size;i += 4) {

		uchar r = (uchar)buff[i];
		uchar g = (uchar)buff[i + 1];
		uchar b = (uchar)buff[i + 2];
		uchar a = (uchar)buff[i + 3] * 100 / 255;
		l.GetMatrix()[y*w + x] = Pixel(r, g, b, a);
		x++;
		if (x >= w) {
			x = 0;
			y--;
		}
	}

	delete[] buff;
	f.close();

}

void Pam::out(const std::string & path, Layer & l) {
	int w = l.GetWidth();
	int h = l.GetHeight();
	std::ofstream f(path, std::ios::binary);
	std::string header = "P7\nWIDTH " + std::to_string(l.GetWidth()) + "\nHEIGHT " + std::to_string(l.GetHeight());
	header += "\nDEPTH 4\nMAXVAL 255\nTUPLTYPE RGB_ALPHA\nENDHDR\n";
	f << header;
	using uchar = unsigned char;

	int size = 4 * w * h;

	uchar* buff = new uchar[size];

	int x = 0;
	int y = h - 1;

	for (int i = 0; i < size; i += 4) {
		uchar r = (uchar)l.GetMatrix()[y * w + x].GetRed();
		uchar g = (uchar)l.GetMatrix()[y * w + x].GetGreen();
		uchar b = (uchar)l.GetMatrix()[y * w + x].GetBlue();
		uchar a = (uchar)l.GetMatrix()[y * w + x].GetAlpha() * 255 / 100;
		buff[i] = r;
		buff[i + 1] = g;
		buff[i + 2] = b;
		buff[i + 3] = a;
		x++;
		if (x >= w) {
			x = 0;
			y--;
		}
	}
	f.write((char*)buff, size);
	delete[] buff;
	f.close();
}

