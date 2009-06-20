#include <SDL.h>

#ifndef __COLOR_H__
#define __COLOR_H__

class Color{
	
	public: 
		Color(int colorFondo_R,int colorFondo_G,int colorFondo_B);
		Color();
		~Color();
		int getColorFondo_R();
		int getColorFondo_G();
		int getColorFondo_B();
		SDL_Color getColor();
		void setColor(SDL_Color color);	
	private:
		//int colorFondo_R;
		//int colorFondo_G;
		//int colorFondo_B;
		SDL_Color color;


};
#endif