/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                          TDA MATRIZ DINAMICA                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/


#include "matrizD.h"



/*******************************PRIMITIVAS*************************************/

/*----------------------------------------------------------------------------*/
void Crear(MatrizDinamica &matriz,CantColumnas columnas,CantFilas filas){

    if ( (filas>0) && (columnas>0) ){

        matriz.filas = filas;
        matriz.columnas = columnas;
        matriz.matriz = new DatoMatriz* [filas]; //creo las filas

        for (int j = 0; j < filas; j++)
            matriz.matriz[j] = new DatoMatriz [columnas]; //creo las columnas

        for (int i = 0; i < filas; i++) // pongo en vacio todas las posiciones
            for (int j = 0; j < columnas; j++)
                matriz.matriz[i][j] = datoVacio();

    }
}


/*---------------------------------------------------------------------------*/

void Destruir(MatrizDinamica &matriz)
{
    for (int i = 0; i < getCantFilas(matriz); i++){ // liberamos la memoria
        delete(matriz.matriz[i]); // libero la memoria
        matriz.matriz[i]=NULL;
    }
    delete (matriz.matriz);
    matriz.matriz=NULL;
}

/*---------------------------------------------------------------------------*/
void setDato(MatrizDinamica &matriz,DatoMatriz dato,CantFilas fila, CantColumnas columna){

        matriz.matriz[fila][columna]= dato;
}
DatoMatriz datoVacio()
{
    return NULL;
}
/*---------------------------------------------------------------------------*/
DatoMatriz getDato(MatrizDinamica &matriz,int fila, int columna){
    if((fila>=0)&&(columna>=0))
        return matriz.matriz[fila][columna];
    else
        return datoVacio();
}
CantFilas getCantFilas(MatrizDinamica &matriz)
{
    return matriz.filas;
}
CantColumnas getCantColumnas(MatrizDinamica &matriz)
{
    return matriz.columnas;
}
/*---------------------------------------------------------------------------*/
