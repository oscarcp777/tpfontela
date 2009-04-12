#include "ColaLista.h"

void ColaLista::push(const Dato& dato) {
    lista.agregar(dato);
}

Dato ColaLista::pop() {
    Dato dato = lista.obtenerSiguiente();
    lista.eliminarDato();
    return dato;
}

Dato ColaLista::top() {
    return lista.obtenerSiguiente();
}

bool ColaLista::estaVacia() {
    return lista.estaVacia();
}
