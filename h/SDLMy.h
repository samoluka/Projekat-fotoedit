#include <iostream>
#include <string>
#include <SDL.h>

class SDLMY {
public:
	int WIDTH = 1200, HEIGHT = 667;
	std::string file;
	int changeg = 1;
	int change[6] = { 1,1,1,1,1,1 };
	int finished = 0;
	int loaded = 0;
	int reload = 1;
	std::string l1, l2, l3, l4, l5, l6;

	void load(const std::string s, SDL_Surface*& sur, int& c) {
		if (c) {
			sur = SDL_LoadBMP(s.c_str());
			c = 0;
		}
		if (sur == NULL)
		{
			std::cout << "SDL could not load image! SDL Error: " << SDL_GetError() << std::endl;
			std::cout << s << std::endl;
		}
	}
	void draw(int x,int y,int h, int w, SDL_Surface*& sur, SDL_Surface*& win) {
		SDL_Rect d;
		d.x = x;
		d.y = y;
		d.h = h;
		d.w = w;
		SDL_BlitScaled(sur, NULL, win, &d);
	}
	void SDLmain() {
		SDL_Surface *imageSurface = NULL;
		SDL_Surface *imageSurface1 = NULL;
		SDL_Surface *imageSurface2 = NULL;
		SDL_Surface *imageSurface3 = NULL;
		SDL_Surface *imageSurface4 = NULL;
		SDL_Surface *imageSurface5 = NULL;
		SDL_Surface *imageSurface6 = NULL;
		SDL_Surface *windowSurface = NULL;
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		}

		SDL_Window *window = SDL_CreateWindow("Slika Projekta", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
		windowSurface = SDL_GetWindowSurface(window);

		if (NULL == window)
		{
			std::cout << "Could not create window: " << SDL_GetError() << std::endl;

			return;
		}

		SDL_Event windowEvent;
		while (!finished) {
			loaded = 1;
			SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 200, 200, 200));
			load(file, imageSurface, changeg);
			load(l1, imageSurface1, change[0]);
			load(l2, imageSurface2, change[1]);
			load(l3, imageSurface3, change[2]);
			load(l4, imageSurface4, change[3]);
			load(l5, imageSurface5, change[4]);
			load(l6, imageSurface6, change[5]);
			while (!changeg && !change[0] && !change[1] && !change[2] && !change[3] && !change[4] && !change[5])
			{
				if (finished) break;
				if (SDL_PollEvent(&windowEvent))
				{
					if (SDL_QUIT == windowEvent.type)
					{
						break;
					}
				}
				SDL_Rect dest;
				dest.x = 200;
				dest.y = 41;
				dest.w = 875;
				dest.h = 571;
				int w = imageSurface->w;
				int h = imageSurface->h;
				if (w > h) {
					if (w < dest.w) {
						dest.w = w;
						dest.h =int( dest.w*h )/ w % dest.h;
					}
					else {
						float t = (dest.w * 1.0 / w * 1.0) * h;
						dest.h = int(t) % dest.h;
					}
				}
				else {
					if (h < dest.h) {
						dest.h = h;
						dest.w = dest.h*w / h % dest.w;
					}
					else {
						float t = (dest.h*1.0 / h * 1.0)*w;
						dest.w = int(t) % dest.w;
					}
				}
				dest.x = dest.x + (875 - dest.w) / 2;
				dest.y = dest.y + (571 - dest.h) / 2;
				draw(dest.x,dest.y,dest.h,dest.w, imageSurface, windowSurface);
				draw(50, 20, 80, 80, imageSurface1, windowSurface);
				draw(50, 120, 80, 80, imageSurface2, windowSurface);
				draw(50, 220, 80, 80, imageSurface3, windowSurface);
				draw(50, 320, 80, 80, imageSurface4, windowSurface);
				draw(50, 420, 80, 80, imageSurface5, windowSurface);
				draw(50, 520, 80, 80, imageSurface6, windowSurface);
				SDL_UpdateWindowSurface(window);
			}
			/*
			std::cout << file << std::endl;
			std::cout << "Ovde je Promena PRomena Kalus" << std::endl;*/
			SDL_FillRect(imageSurface, NULL, 0x000000);
		}
		std::cout << "gasim nit" << std::endl;
		SDL_FreeSurface(imageSurface);
		SDL_FreeSurface(windowSurface);
		imageSurface = NULL;
		windowSurface = NULL;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};