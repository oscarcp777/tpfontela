/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/*****************************************************
 * TDA Carga
 * Archivo : CargaPerforadora.h , CargaPerforadora.cpp
 *****************************************************/



#ifndef __CARGAPERFORADORA_H__
#define __CARGAPERFORADORA_H__
#include "definiciones.h"

/******************************************************************************/
/* Declaracion de tipos */
/*----------------------*/

/* REMITIRSE AL ARCHIVO "definiciones.h" */


/******************************************************************************/
/* Definición del Tipo de Dato */
/*-----------------------------*/


/* REMITIRSE AL ARCHIVO "definiciones.h" */



/*----------------------------------------------------------------------------*/

/*
  pre : --------------
  post: crea cragaPerforadora , setea por defoult los valores de energia,
        hierro y madera;
        Energia: 15 (integer sin signo quince).
        Hierro:  10 (integer sin signo diez).
        Madera:  20 (integer sin signo veinte).


  Perforadora: perforadora a ser creada.
*/
void crear(CargaPerforadora& cargaPerforadora);

/*----------------------------------------------------------------------------*/

/*
  pre : La CargaPerforadora debe haber sido creada con crear().
  post: Libera los recursos que posee CargaPerforadora y la inutiliza.

 CargaPerforadora: CargaPerforadora a ser destruida;
*/
void destruir(CargaPerforadora& cargaPerforadora);

/*----------------------------------------------------------------------------*/
/*
  pre : CargaPerforadora a sido creado.
  post: Cambia el valor de la madera, este debe ser mayor a cero.

  Madera: nuevo valor de madera.
*/
void setMadera (CargaPerforadora& cargaPerforadora, Madera madera);


/*----------------------------------------------------------------------------*/

/*
  Pre :La CargaPerforadora debe haber sido creada.

  Post: Devuelve el valor de la madera de la cargaPerforadora que se pase por
  parametro.

  CargaPerforadora: CargaPerforadora sobre la cual actua la primitiva.

*/
Madera getMadera(CargaPerforadora& cargaPerforadora);

/*----------------------------------------------------------------------------*/

/*
  pre :La Cargaperforadora debe haber sido creada.
  post: Cambia el valor de hierro, este debe ser mayor a cero.

  CargaPerforadora: CargaPerforadora sobre la cual actua la primitiva.
  Hierro: nuevo valor de hierro.
*/
void setHierro(CargaPerforadora& cargaPerforadora, Hierro hierro);

/*----------------------------------------------------------------------------*/

/*
  pre : La CargaPerforadora debe haber sido creado con crear().
  post: Devuelve le valor de Hierro.

  CargaPerforadora: CargaPerforadora sore la cual actua la primitiva.
*/
Hierro getHierro(CargaPerforadora& cargaPerforadora);

/*----------------------------------------------------------------------------*/

/*
  pre : La CargaPerforadora debe haber sido creado con crear().

  post: Devuelve el valor de Energia.

  CargaPerforadora: CargaPerforadora sore la cual actua la primitiva.

*/
Energia getEnergia(CargaPerforadora& cargaPerforadora);
/*----------------------------------------------------------------------------*/

/*
  pre :La perforadora debe haber sido creada
  post: Cambia el valor de energia, este debe ser mayor a cero.

  CargaPerforadora: CargaPerforadora sobre la cual actua la primitiva.
  Energia: nuevo valor de energia.

*/
void setEnergia(CargaPerforadora& cargaPerforadora, Energia energia);
/*----------------------------------------------------------------------------*/
#endif


