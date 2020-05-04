#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Layer.h>
#include <SelectionSet.h>
#include <SelectionObject.h>
#include <RectSelection.h>
#include <string>
#include <Operation.h>
#include <PredefineOperation.h>
#include <CompositeOperation.h>
#include <Bitmap.h>
#include <vector>
#include <utility>
#include "ImageLoader.h"



class Project {
	std::vector<Layer*> l;
	std::vector<SelectionSet*> s;
	std::vector<bool> active;
	Layer crtanje = *new Layer(1, 1, Pixel(0, 0, 0, 0));

	int width = 1;
	int height = 1;
	int ForDraw = 0;


	Pixel ePixel(int, int);


public:
	Project();
	Project(const std::string& path);
	~Project() {
		clear();
	}
	void ExportBMP(const std::string&);

	Layer& GetForDraw() { return crtanje; }
	void addLayer(Layer&);
	void Draw(const std::string& path);
	void DelLayer(int rb);
	void ExportLayer(const std::string& s, int br);
	void ReloadSurface();
	void SetForDraw(int a);
	const int ForDrawNum()const { return ForDraw; }
	void addLayer(const std::string s, Layer& l);
	void addLayer(const std::string s, int num, int x, int y);
	int NumOFLayers() { return l.size(); }
	void addSelection(SelectionSet* s, SelectionObject* so, int i);
	void SelectionsPrint();
	void mediana(int i);
	void changeActive(int r);
	void doOperation(int i, Operation& o, void* operand);
	void doOperationOnSelection(Operation& o, void* operand, int numsel, int numlej);
	void clear();
	void save(std::string path, std::string name);
	void printActive();
};
