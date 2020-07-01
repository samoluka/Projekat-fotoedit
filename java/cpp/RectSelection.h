#pragma once
#include "SelectionObject.h"
class RectSelection :public SelectionObject {
	
	std::pair<int, int> curr;
protected:
	int finished;
	void begin();
	void next();
	bool end();
	std::pair<int, int> current();
	void stampa(std::ostream& os)const override {
		os << "Pocetne koordinate : (" << i << "," << j << ")\n" << "Sirina: " << width << "\nDuzina: " << height;
	}
public:
	int i, j, width, height;
	RectSelection(int, int, int, int);
};

