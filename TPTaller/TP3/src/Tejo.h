/*
 * Tejo.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */



#ifndef TEJO_H_
#define TEJO_H_

#include "Circulo.h"
#include "Direccion.h"
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
		  int getXAnterior();
    	  int getYAnterior();
    	  Direccion* getDireccion();

       void cargarPuntos();
    	 // Modificadoras

    	  void setX(int x);
    	  void setY(int y);
		  void setXAnterior(int x);
    	  void setYAnterior(int y);
    int getVelocidad();
    void setVelocidad(int velocidad);
    std::vector<Posicion*> getPuntosDeInfluencia();
    void setPuntosDeInfluencia(std::vector<Posicion*> puntosDeInfluencia);
    void cargarRadioDeInfluencia();
    SDL_Surface *getImagen();
private:
	std::vector<Posicion*> puntosDeInfluencia;
	Direccion* direccion;
    	int velocidad;
    	Circulo* circulo;
    	SDL_Surface *imagen;
		int XAnterior;
		int YAnterior;
};

#endif /* TEJO_H_ */
