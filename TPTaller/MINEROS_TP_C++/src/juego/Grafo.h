/**
Universidad de Buenos Aires
Facultad de Ingeniería
75.41 Algoritmos y Programación II
Cátedra Ing. Domingo T. Mandrafina

Notas del Autor:
Este archivo forma parte del ejemplo de implementacón del TDA Grafos.

Los lineamientos tras los cuales se elaboró el presente son:

	a) Mostrar otra forma de construir y manejar TDA's
	b) Fortalecer el concepto de no Accesar Directamente los Atributos de un TDA
	c) Mostrar que un TDA no es simplemente un struct, sino que puede ser la composición
	   e interacción de varios TDA's (Arista, Vertice y Conjunto conforman un Grafo )
	d) Eliminar el concepto de que todo TDA es copiable (mediante el operador =) y que el
	   copiar un TDA es simplemente una primitiva mas del mismo.

Los mismos se vieron satisfechos en los siguientes aspectos de la codificación:
	1) El acceso a los TDA's se efectua siempre por punteros al mismo.
	   Esto es lo mas cercano que se puede llegar con programación estructurada
	   al concepto de referencias en lenguajes como Java, Smalltalk, etc.
	   Fortalece el concepto de Identidad de un TDA ya que en expresiones como ...

			TDA* unTDA    = new TDA;
			TDA* otroTDA;

			otroTDA = unTDA;

       ... lo que se copia es un puntero y por lo tanto, se mantiene la identidad del TDA original.
	   (en el ejemplo hay una sola instancia del TDA aunque se tenga 2 "referencias" al mismo)
	2) En ningun .h se definio la estructura del TDA en cuestión sino que simplemente
       se hace mencion a su existencia. En un par de lineas mas abajo se puede apreciar que
	   se declara la existencia de un TDA (struct) pero no su contenido. Esto permite poder
	   definir las primitivas de acceso al mismo (siempre con punteros, ya que se desconoce la
	   estructura y por lo tanto no se podría hablar de pasar por parametro al TDA dado) sin conocer
	   su composición.
	   Esto favorece fuertemente el concepto de abstracción.
	   Una consideración mas a tener en cuenta, es que, los .cpp que hagan #include de este .h
	   no podrán:

		- definir variables del tipo del TDA sino que deberán definir punteros al TDA
		- accesar al contenido del TDA y por ende modificar su estado si no es por medio
		  de las primitivas
		- no podrán copiar TDA si no es por medio de primitivas (esto sirve para evidenciar
		  que la operación de copiado debe ser una primitiva mas del TDA)
	3) Por último, cabe mencionar que el mecanismo de instanciación del TDA se sugiere que no sea
	   mediante ...

			new TDA;

       ... sino mediante las primitivas correposndientes que devuelven una referecia al TDA.

	        TDA* nuevoTDA();

       Esto permite comenzar a introducir conceptos como que un TDA no necesariamente se crea
	   vacio sino que puede forzarse a contener algun valor si solo se dejan constructores que reciben
	   parametros.

	   A demás, el no usar new TDA fortalece la idea de que puede haber otros TDA (o funciones en este caso)
	   que se encargan de generar TDA's dando lugar al concepto de Factory's que se verá mas adelante
	   en Diseño Orientado a Objetos
*/
#ifndef __GRAFO_H_
#define __GRAFO_H_

#ifndef NULL
#define NULL 0
#endif

// Se define la existencia de un TDA llamado Grafo
// Su objetivo es modelar el concepto de Grafo, es decir, conjunto de Vertices y Aristas que relacionan
// dichos vertices.
struct Grafo;

#include "Arista.h"
#include "Vertice.h"

/**
PRE:
	Parámetros
	void (*eliminarInfoVertice) (void*)	--> Forma de eliminar la información referida por "info"
	void (*eliminarInfoArista ) (void*)	--> Forma de eliminar la información contenida en las Aristas

POS:
	Estado Interno
	El grafo queda creado e inicializado sin vertices ni aristas.

	Valor de Retorno
	Grafo* --> Una referencia al nuevo Grafo
	Control de Error
	El valor de retorno será null en caso de no poderse alocar la memoria necesaria
*/
Grafo* nuevoGrafo( void (*eliminarInfoVertice) (void*) = NULL, void (*eliminarInfoArista) (void*) = NULL );

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"

