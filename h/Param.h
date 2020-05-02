#pragma once


class Param {
public:
	virtual void* getRef() = 0;
};
class ParamDouble:public Param {
	double value;
public:
	ParamDouble(double value) {
		this->value = value;
	}
	void* getRef() { return &value; }
};
class ParamInt :public Param {
	int value;
public:
	ParamInt(int value) {
		this->value = value;
	}
	void* getRef() { return &value; }
};
class ParamNull :public Param {
public:
	ParamNull() {}
	void* getRef() { return nullptr; }
};