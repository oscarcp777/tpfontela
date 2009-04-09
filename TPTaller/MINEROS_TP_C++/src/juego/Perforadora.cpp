/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**************************
 * TDA Perforadora
 * Archivo : Perforadora.cpp
 ***************************/

#include "Perforadora.h"

/******************************************************************************/
/* Implementacion de las primitivas*/

void crear (Perforadora & perforadora, TipoID ID, Entorno entorno){
    /* Crea la Carga de la Perforadora (CargaPerforadora) */
    crear(perforadora.carga);
    perforadora.ID= ID;
    perforadora.entorno= entorno;
    perforadora.bodegaPuntos = 0;
    perforadora.tieneSalida = false;
}
/*----------------------------------------------------------------------------*/
void destruir (Perforadora& perforadora){
    destruir(perforadora.carga);
    destruir(perforadora.entorno);
    perforadora.ID=' ';

}

/*----------------------------------------------------------------------------*/

TipoID getID (Perforadora& perforadora){
    return perforadora.ID;
}
/*----------------------------------------------------------------------------*/

Entorno* getEntorno(Perforadora& perforadora){
      return &perforadora.entorno;

}
/*----------------------------------------------------------------------------*/
CargaPerforadora*  getCarga(Perforadora & perforadora){
       return &perforadora.carga;
}

/*----------------------------------------------------------------------------*/

void setBodegaPuntos (Perforadora& perforadora, BodegaPuntos bodegaPuntos){
    if (bodegaPuntos >= 0) {
        perforadora.bodegaPuntos= bodegaPuntos;
    }
}
/*----------------------------------------------------------------------------*/

BodegaPuntos getBodegaPuntos(Perforadora& perforadora){
    return perforadora.bodegaPuntos ;
}
/*----------------------------------------------------------------------------*/

bool getSalida(Perforadora& perforadora){
    return perforadora.tieneSalida;
}
/*----------------------------------------------------------------------------*/

void setSalida(Perforadora& perforadora, bool salida){
    perforadora.tieneSalida = salida;
}
