/**
Universidad de Buenos Aires
Facultad de Ingenier�a
75.41 Algoritmos y Programaci�n II
C�tedra Ing. Domingo T. Mandrafina

Notas del Autor:
Este archivo forma parte del ejemplo de implementac�n del TDA Grafos.

Los lineamientos tras los cuales se elabor� el presente son:

	a) Mostrar otra forma de construir y manejar TDA's
	b) Fortalecer el concepto de no Accesar Directamente los Atributos de un TDA
	c) Mostrar que un TDA no es simplemente un struct, sino que puede ser la composici�n
	   e interacci�n de varios TDA's (Arista, Vertice y Conjunto conforman un Grafo )
	d) Eliminar el concepto de que todo TDA es copiable (mediante el operador =) y que el
	   copiar un TDA es simplemente una primitiva mas del mismo.

Los mismos se vieron satisfechos en los siguientes aspectos de la codificaci�n:
	1) El acceso a los TDA's se efectua siempre por punteros al mismo.
	   Esto es lo mas cercano que se puede llegar con programaci�n estructurada
	   al concepto de referencias en lenguajes como Java, Smalltalk, etc.
	   Fortalece el concepto de Identidad de un TDA ya que en expresiones como ...

			TDA* unTDA    = new TDA;
			TDA* otroTDA;

			otroTDA = unTDA;

       ... lo que se copia es un puntero y por lo tanto, se mantiene la identidad del TDA original.
	   (en el ejemplo hay una sola instancia del TDA aunque se tenga 2 "referencias" al mismo)
	2) En ningun .h se definio la estructura del TDA en cuesti�n sino que simplemente
       se hace mencion a su existencia. En un par de lineas mas abajo se puede apreciar que
	   se declara la existencia de un TDA (struct) pero no su contenido. Esto permite poder
	   definir las primitivas de acceso al mismo (siempre con punteros, ya que se desconoce la
	   estructura y por lo tanto no se podr�a hablar de pasar por parametro al TDA dado) sin conocer
	   su composici�n.
	   Esto favorece fuertemente el concepto de abstracci�n.
	   Una consideraci�n mas a tener en cuenta, es que, los .cpp que hagan #include de este .h
	   no podr�n:

		- definir variables del tipo del TDA sino que deber�n definir punteros al TDA
		- accesar al contenido del TDA y por ende modificar su estado si no es por medio
		  de las primitivas
		- no podr�n copiar TDA si no es por medio de primitivas (esto sirve para evidenciar
		  que la operaci�n de copiado debe ser una primitiva mas del TDA)
	3) Por �ltimo, cabe mencionar que el mecanismo de instanciaci�n del TDA se sugiere que no sea
	   mediante ...

			new TDA;

       ... sino mediante las primitivas correposndientes que devuelven una referecia al TDA.

	        TDA* nuevoTDA();

       Esto permite comenzar a introducir conceptos como que un TDA no necesariamente se crea
	   vacio sino que puede forzarse a contener algun valor si solo se dejan constructores que reciben
	   parametros.

	   A dem�s, el no usar new TDA fortalece la idea de que puede haber otros TDA (o funciones en este caso)
	   que se encargan de generar TDA's dando lugar al concepto de Factory's que se ver� mas adelante
	   en Dise�o Orientado a Objetos
*/
#ifndef __CONJUNTO_H_
#define __CONJUNTO_H_

#ifndef NULL
#define NULL 0
#endif


// Se define la existencia de un TDA llamado Conjunto
// Su objetivo es modelar el concepto de Conjunto, es decir,
// elementos no duplicados agrupados bajo una misma entidad (el conjunto en si)
struct Conjunto;

/**
PRE:
	Par�metros
	void (*EliminarElemento)(void*) = NULL		--> Forma de eliminar la informaci�n contenida por el conjunto
	                                                Si esta funci�n es NULL, cada uno de los elementos deber�n
													eliminarse manualmente (o guardar referencias aparte) antes de destruir
													el conjunto para no dejar memoria perdida.

POS:
	Estado Interno
	El conjunto queda creado e inicializado. EliminarElemento ser� la funci�n invocada al querer
	eliminar cada uno de los elementos contenido en el al momento de invocar su destrucci�n
	mediante eliminarConjunto.

	Valor de Retorno
	Conjunto*									--> Referencia al conjunto generado

	Control de Error
	El valor de retorno ser� null en caso de no poderse alocar la memoria necesaria
*/
Conjunto* nuevoConjunto    ( void (*EliminarElemento) (void*) = NULL );

/**
PRE:
	Par�metros
	Conjunto* unConjunto                       --> conjunto creado con "nuevoConjunto"

POS:
	Estado Interno
	El conjunto no no puede ser utilizado nuevamente
	Para cada uno de los elementos contenidos en el mismo se ha invocado a la funci�n
	EliminarElemento (pasada al momento de crearse el conjunto)
*/
void       eliminarConjunto (Conjunto* unConjunto);

