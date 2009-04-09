/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA ArchivoRegistros
 * Implementaci�n con fstream.
 * Archivo : archivoRegistros.h
 * Versi�n : 1.2
 */

#ifndef __ARCHIVOREGISTROS_H__
#define __ARCHIVOREGISTROS_H__

/******************************************************************************/
/* Headers */
/*---------*/

#include <fstream>
#include <string>


/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/

struct ArchivoRegistros {
                         std::fstream  archivo;  // referencia al archivo
                         int tamanioRegistro;    // tama�o en bytes del registro
};


/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : ninguna.
  post: abre el archivo, si no existe lo crea.
  
  archivoRegistros : estructura de datos a ser creada.
  nombre : nombre f�sico del archivo, path incluido.
  tamanioRegistro : tamanio en bytes de los registros del archivo.
*/
void crear(ArchivoRegistros &archivoRegistros, std::string nombre, 
           int tamanioRegistro);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoRegistros ha sido creado con crear().
  post: cierra el archivo 

  archivoRegistros : archivo sobre el cual se aplica la primitiva.
*/
void destruir(ArchivoRegistros &archivoRegistros);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoRegistros ha sido creado con crear() y registro es un puntero
        a un struct del tama�o correspondiente al de los registros del archivo.
  post: escribe el registro en el archivo en la posici�n actual.
  
  archivoRegistros : archivo sobre el cual se aplica la primitiva.
  registro : puntero hacia el registro a ser escrito en el archivo.
*/
void escribir(ArchivoRegistros& archivoRegistros, const void* registro);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoRegistros ha sido creado con crear() y registro es un puntero
        a un struct del tama�o correspondiente al de los registros del archivo.
  post: lee del archivo el registro en la posici�n actual.
  
  archivoRegistros : archivo sobre el cual se aplica la primitiva.
  registro : puntero hacia el registro donde colocar la lectura.
*/
void leer(ArchivoRegistros& archivoRegistros, void* registro);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoRegistros ha sido creado con crear().
  post: devuelve true si se ha llegado al fin del archivo, es decir no se puede
        leer m�s registros. false en caso contrario.

  archivoRegistros : archivo sobre el cual se aplica la primitiva.
*/
bool fin(ArchivoRegistros& archivoRegistros);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoRegistros ha sido creado con crear().
  post: devuelve la posici�n relativa del registro actual.

  archivoRegistros : archivo sobre el cual se aplica la primitiva.
*/
long int posicion(ArchivoRegistros& archivoRegistros);

/*----------------------------------------------------------------------------*/
/*
  pre : archivoRegistros ha sido creado con crear().
  post: cambia la posici�n actual.
  
  archivoRegistros : archivo sobre el cual se aplica la primitiva.
  posicion : n�mero de registro (0..n)
*/
void posicionarse(ArchivoRegistros& archivoRegistros, long int posicion);

/******************************************************************************/

#endif
