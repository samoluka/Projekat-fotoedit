#include "SelectionSet.h"


void SelectionSet::doOperation(Layer& l, Operation& op, void* operand)const {
	for (auto& x : s) {
		x->doOperation(l, op, operand);
	}
}
void SelectionSet::AddSelection(SelectionObject* selection) {
	s.insert(selection);
}
void SelectionSet::RemoveSelection(SelectionObject* selection) {
	auto it = s.begin();
	while (it != s.end()) {
		if (*it == selection) it = s.erase(it);
		else it++;
	}
};

std::ostream & operator<<(std::ostream & os, SelectionSet & obj) {
	for (auto& x : obj.s) {
		os << *x << std::endl;
	}
	return os;
}
