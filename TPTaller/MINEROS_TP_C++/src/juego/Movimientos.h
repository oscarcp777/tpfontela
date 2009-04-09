/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************
 * TDA Movimientos
 * Archivo : Movimientos.h , Movimientos.cpp
 ******************************************/
#ifndef __MOVIMIENTOS__H__
#define __MOVIMIENTOS__H__

#include "definiciones.h"
#include "dado.h"

//TIPO DE DATO

//REMITIRSE AL ARCHIVO "definiciones.h"

/*Axiomas:
        -El valor de nada puede solamente ser mayor o igual a 1
*/

/* Primitivas */

/*  pre:  -
    post: crea una instancia de movimientos
*/
void crear(Movimientos &movimientos);

/*  pre:  movimientos creados
    post: le asigna a los movimientos valores -1
*/
void destruir(Movimientos &movimientos);

/*  pre:  movientos creados
    post: devuelve el valor de arriba
*/
prioridadMovimiento obtenerArriba(const Movimientos &movimientos);

/*  pre: movimientos creados
    post: asigna el valor de movimiento a arriba
*/
void asignarArriba(Movimientos &movimientos, prioridadMovimiento valor);

/*  pre:  movientos creados
    post: devuelve el valor de abajo
*/
prioridadMovimiento obtenerAbajo(const Movimientos &movimientos);

/*  pre: movimientos creados
    post: asigna el valor de movimiento a abajo
*/
void asignarAbajo(Movimientos &movimientos, prioridadMovimiento valor);

/*  pre:  movientos creados
    post: devuelve el valor de derecha
*/
prioridadMovimiento obtenerDerecha(const Movimientos &movimientos);

/*  pre: movimientos creados
    post: asigna el valor de movimiento a derecha
*/
void asignarDerecha(Movimientos &movimientos, prioridadMovimiento valor);

/*  pre:  movientos creados
    post: devuelve el valor de izquierda
*/
prioridadMovimiento obtenerIzquierda(const Movimientos &movimientos);

/*  pre: movimientos creados
    post: asigna el valor de movimiento a izquierda
*/
void asignarIzquierda(Movimientos &movimientos, prioridadMovimiento valor);

/*  pre:  movientos creados
    post: devuelve el valor de nada
*/
prioridadMovimiento obtenerNada(const Movimientos &movimientos);

/*  pre: movimientos creados
    post: asigna el valor de movimiento a nada
*/
void asignarNada(Movimientos &movimientos, prioridadMovimiento valor);

/*  pre:  instancia de movimientos creada
    post: devuelve el movimiento con mayor prioridad. Si hay dos mayores,
          devuelve uno al azar (el calculo lo hace mediante el dado)

*/
EnumMovimiento obtenerMayorPrioridad(const Movimientos &movimientos);
#endif

