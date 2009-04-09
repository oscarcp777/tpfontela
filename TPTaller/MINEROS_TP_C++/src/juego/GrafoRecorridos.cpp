#include "GrafoRecorridos.h"
#include "Cola.h"
#include "Pila.h"
#include "tablero.h"
#include "definiciones.h"


void desmarcarVertices (
	Grafo* unGrafo,
	void (*desmarcar    ) (Vertice* Vertice)
) {
	// Se monta un iterador sobre el conjunto de Vertices
	IteradorConjunto* iteradorVertices = nuevoIterador ( getConjuntoDeVertices ( unGrafo ) );

	// Mientras no se haya llegado al fin del mismo
	while (!fin ( iteradorVertices ) ) {
		// Se invoca al procedimiento pasado por parametro para desmarcar cada vertice
		desmarcar ( (Vertice *) ( obtenerElemento  ( iteradorVertices ) ) );

		// Nos desplazamos al siguiente elemento mediante el iterador
		irAlSiguiente ( iteradorVertices );
	}

	// Eliminamos el iterador
	eliminarIterador (iteradorVertices);
}

void apilarHijos ( Pila* pila, Vertice* unVertice, bool (*debeMarcarse ) (Vertice* VerticeDestino )) {
	// Se monta un iterador sobre el conjunto de Aristas Salientes del Vertice
	IteradorConjunto* iteradorAristas = nuevoIterador ( getAristasSalientes ( unVertice ) );
    Vertice* vertice;

	// Mientras no se haya llegado al fin del mismo
	while (!fin ( iteradorAristas ) ) {

		// Agregamos los elementos a la Pila
		// Notar el orden de inclusión, el cual ha de ser inverso al de extracción
		// dado el comportamiento FirstIn - FirstOut de la estructura
		vertice = getVerticeDestino( (Arista*) ( obtenerElemento  ( iteradorAristas ) ) );
		if (debeMarcarse (vertice))
            agregarElemento(pila, vertice);

		// Nos desplazamos al siguiente elemento mediante el iterador
		irAlSiguiente ( iteradorAristas );
	}
	// Eliminamos el iterador
	eliminarIterador (iteradorAristas);
}

void recorrido(
	Tablero &tablero,
	void (*desmarcar    ) (Vertice* Vertice),
	bool (*debeMarcarse ) (Vertice* VerticeDestino ),
	void (*marcar       ) (Vertice* VerticeDestino ),
	ListaDeBots::Lista &listaBots
) {
	Vertice* verticeAProcesar;
	//Vertice* verticeOrigen;
	//Arista * arista;
	Pila* pila = nuevaPila();
    Grafo* unGrafo = getGrafo(tablero);
    Vertice* verticeDePartida = tablero.entrada.dondeSeCargo;

	// Procedemos a Desmarcar los Vertices mediante la funcion Parametro
	desmarcarVertices (unGrafo, desmarcar);

	// Apilamos el primer elemento
	agregarElemento (pila, verticeDePartida);

	// Mientas que la pila no este vacia
	DatoVertice* datoVertice;
	Casillero* casilleroAuxiliar;
	Bot* botAuxiliar;
	while (!estaVacia(pila)) {
		// Removemos un Elemento
		// Notad el orden de remoción de los elementos de la Pila
		// (inverso al orden de inclusión)
		verticeAProcesar = (Vertice*) ( quitarElemento (pila) );

		// Si debe marcarse...
		if (debeMarcarse (verticeAProcesar)) {
			// ...procedemos a marcarlo
			marcar (verticeAProcesar);
			//... y apilamos sus hijos
			apilarHijos ( pila, verticeAProcesar, debeMarcarse);
            datoVertice = static_cast<DatoVertice*>(getInfo(verticeAProcesar));
            casilleroAuxiliar = buscarCasilleroPorId(tablero,datoVertice->Id);
            if (casilleroAuxiliar != NULL)
            {
                botAuxiliar = obtenerBot(*casilleroAuxiliar);
                if(botAuxiliar != SinBot())
                {
                    Perforadora* Pperf;
                    Pperf = get_Perforadora(*botAuxiliar);
                    setSalida(*Pperf, true);
                }
            }
        }

    }
    // por último eliminamos la estructura
	eliminarPila ( pila );
}
