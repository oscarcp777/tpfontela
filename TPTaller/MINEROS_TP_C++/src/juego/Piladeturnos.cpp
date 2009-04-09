/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA Pila
 * Implementaci�n Independiente
 * Archivo : Pila.cpp
 * Versi�n : 1.1
 */
#include "Piladeturnos.h"

namespace Pturnos{
/******************************************************************************/
/* Implementaci�n de Primitivas */
/*------------------------------*/

void crearPila(Pila &pila){
  pila.tope = NULL;
}

/*----------------------------------------------------------------------------*/
bool pilaVacia(Pila &pila) {

  return (pila.tope == NULL);
}

/*----------------------------------------------------------------------------*/
PtrNodoPila crearNodoPila(Dato dato) {

  /* reserva memoria para el nodo y le copia el dato */
  PtrNodoPila ptrAux = new NodoPila;
  ptrAux->dato = dato;
  ptrAux->sgte = NULL;

  return ptrAux;
}

/*----------------------------------------------------------------------------*/
void apilar(Pila &pila, Dato dato) {

  /* crea el nodo */
  PtrNodoPila ptrNuevoNodo = crearNodoPila(dato);
  /* reestructura la pila */
  ptrNuevoNodo->sgte = pila.tope;
  pila.tope = ptrNuevoNodo;
}

/*----------------------------------------------------------------------------*/
void obtenerDatoPrimero(Pila &pila, Dato &dato) {

  if (! pilaVacia(pila))
    dato = pila.tope->dato;
}

/*----------------------------------------------------------------------------*/
void eliminarNodoPrimero(Pila &pila) {

  PtrNodoPila ptrNodo;

  ptrNodo = pila.tope;
  pila.tope = pila.tope->sgte;

  destruir(ptrNodo -> dato); //Destruye el TDA turno
  delete ptrNodo;
}

/*----------------------------------------------------------------------------*/
void desapilar(Pila &pila, Dato &dato) {

  if (! pilaVacia(pila)) {

    obtenerDatoPrimero(pila,dato);
    eliminarNodoPrimero(pila);
  }
}

/*----------------------------------------------------------------------------*/
void eliminarPila(Pila &pila) {

  /* elimina todos los nodos de la pila */
  while (! pilaVacia(pila))
    eliminarNodoPrimero(pila);
}

/*----------------------------------------------------------------------------*/
}
