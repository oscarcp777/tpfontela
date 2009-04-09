/****************************************
    TDA: estrategia
    Archivos: estrategia.h, estrategia.cpp
****************************************/
//definicion de constante para evitar que incluya dos veces la libreria
#ifndef __ESTRATEGIA__H__
#define __ESTRATEGIA__H__

//Headers
#include "bot.h"
#include "Movimientos.h"
#include "Actitudes.h"
#include "casillero.h"
#include "Perforadora.h"
#include "definiciones.h"


//definicion del tipo de datos que posee la estrategia

/* REMITIRSE AL ARCHIVO "definiciones.h" */

/* Primitivas */

/*  pre: -
    post: crea una estrategia y la prepara para que se le carguen los valores.

    estrategia: estrategia a ser creada
*/
void crear(Estrategia &estrategia);

/*  pre: instancia de estrategia creada
    post: libera los recursos utilizados por la estrategia e inutiliza la misma

    estrategia: estrategia a ser destruida
*/
void destruir(Estrategia &estrategia);

/*  pre:  estrategia creada.
    post: asigna a la estrategia pasada como parametro los movimientos

    estrategia: estrategia al cual se le agregan movimientos
    movimiento: movimientos a asignar
*/
void asignarMovimientos(Estrategia &estrategia, Movimientos &movimientosNuevos);

/*  pre:  estrategia creada.
    post: asigna las actitudes.

    estrategia: estrategia al cual se le agrega la actitud
    actitudes: actitudes a asignar
*/
void asignarActitudes(Estrategia &estrategia, Actitudes &actitudesNuevas);

/*  pre:  estrategia creada.
    post: retorna la prioridad de movimientos que posee esa estrategia

    estrategia: estrategia de la cual se obienen los movimientos
*/
Movimientos *obtenerMovimientos(Estrategia &estrategia);

/*  pre:  estrategia creada
    post: retorna la actidud que posee esa estrategia

    estrategia: estrategia de la cual se obienen las actutudes
*/
Actitudes *obtenerActitudes(Estrategia &estrategia);

/*  pre:  estrategia creada y con movimientos ingresados.
    post: calcula el movimiento que puede realizar la perforadora. Para esto
          tiene en cuenta los que no se pueden hacer y mediante el algoritmo
          de elección decide cual hacer.
          Luego devuelve su valor.

    estrategia: tda de la estrategia con la cual se va a calcular
    perforadora: perforadora del bot que se va a calcular la estrategia
    equipoBot: es el equipo del bot dueño de la perforadora
*/


EnumMovimiento calcularMovimiento(Estrategia &estrategia, Perforadora &perforadora, tId_Equipo equipoBot);



#endif

