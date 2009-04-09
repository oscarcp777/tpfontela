/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************
 * TDA Perforadora
 * Archivo : Perforadora.h , Perforadora.cpp
 ******************************************/


#ifndef __PERFORADORA_H__
#define __PERFORADORA_H__

#include "CargaPerforadora.h"   /* utiliza el TDA CargaPerforadora*/
#include "Entorno.h"


/******************************************************************************/
/* Declaracion de tipos */
/*----------------------*/

/* REMITIRSE AL ARCHIVO "definiciones.h" */


/******************************************************************************/
/* Definición del Tipo de Dato */
/*-----------------------------*/

/* REMITIRSE AL ARCHIVO "definiciones.h" */


/******************************************************************************/
/* Declaración de Primitivas */
/*---------------------------*/

/*
  pre : ---------------------------------
  post: crea perforadora y la deja lista para ser usada

  Perforadora: Perforadora a ser creada.
  ID: identificador de la perforadora.
  Entorno: valor de tipo entorno inicial.
   */
void crear(Perforadora& perforadora,TipoID ID,Entorno entorno);

/*----------------------------------------------------------------------------*/

/*
  pre : Perforadora ya ha sido creada en crear();
  post: Libera los recursos que utiliza la Perforadora, y esta queda invalidada
        para ser usada;

  Perforadora: Perforadora a ser destruida;
*/
void destruir (Perforadora& perforadora);
/*----------------------------------------------------------------------------*/

/*
  pre : La perforadora debe haber sido creada en crear();
  post: Devuelve el Id de la perforadora que se pase por parametro;

  Perforadora: Perforadora de la cual se obtiene el ID;
*/
TipoID getID(Perforadora & perforadora );

/*----------------------------------------------------------------------------*/

/*
  pre : La perforadora debe haber sido creada en Perforadora_Crear();
  post: Devuelve un puntero a la carga que posee la perforadora;

*/
CargaPerforadora*  getCarga(Perforadora& perforadora);

/*----------------------------------------------------------------------------*/

/*
  pre : La perforadora debe haber sido creada con Perforadora_Crear().
  post: Devuelve un puntero al entorno de la perforadora pasada por parametro.
Perforadora: perforadora sobre la cual se invoca la primitiva.
*/
Entorno* getEntorno(Perforadora& perforadora);

/*----------------------------------------------------------------------------*/

/*
  pre :La perforadora debe haber sido creada en crear();
  post:Cambia el valor que posee la BodegaPuntos, este debe ser mayor a 0(cero)

  Perforadora: Perforadora sobre la cual actua la primitiva.
  BodegaPuntos: nuevo valor de bodegaPuntos.
*/
void setBodegaPuntos (Perforadora& perforadora, BodegaPuntos bodegaPuntos);
/*----------------------------------------------------------------------------*/

/*
  pre : La perforadora debe haber sido creada en crear().
  post: Devuelve el valor de BodegaPuntos.

  Perforadora: Perforadora sobre la cual actua la primitiva.

*/
BodegaPuntos getBodegaPuntos(Perforadora& perforadora);

/*----------------------------------------------------------------------------*/

/*
  pre : La perforadora debe haber sido creada en crear().
  post: Devuelve si tiene salida.

  Perforadora: Perforadora sobre la cual actua la primitiva.

*/
bool getSalida(Perforadora& perforadora);

/*----------------------------------------------------------------------------*/

/*
  pre : La perforadora debe haber sido creada en crear().
  post: Coloca el estado de salida de la perforadora.

  Perforadora: Perforadora sobre la cual actua la primitiva.
  salida: Vble que vale true si la perf tiene salida y false de lo contrario.
*/

void setSalida(Perforadora& perforadora, bool salida);

/*----------------------------------------------------------------------------*/

#endif


