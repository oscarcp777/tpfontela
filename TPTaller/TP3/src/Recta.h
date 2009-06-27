/*
 * Recta.h
 *
 *  Created on: 11/06/2009
 *      Author: oscar
 */

#ifndef RECTA_H_
#define RECTA_H_
#include <iostream>
#include "Posicion.h"
class Recta {
public:
	/**
	 * para generar una recta solo se necesitan don puntos
	 */
	Recta(int x1,int x2,int y1,int y2);
	Recta();
	virtual ~Recta();
	int getValor(int x);
	/**
	 * devuelve una recta perpendicular a actual necesita que se le pase el
	 * punto de interseccionde las rectas
	 */
	Recta* getRectaPerpendicular(int x,int y);
    float getPendiente();
    /**
     * devuelve el punto de intersecion entre dos rectas
     */
    Posicion* getInterseccion(Recta* recta);
    void setPendiente(float pendiente);
    double getAnguloConAbcisa();
    float getOrdenada();
    int getCortaX();
    void setOrdenada(float ordenada);
   void toString();
    int getInfinito();
    void setInfinito(int infinito);
	int getX1();
	int getX2();
	int getY1();
	int getY2();
    int getValorInverso(int y);

private:
	float pendiente;
	float ordenada;

	int infinito;
	int x1;
	int x2;
	int y1;
	int y2;

};

#endif /* RECTA_H_ */
