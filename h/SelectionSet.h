#pragma once
#include <vector>
#include "Operation.h"
#include "Layer.h"
#include "SelectionObject.h"
#include <set>
class SelectionSet{
	std::set<SelectionObject*> s;

	friend bool operator==(const SelectionSet& s1, const SelectionSet& s2) {
		return &s1 == &s2;
	}
public:
	auto begin() { return s.begin(); }
	auto end() { return s.end(); }
	void doOperation(Layer&, Operation&, void* = nullptr)const;
	void AddSelection(SelectionObject*);
	void RemoveSelection(SelectionObject*);
	friend std::ostream& operator<<(std::ostream& os, SelectionSet& obj);
};