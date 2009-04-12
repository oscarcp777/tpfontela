/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA ArchivoTexto
 * Implementación con fstream.
 * Archivo : ArchivoTexto.h
 * Versión : 1.0
 */

#ifndef __ARCHIVOTEXTO_H__
#define __ARCHIVOTEXTO_H__

/******************************************************************************/
/* Headers */
/*---------*/

#include <fstream>


/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/

typedef struct {
                         std::fstream  archivo;  // referencia al archivo
}ArchivoTexto;


/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : ninguna.
  post: abre el archivo, si no existe lo crea. Una vez realizada la apertura
        el cursor se coloca al principio del archivo.
  
  archivoTexto : estructura de datos a ser creada.
  nombre : nombre físico del archivo, path incluido.
*/
void crear( ArchivoTexto &archivoTexto , std::string nombre );


/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: cierra el archivo

  archivoTexto : archivo sobre el cual se aplica la primitiva.
*/
void destruir( ArchivoTexto &archivoTexto );

/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: escribe el caracter en el archivo en la posición actual del cursor y
        luego de realizarse dicho cursor se coloca en la posicion siguiente a la
        escrita.

  archivoTexto : archivo sobre el cual se aplica la primitiva.
  Caracter : caracter a ser escrito en el archivo.
*/
void escribirCaracter(ArchivoTexto &archivoTexto, char Caracter);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: escribe la cadena de caracteres en el archivo a partir de la posición
        actual del cursor y luego de realizarse dicho cursor se coloca en la
        posicion siguiente al ultimo caracter de la cadena.

  archivoTexto : archivo sobre el cual se aplica la primitiva.
  Cadena : Cadena de caracteres a ser escrita en el archivo.
*/
void escribirCadena(ArchivoTexto &archivoTexto, std::string Cadena);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: posiciona el cursor en una nueva linea por debajo de la actual.

  archivoTexto : archivo sobre el cual se aplica la primitiva.
*/
void bajarDeLinea( ArchivoTexto &archivoTexto );

/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: escribe una tabularion en el archivo, quedando el cursor en la posicion
        siguiente a la tabulacion.

  archivoTexto : archivo sobre el cual se aplica la primitiva.
*/
void tabular( ArchivoTexto &archivoTexto );

/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: lee del archivo una cadena de caracteres a partir de la posición actual
        del cursor hasta el fin de la linea donde se encuentra el mismo.
        Luego de esta lectura el cursor queda colocado en el comienzo de la
        siguiente linea.

  archivoTexto : archivo sobre el cual se aplica la primitiva.
  Cadena : Cadena donde colocar la lectura.
  retorno: Boolean indicando si se pudo realizar la lectura o no
*/
bool leerLinea( ArchivoTexto &archivoTexto, std::string &Cadena );

/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: posiciona el cursor al comienzo del archivo de texto

  archivoTexto : archivo sobre el cual se aplica la primitiva.
*/
void irAlComienzo( ArchivoTexto &archivoTexto );

/*----------------------------------------------------------------------------*/
/*
  pre : archivoTexto ha sido creado con crear().
  post: posiciona el cursor al final del archivo de texto

  archivoTexto : archivo sobre el cual se aplica la primitiva.
*/
void irAlFinal( ArchivoTexto &archivoTexto );

/******************************************************************************/

/*
  pre : archivoRegistros ha sido creado con crear().
  post: devuelve true si se ha llegado al fin del archivo, es decir no se puede
        leer más registros. false en caso contrario.

  archivoRegistros : archivo sobre el cual se aplica la primitiva.
*/
bool fin(ArchivoTexto &archivoTexto );


#endif
