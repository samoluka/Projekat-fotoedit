#define _CRT_SECURE_NO_WARNINGS

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cctype>
#include "Pixel.h"
#include "SDLMy.h"
#include "Layer.h"
#include "Bitmap.h"
#include "PredefineOperation.h"
#include "CompositeOperation.h"
#include "SelectionSet.h"
#include "RectSelection.h"
#include "Project.h"
#include "Pam.h"
#include "ImageLoader.h"

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

bool is_number(std::string& s){
	int i = s[0] == '-' ? 1 : 0;
	for (i;i < s.length(); i++) {
		if (!isdigit(s[i])) return false;
	}
	return true;
}

void ispis_prvi() {
	std::cout << "1. Prazan projekat\n2. Ucitaj projekat iz fajla\n0. Napusti program\n//////////////////\n";
}

int obrada_prva(Project& p) {
	std::string s;
	Project p2;
	std::string path;
	ispis_prvi();
	std::getline(std::cin, s);
	int komanda = isdigit(s[0]) ? std::stoi(s) : 3;
	switch (komanda) {
	case 0:
		return 0;
	case 1:
		p.clear();
		break;
	case 2:
		p.clear();
		std::cout << "Unesi putanju do fajla projekta\n";
		std::getline(std::cin, path);
		p = * new Project(path);
		
		break;
	default:
		p.clear();
		break;
	}
	return 1;
}

void ispis_drugi() {
	std::cout << "1. Dodaj sloj \n2.Dodaj selekciju \n3.Pogledaj selekcije \n4.Promeni aktivnost sloja\n";
	std::cout << "5.Uradi operaciju na sloju \n6.Uradi operaciju na selekciji \n7.Dodaj sliku na sloj \n8.Obrisi sloj ";
	std::cout << "\n9. Promeni prikaz \n10.Eksportuj projekat kao sliku \n11.Sacuvaj projekat \n12.Pogledaj aktivnost slojeva ";
	std::cout << "\n0.Povratak na pocetni meni\n//////////////////\n";
}
std::map<int, Operation*> getOperation = {
	{1,new OperationPlus()},{2,new OperationMinus()},{3,new OperationMinusInvers()}
	,{4,new OperationMul()},{5,new OperationDiv()},{6,new OperationDivInvers()},
	{7,new OperationPower()},{8,new OperationLogarithm()},{9,new OperationMin()},{10,new OperationMax()},
	{11,new OperationInvers()},{12,new OperationGreyScale()},{13,new OperationBlackWhite()},{16,new OperationABS()},
	{17,new OperationSetAlpha()},{18,new OperationSetColor()}
};
void ispis_operacija_meni() {
	std::cout << "1. Plus \n2. Minus \n3. Inverzni Minus \n4. Mnozenje \n5. Deljenje \n6. Inverzno deljenje";
	std::cout << "\n7. Stepenovanje \n8. Logaritam \n9. Na minimum: \n10. Na maksimum \n11. Inverzija \n12. Sivo";
	std::cout << "\n13. Crno-belo \n14. Medijana \n15. Kompozitna f-ja\n16. Apsolutna vrednost \n17.Postavi prozirnost\n";
	std::cout << "18. Oboj\n";
}
void operacija_meni(Project& p, int numsloj) {
	std::string s;
	ispis_operacija_meni();
	std::string operand;

	std::getline(std::cin, s);
	int komanda = isdigit(s[0]) ? std::stoi(s) : 19;

	if (komanda == 14) {
		p.mediana(numsloj);
		return;
	}
	if (komanda < 0 || komanda > 18) return;
	Operation* o = nullptr;
	void* v = nullptr;
	if (komanda == 15) {
		std::cout << "Unesite putanju do kompositne operacije:\n";
		std::getline(std::cin, operand);
		o = new CompositeOperation(operand);
	}
	else {
		o = getOperation[komanda];
		if (o->GetNumOfOperand()) {
			std::cout << "Unesite operand operacije:\n";
			std::getline(std::cin, operand);
		}
		v = o->GetParam(operand).getRef();
	}
	try {
		p.doOperation(numsloj, *o, v);
	}
	catch(GOperand_Null& g){
		std::cout << g << std::endl;
	}
}

void operacija_meni(Project& p, int numsloj, int numselekcije) {
	std::string s;
	ispis_operacija_meni();
	

	std::getline(std::cin, s);
	int komanda = isdigit(s[0]) ? std::stoi(s) : 19;

	std::string operand;

	if (komanda == 14) {
		p.mediana(numsloj);
		return;
	}
	if (komanda < 0 || komanda > 18) return;
	Operation* o = nullptr;
	void* v = nullptr;
	if (komanda == 15) {
		std::cout << "Unesite putanju do kompositne operacije:\n";
		std::getline(std::cin, operand);
		o = new CompositeOperation(operand);
	}
	else {
		o = getOperation[komanda];
		if (o->GetNumOfOperand()) {
			std::cout << "Unesite operand operacije:\n";
			std::getline(std::cin, operand);
		}
		v = o->GetParam(operand).getRef();
	}
	try {
		p.doOperationOnSelection(*o, v, numselekcije, numsloj);
	}
	catch (GOperand_Null& g) {
		std::cout << g << std::endl;
	}
}

