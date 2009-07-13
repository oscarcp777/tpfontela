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
#include "Posicion.h"
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
	static Posicion* hallarPuntoTriangulo(Recta* recta, int x, int y);
	static void colisionCirculo(Tejo* tejo,Circulo* figura);
	static double hallarDistancia(Recta* recta, int x, int y);
	static void decidirDireccionPrimerCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void decidirDireccionSegundoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void decidirDireccionTercerCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void decidirDireccionCuartoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY);
	static void decidirDireccionPrimerCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo);
	static void decidirDireccionSegundoCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo);
	static void decidirDireccionTercerCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo);
	static void decidirDireccionCuartoCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo);
	static void colisionRectangulo(Rectangulo* rectangulo,Tejo* tejo);
	static void colisionCuadrado(Cuadrado* cuadrado,Tejo* tejo);
	static void colisionTriangulo(Triangulo* Triangulo,Tejo* tejo);
	static bool verificarExcepciones(Recta* rectaEntreRadios,Tejo* tejo,Circulo* figura);
	static void asignarDireccionTrianguloConPendiente(Tejo*  tejo,Recta* recta,Triangulo* triangulo);
	static void asignarDireccionTriangulo(Tejo* tejo,Recta* recta,Triangulo* triangulo);
	static bool getZonaDeInfluencia(Recta* rectaDireccionTejo,Recta*recta,Triangulo* triangulo,Tejo*tejo );
	static bool isPuntoZonaDeInfluenciaTejo(Posicion* posicion,Tejo* tejo);
	static bool isPuntoZonaDeInfluenciaTriangulo(Posicion* posicion,Triangulo* triangulo);
	static Recta* getRectaDeColision(Triangulo* triangulo,Tejo* tejo);
	static int getTipoPendienteCeroOInfinito(Triangulo* triangulo);
	static Recta* obtenerRectaParalelaRectaDirTejo(Triangulo*triangulo,Tejo*tejo,Posicion*posicionTejo);
	static double obtenerAnguloSegunBase(Triangulo*triangulo,Tejo*tejo,Posicion*verticeChoque);
	static double obtenerAnguloTejo(Posicion*vertice,Posicion*posicionAcomparar,Recta*rectaDireccion,Tejo*tejo,Triangulo*triangulo);
};

#endif /* CONTROLADORCOLISIONES_H_ */
