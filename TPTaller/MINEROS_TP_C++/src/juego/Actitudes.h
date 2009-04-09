/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************
 * TDA Movimientos
 * Archivo : Movimientos.h , Movimientos.cpp
 ******************************************/
#ifndef __ACTITUDES__H__
#define __ACTITUDES__H__

#include "definiciones.h"

/* TIPO DE DATO */

/* REMITIRSE AL ARCHIVO "definiciones.h" */


/*  pre:  -
    post: crea una instancia de actitudes
*/
void crear(Actitudes &actitudes);

/*  pre:  actitudes creados
    post: le asigna a las actitudes valores -1
*/
void destruir(Actitudes &actitudes);

/*  pre:  instancia creada
    post: asigna un nuevo valor
*/
void asignarProcesarOro(Actitudes &actitudes, prioridadActitud valor);

/*  pre:  instancia creada
    post: devuelve el valor
*/
prioridadActitud obtenerProcesarOro(const Actitudes &actitudes);

/*  pre:  instancia creada
    post: asigna un nuevo valor
*/
void asignarProcesarPlata(Actitudes &actitudes, prioridadActitud valor);

/*  pre:  instancia creada
    post: devuelve el valor
*/
prioridadActitud obtenerProcesarPlata(const Actitudes &actitudes);

/*  pre:  instancia creada
    post: asigna un nuevo valor
*/
void asignarProcesarCobre(Actitudes &actitudes, prioridadActitud valor);

/*  pre:  instancia creada
    post: devuelve el valor
*/
prioridadActitud obtenerProcesarCobre(const Actitudes &actitudes);

/*  pre:  instancia creada
    post: asigna un nuevo valor
*/
void asignarConstruirConducto(Actitudes &actitudes, prioridadActitud valor);

/*  pre:  instancia creada
    post: devuelve el valor
*/
prioridadActitud obtenerConstruirConducto(const Actitudes &actitudes);

/*  pre:  instancia creada
    post: asigna un nuevo valor
*/
void asignarDestruirConducto(Actitudes &actitudes, prioridadActitud valor);

/*  pre:  instancia creada
    post: devuelve el valor
*/
prioridadActitud obtenerDestruirConducto(const Actitudes &actitudes);

/*  pre:  instancia creada
    post: asigna un nuevo valor
*/
void asignarDestruirPerforadora(Actitudes &actitudes, prioridadActitud valor);

/*  pre:  instancia creada
    post: devuelve el valor
*/
prioridadActitud obtenerDestruirPerforadora(const Actitudes &actitudes);

/*  pre:  instancia creada
    post: devuelve el movimiento con mayor valor
*/


#endif

