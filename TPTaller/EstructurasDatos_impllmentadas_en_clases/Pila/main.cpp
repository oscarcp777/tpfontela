#include <iostream>
#include "Pila.h"

void testPila() {
	std::cout << "Test de pila con enteros"<< std::endl;
	Pila pilaEnteros;

	int a = 1;
	int b = 2;
	int c = 3;

	pilaEnteros.push(&a);
	pilaEnteros.push(&b);
	pilaEnteros.push(&c);

	while (!pilaEnteros.estaVacia()) {
		std::cout << "Saco un elemento : "<< *(int*)pilaEnteros.pop()
				<< std::endl;
	}

	std::cout << "Fin Test de pila con enteros"<< std::endl;
}

int main(int argc, char **argv) {
	testPila();
}
