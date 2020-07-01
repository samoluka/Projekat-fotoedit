#pragma once
#include "Operation.h";
#include "Greske.h"
#include <string>
#include <regex>
class OperationSetAlpha :public Operation {
public:
	int GetNumOfOperand()const override { return 1; };
	std::string GetName()const { return "SetAlpha"; };
	ParamInt& GetParam(const std::string& s)const override { 
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int i = *(int*)operand;
		p.SetAlpha(i);
		return p;
	}
};
class OperationABS :public Operation {
public:
	int GetNumOfOperand()const override { return 0; };
	std::string GetName()const { return "abs"; };
	ParamNull& GetParam(const std::string&)const override { return *new ParamNull(); }
	IntPixel& operator()(IntPixel& p, void* operand)override {
		p.abs();
		return p;
	}
};
class OperationGreyScale :public Operation {
public:
	int GetNumOfOperand()const override { return 0; };
	std::string GetName()const { return "greyscale"; };
	ParamNull& GetParam(const std::string&)const override { return *new ParamNull(); }
	IntPixel& operator()(IntPixel& p, void* operand)override {
		p.greyscale();
		return p;
	}
};
class OperationBlackWhite :public Operation {
public:
	int GetNumOfOperand()const override { return 0; }
	std::string GetName()const { return "bw"; };
	ParamNull& GetParam(const std::string&)const override { return *new ParamNull(); }
	IntPixel& operator()(IntPixel& p, void* operand)override {
		p.black_white();
		return p;
	}
};

class OperationInvers :public Operation {
public:
	int GetNumOfOperand()const override { return 0; }
	ParamNull& GetParam(const std::string&)const override { return *new ParamNull(); }
	std::string GetName()const { return "invers"; };
	IntPixel& operator()(IntPixel& p, void* operand)override {
		p.invers();
		return p;
	}
};
class OperationMin :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "min"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.min(o);
		return p;
	}
};
class OperationMax :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "max"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.max(o);
		return p;
	}
};
class OperationLogarithm :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "log"; };
	ParamDouble& GetParam(const std::string& s)const override {
		std::regex opt1("([0-9]*).([0-9]+) *");
		std::smatch res;
		if (std::regex_match(s, res, opt1)) {
			double d = std::stod(s);
			return *new ParamDouble(d);
		}
		return *new ParamDouble(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		double o = *(double*)operand;
		p.logarithm(o);
		return p;
	}
};
class OperationPower :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "pow"; };
	ParamDouble& GetParam(const std::string& s)const override {
		std::regex opt1("([0-9]*).([0-9]+) *");
		std::smatch res;
		if (std::regex_match(s, res, opt1)) {
			double d = std::stod(s);
			return *new ParamDouble(d);
		}
		return *new ParamDouble(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		double o = *(double*)operand;
		p.power(o);
		return p;
	}
};

class OperationDivInvers :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "idiv"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.inverzno_podeli(o);
		return p;
	}
};
class OperationDiv :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "div"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.podeli(o);
		return p;
	}
};
class OperationMul :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "mul"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.pomnozi(o);
		return p;
	}
};
class OperationMinusInvers :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "imin"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.inverzno_oduzmi(o);
		return p;
	}
};
class OperationMinus :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "min"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.oduzmi(o);
		return p;
	}
};
class OperationPlus :public Operation {
public:
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "plus"; };
	ParamInt& GetParam(const std::string& s)const override {
		if (isdigit(s[0])) {
			return *new ParamInt(std::atoi(s.c_str()));
		}
		return *new ParamInt(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		int o = *(int*)operand;
		p.saberi(o);
		return p;
	}
};
class OperationSetColor :public Operation {
	int GetNumOfOperand()const override { return 1; }
	std::string GetName()const { return "SetColor"; };
	ParamPix& GetParam(const std::string& s)const override {
		std::regex opt1("([0-9]+) ([0-9]+) ([0-9]+) *");
		std::smatch res;
		if (std::regex_match(s, res, opt1)) {
			int r = std::stoi(res[1].str());
			int g = std::stoi(res[2].str());
			int b = std::stoi(res[3].str());
			return *new ParamPix(r, g, b);
		}
		return *new ParamPix(s);
	}
	IntPixel& operator()(IntPixel& p, void* operand)override {
		if (!operand) throw(GOperand_Null());
		Pixel o = *(Pixel*)operand;
		p = o;
		return p;
	}
};