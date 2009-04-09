#include "NodoSimplementeEnlazado.h"
#include "Conjunto.h"

struct Conjunto {
	NodoSimplementeEnlazado* Elementos;	// Referencia al primer nodo (elemento) del conjunto
	void (*EliminarElemento) (void*);		// Forma de Eliminar lo referenciado en los nodos
};

Conjunto* nuevoConjunto    ( void (*EliminarElemento) (void*) ) {
	// Se genera un nuevo Conjunto
	Conjunto* aux = new Conjunto;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializan los atributos
		aux->Elementos        = NULL;
		aux->EliminarElemento = EliminarElemento;
	}

	// Se devuelve el conjunto generado o NULL en caso de no haber memoria suficiente
	return aux;
}

void*      agregarElemento  (Conjunto* unConjunto, void* Elemento) {
	// Un conjunto no admite duplicados, así que se encuentra el elemento
	// (buscarElemento != NULL) no lo agrega pero devuelve la referencia al mismo
	if (buscarElemento(unConjunto,Elemento)!=NULL) return Elemento;

	// Se genera un nuevo nodo para que almacena a Elemento y cuyo siguiente Nodo es el primero del conjunto
	NodoSimplementeEnlazado* nuevoNodo = nuevoNodoSimplementeEnlazado( Elemento, unConjunto->Elementos );

	// Si se pudo alocar la memoria necesaria
	if ( nuevoNodo!=NULL ) {
		// Se agrega el nodo como primer elemento del conjunto
		unConjunto->Elementos = nuevoNodo;
		// Y se devuelve una referencia al elemento agregado
		return Elemento;
	} else {
		// Se devuelve NULL señalando la no factibilidad de agregación
		return NULL;
	}
}

void*      buscarElemento (Conjunto* unConjunto, void* Elemento, bool (*sonIguales) (void*, void*) ) {
	// Se inicializa una variable para que oficie de iterador desde el primer elemento
	NodoSimplementeEnlazado* iterador   = unConjunto->Elementos;

	// Mientras queden elementos sin visitar
	while (iterador!=NULL) {
		// Si no se paso una función de comparacion
		if (sonIguales==NULL) {
			// y tanto la referencia pasada por parametro como la info contenida en el elemento del iterador son iguales
			if (getInfo(iterador)==Elemento)
				// se encontro el elemento y por consiguiente se devuelve una referencia al mismo
				return getInfo ( iterador );
		} else {
			// y la funcion de comparacion determina la igualdad
			if (sonIguales ( getInfo(iterador), Elemento))
				// se encontro el elemento y por consiguiente se devuelve una referencia al mismo
				return getInfo ( iterador );
		}
		// En caso contrario (no se encontro al elemento) se sigue en la busqueda en el siguiente nodo
		iterador = getSiguiente ( iterador );
	}

	// En caso de no encontrar al elemento se devuelve NULL
	return NULL;
}

void       quitarElemento	(Conjunto* unConjunto, void* Elemento) {
	// por default asumimos que no lo encontramos
	bool			 encontrado  = false;

	// montamos un iterador desde el primer elemento
	NodoSimplementeEnlazado* iterador    = unConjunto->Elementos;
	// y montamos otro que ira detras del anterior
	NodoSimplementeEnlazado* iteradorAnt = NULL;

	// mientras que el primer iterador no haya llegado al fin
	while (iterador!=NULL) {
		// si coinciden las referencias
		if ( getInfo ( iterador )==Elemento) {
			// marcamos el flag como encontrado
			encontrado = true;

			// Si el elemento encontrado esta en el primer nodo
			if (iterador==unConjunto->Elementos)
				// Seteamos como primer nodo del conjunto el siguiente
				unConjunto->Elementos = getSiguiente ( iterador );
		}

		// Si el elemento fue encontrado y el iterador Anterior es distinto de NULL
		if (encontrado && iteradorAnt!=NULL) {
			// Se sabe que hubo un elemento antes del que se elimina y por lo tanto
			// a este se le setea el siguiente con el nodo siguiente del que se quita
			setSiguiente ( iteradorAnt , getSiguiente ( iterador ) );
		}

		// El iterador anterior pasa a ser el actual
		iteradorAnt = iterador;
		// El actual pasa a ser el siguiente del mismo
		iterador    = getSiguiente ( iterador );
	}
}

void       eliminarConjunto (Conjunto* unConjunto) {
	NodoSimplementeEnlazado * nodoAEliminar;

	// Mientras no quede vacio el conjunto
	while (!estaVacio(unConjunto)) {
		// Se determina el nodo a eliminar
		nodoAEliminar = unConjunto->Elementos;

		// Si a crear el Conjunto se le indico la forma de eliminar los elementos
		if (unConjunto->EliminarElemento != NULL )
			// Se invoca a esta funcion para la info contenida en el nodo a eliminar
			unConjunto->EliminarElemento ( getInfo ( nodoAEliminar ) );

		// El primer elemento se setea al siguiente del que se quiere eliminar
		unConjunto->Elementos = getSiguiente ( nodoAEliminar );

		// Se invoca a la funcion de destrucción de nodos
		eliminarNodoSimplementeEnlazado ( nodoAEliminar );
	}
    delete unConjunto;
}

bool       estaVacio          (Conjunto*  unConjunto) {
	// El conjunto esta vacio si no tiene elementos
	return (unConjunto->Elementos == NULL);
}

int        cardinalidad     (Conjunto* unConjunto) {
	// Se empieza considerando 0 elementos
	int				 cantElementos = 0;
	// Se monta un iterador desde el primer elemento
	NodoSimplementeEnlazado * iterador      = unConjunto->Elementos;

	// Mientras que no se llegue al último elemento
	while (iterador!=NULL) {
		// Incremento la cantidad de elementos
		cantElementos++;
		// Y mueve el cursor al siguiente
		iterador = getSiguiente ( iterador );
	}

	// por último se devuelve la cantidad de elementos
	return cantElementos;
}


struct IteradorConjunto {
	NodoSimplementeEnlazado* ElementoActual;	// Nodo actual al que apunta
};

IteradorConjunto* nuevoIterador  (const Conjunto* unConjunto) {
	// Se genera un nuevo iterador
	IteradorConjunto* aux = new IteradorConjunto;

	// Si se pudo alocar la memoria necesaria
	if (aux!=NULL) {
		// Se inicializa el elemento actual en el primer elemento del conjunto
		aux->ElementoActual = unConjunto->Elementos;
	}

	// Se devuelve el iterador generado o NULL en caso de no haber memoria suficiente
	return aux;
}

void               eliminarIterador (IteradorConjunto* unIteradorConjunto) {
	// Robustez: si la referencia pasada es nula no se hace nada
	if (unIteradorConjunto!=NULL)
		// Se desaloca la memoria en cuestión
		delete unIteradorConjunto;
}

void			   irAlSiguiente    (IteradorConjunto* unIteradorConjunto) {
	// Se setea el elementoActual al siguiente elemento
	unIteradorConjunto->ElementoActual = getSiguiente ( unIteradorConjunto->ElementoActual );
}

void*			   obtenerElemento  (IteradorConjunto* unIteradorConjunto) {
	//Robustez: si se lego al fin, se devuelve NULL
	if ( fin ( unIteradorConjunto ) ) return NULL;

	// se devuelve la referencia contenida en el nodo actual
	return getInfo ( unIteradorConjunto->ElementoActual );
}

bool               fin              (IteradorConjunto* unIteradorConjunto) {
	// se esta al fin de si el elemento actual es nulo
	return (unIteradorConjunto->ElementoActual == NULL);
}
