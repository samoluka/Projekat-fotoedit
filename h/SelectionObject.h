#pragma once
#include "Layer.h"
#include "Pixel.h"
#include "Operation.h"
#include <utility> 
#include <iostream>
class Layer;

class SelectionObject {
protected:
	virtual void begin() = 0;
	virtual void next() = 0;
	virtual bool end() = 0;
	virtual std::pair<int, int> current() = 0;
	virtual void stampa(std::ostream& os)const = 0;
public:
	virtual void doOperation(Layer&, Operation&,void*);
	friend bool operator == (const SelectionObject& s1, const SelectionObject& s2) {
		return &s1 == &s2;
	}
	friend std::ostream& operator<<(std::ostream& os, const SelectionObject& obj) {
		obj.stampa(os);
		return os;
	}
};