#include "SelectionObject.h"

void SelectionObject::doOperation(Layer & l, Operation & op, void* operand) {
	begin();
	while (!end()) {
		l.doOperationOnPixel(current().first, current().second, op, operand);
		next();
	}
}