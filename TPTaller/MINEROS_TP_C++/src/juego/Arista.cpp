#include "Vertice.h"
#include "Arista.h"

struct Arista {
	void      *info;					// Referencia a la Información de la Arista
	Vertice  *verticeDestino;			// Referencia al Vertice Destino

	void (*eliminarInfoArista) (void*);	// Forma de Eliminar lo referenciado por "info"
};

Arista* nuevaArista ( void* info, Vertice* verticeDestino, void (*eliminarInfoArista) (void*) ) {
	// Se genera una nueva Arista
	Arista* aux = new Arista;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializan los atributos
		aux->info               = info;
		aux->eliminarInfoArista = eliminarInfoArista;
		aux->verticeDestino     = verticeDestino;
	}

	// Se devuelve la arista generada o NULL en caso de no haber memoria suficiente
	return aux;
}

void     eliminarArista (Arista* unaArista) {
	// Consideración de Robustez: si se paso una referencia nula no hace nada
	if (unaArista==NULL) return;

	// Si la arista fue creada con una función para eliminar la info
	if (unaArista->eliminarInfoArista)
		// Se invoca a dicha función pasandole la info a eliminar
		unaArista->eliminarInfoArista ( unaArista->info );

	// Se desaloca la memoria reservada
	delete unaArista;
}

void eliminarAristaVoid ( void* AristaVoid ) {
	// Se sabe que AristaVoid es un puntero a Arista, así que se castea
	// y se delega la operación en la primitiva eliminarArista
	eliminarArista((Arista*)AristaVoid);
}

void* getInfo (const Arista* unaArista) {
	return unaArista->info;
}

void* setInfo (Arista* unaArista, void* info) {
	return (unaArista->info = info);
}

Vertice* getVerticeDestino ( const Arista* unaArista ) {
	return unaArista->verticeDestino;
}

Vertice* setVerticeDestino ( Arista* unaArista, Vertice* verticeDestino ) {
	return unaArista->verticeDestino = verticeDestino;
}
