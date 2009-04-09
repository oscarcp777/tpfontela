/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                               TDA CARA                                     *
 ******************************************************************************/

/********************************HEADERS***************************************/

#ifndef _CARA_H_
#define _CARA_H_

/********************************AXIOMAS***************************************/
/* 1 - Una vez creada la cara, no se puede cambiar su valor.
   2 - Valor = -1 significa cara inv�lida.
   3 - El valor es un n�mero entero de 1 a 9999.
*/

/******************************COMPOSICION*************************************/

typedef int Valor;

struct Cara {
    Valor valor; //Valor de la cara
};

/*******************************PRIMITIVAS*************************************/

/* Crear:
Pre: Ninguna.
Post: Cara creada con un valor fijo asignado. Si el valor esta mal pasado, asigna
un -1 al valor de la cara, que significa inv�lido.

cara1: Instancia sobre la que se aplica la primitiva.
valor: Valor inicial de la cara.
*/

void crear(Cara &cara1, Valor valor);

/* Destruir:
Pre: Cara creada.
Post: Destruye la cara invalidando su posterior utilizaci�n.

cara1: Instancia sobre la que se aplica la primitiva.
*/

void destruir(Cara &cara1);

/* Get valor:
Pre: Cara creada.
Post: Devuelve el valor de la cara.

cara1: Instancia sobre la que se aplica la primitiva.
*/

int get_Valor(const Cara &cara1);

#endif
/******************************************************************************/



