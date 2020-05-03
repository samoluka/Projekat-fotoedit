#include "ImageLoader.h"
#include "Bitmap.h"
#include "Pam.h"
#include <regex>
#include <string>
#include <map>
#include <functional>


std::map<std::string, ImageLoader*> extension = {
	{"bmp",new BMP()},{"pam",new Pam()}
};

void ImageLoader::in(const std::string& s, Layer& l, int StartX, int StartY) {
	ImageLoader* il;
	int len = s.length();
	std::string ext;
	ext.assign(s, s.length() - 3, 3);
	il = extension[ext];
	il->ReadImage(s, l,StartX,StartY);
}
void ImageLoader::out(const std::string& s, Layer& l) {
	ImageLoader* il;
	int len = s.length();
	std::string ext;
	ext.assign(s, s.length() - 3, 3);
	il = extension[ext];
	il->WriteImage(s, l);
}