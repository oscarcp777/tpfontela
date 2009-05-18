/*
 * Tejo.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Tejo.h"
#include "Circulo.h"
#include "Escenario.h"
Tejo::Tejo() {
	// TODO Auto-generated constructor stub

}
Tejo::Tejo(int radio,Posicion * posicion){
this->setFigura(new Circulo("tejo",radio,posicion));
this->posicion=posicion;
		// Cargamos la imagen
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getFigura()->getIdTextura());
		this->imagen = IMG_Load(path.begin());

		if(this->imagen == NULL) {

			std::cout<< "Error: " << SDL_GetError() << endl;
			exit(1);

		}

		// Calculamos el color transparente, en nuestro caso el verde

		Uint32 colorkey = SDL_MapRGB(imagen->format, 0, 255, 0);
		// Lo establecemos como color transparente
		SDL_SetColorKey(imagen, SDL_SRCCOLORKEY, colorkey);
}
void Tejo::dibujar(SDL_Surface *pantalla){
	SDL_Rect rect;

		rect.x =this->posicion->getX();
		rect.y = this->posicion->getY();
		SDL_BlitSurface(imagen, NULL, pantalla, &rect);
}
Tejo::~Tejo() {
	// TODO Auto-generated destructor stub
}
int Tejo::mover(Posicion* posicion){
  return 0;
}



