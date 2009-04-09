/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                               TDA BOT                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/

#ifndef _BOT_H_
#define _BOT_H_

#include "definiciones.h"
#include "Perforadora.h"
#include "estrategia.h"


/********************************AXIOMAS***************************************/

/*  1- El Id de cada bot se coloca en la creación y luego no puede modifircarse.
    2- Un bot puede pertenecer a un único equipo.
    3- Un bot se relaciona a una perforadora en particular.
    4- Un bot tiene una única estrategia.
    5- Los ID son números enteros que van de 1 a 9999.
    6- El ID = -1 esta reservado para condiciones de invalidez.               */

/******************************COMPOSICION*************************************/
struct Equipo;
struct Bot {
    tId_Bot ID_bot; // Identificador propio del bot.
    tId_Equipo ID_equipo; // Identificador del equipo al que pertenece el bot.
    Equipo* ptrequipo; //Puntero al equipo al cual pertenece
    Estrategia estrategia; // Estrategia utilizada por el bot.
    Perforadora perforadora; // Perforadora asociada al bot.
};

/*******************************PRIMITIVAS*************************************/

/* Crear:
Pre: Ninguna.
Post: Bot creado, con un ID propio y de equipo asignado,estrategia  y
      perforadora creados.

Bot1: Instancia sobre la que se aplica la primitiva.
ID_bot: Valor de ID inicial.
ID_equipo: Valor de ID inicial de equipo.
*/

void crear(Bot &Bot1,tId_Bot ID_bot,tId_Equipo ID_equipo, Equipo* Ptrequipo);

/* Destruir:
Pre: El bot debe estar creado.
Post: El bot queda inválido para su posterior utilización.
      El ID propio queda en -1.

Bot1: Instancia sobre la que se aplica la primitiva.
*/

void destruir(Bot &Bot1);

/* Get Estrategia:
Pre: El bot debe estar creado.
Post: Devuelve un puntero a la estrategia del bot.

Bot1: Instancia sobre la que se aplica la primitiva.
*/

Estrategia* get_Estrategia(Bot &Bot1);

/* Get ID:
Pre: El bot debe estar creado.
Post: Devuelve el ID propio del bot.

Bot1: Instancia sobre la que se aplica la primitiva.
*/

tId_Bot get_ID(const Bot &Bot1);

/*Get Equipo:
Pre: El bot debe estar creado.
Post: Devuelve el ID del equipo al que pertenece el Bot.

Bot1: Instancia sobre la que se aplica la primitiva.
*/

tId_Equipo get_Equipo(const Bot &Bot1);

/*Get PtrEquipo:
Pre: El bot debe estar creado.
Post: Devuelve un puntero al equipo al que pertenece el Bot.

Bot1: Instancia sobre la que se aplica la primitiva.
*/

Equipo* get_PtrEquipo(const Bot &Bot1);

/*Get Perforadora:
Pre: El bot debe estar creado.
Post: Devuelve un puntero a la perforadora del bot.

Bot1: Instancia sobre la que se aplica la primitiva.
*/

Perforadora* get_Perforadora(Bot &Bot1);

/*Realizar Movimiento:
Pre: El bot debe estar creado con equipo asignado. La estrategia y la perforadora
     deben estar previamente asignados.
Post: Devuelve el movimiento válido que el bot desea realizar,
      basado en su estrategia.

Bot1: Instancia sobre la que se aplica la primitiva.
*/

EnumMovimiento realizar_Movimiento(Bot &Bot1);



#endif

/******************************************************************************/

