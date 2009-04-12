#include "Pila.h"

#ifndef NULL
#define NULL 0
#endif

Pila::Pila() {
    tope = NULL;
}

Pila::~Pila() {
    while (!estaVacia()) {
        pop();
    }
}

void Pila::push(const Dato& dato) {
    NodoSimplementeEnlazado* aux = tope;
    tope = new NodoSimplementeEnlazado();
    tope->setSiguiente(aux);
    tope->setDato(dato);
}

Dato Pila::pop() {
    if (tope == NULL)
        return NULL;
    Dato aux = tope->getDato();
    NodoSimplementeEnlazado* aElminiar = tope;
    tope = tope->getSiguiente();
    delete aElminiar;
    return aux;
}

Dato Pila::top() {
    if (tope == NULL)
        return NULL;
    return tope->getDato();
}

bool Pila::estaVacia() {
    return (tope == NULL);
}
