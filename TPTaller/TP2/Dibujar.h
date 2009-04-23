#include <string>
#include <fstream>
#include "SDL.h"
using namespace std;
class Dibujar{
private:
	static Dibujar *unicaInstanciaDibujar;
	protected:
			Dibujar();
    
public:
	 SDL_Surface *pantalla;
 	 static Dibujar* obtenerInstancia();
     void dibujarRectangulo(int posX, int posY, int ancho, int alto, int color);
	 void dibujarCirculo(int posX, int posY, int radio, int color);/**/
};
