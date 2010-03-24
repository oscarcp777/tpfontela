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

private:
	fstream file;
	string fileName;

protected:
	fstream* getFile();
	string getFileName();

public:
    File();
    ~File();


    virtual void create(string fileName) =0;
    virtual void open(string fileName) =0;
    void read(std::string & datos, int pos);
    void read(char *buffer, int pos, int tamanio);
//    void read(char *buffer, int pos);
    int write(std::string registro, int pos);
//    int write(char *buffer, int pos = -1);
    void write(char *buffer, int pos, int tamanio);
    void close();


    int leerRegistroVariable(string & registro, int posicion = -1);
    void escribirRegistroVariable(string registro);
    void escribirRegistroVariableConPosicion(string registro, int pos);

    bool fin();
    long int posicion(int tamanioRegistro);
    void posicionarse(long int posicion, int tamanioRegistro);

    std::string toString();

    void irAlPrincipio();
    void irAlFinal();


};

#endif /* File_H_ */
