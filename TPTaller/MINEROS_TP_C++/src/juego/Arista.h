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

#ifndef __ARISTA_H_
#define __ARISTA_H_

#ifndef NULL
#define NULL 0
#endif

// Se define la existencia de un TDA llamado Arista
// Su objetivo es modelar las aristas de un grafo
// Esta muy orientado a ser una parte componente del Grafo y por ende deslinda muchas responsabilidades
// en el mismo. Ej. Saber el vertice origen de la misma.
struct Arista;

// Necesario porque hay primitivas que devuelven referencias a Vertice
#include "Vertice.h"

/**
PRE:
	Parámetros
	void*		info						--> Información que contendrá la nueva Arista
	Vertice*	verticeDestino				--> Vertice a Donde Apuntará la nueva Arista
	void (*eliminarInfoVertice) (void*)		--> Forma de eliminar la información referida por "info"

POS:
	Estado Interno
	La arista queda creada e inicializada con una info como información y verticeDestino como
	vertice destino de la misma. Asi mismo, conserva a eliminarInfoVertice como la forma
	para liberar info en caso de solicitarse su eliminación mediante eliminarArista

	Valor de Retorno
	Arista*								--> Una referencia a la nueva Arista

	Control de Error
	El valor de retorno será null en caso de no poderse alocar la memoria necesaria
*/
Arista* nuevaArista    ( void* info, Vertice* verticeDestino, void (*eliminarInfoVertice) (void*) );


/**
PRE:
	Parámetros
	Arista* unaArista						--> arista creada con "nuevaArista"

POS:
	Estado Interno
	La arista no puede ser utilizada nuevamente
	Si se había creado la misma con una función para eliminación de la Informacion
	por ella contenida, se ha invocado a dicha función y por ende debería quedar inutilizable
	a lo que apuntaba info.
*/
void     eliminarArista      ( Arista* unaArista   );

/**
PRE:
	Parámetros
	void*    AristaVoid					--> AristaVoid es una referencia a una arista creada con nuevaArista

POS:
	Estado Interno
	La arista apuntada por AristaVoid no puede ser utilizada nuevamente
*/
void     eliminarAristaVoid ( void*    AristaVoid );

/**
PRE:
	Parámetros
	Arista* unaArista						--> Arista (creada por nuevaArista) a la que se le solicita la información que contiene

POS:
	Valor de Retorno
	void*									--> devuelve la información contenida en la arista, generalemente conocida por Peso de la Arista
                                            (requerirá el casteo del usuario quien debe conocer el tipo que almaceno dentro de la arista)

	Comentario
	De modificarse lo apuntado por el valor de retorno, se modificará la información contenida en la arista
*/
void* getInfo (const Arista* unaArista);

/**
PRE:
	Parámetros
	Arista* unaArista						--> Arista (creada por nuevaArista) a la que se le quiere asignar su información
	void*    info							--> Información que se desea contenga la arista.

POS:
	Estado Interno
	La arista contiene ahora a info como información de la misma

	Valor de Retorno
	void*									--> devuelve un puntero a info. Sirve para anidar llamadas.

	Comentario
	La información a la que apuntaba la arista queda desreferenciada por la misma. Tener cuidado de no
	dejar memoria colgada. Proximas llamadas a getInfo devolverán info.
*/
void* setInfo (Arista* unaArista, void* info);

/**
PRE:
	Parámetros
	Arista* unaArista						--> Arista (creada por nuevaArista) a la que se le solicita el vertice al que llega

POS:
	Valor de Retorno
	Vertice*								--> Devuelve el vertice destino de la arista

    Comentario
	Si se modifica información del vertice devuelto impactará sobre el vertice destino de la arista.
*/
Vertice* getVerticeDestino ( const Arista* unaArista );

/**
PRE:
	Parámetros
	Arista* unaArista						--> Arista (creada por nuevaArista) a la que se le solicita el vertice al que llega
	Vertice* verticeDestino				--> nuevo VerticeDestino de la Arista en cuestión

POS:
	Estado Interno
	El vertice destino de la arista pasa a ser verticeDestino

	Valor de Retorno
	Vertice*								--> Devuelve verticeDestino. Sirve para enlazar llamadas.
*/
Vertice* setVerticeDestino ( Arista* unaArista, Vertice* verticeDestino );

#endif

