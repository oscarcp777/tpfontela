/*
 * Tejo.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Circulo.h"
#ifndef TEJO_H_
#define TEJO_H_
#include <SDL.h>
class Tejo{
public:
	Tejo();
	Tejo(Circulo *circulo);
	virtual ~Tejo();
      void dibujar(SDL_Surface *pantalla);
         Circulo* getFigura();
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
    int getVelocidad();
    void setVelocidad(int velocidad);

private:
    	int velocidad;
    	Circulo* circulo;
    	SDL_Surface *imagen;
};

#endif /* TEJO_H_ */
