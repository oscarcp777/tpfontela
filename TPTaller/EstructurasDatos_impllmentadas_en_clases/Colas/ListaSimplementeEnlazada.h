/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
* Lista 
* Implementacion de Lista Simplemente Enlazada con tipo de dato fijo (definido en NodoSimplementeEnlazado.h).
* v0.1
* Autor: Mariano Simone (marianosimone+7541@gmail.com)
**/

#ifndef LISTA_H_
#define LISTA_H_
#include "NodoSimplementeEnlazado.h"

class Lista {
	
private:
    //Puntero al primer elemento de la lista
    NodoSimplementeEnlazado* primero;
    unsigned int actual;

public:
    /*
     * Crea una nueva lista
     */
    Lista();

    /*
     * Nota: Los elementos de la lista no son eliminados
     */
    virtual ~Lista();

    /*
     * Determina si la lista esta vacia o no
     */
    bool estaVacia() const;

    /*
     * Retorna la cantidad de elementos de la lista
     */
    unsigned int tamanio() const;

    /*
     * Inserta el dato al principio de la lista
     */
    void insertarPrincipio(Dato dato);

    /*
     * Inserta el dato al final de la lista
     */
    void agregar(Dato dato);

    /*
     * Retorna el siguiente elemento de la lista
     */
    Dato obtenerSiguiente();
    
    /*
     * Elimina el ultimo dato entregado
     */
     void eliminarDato();

    /*
     * Determina si existe o no un siguiente elemento en la lista
     */
    bool tieneSiguiente();

    /*
     * Regresa el indicador de posicion a 0, para que la proxima vez que se pida el siguiente se retorne el primero
     */
    void reset();
};

#endif
