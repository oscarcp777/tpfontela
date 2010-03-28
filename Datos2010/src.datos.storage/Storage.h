/*
 * Almacenamiento.h
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
 */

#ifndef STORAGE_H_
#define STORAGE_H_



#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "../src.datos.utils/Object.h"
#include "../src.datos.utils/Define.h"
using namespace std;

class Storage:public Object{


public:
	Storage();
	~Storage();



	 /**
	   * Lee del archivo una cadena de caracteres a partir de la posición actual del cursor y hasta:
	   *  - Que se encuentre un fin de linea
	   *  - Se lean MAX_LENGTH caracteres
	   * El contenido leido se almacena en el parámetro "cadena"
	   * Retorna true si pudo leer una linea, o false en caso contrario
	   */
	virtual void read(std::string & datos) =0;

    /**
      * Escribe una cadena de caracteres al archivo en la posición del cursor.
      * Luego de escribirlo, el cursor queda en la posición siguiente al último caracter de la cadena
      *  Si no puede escribir, arroja una excepción
      */
	virtual int write(std::string registro) = 0;
	virtual void close() =0;

	string toString();

	//evaluar existencia
    virtual void irAlPrincipio() = 0;


};

#endif /* STORAGE_H_ */