int obrada_druga(Project& p, SDLMY* s) {
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

	std::string str;

	std::getline(std::cin, str);
	int komanda = isdigit(str[0]) ? std::stoi(str) : 50;


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
			std::getline(std::cin, path);
			if (path == "0") {
				std::cout << "Unesite visinu:\n";
				std::getline(std::cin, str);
				w = isdigit(str[0]) ? std::stoi(str) : 1;

				std::cout << "Unesite sirinu:\n";
				std::getline(std::cin, str);
				h = isdigit(str[0]) ? std::stoi(str) : 1;
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
			std::getline(std::cin, str);
			opcija = is_number(str) ? std::stoi(str) : -2;

			std::cout << "Unesite x koordinatu:\n";
			std::getline(std::cin, str);
			x = isdigit(str[0]) ? std::stoi(str) : 0;
			std::cout << "Unesite y koordinatu:\n";
			std::getline(std::cin, str);
			y = isdigit(str[0]) ? std::stoi(str) : 0;

			std::cout << "Unesite sirinu selekcije:\n";
			std::getline(std::cin, str);
			w = isdigit(str[0]) ? std::stoi(str) : 0;
			std::cout << "Unesite visinu selekcije:\n";
			std::getline(std::cin, str);
			h = isdigit(str[0]) ? std::stoi(str) : 0;

			p.addSelection(new SelectionSet(), new RectSelection(y, x, h, w), opcija);
			break;
		case 3:
			p.SelectionsPrint();
			break;
		case 4:
			std::cout << "Unesite redni broj sloja kome menjate aktivnost:\n";
			std::getline(std::cin, str);
			opcija = isdigit(str[0]) ? std::stoi(str) : -1;
			p.changeActive(opcija);
			break;
		case 5:
			std::cout << "Unesite redni broj sloja na kojem primenjujete operaciju(-1 za sve slojeve):\n";
			std::getline(std::cin, str);
			opcija = is_number(str) ? std::stoi(str) : -2;
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
			std::getline(std::cin, str);
			opcija = isdigit(str[0]) ? std::stoi(str) : -1;

			std::cout << "Unesite redni broj sloja na kojem primenjujete operaciju:(-1 za sve slojeve):\n";
			std::getline(std::cin, str);
			x = is_number(str) ? std::stoi(str) : -2;

			operacija_meni(p, x, opcija);
			if (x >= 0 && x <= 5) {
				p.ExportLayer(l[x], x);
				s->change[x] = 1;
			}
			else if (x == -1) {
				for (int i = 0; i < 6; i++) {
					p.ExportLayer(l[i], i);
					s->change[i] = 1;
				}
			}
			if (x == p.ForDrawNum() || x == -1) {
				p.ReloadSurface();
				p.Draw(s->file);
			}
			s->changeg = 1;
			break;
		case 7:
			std::cout << "Unesi redni broj sloja:\n";
			std::getline(std::cin, str);
			opcija = isdigit(str[0]) ? std::stoi(str) : -1;

			std::cout << "Unesi putanju do slike:\n";
			std::getline(std::cin, path);

			std::cout << "Unesite x koordinatu:\n";
			std::getline(std::cin, str);
			x = isdigit(str[0]) ? std::stoi(str) : 0;
			std::cout << "Unesite y koordinatu:\n";
			std::getline(std::cin, str);
			y = isdigit(str[0]) ? std::stoi(str) : 0;

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
			std::getline(std::cin, str);
			opcija = isdigit(str[0]) ? std::stoi(str) : -1;

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
			std::getline(std::cin, str);
			opcija = is_number(str) ? std::stoi(str) : -2;

			p.SetForDraw(opcija);
			std::cout << "Renderujem sliku...\n";
			p.ReloadSurface();
			p.Draw(s->file);
			s->changeg = 1;
			std::cout << "Spreman\n";
			break;
		case 10:
			std::cout << "Unesite putanju do izlaznog fajla:\n";
			std::getline(std::cin, path);
			p.ExportBMP(path);
			break;
		case 11:
			std::cout << "Unesite putanju do izlaznog fajla:\n";
			std::getline(std::cin, path);
			std::cout << "Unesite ime projekta:\n";
			std::getline(std::cin, name);
			p.save(path, name);
			break;
		case 12:
			p.printActive();
			break;
		default:
			break;
		}
		ispis_drugi();
		std::getline(std::cin, str);
		komanda = isdigit(str[0]) ? std::stoi(str) : 50;
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
}
