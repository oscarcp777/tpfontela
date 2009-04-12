#include <iostream>
#include "Cola.h"
#include "ColaLista.h"

void testCola() {
    std::cout << "Test de cola con enteros" << std::endl;
    Cola colaEnteros;

    int a = 1;
    int b = 2;
    int c = 3;

    colaEnteros.push(&a);
    colaEnteros.push(&b);
    colaEnteros.push(&c);

    while (!colaEnteros.estaVacia()) {
        std::cout << "Saco un elemento : " << *(int*)colaEnteros.pop() << std::endl;
    }

    std::cout << "Fin Test de cola con enteros" << std::endl;
}
void testColaLista() {
    std::cout << "Test de colaLista con enteros" << std::endl;
    ColaLista colaEnteros;

    int a = 1;
    int b = 2;
    int c = 3;

    colaEnteros.push(&a);
    colaEnteros.push(&b);
    colaEnteros.push(&c);

    while (!colaEnteros.estaVacia()) {
        std::cout << "Saco un elemento : " << *(int*)colaEnteros.pop() << std::endl;
    }
    std::cout << "Fin Test de cola con enteros" << std::endl;
}

int main(int argc, char **argv) {
    testCola();
    testColaLista();
}

