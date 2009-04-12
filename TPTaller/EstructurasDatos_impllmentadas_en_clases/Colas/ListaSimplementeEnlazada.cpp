#include "ListaSimplementeEnlazada.h"
#ifndef NULL
#define NULL 0
#endif

Lista::Lista() {
    primero = NULL;
    actual = 0;
}

Lista::~Lista() {
    while (primero != NULL) {
        NodoSimplementeEnlazado* actual = primero;
        primero = primero->getSiguiente();
        delete actual;
    }
}

bool Lista::estaVacia() const {
    return (primero == NULL);
}

void Lista::insertarPrincipio(Dato dato) {
    NodoSimplementeEnlazado* aux = primero;
    primero = new NodoSimplementeEnlazado();
    primero->setSiguiente(aux);
    primero->setDato(dato);
}

void Lista::agregar(Dato dato) {
    NodoSimplementeEnlazado** ultimo = &primero;
    while (*ultimo != NULL) {
        ultimo = &(*ultimo)->getSiguiente();
    }
    *ultimo = new NodoSimplementeEnlazado();
    (*ultimo)->setDato(dato);
}

//Notese que tambien se podria guardar un atributo con este valor
unsigned int Lista::tamanio() const {
    unsigned int elementos = 0;

    NodoSimplementeEnlazado* actual = primero;
    while (actual != NULL) {
        elementos++;
        actual = actual->getSiguiente();
    }
    return elementos;
}

Dato Lista::obtenerSiguiente() {
    unsigned int i = 0;
    NodoSimplementeEnlazado* nodo = primero;
    while (i < actual) {
    	nodo = nodo->getSiguiente();
    	i++;
    }
    actual++;
    return nodo->getDato();
}

void Lista::eliminarDato() {
	unsigned int i = 0;
    NodoSimplementeEnlazado** nodo = &primero;
    while (i < actual-1) {
    	nodo = &(*nodo)->getSiguiente();
    	i++;
    }
    NodoSimplementeEnlazado* aEliminar = *nodo;
	*nodo = (*nodo)->getSiguiente();
	delete aEliminar;
	actual--;
}

bool Lista::tieneSiguiente() {
    return (actual < tamanio());
}

void Lista::reset() {
    actual = 0;
}

