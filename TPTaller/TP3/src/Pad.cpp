/*
 * Pad.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Pad.h"
#include "Rectangulo.h"
#include "Escenario.h"
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
				// Calculamos el color transparente, en nuestro caso el verde
		//		Uint32 colorkey = SDL_MapRGB(imagen->format, 0, 255, 0);
				// Lo establecemos como color transparente
		//		SDL_SetColorKey(imagen, SDL_SRCCOLORKEY, colorkey);
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
// de 4 en 4 píxeles
void Pad::avanzar_x() {
	int x =this->getX();
	x += 4;
	this->setX(x);
}
void Pad::retrasar_x() {
	int x =this->getX();
	x -= 4;
	this->setX(x);
}
void Pad::bajar_y() {
	int y =this->getY();
	y += 4;
	this->setY(y);
}
void Pad::subir_y() {
	int y =this->getY();
	y -= 4;
	this->setY(y);
}
