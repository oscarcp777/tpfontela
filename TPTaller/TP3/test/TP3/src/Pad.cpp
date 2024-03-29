/*
 * Pad.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Pad.h"
#include "Rectangulo.h"
#include "Escenario.h"
const int PIXELES_SALTO=15;
Pad::Pad() {

}
Rectangulo* Pad::getFigura(){
   return this->rectangulo;
}
Pad::Pad(Rectangulo* rectangulo){
	this->imagen=NULL;
	this->rectangulo=rectangulo;
	std::cout<< "padv1: "  <<this->rectangulo->getIdTextura()<< endl;

}

Pad::~Pad() {
	// TODO Auto-generated destructor stub
}
void Pad::dibujar(SDL_Surface *pantalla){
	// Cargamos la imagen
		        if(this->imagen==NULL){
				std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->rectangulo->getIdTextura());
				this->imagen = IMG_Load(path.begin());

				if(this->imagen == NULL) {
					std::cout<< "Error: " << SDL_GetError() << endl;
					exit(1);
				}
				if(this->imagen != NULL){
				this->imagen = this->getFigura()->ScaleSurface(this->imagen, this->getFigura()->getBase(), this->getFigura()->getAltura());
			    }

				// Calculamos el color transparente, en nuestro caso el verde
				Uint32 colorkey = SDL_MapRGB(this->imagen->format, 255, 255, 255);
				// Lo establecemos como color transparente
				SDL_SetColorKey(this->imagen, SDL_SRCCOLORKEY, colorkey);
		         }
		    SDL_Rect rect;
			rect.x =this->getX();
			rect.y = this->getY();
			SDL_BlitSurface(imagen, NULL, pantalla, &rect);
}
int Pad::getX(){
	return this->rectangulo->getPosicion()->getX();
}
int Pad::getY(){
	return this->rectangulo->getPosicion()->getY();
}
void Pad::setX(int x){
	this->rectangulo->getPosicion()->setX(x);
}
void Pad::setY(int y){
	this->rectangulo->getPosicion()->setY(y);
}
// El movimiento de la imagen se establece
// de 4 en 4 p�xeles
void Pad::avanzar_x() {
	int x =this->getX();
	x += PIXELES_SALTO;
	this->setX(x);
}
void Pad::retrasar_x() {
	int x =this->getX();
	x -= PIXELES_SALTO;
	this->setX(x);
}
void Pad::bajar_y() {
	int y =this->getY();
	y += PIXELES_SALTO;
	this->setY(y);
}
void Pad::subir_y() {
	int y =this->getY();
	y -= PIXELES_SALTO;
	this->setY(y);
}
