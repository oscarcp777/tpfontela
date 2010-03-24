/*
 * Archivo.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef FILE_H_
#define FILE_H_

#include "Storage.h"

class File: public Storage {
public:
	/*
	  pre : ninguna.
	  post: abre el File, si no existe lo crea.

	  FileRegistros : estructura de datos a ser creada.
	  nombre : nombre físico del File, path incluido.

	*/
	File();
	std::string toString();
	std::string getClass();
    ~File();

	void abrir();
	void cerrar();
    void crear();
    int guardar(std::string registro, int pos);
    /*
      pre : FileRegistros ha sido creado con crear() y registro es un puntero
            a un struct del tamaño correspondiente al de los registros del File.
      post: escribe el registro en el File en la posición actual.

      registro : puntero hacia el registro a ser escrito en el File.
    */
    int guardar(char* buffer, int pos = -1);
    void guardar(char* buffer, int pos ,int tamanio);
    void leer(std::string& datos, int pos);
    void leer(char* buffer, int pos,int tamanio);
    int leerRegistroVariable(string& registro,int posicion=-1);
    void escribirRegistroVariable(string registro);
    void escribirRegistroVariableConPosicion(string registro,int pos);
    /*
      pre : FileRegistros ha sido creado con crear() y registro es un puntero
            a un struct del tamaño correspondiente al de los registros del File.
      post: lee del File el registro en la posición actual.
      registro : puntero hacia el registro donde colocar la lectura.
    */
    //void leer(void* datos, int tamanio);

    void leer(char* buffer, int pos);
    /*
      pre : FileRegistros ha sido creado con crear().
      post: devuelve true si se ha llegado al fin del File, es decir no se puede
            leer más registros. false en caso contrario.

      FileRegistros : File sobre el cual se aplica la primitiva.
    */
    bool fin();
    /*
      pre : FileRegistros ha sido creado con crear().
      post: devuelve la posición relativa del registro actual.

      FileRegistros : File sobre el cual se aplica la primitiva.
    */
    long int posicion(int tamanioRegistro);
    /*
      pre : FileRegistros ha sido creado con crear().
      post: cambia la posición actual.

      FileRegistros : File sobre el cual se aplica la primitiva.
      posicion : número de registro (0..n)
    */
    void posicionarse(long int posicion,int tamanioRegistro);



    /**
       * Posiciona el cursor al comienzo del File
       */
      void irAlPrincipio();

      /**
       * Posiciona el cursor al final del File
       */
      void irAlFinal();


      //void leer(std::string& datos);


};

#endif /* File_H_ */