/**
PRE:
	Par�metros
	Conjunto* unConjunto                       --> conjunto creado con "nuevoConjunto"
	void* Elemento								--> informaci�n a la que referenciar� el elemento a agregar al conjunto

POS:
	Estado Interno
	El conjunto a generado un nuevo elemento que referencia a *Elemento.

	Valor de Retorno
	void*										--> Referencia a Elemento para poder anidar invocaciones

	Control de Errores
	Si Elemento ya hab�a sido agregado al conjunto, no se generar� un nuevo elemento
	respetando el concepto de no duplicidad de un conjunto.

*/
void*      agregarElemento  (Conjunto* unConjunto, void* Elemento);

/**
PRE:
	Par�metros
	Conjunto* unConjunto                       --> conjunto creado con "nuevoConjunto"
	void* Elemento								--> referencia al elemento que se busca
	bool (*sonIguales) (void*, void*) = NULL	--> Funci�n de comparacion de elementos.
													El parametro Elemento ser� el segundo parametro de esta funcion, el primero
													ser� cada uno de los elementos contenidos en el Conjunto

POS:
	Valor de Retorno
	void*										--> Si el elemento es encontrado devuelve
													la referencia al mismo o null en caso de no hallarlo.

	Comentario
	Si la funcion sonIguales es NULL se compara directamente referencia a referencia para
	ver si apuntan al mismo elemento.
*/
void*      buscarElemento   (Conjunto* unConjunto, void* Elemento, bool (*sonIguales) (void*, void*) = NULL);

/**
PRE:
	Par�metros
	Conjunto* unConjunto                       --> conjunto creado con "nuevoConjunto"
	void* Elemento								--> referencia al elemento que se desea quitar

POS:
	Estado Interno
	El conjunto deja de contener al elemento en cuesti�n.
*/
void       quitarElemento	(Conjunto* unConjunto, void* Elemento);

/**
PRE:
	Par�metros
	Conjunto* unConjunto                       --> conjunto creado con "nuevoConjunto"
POS:
	Valor de Retorno
	int											--> Devuelve la cantidad de elementos contenidos por el conjunto
*/
int        cardinalidad     (Conjunto* unConjunto);

/**
PRE:
	Par�metros
	Conjunto* unConjunto                       --> conjunto creado con "nuevoConjunto"

POS:
	Valor de Retorno
	bool										--> Booleano indicando si esta o no vacio.
*/
bool       estaVacio        (Conjunto* unConjunto);


// Se define la existencia de un TDA llamado IteradorConjunto
// Si bien, matematicamente las operaciones con conjuntos no incluyen recorrer los elementos
// del mismo, sino que a lo sumo se puede preguntar por la existencia o no de un elemento,
// Computacional/Algortimicamente es necesario poder recorrer los elementos componentes.
// Este TDA sirve basicamente para poder recorrer un conjunto. Como es de esperarse, esta intimamente
// relacionado con el mismo, al punto de conocer su estructura interna requeriendose para ello que
// se definan en el mismo .cpp
struct IteradorConjunto;

/**
PRE:
	Par�metros
	Conjunto* unConjunto						--> Conjunto creado con "nuevoConjunto"

POS:
	Estado Interno
	El iterador queda creado e inicializado.

	Valor de Retorno
	IteradorConjunto*							--> referencia al iterador creado

	Control de Error
	El valor de retorno ser� null en caso de no poderse alocar la memoria necesaria

    Comentarios:
	El iterador no soporta operaciones de adici�n / sustracci�n de elementos sobre
	el conjunto una vez creado el mismo.
*/
IteradorConjunto* nuevoIterador    (const Conjunto* unConjunto);

/**
PRE:
	Par�metros
	IteradorConjunto* unIteradorConjunto		--> Iterador de Conjuntos creado con "nuevoIterador"

POS:
	Estado Interno
	No es posible utilizarse nuevamente el iterador
*/
void               eliminarIterador (IteradorConjunto* unIteradorConjunto);

/**
PRE:
	Par�metros
	IteradorConjunto* unIteradorConjunto		--> Iterador de Conjuntos creado con "nuevoIterador"

POS:
	Estado Interno
	El iterador queda posicionado de forma tal de devolver el siguiente elemento, salvo que
	haya llegado al fin().
*/
void			   irAlSiguiente    (IteradorConjunto* unIteradorConjunto);

/**
PRE:
	Par�metros
	IteradorConjunto* unIteradorConjunto		--> Iterador de Conjuntos creado con "nuevoIterador"

POS:
	Valor de Retorno
	bool										--> Boolena indicando la si se han recorrido ya todos los elementos del conjunto
*/
bool               fin              (IteradorConjunto* unIteradorConjunto);

/**
PRE:
	Condicionantes
	No debe haberse alcanzado el fin del iterador, es decir fin(unIteradorConjunto) debe ser false

	Par�metros
	IteradorConjunto* unIteradorConjunto		--> Iterador de Conjuntos creado con "nuevoIterador"

POS:
	Valor de Retorno
	void*                                       --> Referencia al elemento contenido en el conjunto.
*/
void*			   obtenerElemento  (IteradorConjunto* unIteradorConjunto);


#endif

