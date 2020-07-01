#pragma once
#include "Layer.h"
#include <string>


class ImageLoader {
protected:
	virtual void ReadImage(const std::string& s, Layer& l, int StartX, int StartY) = 0;
	virtual void WriteImage(const std::string& s, Layer& l) = 0;
public:
	static void in(const std::string& s, Layer& l, int StartX = 0, int StartY = 0);
	static void out(const std::string& s, Layer& l);
};