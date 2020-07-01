#pragma once
#include "Pixel.h"

class Param {
public:
	virtual void* getRef() = 0;
};
class ParamDouble:public Param {
	int valid = 1;
	double value;
public:
	ParamDouble(const std::string&) {
		valid = 0;
	}
	ParamDouble(double value) {
		this->value = value;
	}
	void* getRef() { 
		if (!valid) return nullptr;
		return &value; 
	}
};
class ParamInt :public Param {
	int valid = 1;
	int value;
public:
	ParamInt(const std::string&) {
		valid = 0;
	}
	ParamInt(int value) {
		this->value = value;
	}
	void* getRef() {
		if (!valid) return nullptr;
		return &value; 
	}
};
class ParamPix :public Param {
private:
	Pixel p;
	int valid = 1;
public:
	ParamPix(const std::string&) {
		valid = 0;
	}
	ParamPix(unsigned char r, unsigned char g, unsigned char b) {
		p = Pixel(r, g, b, 100);
	}
	void* getRef() {
		if (!valid) return nullptr;
		return &p;
	}
};
class ParamNull :public Param {
public:
	ParamNull() {}
	void* getRef() { return nullptr; }
};