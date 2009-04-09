/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA ENTORNO                                    *
 ******************************************************************************/

/********************************HEADERS***************************************/

#ifndef _ENTORNO_H_
#define _ENTORNO_H_

#ifndef NULL
#define NULL      0
#endif

#include "Casillero.h"
#include "definiciones.h"

/********************************AXIOMAS***************************************/
/*
   1 - Las posiciones de los casilleros en un entorno son 4: arriba, abajo,
       izquierda, derecha.
   2 - El entorno esta compuesto por casilleros CONTIGUOS.
   3 - El casillero central esta siempre ocupado por el propietario del entorno,
       por eso no se lo representa.
*/
/******************************COMPOSICION*************************************/

//REMITIRSE AL ARCHIVO "definiciones.h"

/*******************************PRIMITIVAS*************************************/

/* Crear:
Pre: Ninguna.
Post: Entorno creado listo para utilizar.

entorno1: Instancia sobre la que se aplica la primitiva.
arriba,abajo,izquierda,derecha:valores iniciales de cada posición (punteros a
                               casilleros).
*/

void crear(Entorno &entorno1, Casillero* arriba, Casillero* abajo,
                   Casillero* izquierda, Casillero* derecha);

/* Destruir:
Pre: Entorno creado.
Post: Destruye el entorno invalidando su posterior utilización.

entorno1: Instancia sobre la que se aplica la primitiva.
*/

void destruir(Entorno &entorno1);

/* Set arriba:
Pre: Entorno creado.
Post: Asigna en la posición arriba,
      el puntero de casillero pasado como parámetro.

entorno1: Instancia sobre la que se aplica la primitiva.
arriba: Puntero al casillero que se ubica en la posición arriba del entorno.
*/

void setArriba(Entorno &entorno1, Casillero* arriba);

/* Set Abajo:
Pre: Entorno creado.
Post: Asigna en la posición abajo,
      el puntero de casillero pasado como parámetro.

entorno1: Instancia sobre la que se aplica la primitiva.
abajo: Puntero al casillero que se ubica en la posición abajo del entorno.
*/

void setAbajo(Entorno &entorno1, Casillero* abajo);

/* Set Izquierda:
Pre: Entorno creado.
Post: Asigna en la posición izquierda,
      el puntero de casillero pasado como parámetro.

entorno1: Instancia sobre la que se aplica la primitiva.
izq: Puntero al casillero que se ubica en la posición izquierda del entorno.
*/

void setIzquierda(Entorno &entorno1, Casillero* izq);

/* Set Derecha:
Pre: Entorno creado.
Post: Asigna en la posición derecha,
      el puntero de casillero pasado como parámetro.

entorno1: Instancia sobre la que se aplica la primitiva.
der: Puntero al casillero que se ubica en la posición derecha del entorno.
*/

void setDerecha(Entorno &entorno1, Casillero* der);

/* Get Arriba:
Pre: Entorno creado.
Post: Devuelve un puntero al casillero que se ubica en la posición superior en
      el entorno.

entorno1: Instancia sobre la que se aplica la primitiva.
*/

Casillero* getArriba(const Entorno &entorno1);

/* Get Abajo:
Pre: Entorno creado.
Post: Devuelve un puntero al casillero que se ubica en la posición inferior en
      el entorno.

entorno1: Instancia sobre la que se aplica la primitiva.
*/

Casillero* getAbajo(const Entorno &entorno1);

/* Get Izquierda:
Pre: Entorno creado.
Post: Devuelve un puntero al casillero que se ubica en la posición izquierda en
      el entorno.

entorno1: Instancia sobre la que se aplica la primitiva.
*/

Casillero* getIzquierda(const Entorno &entorno1);

/* Get Derecha:
Pre: Entorno creado.
Post: Devuelve un puntero al casillero que se ubica en la posición derecha en
      el entorno.

entorno1: Instancia sobre la que se aplica la primitiva.
*/

Casillero* getDerecha(const Entorno &entorno1);

/* Vacio:
  pre : Entorno Creado.
  post: devuelve la representacion de un casillero vacío.
*/

Casillero* Vacio();

#endif

/******************************************************************************/


