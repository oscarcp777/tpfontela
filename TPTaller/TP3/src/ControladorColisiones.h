/*
 * ControladorColisiones.h
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */

#ifndef CONTROLADORCOLISIONES_H_
#define CONTROLADORCOLISIONES_H_
#include "Tejo.h"
#include "Figura.h"
#include "Circulo.h"
#include "Triangulo.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Recta.h"
#include "Pad.h"


class ControladorColisiones {

public:
	ControladorColisiones();
	virtual ~ControladorColisiones();
	static bool posibilidadDeColisionDispersores();
	static void calcularDireccion();
	static void colisionesPads();
	static int colisionesArcos();
	static void colisionCirculo(Tejo* tejo,Circulo* figura);
	static void decidirDireccionPrimerCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void decidirDireccionSegundoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void decidirDireccionTercerCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void decidirDireccionCuartoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void colisionRectangulo(Rectangulo* rectangulo,Tejo* tejo);
	static void colisionCuadrado(Cuadrado* cuadrado,Tejo* tejo);
	static void colisionTriangulo(Triangulo* Triangulo,Tejo* tejo);
	static bool verificarExcepciones(Recta* rectaEntreRadios,Tejo* tejo,Circulo* figura);
};

#endif /* CONTROLADORCOLISIONES_H_ */
