/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA Pila
 * Implementación Independiente
 * Archivo : Pila.h
 * Versión : 1.1
 */

#ifndef __PILADETURNOS_H__
#define __PILADETURNOS_H__

#ifndef NULL
#define NULL    0
#endif

#include "turno.h"

namespace Pturnos{
/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/

/* Tipo de Informacion que contienen los Nodos de la Pila, identificada como
   Dato. En las bibliografias se suelen utilizar, tambien, sinonimos como
   Info o Elemento. */
typedef turno Dato;

/* Tipo de Estructura de los Nodos de la Pila.*/
struct NodoPila {
                 Dato          dato;   // dato almacenado
                 NodoPila*     sgte;   // siguiente nodo
};

/* Tipo de Puntero a los Nodos de la Pila */
typedef NodoPila* PtrNodoPila;

/* Tipo de estructura de la Pila */
struct Pila {
             PtrNodoPila   tope;       // último nodo de la pila
};

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : ninguna.
  post: pila queda creada y preparada para ser usada.

  pila : estructura de datos a crear.
*/
void crearPila(Pila &pila);

/*----------------------------------------------------------------------------*/
/*
  pre : pila fue creada con crearPila().
  post: devuelve true si pila esta vacia, sino devuelve false

  pila : pila sobre la cual se invoca la primitiva.
*/
bool pilaVacia(Pila &pila);

/*----------------------------------------------------------------------------*/
/*
  Pre : pila fue creada con crearPila().
  Post: agrega al principio un nodo a pila conteniendo dato.

  pila : pila sobre la cual se invoca la primitiva.
  dato : elemento a apilar.
*/
void apilar(Pila &pila, Dato dato);

/*----------------------------------------------------------------------------*/
/*
  pre : pila fue creada con crearPila().
  post: devuelve en dato el contenido del primer nodo de la pila, y
        lo elimina. Si pila esta vacia no actua

  pila : pila sobre la cual se invoca la primitiva.
  dato : elemento desapilado.
*/
void desapilar(Pila &pila, Dato &dato);

/*----------------------------------------------------------------------------*/
/*
  pre : pila fue creada con crearPila().
  post: elimina todos los nodos de pila, quedando destruida e
        inhabilitada para su uso.

  pila : pila sobre la cual se invoca la primitiva.
*/
void eliminarPila(Pila &pila);

#endif
}

