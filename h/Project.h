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



class Project{
	std::vector<Layer*> l;
	std::vector<SelectionSet*> s;
	std::vector<bool> active;
	Layer crtanje = *new Layer(1,1,Pixel(0,0,0,0));

	int width = 0;
	int height = 0;
	int ForDraw = 0;


	Pixel ePixel(int, int);


public:
	Project() {
		crtanje.SetWidth(1);
		crtanje.SetHeight(1);
		crtanje.GetMatrix().resize(1);
	};
	Project(const std::string&);
	void ExportBMP(const std::string&);

	Layer& GetForDraw() {
		return crtanje;
	}
	void addLayer(Layer&);
	void Draw(const std::string& path) {
		ImageLoader::out(path, crtanje);
	}
	void DelLayer(int rb) {
		l.erase(l.begin() + rb);
		if (rb == l.size() || ForDraw + 1 == l.size()) ForDraw--;
		if (rb == 0 && ForDraw == 0) crtanje = *l[0];
	}
	void ExportLayer(const std::string& s, int br) {
		if (br < 0 || br>5) return;
		if (br >= l.size()) {
			Layer e;
			e.SetWidth(1);
			e.SetHeight(1);
			e.GetMatrix().resize(1);
			ImageLoader::out(s, e);
			return;
		}
		ImageLoader::out(s, *l[br]);

	}
	void ReloadSurface() {
		if (ForDraw > -1) {
			crtanje = *l[ForDraw];
			return;
		}
		crtanje.GetMatrix().resize(width*height);
		crtanje.SetHeight(height);
		crtanje.SetWidth(width);
		for (int i = 0; i < crtanje.GetMatrix().size(); i++) {
			crtanje.GetMatrix()[i] = ePixel(l.size() - 1, i);
		}
	}
	void SetForDraw(int a) {
		ForDraw = a;
	}
	const int ForDrawNum()const {
		return ForDraw;
	}
	void addLayer(const std::string s, Layer& l) {
		ImageLoader::in(s, l, 0, 0);
		addLayer(l);
	};
	void addLayer(const std::string s, int num, int x, int y) {
		if (num >= 0 && num < l.size())
			ImageLoader::in(s, *l[num], x, y);
	};
	int NumOFLayers() {
		return l.size();
	}
	void addSelection(SelectionSet* s,SelectionObject* so, int i) {
		//if (i < -1 || i >= this->s.size()) return;
		if (i == -1){
			this->s.push_back(s);
			this->s.back()->AddSelection(so);
			return;
		}

		this->s[i]->AddSelection(so);
	}
	void SelectionsPrint() {
		int i = 0;
		for (auto& x : s) {
			std::cout << "Selekcija " << i << ":\n" << *x;
			i++;
		}
	};
	void mediana(int i) {
		for (auto& x : l) {
			x->median();
	}
	
	};
	void changeActive(int r) {
		if (r >= active.size()) return;
		active[r] = !active[r];
	}
	void doOperation(int i, Operation& o, void* operand) {
		if (i == -1) {
			for (auto& x : l) {
				x->operator()(o, operand);
			}
			return;
		}
		if (i >= l.size()) return;
		l[i]->operator()(o, operand);
	}
	void doOperationOnSelection(Operation& o, void* operand, int numsel, int numlej) {
		if (numsel<0 || numsel>=s.size()) return;
		if (numlej < -1 || numlej >= l.size()) return;
		if (numlej == -1) {
			for (auto& x : l)
				s[numsel]->doOperation(*x, o, operand);
			return;
		}
		s[numsel]->doOperation(*l[numlej], o, operand);
	}
	void init_from_file(std::string s) {};
	void clear() {
		l.clear();
		s.clear();
		active.clear();
		crtanje.SetWidth(100);
		crtanje.SetHeight(100);
		crtanje.GetMatrix().resize(100 * 100);
		width = 0;
		height = 0;
	}
	void save(std::string path,std::string name) {
		std::string proj = path+ "/" + name + ".proj";
		std::ofstream f(proj);
		f << "WIDTH:" << width << std::endl;
		f << "HEIGHT:" << height << std::endl;
		f << "SIZE:" << l.size() << std::endl;
		for (auto&x : l) {
			std::string lay;
			while (1) {
				int r = rand();
				lay = path + "/" + std::to_string(r) + ".bmp";
				FILE* pr = fopen(lay.c_str(), "rb");
				if (!pr) {
					break;
				}
				fclose(pr);
			}
			ImageLoader::out(lay, *x);
			f << lay << std::endl;
		}
		f.close();
	}
};

