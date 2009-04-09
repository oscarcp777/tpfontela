#include "Vertice.h"
#include "Arista.h"
#include "Conjunto.h"


struct Vertice {
	void      *info;					// Referencia a la Información del Vertice
	Conjunto *AristasSalientes;		// Referencia a las aristas que salen del Vertice

	void (*eliminarInfoVertice) (void*);// Forma de Eliminar lo referenciado por "info"
};

Vertice* nuevoVertice    ( void* info, void (*eliminarInfoVertice) (void*), void (*eliminarInfoArista) (void*) ) {
	// Se genera un nuevo Vertice
	Vertice* aux = new Vertice;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializan los atributos
		aux->info                = info;
		aux->eliminarInfoVertice = eliminarInfoVertice;
		//...en particular el conjunto de aristas
		aux->AristasSalientes    = nuevoConjunto ( eliminarAristaVoid );
	}

	// Se devuelve el vertice generado o NULL en caso de no haber memoria suficiente
	return aux;
}

void      eliminarVertice (Vertice* unVertice) {
	// Consideración de Robustez: si se paso una referencia nula no hace nada
	if (unVertice==NULL) return;

	// Si el vertice fue creado con una función para eliminar la info
	if (unVertice->eliminarInfoVertice)
		// Se invoca a dicha función pasandole la info a eliminar
		unVertice->eliminarInfoVertice ( unVertice->info );

	// Se elimina el conjunto de Aristas
	eliminarConjunto( unVertice->AristasSalientes );

	// Se desaloca la memoria reservada
	delete unVertice;
}

void eliminarVerticeVoid ( void* VerticeVoid ) {
	// Se sabe que VerticeVoid es un puntero a Vertice, así que se castea
	// y se delega la operación en la primitiva eliminarVertice
	eliminarVertice((Vertice*)VerticeVoid);
}

void agregarAristaSaliente (Vertice* unVertice, Arista* unaArista) {
	// Se delega a la primitiva agregarElemento del Conjunto de AristasSalientes
	agregarElemento ( unVertice->AristasSalientes, unaArista );
}

void quitarAristaSaliente (Vertice* unVertice, Arista* unaArista) {
	// Se delega a la primitiva quitarElemento del Conjunto de AristasSalientes
	quitarElemento	( unVertice->AristasSalientes, unaArista );
}

void* getInfo (Vertice* unVertice) {
	return unVertice->info;
}

void* setInfo (Vertice* unVertice, void* info) {
	return (unVertice->info = info);
}

Conjunto* getAristasSalientes (Vertice* unVertice) {
	// Se devuelve el conjunto de Aristas Salientes
    return unVertice->AristasSalientes;
}

Arista* buscarAristaSaliente  (Vertice* unVertice, void* InfoArista, bool (*sonIguales) (void*, void*)) {
	Arista* aristaEncontrada = NULL;
    IteradorConjunto* aristas = nuevoIterador ( getAristasSalientes ( unVertice ) );
	while (!fin( aristas ) && aristaEncontrada==NULL) {
		Arista* AristaActual = (Arista*) obtenerElemento ( aristas );
		if ( sonIguales == NULL) {
			if ( getInfo ( AristaActual ) == InfoArista ) {
				aristaEncontrada = AristaActual;
			}
		} else {
			if ( sonIguales ( getInfo ( AristaActual ), InfoArista ) ) {
				aristaEncontrada = AristaActual;
			}
		};

		irAlSiguiente(aristas);
	}
	return aristaEncontrada;
}

