#pragma once
#include <string>
#include "Layer.h"
#include "ImageLoader.h"
class Pam:public ImageLoader {
private:
	void ReadImage(const std::string&, Layer&, int = 0, int = 0);
	void WriteImage(const std::string&, Layer&);
};

