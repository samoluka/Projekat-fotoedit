#pragma once
#include <string>
#include "Layer.h"

class Pam {
public:
	static void load(const std::string&, Layer&);
	static void out(const std::string&, Layer&);
};

