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
#include "Recta.h"
#include <SDL.h>
class Tejo{
public:
	Tejo();
	void cargarPixelesAMover();
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
          void moverTejo();
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
	void setUltimaColisionPad(std::string ultimoPad);
	void setMover(int mover);
	int getMover();


    bool getChoco();
    void setChoco(bool choco);
	void setImagen(SDL_Surface *imagen);
    bool getModificarRadio();

    void setModificarRadio(bool modificarRadio);
private:
	std::vector<Posicion*> puntosDeInfluencia;
	Direccion* direccion;
    	int velocidad;
    	Circulo* circulo;
    	SDL_Surface *imagen;
		int XAnterior;
		int YAnterior;
        int moverMayor;
		int  moverMenor;
		int  mover;
		bool choco;
		bool modificarRadio;
		std::string ultimaColisionPad;

};

#endif /* TEJO_H_ */
