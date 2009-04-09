/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA TURNO                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/

#ifndef _TURNO_H_
#define _TURNO_H_

#include "definiciones.h"
#include "bot.h"
#include "listadebots.h"
#include "archivoTexto.h"
#include "tablero.h"
#include "cadena.h"

/*****************************TIPO DE DATO*************************************/

struct turno {
    int nro;
    Bot* botasignado;
};

/********************************AXIOMAS***************************************/
/* 1 - El n�mero de turno es �nico, por ello solo puede ser asignado en su
creaci�n. */

/*******************************PRIMITIVAS*************************************/

/* Turno crear:
Pre: El bot perteneciente al turno debe ser creado con anterioridad.
Post: Crea el turno, con el bot y el n�mero pasados como par�metro. */

void crear(turno &turno1, int nro, Bot &botaasignar);

/* Turno destruir:
Pre: El turno debe estar creado.
Post: Invalida la utilizaci�n del turno. Coloca el nro en -1 y elimina la ref
al bot. */

void destruir(turno &turno1);

/* Jugar:
Pre: El turno debe estar creado,el tablero y el archivo de salida tambi�n.
Post: El bot realiza f�sicamente su jugada en el tablero. */

void jugar(turno &turno1, Tablero &tablero1, ArchivoTexto &archsalida,
                    ListaDeBots::Lista &listabots);

/* Registrar:
Pre: El turno debe estar creado, y el archivo de salida tambi�n.
Post: Registra el movimiento realizado en el archivo de salida. */

void registrar(turno &turno1, EnumMovimiento movimiento, ArchivoTexto &archsalida);

/* SetBot:
Pre: El turno debe estar creado, el bot asignado debe estar creado.
Post: Asigna un nuevo bot al turno.  */

void setBot(turno &turno1, Bot &botaasignar);

/* GetBot:
Pre: El turno debe estar creado.
Post: Devuelve un puntero al bot del turno. */

Bot* getBot(const turno &turno1);

/* GetNro:
Pre: El turno debe estar creado.
Post: Devuelve el n�mero del turno. */

int getNro(const turno &turno1);

#endif

/******************************************************************************/


