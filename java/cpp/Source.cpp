#define _CRT_SECURE_NO_WARNINGS

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cctype>
#include "Pixel.h"
#include "Layer.h"
#include "Bitmap.h"
#include "PredefineOperation.h"
#include "CompositeOperation.h"
#include "SelectionSet.h"
#include "RectSelection.h"
#include "Project.h"
#include "Pam.h"
#include "ImageLoader.h"



int main(int argc, char *argv[]) {
	Project p;
	if (argc == 5) {
		std::ifstream f(argv[1]);
		std::ifstream h(argv[4]);
		std::ifstream s(argv[3]);
		int x, y, dx, dy;
		int ima = 0;
		CompositeOperation* o = new CompositeOperation(argv[2]);
		std::string linein;
		std::string lineout;
		std::getline(f, linein);
		int height;
		s >> height;
		std::cout << height << "\n";
		while (!s.eof() && height != -1) {
			s >> x >> y >> dx >> dy;
			if (!ima) {
				ima = 1;
				SelectionSet* sel = new SelectionSet();
				p.addSelection(sel, new RectSelection(height - y,x, dx, dy), -1);
				/*SelectionSet* sel2 = new SelectionSet();
				p.addSelection(sel2, new RectSelection(height - y, x, dx, dy), -1);*/
			}
			else {
				p.addSelection(nullptr, new RectSelection(height - y,x, dx, dy), 0);
				//p.addSelection(nullptr, new RectSelection(height - y, x, dx, dy), 1);
			}
		}
		std::cout << "\n\n\n\n";
		p.SelectionsPrint();
		std::cout << "\n\n\n\n\n";
		s.close();
		int k = 0;
		while (std::getline(h, lineout)) {
			Layer l;
			ImageLoader::in(linein, l);
			if (ima) {
				std::cout << "Selekcije\n";
				std::vector<int> old;
				for (auto& x : p.s[0]->s) {
					RectSelection* sl = (RectSelection*)x;
					old.push_back(sl->i);
					sl->i = l.GetHeight() - sl->i;
				}
				p.SelectionsPrint();
				p.addLayer(l);
				p.doOperationOnSelection(*o, nullptr, 0, -1);
				int br = 0;
				for (auto& x : p.s[0]->s) {
					RectSelection* sl = (RectSelection*)x;
					sl->i = old[br];
					br++;
				}
				k = 1;
			}
			else {
				l(*o);
			}
			std::cout << lineout << "\n";
			ImageLoader::out(lineout, l);
			p.DelLayer(0);
			std::getline(f, linein);
		}
		f.close();
		h.close();
		return 0;
	}
	if (argc == 3) {
		std::ifstream f(argv[1]);
		std::string line;
		std::getline(f, line);
		while (!f.eof()) {
			Layer* l = new Layer();
			ImageLoader::in(line, *l);
			p.addLayer(*l);
			std::getline(f, line);
		}
		p.ExportBMP(argv[2]);
	}
}
