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
    void bajar_y();
    void subir_y();
    int getBase();
    int getAltura();
	void setAltura(int altura);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getVelocidad();
    void setVelocidad(int velocidad);
	int getCantGoles();
    void setCantGoles(int cantGoles);
	void setImagen(SDL_Surface *imagen);
	int calcularProximaPosicionAlSubir();
	int calcularProximaPosicionAlBajar();
    bool getModificar();
    void setModificar(bool modificar);
	int getAlturaDefault();
	void setAlturaDefault(int altura);


private:
  	Rectangulo* rectangulo;
  	SDL_Surface *imagen;
  	SDL_Surface* fondoPad;
	Puntaje* puntaje;
	int cantGoles;
	int velocidad;
    bool modificar;
	int alturaDefault;
};

#endif /* PAD_H_ */
