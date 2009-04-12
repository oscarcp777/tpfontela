/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* Clase Arbol
 * Archivo : Arbol.cpp
 * Versión : 1.0
 */

/* Headers */
/*----------------------------------------------------------------------------*/
#include "Arbol.h"


/* Clase Nodo */
/*----------------------------------------------------------------------------*/
Nodo* Nodo::NULO = NULL;     // incializa el atributo de clase NULO.

/* Clase Arbol */
/*----------------------------------------------------------------------------*/
Arbol::Arbol() {

  /* el arbol se crea vacio */
  this->raiz = Nodo::NULO;
}
/*----------------------------------------------------------------------------*/
Arbol::~Arbol() {

  /* de la raiz cuelga todo el arbol */
  this->eliminarSubarbol(this->raiz);
}

/*----------------------------------------------------------------------------*/
void Arbol::eliminarDato(Dato* dato) {

  /* busca el dato dentro del arbol */
  Nodo* nodoBuscado = this->buscarDato(dato);

  /* si lo encontró lo retira y luego lo destruye */
  if (nodoBuscado != Nodo::NULO) {

    Dato* datoBuscado = this->retirarDato(nodoBuscado);
    delete datoBuscado;
  }
}

/*----------------------------------------------------------------------------*/
Nodo* Arbol::getRaiz() const {
  return this->raiz;
}

/*----------------------------------------------------------------------------*/
bool Arbol::vacio() const {

  /* el árbol está vacio si la raiz es nula */
  return this->raiz == Nodo::NULO;
}

/*----------------------------------------------------------------------------*/
void Arbol::eliminarSubarbol(Nodo* nodo) {

  /* recursivamente destruye el subarbol dado */
  if (nodo != Nodo::NULO) {         // condición de corte

    // llamadas recursivas
    this->eliminarSubarbol(nodo->getHijoIzquierdo());   // subarbol izquierdo
    this->eliminarSubarbol(nodo->getHijoDerecho());     // subarbol derecho

    /* borra el dato y el nodo */
    delete nodo->getDato();
    delete nodo;
  }
}

/*----------------------------------------------------------------------------*/

