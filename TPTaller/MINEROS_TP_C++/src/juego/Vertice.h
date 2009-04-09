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
#ifndef __VERTICE_H_
#define __VERTICE_H_

#ifndef NULL
#define NULL 0
#endif


// Se define la existencia de un TDA llamado Vertice
// Su objetivo es modelar los vertices de un grafo
// Esta muy orientado a ser una parte componente del Grafo y por ende deslinda muchas responsabilidades
// en el mismo. Ej. Saber las aristas que a él llegan.
struct Vertice;

// Necesarios porque un vertice contiene al conjunto de aristas que salen de el
#include "Arista.h"
#include "Conjunto.h"

/**
PRE:
	Parámetros
	void*		info						--> Información que contendrá el nuevo Vertice
	void (*eliminarInfoVertice) (void*)		--> Forma de eliminar la información referida por "info"
	void (*eliminarInfoArista ) (void*)		--> Forma de eliminar la información contenida en las Aristas

POS:
	Estado Interno
	El vertice queda creado e inicializado con info como información y sin aristas.

	Valor de Retorno
	Vertice*								--> Una referencia al nuevo Vertice

	Control de Error
	El valor de retorno será null en caso de no poderse alocar la memoria necesaria
*/
Vertice* nuevoVertice         ( void* info, void (*eliminarInfoVertice) (void*), void (*eliminarInfoArista) (void*) );

/**
PRE:
	Parámetros
	Vertice* unVertice						--> vertice creado con "nuevoVertice"

POS:
	Estado Interno
	El vertice no puede ser utilizado nuevamente
	Si se había creado el mismo con una función para eliminación de la Informacion
	por el contenida, se ha invocado a dicha función y por ende debería quedar inutilizable
	lo que era apuntado por info y el contenido de las aristas.
*/
void      eliminarVertice      ( Vertice* unVertice    );

/**
PRE:
	Parámetros
	void*    VerticeVoid					--> VerticeVoid es una referencia a un vertice creado con nuevoVertice

POS:
	Estado Interno
	El vertice apuntado por VerticeVoid no puede ser utilizada nuevamente
*/
void      eliminarVerticeVoid ( void*     VerticeVoid );


/**
PRE:
	Parámetros
	Vertice* unVertice						--> vertice creado con "nuevoVertice" al que se le agregará la arista
	Arista*  unaArista                     --> arista que se desea agregar a unVertice

POS:
	Estado Interno
	El vertice contiene una arista mas en su conjunto de aristas salientes
*/
void agregarAristaSaliente (Vertice* unVertice, Arista* unaArista);


/**
PRE:
	Parámetros
	Vertice* unVertice						--> vertice creado con "nuevoVertice" al que se le quitara la arista
	Arista*  unaArista                     --> arista que se desea quitar a unVertice

POS:
	Estado Interno
	El vertice no contiene mas esa arista en su conjunto de aristas salientes
*/
void quitarAristaSaliente  (Vertice* unVertice, Arista* unaArista);

/**
PRE:
	Parámetros
	Vertice* unVertice						--> vertice creado con "nuevoVertice"

POS:
	Valor de Retorno
	void*									--> Devuelve la referencia que contiene el vertice

*/
void* getInfo (Vertice* unVertice);

/**
PRE:
	Parámetros
	Vertice* unVertice						--> vertice creado con "nuevoVertice"
	void* info								--> información que se desea posea el vertice

POS:
	Valor de Retorno
	void*									--> Devuelve info a los efectos de anidar llamadas

	Comentario
	La info que tenía seteada el vertice no se libera ni destruye, tener cuidado con no
	dejar memoria colgada
*/
void* setInfo (Vertice* unVertice, void* info);

/**
PRE:
	Parámetros
	Vertice* unVertice						--> vertice creado con "nuevoVertice"

POS:
	Valor de Retorno
	Conjunto*								--> Devuelve el conjunto de aristas que salen del vertice en cuestión
*/
Conjunto* getAristasSalientes (Vertice* unVertice);

/**
PRE:
	Parámetros
	Vertice* unVertice						--> vertice creado con "nuevoVertice"
	void* InfoArista						--> Info que debe contener la arista
	bool (*sonIguales) (void*, void*) = NULL--> Funcion que señala si dos aristas son iguales. Si esta función es NULL
												se resuelve en base a si coinciden las referencias

POS:
	Valor de Retorno
	Arista*								--> Referencia a la Arista encontrada o NULL de no hayarla
*/
Arista* buscarAristaSaliente  (Vertice* unVertice, void* InfoArista, bool (*sonIguales) (void*, void*) = NULL);

#endif

