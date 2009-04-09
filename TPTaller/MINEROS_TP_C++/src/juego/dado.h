/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                               TDA DADO                                     *
 ******************************************************************************/

/********************************HEADERS***************************************/

#ifndef _DADO_H_
#define _DADO_H_
#include "cara.h"
#include "listadecaras.h"
#include <stdlib.h>


/********************************AXIOMAS***************************************/
/* 1 - Una vez creado el dado, no se puede cambiar la cantidad de caras.
   2 - El dado es num�rico.
   3 - El n�mero de caras es un n�mero entero de 1 a 9999.
   4 - El n�mero de caras = -1 est� reservado para invalidez.
*/

/******************************COMPOSICION*************************************/

struct Dado {
    int CantidadCaras; //Cantidad de caras del dado
    ListaDeCaras::Lista ListaCaras; //Lista de caras que posee el dado
};

/*******************************PRIMITIVAS*************************************/

/* Crear:
Pre: Semilla para random creada externamente.
Post: Dado creado, listo para su utilizaci�n.
      Los valores de cada cara se asignan autom�ticamente
      segun la cantidad de caras.
      Si la cantidad de caras no respeta los axiomas, coloca al dado como inv�lido.

dado1: Instancia sobre la que se aplica la primitiva.
cantidadcaras: Define la cantidad de caras que tendr� el dado creado.
*/

void crear(Dado &dado1, int cantidadcaras);

/* Destruir:
Pre: Dado creado.
Post: Se destruye el dado, invalidando su utilizaci�n.

dado1: Instancia sobre la que se aplica la primitiva.
*/

void destruir(Dado &dado1);

/* Obtener Cara:
Pre: Dado creado.
Post: Devuelve el valor de una cara del dado seg�n su n�mero de cara.
Si el valor, el n�mero pasado como par�metro o el dado son inv�lidos devuelve
-1.

dado1: Instancia sobre la que se aplica la primitiva.
numero: Numero de cara a obtener el valor.
*/

Valor obtenerCara(Dado &dado1, ListaDeCaras::NumCara numero);

/* Obtener Cantidad de Caras:
Pre: Dado creado.
Post: Devuelve el n�mero de caras del dado. Si es un dado inv�lido devuelve -1.

dado1: Instancia sobre la que se aplica la primitiva.
*/

int obtenerCantDeCaras(Dado &dado1);

/* Tirar:
Pre: Dado creado.
Post: Devuelve un valor de una cara al azar perteneciente al dado.
Ante un eventual error devuelve -1.

dado1: Instancia sobre la que se aplica la primitiva.
*/

Valor tirar(Dado &dado1);

#endif
/******************************************************************************/



