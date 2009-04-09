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
#ifndef __Pila_H_
#define __Pila_H_

#ifndef NULL
#define NULL 0
#endif


// Se define la existencia de un TDA llamado Pila
// Su objetivo es modelar el concepto de Pila, es decir, tratamiento de información
// Último en Entrar - Primero en Salir (Last In - First Out)
struct Pila;

/**
PRE:
	Parámetros
	void (*eliminarInfo)(void*) = NULL		--> Forma de eliminar la información contenida en la Pila

POS:
	Estado Interno
	La Pila queda creada e inicializada. eliminarInfo será la función invocada al querer
	eliminar la información que quedase contenida en ella al momento de invocar su destrucción
	mediante eliminarPila.

	Valor de Retorno
	Pila*									--> Referencia a la Pila generada

	Control de Error
	El valor de retorno será null en caso de no poderse alocar la memoria necesaria
*/
Pila* nuevaPila    ( void (*eliminarInfo)(void*) = NULL );

/**
PRE:
	Parámetros
	Pila* unaPila							--> Pila creada con "nuevaPila"

POS:
	Estado Interno
	La Pila no puede ser utilizada nuevamente
*/
void   eliminarPila (Pila* unaPila);

/**
PRE:
	Parámetros
	Pila* unaPila							--> Pila (creada con "nuevaPila") a la cual se agregará el elemento
	void* Elemento							--> referencia a almacenar en la Pila

POS:
	Estado Interno
	La referencia fue agregada a la Pila. Todo cambio que se haga a la información
    referenciada por Elemento impactará, por consiguiente en los futuros usos que se
	haga de la información guardada en la Pila.
	Una invocación a estaVacia devolverá falso.

	Valor de Retorno
	void*									--> Referencia a Elemento. Sirve para hacer anidaciones de llamadas
*/
void*  agregarElemento ( Pila* unaPila, void* Elemento );

/**
PRE:
	Parámetros
	Pila* unaPila							--> Pila (creada por nuevaPila) a la cual se le solicita el elemento

POS:
	Estado Interno
	Sucesivas llamadas a esta primitiva vaciarán la Pila.

	Valor de Retorno
	void*									--> Referencia al último Elemento colocado con agregarElemento.

	Control de Errores
	void*									--> Será null si no quedan mas elementos en la Pila. No debe utilizarse como
												indicador de que la Pila esta vacia por cuanto, se puede haber apilado un null,
												con lo que se confundirian los conceptos.
*/
void*  quitarElemento  ( Pila* unaPila );

/**
PRE:
	Parámetros
	Pila* unaPila							--> Pila (creada por nuevaPila) de la cual se quiere saber si esta vacia

POS:
	Valor de Retorno
	bool									--> Booleano indicando si esta o no vacia.
*/
bool   estaVacia       ( Pila* unaPila );

#endif

