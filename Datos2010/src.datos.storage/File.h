/*
 * Archivo.h
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
 */

#ifndef FILE_H_
#define FILE_H_

#include "Storage.h"

class File: public Storage {

protected:
	fstream file;
	string fileName;

public:
    File();
    ~File();


    virtual void create(string fileName) =0;
    virtual void open(string fileName) =0;
    /**
      * Escribe una cadena de caracteres al archivo en la posición del cursor.
      * Luego de escribirlo, el cursor queda en la posición siguiente al último caracter de la cadena
      *  Si no puede escribir, arroja una excepción
      */
    void read(std::string & datos);
    void read(char *buffer, int tamanio, int pos=-1);

    /**
      * Lee del archivo una cadena de caracteres a partir de la posición actual del cursor y hasta:
      *  - Que se encuentre un fin de linea
      *  - Se lean MAX_LENGTH caracteres
      * El contenido leido se almacena en el parámetro "cadena"
      * Retorna true si pudo leer una linea, o false en caso contrario
      */
    int  write(std::string registro);
    void write(char *buffer, int tamanio, int pos=-1);
    void close();
    void flush();
    std::string toString();

    void irAlPrincipio();
    void irAlFinal();


};

#endif /* File_H_ */
