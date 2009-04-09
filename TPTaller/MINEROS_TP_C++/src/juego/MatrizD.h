

/******************************************************************************
                        TDA MATRIZ DINAMICA                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/

#ifndef _MATRIZDINAMICA_H_
#define _MATRIZDINAMICA_H_

#include "definiciones.h"

typedef Casillero* DatoMatriz;
typedef int CantColumnas;
typedef int CantFilas;

struct MatrizDinamica{
                      DatoMatriz** matriz;
                      CantColumnas columnas;
                      CantFilas filas;
};

/*AXIOMAS*/
/* - Numero de columnas mayor a cero(0).
   - Numero de filas mayor a cero(0).   */


/*******************************PRIMITIVAS*************************************/

/* Pre: Numero de filas y columnas debe ser mayor a cero(0).
   Post: Crea la Matriz dinamica y  la deja lista para ser utilizada, a cada casillero
         le asigna vacio().
*/
void Crear(MatrizDinamica &matriz,CantColumnas columnas,CantFilas filas);
/*----------------------------------------------------------------------------*/

   /* Pre: Matriz debe haber sido creada en crear().
      Post: libera los recursos de la matriz y libera la memoria dinamica de la matriz.
*/
void Destruir(MatrizDinamica &matriz);

/*----------------------------------------------------------------------------*/
/* Pre: Matriz debe haber sido creada en crear(). Filas y columnas deben ser
        mayor o igual a cero(0) y Casillero debe estar creado.
   Post: Setea el dato pasado por parametro en la columna y fila de la matriz

*/
void setDato(MatrizDinamica &matriz,DatoMatriz dato,int fila, int columna);
/*----------------------------------------------------------------------------*/
/* Pre: Matriz debe haber sido creada en crear(). Filas y columnas deben ser
        mayor o igual a cero(0) y Casillero debe estar creado.
   Post: Devuelve el dato de la columna y fila de la matriz pasada por
         parametro.

*/
DatoMatriz getDato(MatrizDinamica &matriz,int fila, int columna);

/*----------------------------------------------------------------------------*/
/* Pre:  matriz debe haber sido creada
   Post: devuelve la cantidad de columnas de la matriz
*/
CantColumnas getCantColumnas(MatrizDinamica &matriz);

/*----------------------------------------------------------------------------*/
/* Pre:  matriz debe haber sido creada
   Post: devuelve la cantidad de filas de la matriz
*/
CantFilas getCantFilas(MatrizDinamica &matriz);

/*----------------------------------------------------------------------------*/
/* Pre: -
   Post: Devuelve la representacion de un dato vacio (inexistente)

*/
DatoMatriz datoVacio();

#endif

