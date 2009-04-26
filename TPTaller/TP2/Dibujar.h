#include <string>
#include <fstream>
#include <SDL.h>
using namespace std;
class Dibujar{
private:
//	static Dibujar *unicaInstanciaDibujar;
   static void plot( SDL_Surface* surface, int x, int y, int color );
    
public:
//	 SDL_Surface *pantalla;
 //	 static Dibujar* obtenerInstancia();
	 Dibujar();
     static void dibujarRectangulo(SDL_Surface *screen,int posX, int posY, int ancho, int alto);
	 static void dibujarCirculo(SDL_Surface *screen,int posX, int posY, int radio);/**/
	 static void pintarPantalla(SDL_Surface *screen);
	 static void dibujarLinea(SDL_Surface *screen ,int x1, int y1, int x2, int y2);
	 static void dibujarTriangulo(SDL_Surface *screen,int izqX, int izqY,int derX, int derY,int supX, int supY);
};