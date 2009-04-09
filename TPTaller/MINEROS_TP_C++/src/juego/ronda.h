/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA RONDA                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/

#ifndef _RONDA_H_
#define _RONDA_H_

#include "definiciones.h"
#include "turno.h"
#include "tablero.h"
#include "bot.h"
#include "cadena.h"
#include "archivoTexto.h"
#include "Piladeturnos.h"
#include "dado.h"
#include "listadebots.h"
#include "GrafoRecorridos.h"

/*****************************TIPO DE DATO*************************************/
struct Ronda {
    int nroronda;
    Pturnos::Pila turnos;
};

/********************************AXIOMAS***************************************/
/* 1 - El número de ronda es único, por ello solo puede ser asignado en su
creación. */

/*******************************PRIMITIVAS*************************************/

/* Ronda Crear:
Pre: Ninguna.
Post: Crea la ronda, con el nro pasado como parámetro y sin turnos. */

void crear(Ronda &ronda1, int nroronda);

/* Ronda Destruir:
Pre: Ronda creada.
Post: Destruye la ronda, poniendo su número en -1 y vaciando el conjunto de turnos */

void destruir(Ronda &ronda1);

/* Get nro:
Pre: Ronda creada.
Post: Devuelve el nro de la ronda. */

int getnro(const Ronda &ronda1);

/* Llenar Ronda:
Pre: Ronda creada y vacia.
Post: Llena la ronda de turnos de forma azarosa. */

void llenarRonda(Ronda &ronda1, ListaDeBots::Lista &listabots);

/* Realizar Turno:
Pre: Ronda creada y llena, archivo de salida creado externamente.
Post: Toma un turno de la ronda y lo ejecuta. */

void realizarTurno(Ronda &ronda1, Tablero &tablero1, ArchivoTexto &archsalida,
                            ListaDeBots::Lista &listabots, int Cantidad, int Recurso);

/* Agregar Encabezado:
Pre: Ronda creada y archivo de salida creado externamente.
Post: Llena el archivo de salida con el encabezado de la ronda. */

void agregarEncabezado(Ronda &ronda1, ArchivoTexto &archsalida);

/* Agregar Perforadora:
Pre: Ronda creada, bot y archivo de salida creados externamente.
Post: Llena el archivo de salida con los datos de la perforadora
pertenciente al bot pasado como parámetro . */

void agregarPerforadora(Ronda &ronda1, Bot &bot1, ArchivoTexto &archsalida);

/* Agregar Pie:
Pre: Ronda creada y archivo de salida creado externamente.
Post: Llena el archivo de salida con el pie de la ronda. */

void agregarPie(Ronda &ronda1, Tablero &tablero1, ArchivoTexto &archsalida,
                        ListaDeBots::Lista &listabots, GrupoEquipos* grupo);

/* Verificar Salidas:
Pre: Ronda, tablero creados. Lista de bots llena.
Post: Marca que perforadora tienen salida y cuales no.
*/

void VerificarSalidas(Ronda &ronda1, Tablero &tablero1, ListaDeBots::Lista &listabots);


/* Jugar:
Pre: Ronda creada, tablero y archivo de texto creados externamente.
Post: Realiza la dinámica de la ronda completa. */

void jugar(Ronda &ronda1, Tablero &tablero1, ArchivoTexto &archsalida,
                    ListaDeBots::Lista &listabots, GrupoEquipos* grupo);

#endif

/******************************************************************************/

