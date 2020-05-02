#define _CRT_SECURE_NO_WARNINGS
#include "SDLMy.h"
#include <thread>
#include <iostream>
#include "Pixel.h"
#include <vector>
#include "Layer.h"
#include "Bitmap.h"
#include <chrono>
#include <ctime>
#include "PredefineOperation.h"
#include "CompositeOperation.h"
#include "SelectionSet.h"
#include "RectSelection.h"
#include "Project.h"
/*
std::string source1 = "source_image/Velika.bmp";
std::string source2 = "source_image/image4-32bit.bmp";
std::string tmp = "tmp/tmp.bmp";
std::string l[6] = { "tmp/l1.bmp","tmp/l2.bmp","tmp/l3.bmp","tmp/l4.bmp","tmp/l5.bmp","tmp/l6.bmp" };

std::string opt = "opt/opt.opt";
uint64_t timeSinceEpochMillisec() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void crtanje(SDLMY* s) {
	s->SDLmain();
}


void ispis_prvi() {
	std::cout << "1. Prazan projekat\n2. Ucitaj projekat iz fajla\n3. Napusti program\n//////////////////\n";
}

int obrada_prva(Project& p) {
	int komanda;
	Project p2;
	std::string path;
	ispis_prvi();
	std::cin >> komanda;
	switch (komanda) {
	case 0:
		return 0;
	case 1:
		p.clear();
		break;
	case 2:
		p.clear();
		std::cout << "Unesi putanju do fajla projekta\n";
		std::cin >> path;
		p = Project(path);
		
		break;
	default:
		p.clear();
		break;
	}
	return 1;
}

void ispis_drugi() {
	std::cout << "1. Dodaj sloj \n2.Dodaj selekciju \n3.Pogledaj aktivnost selekcija \n4.Promeni aktivnost sloja\n";
	std::cout << "5.Uradi operaciju na sloju \n6.Uradi operaciju na selekciji \n7.Dodaj sliku na sloj \n8.Obrisi sloj ";
	std::cout << "\n9. Promeni prikaz \n10.Eksportuj projekat kao sliku \n11.Sacuvaj projekat ";
	std::cout << "\n0.Povratak na pocetni meni\n//////////////////\n";
}
std::map<int, Operation*> getOperation = {
	{1,new OperationPlus()},{2,new OperationMinus()},{3,new OperationMinusInvers()}
	,{4,new OperationMul()},{5,new OperationDiv()},{6,new OperationDivInvers()},
	{7,new OperationPower()},{8,new OperationLogarithm()},{9,new OperationMin()},{10,new OperationMax()},
	{11,new OperationInvers()},{12,new OperationGreyScale()},{13,new OperationBlackWhite()},{16,new OperationABS()},
	{17,new OperationSetAlpha()}
};
void ispis_operacija_meni() {
	std::cout << "1. Plus \n2. Minus \n3. Inverzni Minus \n4. Mnozenje \n5. Deljenje \n6. Inverzno deljenje";
	std::cout << "\n7. Stepenovanje \n8. Logaritam \n9. Na minimum: \n10. Na maksimum \n11. Inverzija \n12. Sivo";
	std::cout << "\n13. Crno-belo \n14. Medijana \n15. Kompozitna f-ja\n16. Apsolutna vrednost \n17.Postavi prozirnost\n";
}
void operacija_meni(Project& p, int numsloj) {
	int komanda;
	ispis_operacija_meni();
	std::cin >> komanda;
	std::string operand;

	if (komanda == 14) {
		p.mediana(numsloj);
		return;
	}
	if (komanda < 0 || komanda > 17) return;
	Operation* o = nullptr;
	void* v = nullptr;
	if (komanda == 15) {
		std::cout << "Unesite putanju do kompositne operacije:\n";
		std::cin >> operand;
		o = new CompositeOperation(operand);
	}
	else {
		o = getOperation[komanda];
		if (o->GetNumOfOperand()) {
			std::cout << "Unesite operand operacije:\n";
			std::cin >> operand;
		}
		v = o->GetParam(operand).getRef();
	}
	p.doOperation(numsloj, *o, v);
}

void operacija_meni(Project& p, int numsloj, int numselekcije) {
	int komanda;
	ispis_operacija_meni();
	std::cin >> komanda;
	std::string operand;

	if (komanda == 14) {
		p.mediana(numsloj);
		return;
	}
	if (komanda < 0 || komanda > 15) return;
	Operation* o = nullptr;
	void* v = nullptr;
	if (komanda == 15) {
		std::cout << "Unesite putanju do kompositne operacije:\n";
		std::cin >> operand;
		o = new CompositeOperation(operand);
	}
	else {
		o = getOperation[komanda];
		if (o->GetNumOfOperand()) {
			std::cout << "Unesite operand operacije:\n";
			std::cin >> operand;
		}
		v = o->GetParam(operand).getRef();
	}
	p.doOperationOnSelection(*o, v, numselekcije, numsloj);
}

int obrada_druga(Project& p, SDLMY* s) {
	int komanda;
	int opcija;
	int x, y, w, h;
	p.ExportLayer(l[0], 0);
	p.ExportLayer(l[1], 1);
	p.ExportLayer(l[2], 2);
	p.ExportLayer(l[3], 3);
	p.ExportLayer(l[4], 4);
	p.ExportLayer(l[5], 5);
	p.ReloadSurface();
	p.Draw(s->file);
	s->change[0] = 1;
	s->change[1] = 1;
	s->change[2] = 1;
	s->change[3] = 1;
	s->change[4] = 1;
	s->change[5] = 1;
	s->changeg = 1;
	std::string path;
	std::string name;
	ispis_drugi();
	std::cin >> komanda;
	while (1) {
		switch (komanda) {
		case 0:
			p.clear();
			p.ExportLayer(s->file, 1);
			for (int i = 0; i < 6; i++) {
				p.ExportLayer(l[i], i);
				s->change[i] = 1;
			}
			s->changeg = 1;
			return 0;
		case 1:
			std::cout << "Unesite path do slike za inicijalizaciju sloja(0 za prazan sloj):\n";
			std::cin >> path;
			if (path == "0") {
				std::cout << "Unesite visinu i sirinu:\n";
				std::cin >> h >> w;
				p.addLayer(*new Layer(h, w,*new Pixel(0, 0, 0, 255)));
				break;
			}
			p.addLayer(path, *new Layer());
			p.Draw(s->file);
			p.ExportLayer(l[p.NumOFLayers() - 1], p.NumOFLayers() - 1);
			if (p.NumOFLayers() <= 6)
				s->change[p.NumOFLayers() - 1] = 1;
			s->changeg = 1;
			break;
		case 2:
			std::cout << "Unesite redni broj skupa selekcija u koji zelite da dodate selekciju(-1 za novi skup):\n";
			std::cin >> opcija;
			std::cout << "Unesite pocetne koordinate:\n";
			std::cin >> x >> y;
			std::cout << "Unesite sirinu selekcije:\n";
			std::cin >> w;
			std::cout << "Unesite visinu selekcije:\n";
			std::cin >> h;
			p.addSelection(new SelectionSet(), new RectSelection(x, y, h, w), opcija);
			break;
		case 3:
			p.SelectionsPrint();
			break;
		case 4:
			std::cout << "Unesite redni broj sloja kome menjate aktivnost:\n";
			std::cin >> opcija;
			p.changeActive(opcija);
			break;
		case 5:
			std::cout << "Unesite redni broj sloja na kojem primenjujete operaciju(-1 za sve slojeve):\n";
			std::cin >> opcija;
			operacija_meni(p, opcija);
			if (opcija >=0 && opcija <= 5) {
				p.ExportLayer(l[opcija], opcija);
				s->change[opcija] = 1;
			}
			else if (opcija == -1) {
				for (int i = 0; i < 6; i++) {
					p.ExportLayer(l[i], i);
					s->change[i] = 1;
				}
			}
			if (opcija == p.ForDrawNum() || opcija == -1) {
				p.ReloadSurface();
				p.Draw(s->file);
			}
			s->changeg = 1;
			break;
		case 6:
			std::cout << "Unesite redni broj skupa selekcija na kojem primenjujete operaciju:\n";
			std::cin >> opcija;
			std::cout << "Unesite redni broj sloja na kojem primenjujete operaciju:(-1 za sve slojeve):\n";
			std::cin >> x;
			operacija_meni(p, x, opcija);
			if (opcija >= 0 && opcija <= 5) {
				p.ExportLayer(l[opcija], opcija);
				s->change[opcija] = 1;
			}
			else if (opcija == -1) {
				for (int i = 0; i < 6; i++) {
					p.ExportLayer(l[i], i);
					s->change[i] = 1;
				}
			}
			if (opcija == p.ForDrawNum() || opcija == -1) {
				p.ReloadSurface();
				p.Draw(s->file);
			}
			s->changeg = 1;
			break;
		case 7:
			std::cout << "Unesi redni broj sloja:\n";
			std::cin >> opcija;
			std::cout << "Unesi putanju do slike:\n";
			std::cin >> path;
			std::cout << "Unesi pocetne koordinate slike:\n";
			std::cin >> x >> y;
			p.addLayer(path, opcija, x, y);
			if (opcija >= 0 && opcija < 6) {
				p.ExportLayer(l[opcija], opcija);
				s->change[opcija] = 1;
			}
			if (opcija == p.ForDrawNum()) {
				p.ReloadSurface();
				p.Draw(s->file);
			}
			s->changeg = 1;
			break;
		case 8:
			std::cout << "Unesite redni broj sloja koji zelite da obrisete:\n";
			std::cin >> opcija;
			p.DelLayer(opcija);
			if (opcija == p.ForDrawNum() || p.ForDrawNum() + 1 == p.NumOFLayers()) {
				p.ReloadSurface();
				p.Draw(s->file);
			}
			for (;opcija <= 5;opcija++) {
				p.ExportLayer(l[opcija], opcija);
				s->change[opcija] = 1;
			}
			s->changeg = 1;
			break;
		case 9:
			std::cout << "Unesite redni broj sloja za prikaz(-1 za ceo projekat):\n";
			std::cin >> opcija;
			p.SetForDraw(opcija);
			std::cout << "Renderujem sliku...\n";
			p.ReloadSurface();
			p.Draw(s->file);
			s->changeg = 1;
			std::cout << "Spreman\n";
			break;
		case 10:
			std::cout << "Unesite putanju do izlaznog fajla:\n";
			std::cin >> path;
			p.ExportBMP(path);
			break;
		case 11:
			std::cout << "Unesite putanju do izlaznog fajla:\n";
			std::cin >> path;
			std::cout << "Unesite ime projekta:\n";
			std::cin >> name;
			p.save(path, name);
			break;
		default:
			break;
		}
		ispis_drugi();
		std::cin >> komanda;
	}
}


int main(int argc, char *argv[]) {
	Project p;
	p.Draw(tmp);
	p.ExportLayer(l[0], 0);
	p.ExportLayer(l[1], 1);
	p.ExportLayer(l[2], 2);
	p.ExportLayer(l[3], 3);
	p.ExportLayer(l[4], 4);
	p.ExportLayer(l[5], 5);
	SDLMY* s = new SDLMY();
	s->file = tmp;
	s->l1 = l[0];
	s->l2 = l[1];
	s->l3 = l[2];
	s->l4 = l[3];
	s->l5 = l[4];
	s->l6 = l[5];
	std::thread t(crtanje, s);
	while (1) {
		if (!obrada_prva(p)) {
			s->finished = 1;
			t.join();
			return 0;
		}
		obrada_druga(p, s);
	}
	return 0;
}*/
#include "Pam.h"

int main(int argc, char *argv[]) {
	std::string path = "image2-32bit.pam";
	Layer l;
	Pam::load(path,l);
	Pam::out("pam eksport.pam", l);
	BMP::ExportBMP("medjustanje.bmp",l);
	Pam::load("pam eksport.pam", l);
	BMP::ExportBMP("proba pam krajnje.bmp", l);
	return 0;
}