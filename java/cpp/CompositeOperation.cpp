#include "CompositeOperation.h"
#include <regex>
#include <fstream>
#include <vector>


std::map<std::string, Operation*> CompositeOperation::getOperation = {
	{"plus",new OperationPlus()},{"minus",new OperationMinus()},{"iminus",new OperationMinusInvers()}
	,{"mul",new OperationMul()},{"div",new OperationDiv()},{"idiv",new OperationDivInvers()},
	{"pow",new OperationPower()},{"log",new OperationLogarithm()},{"min",new OperationMin()},{"max",new OperationMax()},
	{"invers",new OperationInvers()},{"greyscale",new OperationGreyScale()},{"blackwhite",new OperationBlackWhite()},
	{"<>",new CompositeOperation()},{"SetAlpha",new OperationSetAlpha()}
};

/*

Izgled fajla:

kod_Operacije  (proizvoljno razmaka) operand(*ako je potrebno);
....
" Putanja do druge kompozitne operacije"
...
...
END

*/

CompositeOperation::CompositeOperation(const std::string file){
	std::ifstream f(file);

	if (!f) {
		std::cout << "Nema fajla " + file + "\n";
		return;
	}
	Operation* o;
	std::string op;
	std::string line;
	std::smatch res;
	std::regex opt1("([a-zA-z]+)[ ]*([0-9.]*);.*");
	std::regex opt2("<(.*)>;.*");
	std::getline(f, line);
	while (line!="END") {
		if (line[0] == '\\' && line[1] == '\\') {
			std::getline(f, line);
			continue;
		}
		if (line[0] != '<') {
			std::regex_match(line, res, opt1);
			//std::cout << res[1] << "\n";
			o = getOperation[res[1]];
			if (!o) {
				std::getline(f, line);
				continue;
			}
			if (o->GetNumOfOperand()) {
				if (res[2] == "") throw GCompose_Operation_Fail();
				operand.push_back(o->GetParam(res[2]).getRef());
			}
			F.push_back(o);
		}
		else {
			std::regex_match(line, res, opt2);
			o = new CompositeOperation(res[1]);
			F.push_back(o);
		}
		std::getline(f, line);
	}
	f.close();
}

int CompositeOperation::GetNumOfOperand() const{
	return 0;
}

IntPixel & CompositeOperation::operator()(IntPixel & p, void *) {
	Operation* o;
	void* v;
	auto x = operand.begin();
	for (auto& o : F) {
		v = nullptr;
		//std::cout << o->GetName() << "\n";
		if (o->GetNumOfOperand()) {
			v = *x++;
		}
		o->operator()(p, v);
	}
	return p;
}
ParamNull& CompositeOperation::GetParam(const std::string&)const { return *new ParamNull(); }