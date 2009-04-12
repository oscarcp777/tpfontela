/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
* Pila
* Implementacion con tipo de dato fijo (definido en NodoSimplementeEnlazado.h).
* v0.1
* Autor: Mariano Simone (marianosimone+7541@gmail.com)
**/
#ifndef PILA_H_
#define PILA_H_

#include "NodoSimplementeEnlazado.h"

class Pila {
private:
    NodoSimplementeEnlazado* tope;

public:
    Pila();
    ~Pila();
    
    /**
     * Agrega el elemento a la pila
     * Axioma: desapilar(apilar(unDato)) == unDato
     */
    void push(const Dato& dato);
    
    /**
     * Retorna el ultimo dato ingresado, y lo elimina de la pila
     */
    Dato pop();
    
    /**
     * Retorna el ultimo dato ingresado
     */
    Dato top();
    
    bool estaVacia();
};

#endif
