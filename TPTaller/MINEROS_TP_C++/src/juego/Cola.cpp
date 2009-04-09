#include "Cola.h"
#include "NodoSimplementeEnlazado.h"

struct Cola {
	NodoSimplementeEnlazado* primerElemento;	// Referencia al primer nodo ingresado
	NodoSimplementeEnlazado* ultimoElemento;	// Referencia al último nodo ingresado

	void (*eliminarInfo)(void*);				// Forma de Eliminar lo referenciado en los nodos
};

Cola* nuevaCola    ( void (*eliminarInfo)(void*) ) {
	// Se genera una nueva Cola
	Cola *aux = new Cola;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializan los atributos
		aux->primerElemento = NULL;
		aux->ultimoElemento = NULL;
		aux->eliminarInfo   = eliminarInfo;
	}

	// Se devuelve la cola generada o NULL en caso de no haber memoria suficiente
	return aux;
}

void   eliminarCola (Cola* unaCola) {
	void* elementoAEliminar;

	while (!estaVacia(unaCola)) {
		// Se quita un elemento
		elementoAEliminar = quitarElemento(unaCola);

		// Y si la cola fue creada con una función para eliminar la info
		if (unaCola->eliminarInfo != NULL)
			// Se invoca a dicha función pasandole la info a eliminar
			unaCola->eliminarInfo ( elementoAEliminar );
	}
}

void*  agregarElemento ( Cola* unaCola, void* Elemento ) {
	// Se genera un nuevo nodo con Elemento como información y NULL como siguiente nodo
	NodoSimplementeEnlazado* aux = nuevoNodoSimplementeEnlazado ( Elemento, NULL );

	// Si no se pudo alocar memoria se devuelve NULL
	if (aux==NULL) return NULL;

	// Si la cola esta vacia
	if ( estaVacia ( unaCola ) ) {
		// El nuevo nodo ocupa el lugar de primer y último nodo
		unaCola->ultimoElemento = aux;
		unaCola->primerElemento = aux;
	} else {
		// Sino al último elemento se le asigna como siguiente el nuevo
		setSiguiente ( unaCola->ultimoElemento, aux );
		// y el nuevo pasa a ser el último
		unaCola->ultimoElemento = aux;
	}

	// Se devuelve el elemento en cuestión
	return Elemento;
}

void*  quitarElemento  ( Cola* unaCola ) {
	// Consideracion de Robustez, si la cola esta vacia se devuelve NULL
	if ( estaVacia ( unaCola ) ) return NULL;

	// Se determina el nodo a quitar
	NodoSimplementeEnlazado* nodoAEliminar = unaCola->primerElemento;

	// Se obtiene la información que este contiene
	void*                     infoADevolver = getInfo ( nodoAEliminar );

	// Se cambia el primer elemento por el siguiente al nodo a quitar
	unaCola->primerElemento = getSiguiente ( nodoAEliminar );

	// Si el primer elemento es NULL,
	if (unaCola->primerElemento==NULL)
		// se setea el último elemento a NULL
		unaCola->ultimoElemento = NULL;

	// Se procede a eliminar el nodo en cuestión
	eliminarNodoSimplementeEnlazado ( nodoAEliminar );

	// Se devuelve la información que este contenia
	return infoADevolver;
}

bool   estaVacia       ( Cola* unaCola ) {
	//  Esta vacia si no tiene mas nodos
	return ( unaCola->primerElemento == NULL );
}

