/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************
 * TDA Minerales
 * Archivo : Minerales.h , Minerales.cpp
 ******************************************/


#ifndef __MINERALES_H__
#define __MINERALES_H__

#include "definiciones.h"

//definicion del tipo de datos que posee minerales

/* REMITIRSE AL ARCHIVO "definiciones.h" */

/*  Axiomas:
            - Si el contenido es oro, los puntos son 5.
            - Si el contenido es plata, los puntos son 3.
            - Si el contenido es cobre, los puntos son 1.
            - Si el contenido son rocas, los puntos van del 1 al 9.

*/

/* Primitivas */

/*  pre:  si el mineral tiene un numero fijo de puntos, se setean automaticamente
          independientemente de lo que se pase por parametro. Tambien se puede
          usar el otro crear, que recibe solo el mineral para el mismo fin.
          Los puntos deben ser validos.
    post: crea una instancia de contenido, lista para ser usada.

    mineral:   tda mineral al cual asignarle el mineral
    contenido: mineral a agregar
    valor:     puntos que va a tener
*/
void crear(Mineral &mineral, EnumMinerales contenido, Puntos valor);

/*  pre:  No se puede pasar como parametro alguna roca. De lo contrario asigna
          automaticamente una roca con puntos 1.
    post: crea una instancia de contenido, lista para ser usada. Asigna
          automaticamente los puntos del mineral.

    mineral:   tda mineral al cual asignarle el mineral
    contenido: mineral a agregar
*/

/*  pre:  mineral creado
    post: Invalida el mineral para su posterior utilización
*/
void destruir(Mineral &mineral);

void crear(Mineral &mineral, EnumMinerales contenido);

/*  pre:  instancia de mineral creada
    post: devuelve el tipo de mineral que posee

    mineral: sobre el cual se quiere obtener el tipo
*/
EnumMinerales obtenerTipo(const Mineral &mineral);

/*  pre:  instancia de mineral creada
    post: devuelve los puntos que insume el proceso de mineral.

    mineral: sobre el cual se quiere obtener el tipo
*/
Puntos obtenerPuntos(const Mineral &mineral);

/*  pre:  instancia de mineral creada.
    post: Asigna el tipo al mineral y los puntos. Si el mineral tiene puntos
          fijos, los asigna automaticamente.
          Los puntos deben ser validos.

    mineral:   instancia del tipo mineral sobre la cual se hace la asignacion
    contenido: el tipo de mineral que se agrega
    valor:     valor que se le asignan a los puntos
*/
void asignarMineral(Mineral &mineral, EnumMinerales contenido, Puntos valor);

/*  pre:  instancia de mineral creada.
    post: Asigna el tipo al mineral y los puntos automaticamente. Si el mineral
          es roca no hace nada.

    mineral:   instancia del tipo mineral sobre la cual se hace la asignacion
    contenido: el tipo de mineral que se agrega
    valor:     valor que se le asignan a los puntos
*/
void asignarMineral(Mineral &mineral, EnumMinerales contenido);
#endif

