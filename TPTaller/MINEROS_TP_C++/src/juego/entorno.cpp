/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA ENTORNO                                    *
 ******************************************************************************/

/********************************HEADERS***************************************/
#include "entorno.h"

/*******************************PRIMITIVAS*************************************/

/* Crear */

void crear(Entorno &entorno1, Casillero* arriba, Casillero* abajo, Casillero* izquierda, Casillero* derecha){
    entorno1.arriba = arriba; //Inicializa el casillero superior
    entorno1.abajo = abajo; //Inicializa el casillero inferior
    entorno1.derecha = derecha; //Inicializa el casillero derecho
    entorno1.izquierda = izquierda; //Inicializa el casillero izquierdo
}

/* Destruir */

void destruir(Entorno &entorno1){
    entorno1.arriba = Vacio(); //Vac�a el casillero superior
    entorno1.abajo = Vacio(); //Vac�a el casillero inferior
    entorno1.derecha = Vacio(); //Vac�a el casillero derecho
    entorno1.izquierda = Vacio(); //Vac�a el casillero izquierdo
}

/* Set Arriba */

void setArriba(Entorno &entorno1, Casillero* arriba){
    entorno1.arriba = arriba; //Asigna el valor mandado como par�metro
}

/* Set Abajo */

void setAbajo(Entorno &entorno1, Casillero* abajo){
    entorno1.abajo = abajo; //Asigna el valor mandado como par�metro
}

/* Set Izquierda */

void setIzquierda(Entorno &entorno1, Casillero* izquierda){
    entorno1.izquierda = izquierda; //Asigna el valor mandado como par�metro
}

/* Set Derecha */

void setDerecha(Entorno &entorno1, Casillero* derecha){
    entorno1.derecha = derecha; //Asigna el valor mandado como par�metro
}

/* Get Arriba */

Casillero* getArriba(const Entorno &entorno1){
    return entorno1.arriba; //Devuelve un puntero a casillero
}

/* Get Abajo */

Casillero* getAbajo(const Entorno &entorno1){
    return entorno1.abajo; //Devuelve un puntero a casillero
}

/* Get Izquierda */

Casillero* getIzquierda(const Entorno &entorno1){
    return entorno1.izquierda; //Devuelve un puntero a casillero
}

/* Get Derecha */

Casillero* getDerecha(const Entorno &entorno1){
    return entorno1.derecha; //Devuelve un puntero a casillero
}

/* Vacio */

Casillero* Vacio(){
    return NULL;
}

/******************************************************************************/


