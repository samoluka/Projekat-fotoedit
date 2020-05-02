#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Layer.h"
class BMP {
public:
	static void ReadBMP(const std::string&, Layer&, int = 0, int = 0);
	static void ExportBMP(const std::string&,Layer&);
};