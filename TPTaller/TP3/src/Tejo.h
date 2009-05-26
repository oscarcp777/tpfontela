/*
 * Tejo.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Circulo.h"
#include "Direccion.h"
#ifndef TEJO_H_
#define TEJO_H_
#include <vector>
#include <math.h>
#include "Posicion.h"
#include <SDL.h>
class Tejo{
public:
	Tejo();
	Tejo(Circulo *circulo);
	virtual ~Tejo();
	void borrarTejo();
      void dibujar(SDL_Surface *pantalla);
         Circulo* getFigura();
    	 void mover_x();
    	// void retrasar_x();

    	  // Modifica la posici�n del personaje con respecto al eje Y
    	// void bajar_y();
    	 void mover_y();
    	 // Consultoras
    	 int getRadio();
    	  int getX();
    	  int getY();
    	  Direccion* getDireccion();

       void cargarPuntos();
    	 // Modificadoras

    	  void setX(int x);
    	  void setY(int y);
    int getVelocidad();
    void setVelocidad(int velocidad);
    std::vector<Posicion*> getPuntosDeInfluencia();
    void setPuntosDeInfluencia(std::vector<Posicion*> puntosDeInfluencia);
    void cargarRadioDeInfluencia();

private:
	std::vector<Posicion*> puntosDeInfluencia;
	Direccion* direccion;
    	int velocidad;
    	Circulo* circulo;
    	SDL_Surface *imagen;
};

#endif /* TEJO_H_ */
