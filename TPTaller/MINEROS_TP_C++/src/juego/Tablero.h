/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA Tablero                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/

/****************************************
    TDA: Tablero
    Archivos: tablero.h, tablero.cpp
****************************************/

#ifndef __TABLERO__H__
#define __TABLERO__H__
#include "MatrizD.h"
#include "listadebots.h"
#include "archivoTexto.h"
#include "definiciones.h"
#include "cadena.h"
#include "dado.h"
#include "casillero.h"
#include "equipo.h"
#include "grupoequipos.h"
#include "Grafo.h"


/*---------------------------------------------------------------------------*/
/* Axiomas :
            - Primera fila es reservada para posicionar inicialmente a los bots
              en forma azaroza y esta luego no podra volver a ser utilizada.*/


/*----------------------------------------------------------------------------*/

struct Tablero{
               MatrizDinamica Matriz;
               Grafo *grafo;
               DatoVertice entrada;//vertice que contiene a todos los que
                                   //entran
};


/****************************************************************************/
/*  Primitivas  */
/*--------------*/

/* Pre: Archivo mnadadopor parametro debe estar creado.
   Post:Deja la instancia de tablero creada en memoria con sus dimensiones
        y los casilleros con las fichas iniciales indicadas por el archivo
        de tablero pasado como parámetro.
*/

void Crear(Tablero &tablero, ArchivoTexto &aTablero);
/*---------------------------------------------------------------------------*/

/* Pre: El tablero debe haber sido creado con Tablero_Crear().
   Post: Libera las entidades del tablero y lo destruye, dejandolo inavilitado
         para ser utilizado.

*/

void Destruir(Tablero &Tablero);
/*---------------------------------------------------------------------------*/

/* Pre:El tablero debe haber sido creado con Tablero_Crear().
   Post:ubica los bots provenientes del archvio pasado por parametro en forma
        azarosa en la primera fila del tablero.
*/

void UbicarBotsIniciales(Tablero &tablero, ListaDeBots::Lista& botIniciales);
/*---------------------------------------------------------------------------*/

/* Pre: El tablero debe haber sido creado con Tablero_Crear().
   Post:Realiza todas las actualizaciones de casilleros que implican mover un
        bot, en base a lo que hay en el casillero al cual el bot se va a mover.

*/

void moverBot(Tablero &Tablero,Bot* punteroBot,EnumMovimiento movimiento);
/*---------------------------------------------------------------------------*/

/* Pre:El tablero debe haber sido creado con Tablero_Crear().
   Post:devuelve el entorno de la perforadora actualizado.
*/

void ActualizarEntorno(Tablero &tablero,Bot &bot);

/*---------------------------------------------------------------------------*/

/* Pre: Tablero y archivo de texto pasado por parametro deben estar creados.
   Post:actualiza el archivo pasado por parametro con los datos de la matriz.
*/

void ActualizarSalida(Tablero &tablero,ArchivoTexto &archsalida, GrupoEquipos* grupo);
/*---------------------------------------------------------------------------*/

/* Pre: Tablero debe estar creado.
   Post: devuelve un puntero a la matriz del tablero.
*/

MatrizDinamica* getMatriz(Tablero &tablero);
/*---------------------------------------------------------------------------*/

/* Pre: Tablero, bot deben estar creados.
   Post: modifica en la referencia el valor de la fila y la columna
*/

void buscarCasillero(Tablero &tablero,Bot &bot, int &ContFila, int &ContColum);

/* Pre: Tablero creado
   Post: devuelve un puntero al casillero buscado.
*/

Casillero* buscarCasilleroPorId(Tablero &tablero,int id);

/* Pre:  Tablero creado
   Post: Devuelve un puntero al grafo con las rutas de los bots
*/
Grafo* getGrafo(Tablero &tablero);

/* Pre:  Tablero creado
   Post: Devuelve un puntero al dato del vertice de entrada
*/
DatoVertice* getEntrada(Tablero &tablero);

#endif
