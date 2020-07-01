#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Layer.h"
#include "ImageLoader.h"


class BMP:public ImageLoader {
private:
	void ReadImage(const std::string&, Layer&, int = 0, int = 0);
	void WriteImage(const std::string&, Layer&);
};