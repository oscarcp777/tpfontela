#include "NodoSimplementeEnlazado.h"

#define NULL 0

struct NodoSimplementeEnlazado {
	void                    * Info;			// Información del Nodo
	NodoSimplementeEnlazado* Siguiente;	// Referencia al Siguiente Nodo
};

NodoSimplementeEnlazado* nuevoNodoSimplementeEnlazado ( void* Info, NodoSimplementeEnlazado* Siguiente ) {
	// Se genera un nuevo Nodo
	NodoSimplementeEnlazado* aux = new NodoSimplementeEnlazado;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializan los atributos
		setInfo      ( aux, Info      );
		setSiguiente ( aux, Siguiente );
	}

	// Se devuelve el nodo generado o NULL en caso de no haber memoria suficiente
	return aux;
}

void eliminarNodoSimplementeEnlazado ( NodoSimplementeEnlazado* unNodo ) {
	// Consideración de Robustez: si se paso una referencia nula no hace nada
	if (unNodo==NULL) return;

	// Se desaloca la memoria reservada
	// Conforme al comportamiento indicado en las PRE y POS, no se libera
	// la memoria referenciada por la info del nodo.
	delete unNodo;
}

void* setInfo (NodoSimplementeEnlazado* unNodo, void* Info) {
	return unNodo->Info = Info;
}

void* getInfo (NodoSimplementeEnlazado* unNodo) {
	return unNodo->Info;
}

NodoSimplementeEnlazado* setSiguiente (NodoSimplementeEnlazado* unNodo, NodoSimplementeEnlazado* nodoSiguiente) {
	return unNodo->Siguiente = nodoSiguiente;
}

NodoSimplementeEnlazado* getSiguiente (NodoSimplementeEnlazado* unNodo) {
	return unNodo->Siguiente;
}
