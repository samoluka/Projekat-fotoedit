#pragma once
#include <iostream>


class GAlpha_domen {
public:
	friend std::ostream& operator<<(std::ostream& os, const GAlpha_domen& g) {
		os << "Parametar alpha mora da bude izmedju 0 i 100...";
		return os;
	}
};
class GDim_domen {
public:
	friend std::ostream& operator<<(std::ostream& os, const GDim_domen& g) {
		os << "Parametar dimenzije mora da bude veci od 0...";
		return os;
	}
};

class GIndex {
public:
	friend std::ostream& operator<<(std::ostream& os, const GIndex& g) {
		os << "Indeks nije u okviru sirine i duzine zadatkog sloja";
		return os;
	}
};

class GOperand_Null {
public:
	friend std::ostream& operator<<(std::ostream& os, const GOperand_Null& g) {
		os << "los operand";
		return os;
	}
};
class GOperand_Number {
public:
	friend std::ostream& operator<<(std::ostream& os, const GOperand_Number& g) {
		os << "nedovoljno operatora";
		return os;
	}
};

class GCompose_Operation_Fail{
public:
	friend std::ostream& operator<<(std::ostream& os, const GCompose_Operation_Fail& g) {
		os << "Fajl operacije je korumpiran";
		return os;
	}
};