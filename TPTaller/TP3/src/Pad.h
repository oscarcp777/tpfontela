/*
 * Pad.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Rectangulo.h"
#ifndef PAD_H_
#define PAD_H_
#include <SDL.h>
#include "Figura.h"
#include "Movible.h"
class Pad{
public:
	Pad();
	Pad(Rectangulo* rectangulo);
	virtual ~Pad();
    void dibujar(SDL_Surface *pantalla);
    Rectangulo* getFigura();
  	 void avanzar_x();
  	 void retrasar_x();

  	  // Modifica la posición del personaje con respecto al eje Y
  	 void bajar_y();
  	 void subir_y();
  	 // Consultoras

  	  int getX();
  	  int getY();


  	 // Modificadoras

  	  void setX(int x);
  	  void setY(int y);

  private:
  	Rectangulo* rectangulo;
  	SDL_Surface *imagen;
  	SDL_Surface* fondoPad;
};

#endif /* PAD_H_ */
