/*
 * Tejo.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include "Circulo.h"
#include "Direccion.h"
#ifndef __TEJO_H__
#define __TEJO_H__
#include <vector>
#include <math.h>
#include "Posicion.h"
#include "Recta.h"
#include <SDL.h>
class Tejo{
public:
	Tejo();
	Recta* getRectaDireccion();
	int getYSiguiente(int y);
	int getXSiguiente(int x);
	Tejo(Circulo *circulo);
	virtual ~Tejo();
	void borrarTejo();
      void dibujar(SDL_Surface *pantalla);
         Circulo* getFigura();
    	 void mover_x();
    	// void retrasar_x();

    	  // Modifica la posición del personaje con respecto al eje Y
    	// void bajar_y();
    	 void mover_y();
    	 // Consultoras
    	 int getRadio();
		 void setRadio(int radio);
    	  int getX();
    	  int getY();
		  int getXAnterior();
    	  int getYAnterior();
    	  Direccion* getDireccion();
          void moverTejo

			  ();
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

	std::string obtenerUltimaColisionPad();
	void setMover(int mover);
	int getMover();


    bool getChoco();
    void setChoco(bool choco);

private:
	std::vector<Posicion*> puntosDeInfluencia;
	Direccion* direccion;
    	int velocidad;
    	Circulo* circulo;
    	SDL_Surface *imagen;
		int XAnterior;
		int YAnterior;

		int mover;

		bool choco;

};

#endif /* TEJO_H_ */
