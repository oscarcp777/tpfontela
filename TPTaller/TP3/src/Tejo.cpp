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
Circulo* Tejo::getFigura(){
return	this->circulo;
}
Tejo::Tejo(Circulo* circulo){
	this->circulo=circulo;
	std::cout<< "padv1: "  <<this->circulo->getIdTextura()<< endl;
	this->imagen=NULL;
}
int Tejo::getVelocidad()
   {
       return velocidad;
   }

   void Tejo::setVelocidad(int velocidad)
   {
       this->velocidad = velocidad;
   }
void Tejo::dibujar(SDL_Surface *pantalla){
	// Cargamos la imagen
	        if(this->imagen==NULL){
			std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->circulo->getIdTextura());
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
	    SDL_Rect rect;
		rect.x =this->getX();
		rect.y = this->getY();
		SDL_BlitSurface(imagen, NULL, pantalla, &rect);
}
Tejo::~Tejo() {
	// TODO Auto-generated destructor stub
}
int Tejo::getX(){
	return this->circulo->getPosicion()->getX();
}
int Tejo::getY(){
	return this->circulo->getPosicion()->getY();
}
void Tejo::setX(int x){
	this->circulo->getPosicion()->setX(x);
}
void Tejo::setY(int y){
	this->circulo->getPosicion()->setY(y);
}
// El movimiento de la imagen se establece
// de 4 en 4 píxeles
void Tejo::avanzar_x() {
	int x =this->getX();
	x += 4;
	this->setX(x);
}
void Tejo::retrasar_x() {
	int x =this->getX();
	x -= 4;
	this->setX(x);
}
void Tejo::bajar_y() {
	int y =this->getY();
	y += 4;
	this->setY(y);
}
void Tejo::subir_y() {
	int y =this->getY();
	y -= 4;
	this->setY(y);
}




