/*
 * BufferFile.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef BUFFERFILE_H_
#define BUFFERFILE_H_
#include "IOBuffer.h"
#include "../src.datos.utils/Object.h"
using namespace std;
class BufferFile :public Object{

protected:
 IOBuffer & buffer;
 fstream file;
 int headerSize;


public:
	BufferFile(IOBuffer & from);

	/**
	 *lee un registro en el buffer
	 *@autor oscar
	 *@return si se usa sin parametros retorna en siguiente registro del archivo
	 *@return retorna la direccion del registro
	 */
	int read(int addr = -1);
	IOBuffer & getBuffer();
	virtual ~BufferFile();
	int open(string filename, ios_base::openmode mode);
	int close();
	int write(int addr = -1);
	/**
	 * escribe el corriente buffer al final de archivo
	*@autor oscar
	*@
	 */
	int append();
	int create(string filename,ios_base::openmode mode);
	/**
	 * restablece al primer registro de datos
	 */
	int reWind();
	 int ReadHeader();
	  int WriteHeader();

};

#endif /* BUFFERFILE_H_ */
