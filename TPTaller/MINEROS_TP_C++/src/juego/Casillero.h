/****************************************
    TDA: casillero
    Archivos: casillero.h, casillero.cpp
****************************************/
//definicion de constante para evitar que incluya dos veces la libreria

#ifndef __CASILLERO__H__
#define __CASILLERO__H__

#include "minerales.h"
#include "bot.h"
#include "definiciones.h"

/* TIPO DE DATO */

/* REMITIRSE AL ARCHIVO "definiciones.h" */

/* Axiomas:
            - La tuberia esta relacionada con el equipo que la posee
            - No puede haber una tuberia sin equipo
            - Puede no haber tuberia
            - Puede estar vacio el casillero
            - No puede haber un bot y un mineral a la vez en un casillero
            - El id de casillero debe ser mayor a 0
*/

/* Primitivas */

/*  pre:  el id de casillero debe ser unico y mayor a 0
    post: Crea una instancia de casillero lista para ser usada. Deja inicialiazdo
          el casillero como vacio.

    casillero: casillero a crear
*/
void crear(Casillero &casillero, int id);

/*  pre:  casillero creado
    post: libera recursos utilizados por el casillero y lo inutiliza

    casillero: casillero a destruir
*/
void destruir(Casillero &casillero);

/*  pre:  casillero creado
    post: asigna al casillero una referencia a un bot

    casillero: casillero al cual se asigna
    bot: referencia al bot a asignar
*/
void asignarBot(Casillero &casillero, Bot* bot);

/*  pre:  casillero creado
    post: devuelve la referencia al bot que posee el casillero

    casillero: casillero del cual se obtiene
*/
Bot* obtenerBot(const Casillero &casillero);

/*  pre:  casillero creado
    post: Quita el bot del casillero, para esto asigna vacio.

    casillero: casillero del cual se obtiene
*/
void quitarBot(Casillero &casillero);

/*  pre:  casillero creado
    post: asigna al casillero un mineral

    casillero: casillero al cual se asigna
    mineral: mineral que se asigna
*/
void asignarMineral(Casillero &casillero, Mineral mineral);

/*  pre:  casillero creado
    post: obtiene un puntero al mineral de un casillero

    casillero: casillero del cual se obtiene
*/
Mineral* obtenerMineral(Casillero &casillero);

/*  pre:  casillero creado
    post: quita el mineral del casillero. Asigna el mineral ninguno.

    casillero: casillero del cual se quita
*/
void quitarMineral(Casillero &casillero);

/*  pre:  casillero creado.
    post: asigna la referencia al dato del vertice. No se debe destruir
          el mismo.

    casillero: casillero del cual se obtiene
*/
void asignarTuberia(Casillero &casillero, DatoVertice* dato);

/*  pre:  casillero creado
    post: obtiene el equipo del cual es la tuberia. Si no tiene ningun vertice
          devuelve -1

    casillero: casillero del cual se obtiene
*/
Tuberia obtenerTuberia(Casillero &casillero);

/*  pre:  casillero creado
    post: obtiene una referencia a la info del vertice del casillero.

    casillero: casillero del cual se obtiene
*/
Tuberia obtenerTuberia(Casillero &casillero);

DatoVertice* obtenerPunteroTuberia(Casillero &casillero);
/*  pre:  casillero creado
    post: asigna a las variables pasadas por parametros los puntos necesarios
          para moverse a este casillero. Esto lo calcula mediante los puntos
          especificados:
                        -20 pts de energia por matar otra perforadora
                        -1 pto de energia, 4 de madera y 2 de hierro para
                         construir conducto
                        -10 pts de energia por destruir el conducto de otro equipo
                        -Los pts de energia variables del mineral por procesarlo
*/
void obtenerPuntosNecesarios(Casillero &casillero, tId_Equipo equipoBot, Energia &energia, Madera &madera, Hierro &hierro);

/* Sin Bot:
  pre : Casillero Creado.
  post: Devuelve la representacion de un casillero sin bot.
*/
Bot* SinBot();

/* Sin Tuberia:
  pre : Casillero Creado.
  post: Devuelve la representacion de un casillero sin tuberia.
*/

DatoVertice* SinTuberia();

/* Sin Mineral:
  pre : Casillero Creado.
  post: Devuelve la representacion de un casillero sin mineral.
*/

Mineral* SinMineral();

/*
  pre : Casillero creado
  post: Devuelve el id del casillero
*/
int obtenerId(Casillero &casillero);


#endif

