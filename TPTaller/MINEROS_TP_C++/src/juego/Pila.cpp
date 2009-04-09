#include "Pila.h"
#include "NodoSimplementeEnlazado.h"

#define NULL 0

struct Pila {
	NodoSimplementeEnlazado* elementos;	// Referencia al último nodo ingresado
	void (*eliminarInfo)(void*);			// Forma de Eliminar lo referenciado en los nodos
};

Pila* nuevaPila    ( void (*eliminarInfo)(void*) ) {
	// Se genera una nueva Pila
	Pila *aux = new Pila;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializan los atributos
		aux->elementos    = NULL;
		aux->eliminarInfo = eliminarInfo;
	}

	// Se devuelve la pila generada o NULL en caso de no haber memoria suficiente
	return aux;
}

void   eliminarPila (Pila* unaPila) {
	void* elementoAEliminar;

	while (!estaVacia(unaPila)) {
		// Se quita un elemento
		elementoAEliminar = quitarElemento(unaPila);

		// Y si la pila fue creada con una función para eliminar la info
		if (unaPila->eliminarInfo != NULL)
			// Se invoca a dicha función pasandole la info a eliminar
			unaPila->eliminarInfo ( quitarElemento(unaPila) );
	}

    delete unaPila;
}

void*  agregarElemento ( Pila* unaPila, void* Elemento ) {
	// Se genera un nuevo nodo con Elemento como información y el último elemento de la pila como siguiente nodo
	NodoSimplementeEnlazado* aux = nuevoNodoSimplementeEnlazado (Elemento, unaPila->elementos );

	// Si no se pudo alocar memoria se devuelve NULL
	if (aux==NULL) return NULL;

	// Si marca como último elemento al nuevo
	unaPila->elementos = aux;

	// Se devuelve el elemento en cuestión
	return Elemento;
}

void*  quitarElemento  ( Pila* unaPila ) {
	// Consideracion de Robustez, si la cola esta vacia se devuelve NULL
	if ( estaVacia ( unaPila ) ) return NULL;

	// Se determina el nodo a quitar
	NodoSimplementeEnlazado* nodoAEliminar = unaPila->elementos;

	// Se obtiene la información que este contiene
	void*                     infoADevolver = getInfo ( unaPila->elementos );

	// Se cambia el primer elemento por el siguiente al nodo a quitar
	unaPila->elementos = getSiguiente ( unaPila->elementos );

	// Se procede a eliminar el nodo en cuestión
	eliminarNodoSimplementeEnlazado ( nodoAEliminar );

	// Se devuelve la información que este contenia
	return infoADevolver;
}

bool   estaVacia       ( Pila* unaPila ) {
	//  Esta vacia si no tiene mas nodos
	return ( unaPila->elementos == NULL );
}

