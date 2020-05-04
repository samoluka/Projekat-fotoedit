#pragma once
#include "Pixel.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Greske.h"
#include <functional>
#include <valarray>
#include <array>
#include "Operation.h"
#include "SelectionObject.h"

class Layer {
private:

	static void OK_Height(int);
	static void OK_Width(int);
	bool OK_Cord(int, int)const;

	int height, width;
	std::valarray<Pixel> matrica;

	const Pixel Mediana(int i, int j)const;
public:

	Layer() :Layer(1,1, Pixel(0, 0, 0, 0)) {};
	Layer(int, int, Pixel);

	void SetHeight(int height);
	void SetWidth(int width);

	auto begin() { return std::begin(matrica); }
	auto end() { return std::end(matrica); }

	void resize(int NewHeight, int NewWidth);

	std::valarray<Pixel>& GetMatrix() { return matrica; };
	const Pixel& GetPixel(int i, int j)const { if (!OK_Cord(i, j)) return Pixel(0, 0, 0, 0); return matrica[i*width + j]; }
	void SetPixel(int i, int j, const Pixel& p) { if (!OK_Cord(i, j)) throw GDim_domen(); matrica[i*width + j] = p; };
	const int GetHeight()const { return height; }
	const int GetWidth()const { return width; }
	int transform(int i)const { return height - i; }
	void median();
	void operator()(Operation& o, void* operand = nullptr);
	friend std::ostream& operator<<(std::ostream& os, Layer obj);
	void doOperationOnPixel(int i, int j, Operation& o, void* operand = nullptr);

};