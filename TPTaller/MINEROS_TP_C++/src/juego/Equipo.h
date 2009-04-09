/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA Equipo
 * Archivo : Equipo.h
 */

#ifndef __EQUIPO_H__
#define __EQUIPO_H__

#include "listadebots.h"
#include "bot.h"

#include "definiciones.h"



/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/
typedef Bot* Pbot;
/* Tipo de Dato */
struct Equipo {
                    tId_Equipo id;            //identificacion del equipo
                    std::string nombre;         // nombre del equipo///
                    char perfoChar;            // caracter perforad
                    char caminChar;            // caracter camino

                    ListaDeBots::Lista listBots;           // lista de bots a jugar
};

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : ninguna.
  post: equipo queda creado y preparado para ser usado.

  equipo : estructura de datos a ser creada.
  id: ident de equipo
  nom: nombre de equipo
  perChar: caracter q identif a la perforadora del equipo
  camChar: caracter q identif al camino del equipo
*/
void crearEquipo(Equipo &equip, tId_Equipo id, std::string nom, char perChar, char camChar);

/******************************************************************************/

/* pre: el equipo existe
   post: devuelbe el nombre del equipo

*/

std::string getnombre(Equipo &equip);

/******************************************************************************/

/* pre: el equipo existe
   post: devuelbe el id del equipo

*/

tId_Equipo getid(Equipo &equip);

/******************************************************************************/

/* pre: el equipo existe
   post: devuelbe el caracter asociado a los caminos del equipo

*/

char getCaracterCamino(Equipo &equip);

/******************************************************************************/

/* pre: el equipo existe
   post: devuelbe el caracter asociado a las perforadoras del equipo

*/

char getCaracterPerforadora(Equipo &equip);

/******************************************************************************/

/* pre: el equipo existe y tiene una lista de bots creada, pbot es el puntero
    al bot a cargar
   post: Adiciona el puntero a bot, en la lista de bots del equipo

*/

void cargarBotaEquip (Equipo &equip, Pbot pbot);

/******************************************************************************/

/* pre: el equipo existe,tiene una lista de bots creada, pbot es el puntero
    al bot a del cual se desea eliminar el nodo
   post: si pbot pretenece a la lista de bots, elimina el nodo. de caso
    no hace nada

*/

void sacarBot (Equipo &equip, Pbot pbot);

/******************************************************************************/

/* pre: el equipo existe,tiene una lista de bots creada
   post: devuelve la cantidad de bots q le pertencen al equipo

*/


int cantBots(Equipo &equip);
/******************************************************************************/

/* pre: el equipo existe,tiene una lista de bots creada y cargada,listabotsalida
    es una lista creada con crear lista de punteros a bot
   post: devuelve una lista con los bots q le pertencen al equipo.
   Aclaración: Agrega los bots del equipo a la lista pasada como parámetro. Si la
   lista ya tenia bots, entonces ahora tendra esos más los nuevos agregados.
*/


void ObtenerListaBots(Equipo &equip,ListaDeBots::Lista &listabotsalida);

/******************************************************************************/

/* pre: el equipo existe
   post: equipo queda en un estado invalido

*/

void destruirequipo(Equipo &equip);
/******************************************************************************/

/* pre:  el equipo existe y tiene bots asociados
   post: devuelve la suma de la cantidad de puntos de cada bot perteneciante
         al equipo

*/

BodegaPuntos GetPuntosEquipo(Equipo &equip);
/******************************************************************************/


#endif

