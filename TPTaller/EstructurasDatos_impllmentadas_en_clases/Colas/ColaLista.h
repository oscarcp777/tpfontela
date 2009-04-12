#ifndef COLALISTA_H_
#define COLALISTA_H_
#include "ListaSimplementeEnlazada.h"

class ColaLista {
private:
    Lista lista;
public:

    /**
    * Agrega el elemento a la cola
    */
    void push(const Dato& dato);

    /**
     * Retorna el primer dato ingresado, y lo elimina de la cola
     */
    Dato pop();

    /**
     * Retorna el primer dato ingresado
     */
    Dato top();

    bool estaVacia();
};

#endif /*COLALISTA_H_*/
