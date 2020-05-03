#include "Project.h"
#include <regex>
Pixel Project::ePixel(int i, int pixnum) {
	if (i == -1) return Pixel(0, 0, 0, 0);
	//if (!active[i]) return Pixel(0, 0, 0, 0);
	Pixel p;
	if (pixnum >= l[i]->GetMatrix().size()) p = Pixel(0, 0, 0, 0);
	else p = l[i]->GetMatrix()[pixnum];
	Pixel ispod = ePixel(i - 1, pixnum);
	float r, g, b, a;
	r = (p.GetRed()*(p.GetAlpha() / 100.) + ispod.GetRed()*(ispod.GetAlpha() / 100.) * (1 - (p.GetAlpha() / 100.)));
	b=(p.GetBlue()*(p.GetAlpha() / 100.) + ispod.GetBlue()*(ispod.GetAlpha() / 100.) * (1 - (p.GetAlpha() / 100.)));
	g=(p.GetGreen()*(p.GetAlpha() / 100.) + ispod.GetGreen()*(ispod.GetAlpha() / 100.) * (1 - (p.GetAlpha() / 100.)));
	a=(p.GetAlpha()*(p.GetAlpha() / 100.) + ispod.GetAlpha()*(ispod.GetAlpha() / 100.) * (1 - (p.GetAlpha() / 100.)));
	p = Pixel(r, g, b, a);
	return p;
}

Project::Project(const std::string & path) {
	std::ifstream f(path);
	std::string input;

	std::regex opt1("WIDTH:([0-9]*)");
	std::regex opt2("HEIGHT:([0-9]*)");
	std::regex opt3("SIZE:([0-9]*)");
	std::smatch res;
	f >> input;
	std::regex_match(input, res, opt1);
	input = (std::string)res[1];
	width = std::atoi(input.c_str());

	f >> input;
	std::regex_match(input, res, opt2);
	input = (std::string)res[1];
	height = std::atoi(input.c_str());
	f >> input;
	std::regex_match(input, res, opt3);
	input = (std::string)res[1];
	int size = std::atoi(input.c_str());
	Layer* l = new Layer[size];
	for (int i = 0; i < size; i++) {

		f >> input;
		ImageLoader::in(input, l[i]);
		this->l.push_back(&l[i]);
		this->active.push_back(1);
		std::cout << "Ucitana slika\n";
	}

	ForDraw = 0;
	f.close();
}

void Project::ExportBMP(const std::string &s) {
	Layer e;
	e.GetMatrix().resize(width*height);
	e.SetHeight(height);
	e.SetWidth(width);
	for (int i = 0; i < e.GetMatrix().size(); i++) {
		e.GetMatrix()[i] = ePixel(l.size() - 1, i);
	}
	ImageLoader::out(s, e);
}

void Project::addLayer(Layer &l) {
	if (this->l.empty()) {
		crtanje = l;
	}
	this->l.push_back(&l);
	active.push_back(1);
	int lh = l.GetHeight(), lw = l.GetWidth(), h = height, w = width;
	if (width >= l.GetWidth())
		lw = w;
	else
		w = lw;
	if (height >= l.GetHeight()) 
		lh = h;
	else 
		h = lh;
	l.resize(lh, lw);
	for (auto& x : this->l) x->resize(h, w);
	width = w;
	height = h;

}