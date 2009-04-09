/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA Lista
 * Implementaci�n Simplemente Enlazada
 * Archivo : Lista.cpp
 * Versi�n : 1.1
 */


#include "indiceEquipos.h"

/******************************************************************************/
/* Definici�n de Tipos de Datos para manejo interno */
/*--------------------------------------------------*/
namespace indiceEquipos{
/* tipo enumerado para realizar comparaciones */
enum ResultadoComparacion {
  mayor,
  igual,
  menor
};


/******************************************************************************/
/* Funciones Adicionales */
/*-----------------------*/

/*
  pre : ninguna.
  post: compara ambos dato1 y dato2, devuelve
          mayor si dato1 es mayor que dato2,
          igual si dato1 es igual a dato2,
          menor si dato1 es menor que dato2.

  dato1 : dato a comparar.
  dato2 : dato a comparar.
  return resultado de comparar dato1 respecto de dato2.
*/
ResultadoComparacion compararDato(Dato dato1, Dato dato2) {

  if (dato1.id == dato2.id) return igual;     // ambos son iguales

  else
    if (dato1.id > dato2.id) return mayor;       // dato1 es mayo que dato2

    else return menor;      // dato1 es menor que dato2
}


/******************************************************************************/
/* Implementaci�n de Primitivas */
/*------------------------------*/

void crearLista(Lista &lista) {
  lista.primero = fin();
}

/*----------------------------------------------------------------------------*/
bool listaVacia(Lista &lista) {

  return (lista.primero == fin());
}

/*----------------------------------------------------------------------------*/
PtrNodoLista fin() {
  return NULL;
}

/*----------------------------------------------------------------------------*/
PtrNodoLista primero(Lista &lista) {
  return lista.primero;
}

/*----------------------------------------------------------------------------*/
PtrNodoLista siguiente(Lista &lista, PtrNodoLista ptrNodo) {

  /* verifica si la lista est� vacia o si ptrNodo es el �ltimo */
  if ((! listaVacia(lista)) && (ptrNodo != fin()))
    return ptrNodo->sgte;
  else
    return fin();
}

/*----------------------------------------------------------------------------*/
PtrNodoLista anterior(Lista &lista, PtrNodoLista ptrNodo) {

  PtrNodoLista ptrPrevio = fin();
  PtrNodoLista ptrCursor = primero(lista);

  while (( ptrCursor != fin()) && (ptrCursor != ptrNodo)) {
    ptrPrevio = ptrCursor;
    ptrCursor = siguiente(lista,ptrCursor);
  }
  return ptrPrevio;
}

/*----------------------------------------------------------------------------*/
PtrNodoLista ultimo(Lista &lista) {

  /* el �ltimo nodo de la lista es el anterior al fin() */
  return anterior(lista,fin());
}

/*----------------------------------------------------------------------------*/
PtrNodoLista crearNodoLista(Dato dato) {

  /* reserva memoria para el nodo y luego completa sus datos */
  PtrNodoLista ptrAux = new NodoLista;

  ptrAux->dato = dato;
  ptrAux->sgte = fin();

  return ptrAux;
}

/*----------------------------------------------------------------------------*/
PtrNodoLista adicionarPrincipio(Lista &lista, Dato dato) {

  /* crea el nodo */
  PtrNodoLista ptrNuevoNodo = crearNodoLista(dato);

  /* lo incorpora al principio de la lista */
  ptrNuevoNodo->sgte = lista.primero;
  lista.primero = ptrNuevoNodo;

  return ptrNuevoNodo;
}

/*----------------------------------------------------------------------------*/
PtrNodoLista adicionarDespues(Lista &lista, Dato dato, PtrNodoLista ptrNodo) {

  PtrNodoLista ptrNuevoNodo = fin();

  /* si la lista est� vacia se adiciona la principio */
  if (listaVacia(lista))
    ptrNuevoNodo = adicionarPrincipio(lista,dato);

  else {
    if (ptrNodo != fin()) {

      /* crea el nodo y lo intercala en la lista */
      ptrNuevoNodo = crearNodoLista(dato);

      ptrNuevoNodo->sgte = ptrNodo->sgte;
      ptrNodo->sgte = ptrNuevoNodo;
    }
  }
  return ptrNuevoNodo;
}

/*----------------------------------------------------------------------------*/
PtrNodoLista adicionarFinal(Lista &lista, Dato dato) {

  /* adiciona el dato despu�s del �ltimo nodo de la lista */
  return adicionarDespues(lista,dato,ultimo(lista));
}

/*----------------------------------------------------------------------------*/
PtrNodoLista adicionarAntes(Lista &lista, Dato dato, PtrNodoLista ptrNodo) {

  PtrNodoLista ptrNuevoNodo = fin();

  if (! listaVacia(lista)) {
    if (ptrNodo != primero(lista))
      ptrNuevoNodo = adicionarDespues(lista,dato,anterior(lista,ptrNodo));
    else
      ptrNuevoNodo = adicionarPrincipio(lista,dato);
   }
   return ptrNuevoNodo;
}

/*----------------------------------------------------------------------------*/
void colocarDato(Lista &lista, Dato &dato, PtrNodoLista ptrNodo) {

  if ( (! listaVacia(lista)) && (ptrNodo != fin()))
    ptrNodo->dato = dato;
}

/*----------------------------------------------------------------------------*/
void obtenerDato(Lista &lista, Dato &dato, PtrNodoLista ptrNodo) {

  if ((! listaVacia(lista)) && (ptrNodo != fin()))
    dato = ptrNodo->dato;
}

/*----------------------------------------------------------------------------*/
void eliminarNodo(Lista &lista, PtrNodoLista ptrNodo) {

  PtrNodoLista ptrPrevio;

  /* verifica que la lista no est� vacia y que nodo no sea fin*/
  if ((! listaVacia(lista)) && (ptrNodo != fin())) {

    if (ptrNodo == primero(lista))
      lista.primero = siguiente(lista,primero(lista));

    else {
      ptrPrevio = anterior( lista , ptrNodo );
      ptrPrevio->sgte = ptrNodo->sgte;
    }
    delete ptrNodo;
  }
}

/*----------------------------------------------------------------------------*/
void eliminarNodoPrimero(Lista &lista) {

  if (! listaVacia(lista))
    eliminarNodo(lista,primero(lista));
}

/*----------------------------------------------------------------------------*/
void eliminarNodoUltimo(Lista &lista) {

  if (! listaVacia(lista))
    eliminarNodo(lista,ultimo(lista));
}

/*----------------------------------------------------------------------------*/
void eliminarLista(Lista &lista) {

  /* retira uno a uno los nodos de la lista */
  while (! listaVacia(lista))
    eliminarNodo(lista,primero(lista));
}

/*----------------------------------------------------------------------------*/
PtrNodoLista localizarDato(Lista &lista, Dato dato) {

   bool encontrado = false;
   Dato datoCursor;
   PtrNodoLista ptrCursor = primero(lista);

  /* recorre los nodos hasta llegar al �ltimo o hasta
     encontrar el nodo buscado */
  while ((ptrCursor != fin()) && (! encontrado)) {

    /* obtiene el dato del nodo y lo compara */
    obtenerDato(lista,datoCursor,ptrCursor);
    if (compararDato(datoCursor,dato) == igual)
      encontrado = true;
    else
      ptrCursor = siguiente(lista,ptrCursor);
  }

  /* si no lo encontr� devuelve fin */
  if (! encontrado)
    ptrCursor = fin();

  return ptrCursor;
}

/*----------------------------------------------------------------------------*/
void eliminarDato(Lista &lista, Dato dato) {

  /* localiza el dato y luego lo elimina */
  PtrNodoLista ptrNodo = localizarDato(lista,dato);
  if (ptrNodo != fin())
    eliminarNodo(lista,ptrNodo);
}

/*----------------------------------------------------------------------------*/
PtrNodoLista insertarDato(Lista &lista, Dato dato) {

  PtrNodoLista ptrPrevio = primero(lista);
  PtrNodoLista ptrCursor = primero(lista);
  PtrNodoLista ptrNuevoNodo;
  Dato datoCursor;
  bool ubicado = false;

  /* recorre la lista buscando el lugar de la inserci�n */
  while ((ptrCursor != fin()) && (! ubicado)) {

    obtenerDato(lista,datoCursor,ptrCursor);
    if (compararDato(datoCursor,dato) == mayor)
      ubicado = true;

    else {
      ptrPrevio = ptrCursor;
      ptrCursor = siguiente(lista,ptrCursor);
    }
  }

  if (ptrCursor == primero(lista))
    ptrNuevoNodo = adicionarPrincipio(lista,dato);
  else
    ptrNuevoNodo = adicionarDespues(lista,dato,ptrPrevio);

  return ptrNuevoNodo;
}

/*----------------------------------------------------------------------------*/
}
