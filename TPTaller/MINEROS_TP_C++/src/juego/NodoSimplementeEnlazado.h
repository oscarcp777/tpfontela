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

       ... sino mediante las primitivas correspondientes que devuelven una referecia al TDA.

	        TDA* nuevoTDA();

       Esto permite comenzar a introducir conceptos como que un TDA no necesariamente se crea 
	   vacio sino que puede forzarse a contener algun valor si solo se dejan constructores que reciben 
	   parametros.

	   A dem�s, el no usar new TDA fortalece la idea de que puede haber otros TDA (o funciones en este caso)
	   que se encargan de generar TDA's dando lugar al concepto de Factory's que se ver� mas adelante 
	   en Dise�o Orientado a Objetos
*/
#ifndef __NODOSIMPLEMENTEENLAZADO_H_
#define __NODOSIMPLEMENTEENLAZADO_H_

// Se define la existencia de un TDA NodoSimplementeEnlazado
// Su objetivo es modelar el concepto de Nodo, muy utilizado para las estructuras como
// Lista, Pila, Cola, etc.
// En particular se basa en la definici�n de SimplementeEnlazados.
// El hecho de que el usuario de la pila, cola o lista no deba usar este TDA. Ya que 
// dichas estructuras nunca devuelven referencias de este tipo hace que sea muy facil cambiar
// la implementaci�n de las pilas, colas o lista por nodos doblemente enlazados u de otro tipo.
struct NodoSimplementeEnlazado;

/**
PRE: 
	Par�metros
	void*						Info			--> Referencia a almacenarse en el Nodo
	NodoSimplementeEnlazado*	Siguiente		--> Para enlazar con otro Nodo

POS:
	Estado Interno
	El nodo queda creado e inicializado. Info ser� la informaci�n que el almacene y siguiente 
	ser� el proximo Nodo.

	Valor de Retorno
	NodoSimplementeEnlazado*					--> Referencia al nodo generado

	Control de Error
	El valor de retorno ser� null en caso de no poderse alocar la memoria necesaria
*/
NodoSimplementeEnlazado* nuevoNodoSimplementeEnlazado    ( void* Info, NodoSimplementeEnlazado* Siguiente );

/**
PRE: 
	Par�metros
	NodoSimplementeEnlazado* unNodo			--> Nodo creado con nuevoNodoSimplementeEnlazado

POS:
	Estado Interno
	No se puede volver a utilizar el Nodo. Notar que no se elimina la informaci�n a la que
	referencia el mismo.
*/
void                      eliminarNodoSimplementeEnlazado ( NodoSimplementeEnlazado* unNodo );

/**
PRE: 
	Par�metros
	NodoSimplementeEnlazado* unNodo			--> Nodo creado con nuevoNodoSimplementeEnlazado
	void* Info									--> Informaci�n a setearle al nodo
POS:
	Estado Interno
	Info queda seteada como la informaci�n componente del nodo. Si el nodo ten�a una referencia anterior
	esta se pierde.

	Valor de Retorno
	void*										--> Devuelve un referencia a Info para anidar llamadas
*/
void*                     setInfo                         (NodoSimplementeEnlazado* unNodo, void* Info);

/**
PRE: 
	Par�metros
	NodoSimplementeEnlazado* unNodo			--> Nodo creado con nuevoNodoSimplementeEnlazado
POS:
	Valor de Retorno
	void*										--> Informaci�n contenida por el nodo 
*/
void*                     getInfo                         (NodoSimplementeEnlazado* unNodo);

/**
PRE: 
	Par�metros
	NodoSimplementeEnlazado* unNodo			--> Nodo creado con nuevoNodoSimplementeEnlazado
	NodoSimplementeEnlazado* nodoSiguiente		--> Referencia al Siguiente nodo al que debe apuntar el actual

POS:
	Estado Interno
	El nodo guarda a nodoSiguiente como su proximo nodo.

	Valor de Retorno
	NodoSimplementeEnlazado*					--> Devuelve un referencia a nodoSiguiente para anidar llamadas
*/
NodoSimplementeEnlazado* setSiguiente                    (NodoSimplementeEnlazado* unNodo, NodoSimplementeEnlazado* nodoSiguiente);

/**
PRE: 
	Par�metros
	NodoSimplementeEnlazado* unNodo			--> Nodo creado con nuevoNodoSimplementeEnlazado
POS:
	Valor de Retorno
	NodoSimplementeEnlazado*					--> Devuelve un referencia al siguiente nodo de unNodo
*/
NodoSimplementeEnlazado* getSiguiente                    (NodoSimplementeEnlazado* unNodo);

#endif

