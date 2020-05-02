#pragma once
#include "Operation.h"
#include <stack>
#include <map>
#include "PredefineOperation.h"
#include <vector>


class CompositeOperation :public Operation {


	std::vector<Operation*> F;
	std::vector<void*> operand;
	static std::map<std::string, Operation*> getOperation;
public:
	CompositeOperation() {};
	CompositeOperation(const std::string);

	int GetNumOfOperand()const override;
	std::string GetName()const { return "co"; };
	IntPixel& operator()(IntPixel&, void*);
	ParamNull& GetParam(const std::string&)const override;
};