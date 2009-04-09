/****************************************
    TDA: juego
    Archivos: juego.h, juego.cpp
****************************************/
//definicion de constante para evitar que incluya dos veces la libreria

#ifndef __JUEGO__H__
#define __JUEGO__H__

#include "archivoRegistros.h"
#include "archivoTexto.h"
#include "Tablero.h"
#include "grupoequipos.h"
#include "ronda.h"
#include "definiciones.h"


/*	Axiomas:
            -El juego dura una cantidad X de rondas
*/

typedef int tRondas;
typedef int tPuntos;


struct Juego{
			Tablero tablero;
			GrupoEquipos equipos;
			tRondas cantRondas;
			tRondas rondaActual;
			ArchivoTexto aResultado;
			ListaDeBots::Lista botsEnjuego;
			Ronda ronda;
};

/*  pre:  el archivo de configuración pasado por parámetro debe estar creado y
          con los parametros correctos
    post: crea una instancia del juego cargando todos los archivos iniciales dejándola lista para comenzar.
          Si falla, pone el nro de rondas en -1.
*/
void crear(Juego &juego, ArchivoTexto &partida);

/*  pre:  el juego se encuentre creado
    post: libera recursos utilizados por el juego
*/
void destruir(Juego &juego);

/*  pre:  juego creado
    post: da comienzo a la partida, la cual dura la cantidad de rondas. Tambien genera el archivo de salida de la partida.
*/
void comenzar(Juego &juego);

/*  pre:  juego creado y comenzado.
    Post: termina el juego y completa el archivo de salida
*/
void terminar(Juego &juego);

/* pre:  juego creado
   post: devuelve la cantidad máxima de rondas del juego
*/
tRondas cantidadRondas(Juego &juego);

/*  pre:  juego creado
    post: devuelve el numero de la ronda actual, devuelve 0 si el juego todavía no comenzo
*/
tRondas rondaActual(Juego &juego);

/*  pre:  juego creado
    post: devuelve el equipo con mas puntos hasta el momento
*/
Equipo* equipoConMasPuntos(Juego &juego);

/*  pre:  juego creado y comenzado
    post: devuelve la ronda actual
*/
Ronda* obtenerRonda(Juego &juego);

/* pre: juego creado
   post: devuelve una referencia al archivo de resultados. No se lo debe
         destruir.
*/
ArchivoTexto* obtenerAResultados(Juego &juego);

/* pre: juego creado
   post: devuelve una referencia al tablero del juego
*/
Tablero* obtenerTablero(Juego &juego);

/* pre: juego creado
   post: devuelve una referencia a los equipos del juego
*/
GrupoEquipos* obtenerEquipos(Juego &juego);

/* pre: juego creado
   post: devuelve una referencia a los equipos del juego
*/
ListaDeBots::Lista* obtenerBotsEnJuego(Juego &juego);

/* pre: juego creado
   post: asigna la lista de todos los bots que estan jugando
*/
void asignarBotsEnJuego(Juego &juego);

#endif

