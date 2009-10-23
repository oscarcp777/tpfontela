/*
 * Archivo.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include "Almacenamiento.h"

class Archivo: public Almacenamiento {
public:
	/*
	  pre : ninguna.
	  post: abre el archivo, si no existe lo crea.

	  archivoRegistros : estructura de datos a ser creada.
	  nombre : nombre físico del archivo, path incluido.

	*/
	Archivo();
	std::string toString();
	std::string getClass();
	virtual ~Archivo();

	void abrir();
	void cerrar();

    void guardar(std::string registro);
    /*
      pre : archivoRegistros ha sido creado con crear() y registro es un puntero
            a un struct del tamaño correspondiente al de los registros del archivo.
      post: escribe el registro en el archivo en la posición actual.

      registro : puntero hacia el registro a ser escrito en el archivo.
    */
    void guardar();


    /*
      pre : archivoRegistros ha sido creado con crear() y registro es un puntero
            a un struct del tamaño correspondiente al de los registros del archivo.
      post: lee del archivo el registro en la posición actual.
      registro : puntero hacia el registro donde colocar la lectura.
    */
    void leer(void* datos, int tamanio);
    /*
      pre : archivoRegistros ha sido creado con crear().
      post: devuelve true si se ha llegado al fin del archivo, es decir no se puede
            leer más registros. false en caso contrario.

      archivoRegistros : archivo sobre el cual se aplica la primitiva.
    */
    bool fin();
    /*
      pre : archivoRegistros ha sido creado con crear().
      post: devuelve la posición relativa del registro actual.

      archivoRegistros : archivo sobre el cual se aplica la primitiva.
    */
    long int posicion(int tamanioRegistro);
    /*
      pre : archivoRegistros ha sido creado con crear().
      post: cambia la posición actual.

      archivoRegistros : archivo sobre el cual se aplica la primitiva.
      posicion : número de registro (0..n)
    */
    void posicionarse(long int posicion,int tamanioRegistro);



    /**
       * Posiciona el cursor al comienzo del archivo
       */
      void irAlPrincipio();

      /**
       * Posiciona el cursor al final del archivo
       */
      void irAlFinal();


      std::string leerMetadata();
      void escribirMetadata(std::string metadata);
      void leer(std::string& datos);


};

#endif /* ARCHIVO_H_ */
