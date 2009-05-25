/*
 * Tejo.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Tejo.h"
#include "Circulo.h"
#include <math.h>
#include "Escenario.h"
const int PIXELES_SALTO=5;
#define NEGRO 0x000000
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
void Tejo::borrarTejo(){
	Escenario* escenario=Escenario::obtenerInstancia();
	SDL_Rect rectangulo;
	rectangulo.x=this->getX();
	rectangulo.y=this->getY();
	rectangulo.w=this->getFigura()->getRadio()*2;
	rectangulo.h=this->getFigura()->getRadio()*2;
	SDL_FillRect(escenario->getScreen(),&rectangulo,SDL_MapRGB(escenario->getScreen()->format,87,122,18));
//	SDL_UpdateRect(escenario->getScreen(),this->getX(),this->getY(), this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);
}
void dibujarCirculo(int posX, int posY, int radio, int color){
	Escenario* escenario=Escenario::obtenerInstancia();
  int i, j;
  int PITCH =(escenario->getScreen())->pitch / 4;
  for (i = 0; i < 2 * radio; i++)
  {
    // vertical clipping: (top and bottom)
	  if ((posY - radio + i) >= 0 && (posY - radio + i) < Escenario::obtenerInstancia()->getAlto())
    {
		  int len = (int)sqrt((float)(radio * radio - (radio - i) * (radio - i))) * 2;
      int xofs = posX - len / 2;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= Escenario::obtenerInstancia()->getAncho())
      {
        len -= (xofs + len) - Escenario::obtenerInstancia()->getAncho();
      }
      int ofs = (posY - radio + i) * PITCH + xofs;

      // note that len may be 0 at this point,
      // and no pixels get drawn!
      for (j = 0; j < len; j++)
        ((unsigned int*)(escenario->getScreen())->pixels)[ofs + j] = color;
    }
  }
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
//	 Cargamos la imagen
	        if(this->imagen==NULL){
			std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->circulo->getIdTextura());
//			this->imagen = IMG_Load(path.begin());
			this->imagen = SDL_LoadBMP(path.begin());
			if(this->imagen == NULL) {
				std::cout<< "Error: " << SDL_GetError() << endl;
				exit(1);
			}
			//si la imagen no es null (es decir si la levanto bien) la escalo
			if(this->imagen != NULL){
		     this->imagen = this->getFigura()->ScaleSurface(this->imagen, this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);
			}
//			// Calculamos el color transparente, en nuestro caso el verde
			SDL_SetColorKey(this->imagen,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(this->imagen->format,255,255,255));
			this->imagen=SDL_DisplayFormat(this->imagen);
	         }
	        SDL_SetColorKey(this->imagen,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(this->imagen->format,255,255,255));
	        this->imagen=SDL_DisplayFormat(this->imagen);
	    SDL_Rect rect;
		rect.x =this->getX();
		rect.y = this->getY();
		SDL_BlitSurface(this->imagen, NULL, pantalla, &rect);
//	dibujarCirculo( this->getX(),  this->getY(),  this->getFigura()->getRadio(),  NEGRO);
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
	borrarTejo();
	int x =this->getX();
	x += PIXELES_SALTO;
	this->setX(x);
}
void Tejo::retrasar_x() {
	borrarTejo();
	int x =this->getX();
	x -= PIXELES_SALTO;
	this->setX(x);
}
void Tejo::bajar_y() {
	borrarTejo();
	int y =this->getY();
	y += PIXELES_SALTO;
	this->setY(y);
}
void Tejo::subir_y() {
	borrarTejo();
	int y =this->getY();
	y -= PIXELES_SALTO;
	this->setY(y);
}




