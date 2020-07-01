#include "RectSelection.h"

void RectSelection::begin(){
	curr = std::make_pair(i, j);
	finished = 0;
}

void RectSelection::next(){
	curr.second = curr.second + 1;
	if (curr.second - j > width) {
		curr.second = j;
		curr.first--;
		if (i - curr.first > height) finished = 1;
	}
}

bool RectSelection::end(){
	return finished;
}
std::pair<int, int> RectSelection::current() {
	return curr;
}

RectSelection::RectSelection(int i, int j, int width, int height) {
	this->i = i;
	if (i < 0) this->i = 0;
	this->j = j;
	if (j < 0) this->j = 0;
	this->width = width;
	if (width < 0) this->width = 0;
	this->height = height;
	if (height < 0) this->height = 0;
}
