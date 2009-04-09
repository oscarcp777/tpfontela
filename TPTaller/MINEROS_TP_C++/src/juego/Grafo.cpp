#include "Grafo.h"
#include "Conjunto.h"
#include "Vertice.h"
#include "Arista.h"

struct Grafo {
	Conjunto* ConjuntoDeVertices;			// Conjunto de Vertices
	void (*eliminarInfoVertice) (void*);	// Procedimiento para eliminar la info contenida en los vertices
	void (*eliminarInfoArista ) (void*);	// Procedimiento para eliminar la info contenida en las aristas
};

Grafo* nuevoGrafo    ( void (*eliminarInfoVertice) (void*), void (*eliminarInfoArista) (void*) ) {
	// Se genera un nuevo grafo
	Grafo *aux= new Grafo;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializan los atributos, en particular el conjunto de Vertices
		// Notar el parametro que señala la forma en que el conjunto eliminará
		// los elementos del mismo al solicitar su destrucción
		aux->ConjuntoDeVertices  = nuevoConjunto ( eliminarVerticeVoid );
		aux->eliminarInfoArista  = eliminarInfoArista;
		aux->eliminarInfoVertice = eliminarInfoVertice;
	}

	// Se devuelve el grafo generado o NULL en caso de no haber memoria suficiente
	return aux;
}

void eliminarGrafo (Grafo* unGrafo) {
	// Consideración de Robustez: si se paso una referencia nula no hace nada
	if (unGrafo==NULL) return;

	// Se procede a eliminar el conjunto de vertices
	eliminarConjunto(unGrafo->ConjuntoDeVertices);

	// Se desaloca la memoria reservada
	delete unGrafo;
}

Arista* agregarAristaDirigida (Grafo* unGrafo, Vertice* VerticeOrigen, Vertice* VerticeDestino, void* InfoArista) {
	// Se genera una nueva Arista
	Arista* aux = nuevaArista ( InfoArista, VerticeDestino, unGrafo->eliminarInfoArista );

	// Si se logro alocar la memoria en cuestión
	if (aux!=NULL)
		// Se invoca a la primitiva agregarAristaSaliente del Vertice
		agregarAristaSaliente ( VerticeOrigen, aux );

	// Se devuelve la Arista generada o NULL en caso de no haberse reservado memoria
	return aux;
}

bool agregarAristaNoDirigida (Grafo* unGrafo, Vertice* Vertice1, Vertice* Vertice2, void* InfoArista) {
	// Se generan dos Aristas, una que sale del V1 y llega al V2 y otra que sale del V2 y llega al V1
	Arista* aristaQueLlegaAV2 = nuevaArista ( InfoArista, Vertice2, unGrafo->eliminarInfoArista );
	Arista* aristaQueLlegaAV1 = nuevaArista ( InfoArista, Vertice1 , NULL                        );


	// Si se logro alocar la memoria en cuestión
	if (aristaQueLlegaAV2==NULL || aristaQueLlegaAV1==NULL) {
		if (aristaQueLlegaAV2!=NULL) eliminarArista ( aristaQueLlegaAV2 );
		if (aristaQueLlegaAV1!=NULL) eliminarArista ( aristaQueLlegaAV1 );
		return false;
	}

	// Se invoca a la primitiva agregarAristaSaliente del Vertice
	agregarAristaSaliente ( Vertice1, aristaQueLlegaAV2 );
	agregarAristaSaliente ( Vertice2, aristaQueLlegaAV1 );

	// Se devuelve la Arista generada o NULL en caso de no haberse reservado memoria
	return true;
}