POS:
	Estado Interno
	El grafo no puede ser utilizado nuevamente
	Si se había creado el mismo con una función para eliminación de la Informacion
	por el contenida, se ha invocado a dicha función y por ende debería quedar inutilizable
	la info de cada vertice y/o arista
*/
void eliminarGrafo( Grafo* unGrafo );

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"
	Vertice* VerticeOrigen --> Vertice origen de la arista
	Vertice* VerticeDestino	--> Vertice destino de la arista
	void* InfoArista --> Info que debe contener la arista

POS:
	Valor de Retorno
	Arista*	--> Referencia a la arista generada

	Estado Interno
	El grafo contiene una arista mas entre el vertice VerticeOrigen y el VerticeDestino
*/
Arista* agregarAristaDirigida(Grafo* unGrafo, Vertice* VerticeOrigen, Vertice* VerticeDestino, void* InfoArista);

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"
	Vertice* Vertice1 --> Uno de los Vertices de la arista (No se puede hablar de VerticeOrigen o Destino porque es NoDirigido)
	Vertice* Vertice2 --> Uno de los Vertices de la arista (No se puede hablar de VerticeOrigen o Destino porque es NoDirigido)
	void* InfoArista --> Info que debe contener la arista

POS:
	Valor de Retorno
	bool true si no hubo problemas, false en caso contrario

	Estado Interno
	El grafo contiene dos arista dirigidas que vinculan bidireccionalmente el vertice Vertice1 con el Vertice2.
	La particularidad es que ambas aristas apuntan al mismo InfoArista.
*/
bool agregarAristaNoDirigida(Grafo* unGrafo, Vertice* Vertice1, Vertice* Vertice2, void* InfoArista);

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"
	void* InfoArista --> Info que debe contener la arista
	bool (*sonIguales) (void*, void*) = NULL --> Funcion que señala si dos aristas son iguales. Si esta función es NULL se resuelve en base a si coinciden las referencias

POS:
	Valor de Retorno
	Arista* --> Referencia a la Arista encontrada o NULL de no hayarla (en caso de ser una arista no dirigida, devolverá la primer ocurrencia)
*/
Arista* buscarArista(Grafo* unGrafo, void* InfoArista, bool (*sonIguales) (void*, void*) = NULL);

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"
	void* InfoArista --> Info de la arista a Quitar
	bool (*sonIguales) (void*, void*) = NULL --> Funcion que señala si dos aristas son iguales. Si esta función es NULL se resuelve en base a si coinciden las referencias
POS:
	Estado Interno
	El grafo contiene una arista menos
*/
void quitarArista(Grafo* unGrafo, void* InfoArista, bool (*sonIguales) (void*, void*) = NULL);

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"
	void* InfoVertice --> Info que debe contener el vertice

POS:
	Valor de Retorno
	Vertice* --> Referencia al vertice generado

	Estado Interno
	El grafo contiene un vertice mas
*/
Vertice* agregarVertice(Grafo* unGrafo, void* InfoVertice);

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"
	void* InfoVertice --> Info que debe contener el vertice
	bool (*sonIguales) (void*, void*) = NULL --> Funcion que señala si dos vertices son iguales. Si esta función es NULL se resuelve en base a si coinciden las referencias

POS:
	Valor de Retorno
	Vertice* --> Referencia al vertice encontrada o NULL de no hayarlo
*/
Vertice* buscarVertice(Grafo* unGrafo, void* InfoVertice, bool (*sonIguales) (void*, void*) = NULL);

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"
	void* InfoVertice --> Info del vertice a remover

POS:
	Estado Interno
	El grafo contiene un vertice menos
*/
void quitarVertice(Grafo* unGrafo, void* InfoVertice);


/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"

POS:
	Valor de Retorno
	bool --> Marca si el grafo carece de vertices o no
*/
bool estaVacio(Grafo* unGrafo);

/**
PRE:
	Parámetros
	Grafo* unGrafo --> grafo creado con "nuevoGrafo"

POS:
	Valor de Retorno
	Conjunto* --> Contiene el conjunto de vertices del grafo
*/
const Conjunto* getConjuntoDeVertices (Grafo* unGrafo);

#endif
