/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                               TDA CARA                                     *
 ******************************************************************************/

/********************************HEADERS***************************************/

#include "cara.h"

/*******************************PRIMITIVAS*************************************/

/* Crear */
void crear(Cara &cara1, Valor valor){
    if ((valor > 0) and (valor < 10000)){ //Valida el valor pasado como parámetro
        cara1.valor = valor; //Asigna el valor inicial de la cara
    } else {
        cara1.valor = -1; //Sino lo crea inválido
    }
}

/* Destruir */
void destruir(Cara &cara1){
    cara1.valor = -1; //Asigna un valor inválido
}

/* Get Valor */
int get_Valor(const Cara &cara1){
    return cara1.valor; //Devuelve el valor de la cara
}

/******************************************************************************/

