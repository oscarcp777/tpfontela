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
#include "Puntaje.h"

class Pad{
public:
	Pad();
	Pad(Rectangulo* rectangulo,Puntaje* puntaje);
	virtual ~Pad();
    void dibujar(SDL_Surface *pantalla);
    Rectangulo* getFigura();
	Puntaje* getPuntaje();
  	 void avanzar_x();
  	 void retrasar_x();

  	  // Modifica la posici�n del personaje con respecto al eje Y
  	 void bajar_y();
  	 void subir_y();
  	 // Consultoras
  	int getBase();
	int getAltura();
  	  int getX();
  	  int getY();


  	 // Modificadoras

  	  void setX(int x);
  	  void setY(int y);

  private:
  	Rectangulo* rectangulo;
  	SDL_Surface *imagen;
  	SDL_Surface* fondoPad;
	Puntaje* puntaje;
};

#endif /* PAD_H_ */
