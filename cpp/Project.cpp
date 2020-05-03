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
	b = (p.GetBlue()*(p.GetAlpha() / 100.) + ispod.GetBlue()*(ispod.GetAlpha() / 100.) * (1 - (p.GetAlpha() / 100.)));
	g = (p.GetGreen()*(p.GetAlpha() / 100.) + ispod.GetGreen()*(ispod.GetAlpha() / 100.) * (1 - (p.GetAlpha() / 100.)));
	a = (p.GetAlpha()*(p.GetAlpha() / 100.) + ispod.GetAlpha()*(ispod.GetAlpha() / 100.) * (1 - (p.GetAlpha() / 100.)));
	p = Pixel(r, g, b, a);
	return p;
}



Project::Project() {
	crtanje.SetWidth(1);
	crtanje.SetHeight(1);
	crtanje.GetMatrix().resize(1);
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


void Project::Draw(const std::string& path) {
	ImageLoader::out(path, crtanje);
}

void Project::DelLayer(int rb) {
	l.erase(l.begin() + rb);
	if (rb == l.size() || ForDraw + 1 == l.size()) ForDraw--;
	if (rb == 0 && ForDraw == 0) crtanje = *l[0];
}

void Project::ExportLayer(const std::string& s, int br) {
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

void Project::ReloadSurface() {
	if (ForDraw < -1 || ForDraw >= l.size()) return;
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

void Project::SetForDraw(int a) {
	if (a >= l.size() || a < -1) return;
	ForDraw = a;
}

void Project::addLayer(const std::string s, Layer& l) {
	ImageLoader::in(s, l, 0, 0);
	addLayer(l);
}


void Project::addLayer(const std::string s, int num, int x, int y) {
	if (num >= 0 && num < l.size())
		ImageLoader::in(s, *l[num], x, y);
}

void Project::addSelection(SelectionSet* s, SelectionObject* so, int i) {
	//if (i < -1 || i >= this->s.size()) return;
	if (i == -1) {
		this->s.push_back(s);
		this->s.back()->AddSelection(so);
		return;
	}
	this->s[i]->AddSelection(so);
}

void Project::SelectionsPrint() {
	int i = 0;
	for (auto& x : s) {
		std::cout << "Selekcija " << i << ":\n" << *x;
		i++;
	}
}
void Project::mediana(int i) {
	for (auto& x : l) {
		x->median();
	}
}
void Project::changeActive(int r) {
	if (r >= active.size()) return;
	active[r] = !active[r];
}
void Project::doOperation(int i, Operation& o, void* operand) {
	if (i == -1) {
		for (auto& x : l) {
			x->operator()(o, operand);
		}
		return;
	}
	if (i >= l.size()) return;
	l[i]->operator()(o, operand);
}
void Project::doOperationOnSelection(Operation& o, void* operand, int numsel, int numlej) {
	if (numsel < 0 || numsel >= s.size()) return;
	if (numlej < -1 || numlej >= l.size()) return;
	if (numlej == -1) {
		for (auto& x : l)
			s[numsel]->doOperation(*x, o, operand);
		return;
	}
	s[numsel]->doOperation(*l[numlej], o, operand);
}
void Project::clear() {
	l.clear();
	s.clear();
	active.clear();
	crtanje.SetWidth(100);
	crtanje.SetHeight(100);
	crtanje.GetMatrix().resize(100 * 100);
	width = 0;
	height = 0;
}
void Project::save(std::string path, std::string name) {
	std::string proj = path + "/" + name + ".proj";
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