Arista* buscarArista  (Grafo* unGrafo, void* InfoArista, bool (*sonIguales) (void*, void*) ) {
	// Montamos un iterador para recorrer todos los vertices del grafo
	IteradorConjunto* vertices = nuevoIterador ( unGrafo->ConjuntoDeVertices );
	Arista*           aristaEncontrada = NULL;

	// Mientras que no los hayamos recorrido todos y no hayamos encontrado la arista
	while (!fin( vertices ) && aristaEncontrada==NULL) {
		// Buscamos la arista en el vertice
		aristaEncontrada = buscarAristaSaliente ( (Vertice*) obtenerElemento(vertices), InfoArista, sonIguales );
		irAlSiguiente( vertices );
	}

	eliminarIterador (vertices);

	//Devolvemos la arista encontrada en el vertice o null si ningun vertice contenía dicha Info
	return aristaEncontrada;
}

void     quitarArista  (Grafo* unGrafo, void* InfoArista, bool (*sonIguales) (void*, void*) ) {
	// Montamos un iterador para recorrer todos los vertices del grafo
	IteradorConjunto* vertices         = nuevoIterador ( unGrafo->ConjuntoDeVertices );
	Arista*           aristaEncontrada = NULL;

	// Mientras que no los hayamos recorrido todos y no hayamos encontrado la arista
	while (!fin( vertices ) && aristaEncontrada==NULL) {
		// Buscamos la arista en el vertice
		aristaEncontrada = buscarAristaSaliente ( (Vertice*) obtenerElemento(vertices), InfoArista, sonIguales );
		// Si la encontramos
		if (aristaEncontrada!=NULL) {
			// Obtenemos la arista que le corresponde por ser no dirigida
			Arista* contraparteAristaNoDirigida = buscarAristaSaliente ( getVerticeDestino ( aristaEncontrada), InfoArista, sonIguales );
			// Si la encontramos (significa que era no dirigida)
			if (contraparteAristaNoDirigida!=NULL)
				// Entonces procedemos a quitarla
				quitarAristaSaliente ( getVerticeDestino ( aristaEncontrada), contraparteAristaNoDirigida);

			// Por último quitamos la arista encontrada
			quitarAristaSaliente ( (Vertice*) obtenerElemento(vertices), aristaEncontrada );
		}

		irAlSiguiente( vertices );
	}

	eliminarIterador (vertices);
}

Vertice* agregarVertice (Grafo* unGrafo, void* InfoVertice) {
	// Se genera un nuevo vertice
	Vertice* aux = nuevoVertice ( InfoVertice, unGrafo->eliminarInfoVertice, unGrafo->eliminarInfoArista );

	// Si se logro alocar la memoria en cuestión
	if (aux!=NULL)
		// Se invoca a la primitiva agregarElemento del Conjunto de Vertices
		agregarElemento ( unGrafo->ConjuntoDeVertices, aux );

	// Se devuelve el vertice generado o NULL en caso de no haberse reservado memoria
	return aux;
}

Vertice* buscarVertice (Grafo* unGrafo, void* InfoVertice, bool (*sonIguales) (void*, void*) ) {
	Vertice         * verticeEncontrado = NULL;
	IteradorConjunto* vertices          = nuevoIterador ( unGrafo->ConjuntoDeVertices );

	while ( !fin ( vertices ) && verticeEncontrado==NULL ) {
		Vertice * verticeActual = (Vertice * ) ( obtenerElemento ( vertices ) );

		// Si no se pasó una función de comparación
		if ( sonIguales==NULL ) {
			// Evaluamos igualdad por la dirección de memoria
			if ( getInfo ( verticeActual ) == InfoVertice )
				verticeEncontrado = verticeActual;
		} else
			// Evaluamos igualdad con la función en cuestión
			if ( sonIguales ( getInfo ( verticeActual ) , InfoVertice ) )
				verticeEncontrado = verticeActual;

		// Nos movemos al siguiente vertice
		irAlSiguiente ( vertices );
	}

	// Eliminamos el iterador
	eliminarIterador ( vertices );

	// Devolvemos el vertice encontrado o NULL e caso de no haberlo encontrado
	return verticeEncontrado;
}

const Conjunto* getConjuntoDeVertices (Grafo* unGrafo) {
	return unGrafo->ConjuntoDeVertices;
}

