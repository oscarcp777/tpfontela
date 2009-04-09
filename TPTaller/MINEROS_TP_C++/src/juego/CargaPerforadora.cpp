/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA CargaPerforadora
 * Archivo : CargaPerforadora.cpp
 */


#include "CargaPerforadora.h"

/******************************************************************************/

/******************************************************************************/

/* Implementacion de las primitivas */

void crear (CargaPerforadora& cargaPerforadora) {
    setMadera(cargaPerforadora, 20);
    setHierro (cargaPerforadora, 10);
    setEnergia( cargaPerforadora, 15);
}

/*----------------------------------------------------------------------------*/

void destruir(CargaPerforadora& cargaPerforadora){
    cargaPerforadora.madera= -1;
    cargaPerforadora.hierro= -1;
    cargaPerforadora.energia=-1;
}


/*----------------------------------------------------------------------------*/


void setMadera (CargaPerforadora& cargaPerforadora, Madera madera){
    /* Madera puede ser mayor o igual a 0(cero) */
    if ( madera >= 0 ) {
         cargaPerforadora.madera= madera;
    } else {
        cargaPerforadora.madera = 0;
    }
    /* Si madera es menor a 0(cero) lo pone en 0 */
}
/*----------------------------------------------------------------------------*/

Madera getMadera(CargaPerforadora& cargaPerforadora){
    return cargaPerforadora.madera;
}


/*----------------------------------------------------------------------------*/


void setHierro(CargaPerforadora& cargaPerforadora, Hierro hierro){
    /* Hierro puede ser mayor o igual a 0(cero) */
    if ( hierro >= 0 ) {
         cargaPerforadora.hierro= hierro;
    } else {
        cargaPerforadora.hierro = 0;
    }
    /* Si hierro es menor a 0(cero) lo pone en 0 */
}
/*----------------------------------------------------------------------------*/


Hierro getHierro(CargaPerforadora & cargaPerforadora) {
    return cargaPerforadora.hierro;
}

/*----------------------------------------------------------------------------*/


Energia getEnergia(CargaPerforadora& cargaPerforadora){
    return cargaPerforadora.energia;
}
/*----------------------------------------------------------------------------*/


void setEnergia(CargaPerforadora& cargaPerforadora, Energia energia){
    /* Energia puede ser mayor o igual a 0(cero) */
    if ( energia >= 0 ) {
         cargaPerforadora.energia= energia;
    } else {
        cargaPerforadora.energia = 0;
    }
    /* Si energia es menor a 0(cero) la pone en 0 */
}

