/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
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
   2 - El dado es numérico.
   3 - El número de caras es un número entero de 1 a 9999.
   4 - El número de caras = -1 está reservado para invalidez.
*/

/******************************COMPOSICION*************************************/

struct Dado {
    int CantidadCaras; //Cantidad de caras del dado
    ListaDeCaras::Lista ListaCaras; //Lista de caras que posee el dado
};

/*******************************PRIMITIVAS*************************************/

/* Crear:
Pre: Semilla para random creada externamente.
Post: Dado creado, listo para su utilización.
      Los valores de cada cara se asignan automáticamente
      segun la cantidad de caras.
      Si la cantidad de caras no respeta los axiomas, coloca al dado como inválido.

dado1: Instancia sobre la que se aplica la primitiva.
cantidadcaras: Define la cantidad de caras que tendrá el dado creado.
*/

void crear(Dado &dado1, int cantidadcaras);

/* Destruir:
Pre: Dado creado.
Post: Se destruye el dado, invalidando su utilización.

dado1: Instancia sobre la que se aplica la primitiva.
*/

void destruir(Dado &dado1);

/* Obtener Cara:
Pre: Dado creado.
Post: Devuelve el valor de una cara del dado según su número de cara.
Si el valor, el número pasado como parámetro o el dado son inválidos devuelve
-1.

dado1: Instancia sobre la que se aplica la primitiva.
numero: Numero de cara a obtener el valor.
*/

Valor obtenerCara(Dado &dado1, ListaDeCaras::NumCara numero);

/* Obtener Cantidad de Caras:
Pre: Dado creado.
Post: Devuelve el número de caras del dado. Si es un dado inválido devuelve -1.

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



