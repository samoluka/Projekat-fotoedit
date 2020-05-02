#pragma once
#include "IntPixel.h"
#include "Pixel.h"
#include <string>
#include "Param.h"
class Operation{
public:
	virtual int GetNumOfOperand()const = 0;
	virtual IntPixel& operator()(IntPixel&, void*) = 0;
	virtual std::string GetName()const = 0;
	virtual Param& GetParam(const std::string&)const = 0;
protected:
	int maxchar = 255;
};