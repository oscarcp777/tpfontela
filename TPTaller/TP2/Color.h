#include <SDL.h>


class Color{
	
	public: 
		Color(int colorFondo_R,int colorFondo_G,int colorFondo_B);
		Color();
		~Color();
		int getColorFondo_R();
		int getColorFondo_G();
		int getColorFondo_B();
		SDL_Color getColor();
			
	private:
		//int colorFondo_R;
		//int colorFondo_G;
		//int colorFondo_B;
		SDL_Color color;


};