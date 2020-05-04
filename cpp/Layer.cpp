#include "Layer.h"
#include "Bitmap.h"

void Layer::OK_Height(int height)throw(GDim_domen) {
	if (height < 0) throw GDim_domen();
}
void Layer::OK_Width(int width)throw(GDim_domen) {
	if (width < 0) throw GDim_domen();
}
bool Layer::OK_Cord(int i, int j)const {
	return (i >= 0 && i < height) && (j >= 0 && j < width);
}

const Pixel Layer::Mediana(int i, int j)const {
	int sumar = 0, sumag = 0, sumab = 0;
	int n = 0;
	for (int ii = -1;ii != 2; ii++) {
		for (int jj = -1;jj != 2; jj++) {
			if (OK_Cord(i + ii, j + jj)) {
				sumar += matrica[(i + ii)*width + j + jj].GetRed();
				sumag += matrica[(i + ii)*width + j + jj].GetGreen();
				sumab += matrica[(i + ii)*width + j + jj].GetBlue();
				n++;
			}
		}
	}
	return Pixel(sumar / n, sumag / n, sumab / n, 255);
}
Layer::Layer(int height, int width , Pixel P) {
	if (height <= 0) height = 1;
	if (width <= 0) width = 1;
	try {
		SetHeight(height);
	}
	catch (const GDim_domen & g) {
		std::cerr << g << std::endl;
		std::cerr << "Uzita je podrazumevana vrednost Heigth = 100" << std::endl;
		height = 100;
	}
	try {
		SetWidth(width);
	}
	catch (const GDim_domen & g) {
		std::cerr << g << std::endl;
		std::cerr << "Uzita je podrazumevana vrednost Width = 100" << std::endl;
		width = 100;
	}
	matrica.resize(this->height*this->width);
	
}


//set i get metode

void Layer::SetHeight(int height) {
	OK_Height(height);
	this->height = height;
}
void Layer::SetWidth(int width) {
	OK_Width(width);
	this->width = width;
}
void Layer::resize(int NewHeight, int NewWidth){

	if (NewWidth == width && NewHeight == height) return;
	if (NewWidth <= 0 || NewHeight <= 0) return;
	std::valarray<Pixel> n;
	n.resize(NewWidth*NewHeight);

	for (int i = 0; i<NewHeight; i++)
		for (int j = 0; j <NewWidth; j++) {
			n[i*NewWidth + j] = GetPixel(i, j);
		}
	matrica = n;
	height = NewHeight;
	width = NewWidth;

}

void Layer::median(){
	Pixel* boje = new Pixel[matrica.size()];
	for (int i = 0; i < matrica.size(); i++) {
		boje[i] = Mediana(i / width, i - width * (i / width));
	}
	for (int i = 0; i < matrica.size(); i++) {
		matrica[i].SetRed(boje[i].GetRed());
		matrica[i].SetGreen(boje[i].GetGreen());
		matrica[i].SetBlue(boje[i].GetBlue());
	}

}

void Layer::operator()(Operation & o, void * operand) {
	for (auto& x : matrica) {
		IntPixel p = x;
		x = o(p, operand);
	}
}

void Layer::doOperationOnPixel(int i, int j, Operation & o, void * operand) {
	if (!OK_Cord(i, j)) return;
	IntPixel p = matrica[i*width + j];
	matrica[i*width + j] = o(p, operand);
}
std::ostream & operator<<(std::ostream & os, Layer obj) {
	for (auto& x : obj.matrica) {
		os << x << " ";
	}
	return os;
}