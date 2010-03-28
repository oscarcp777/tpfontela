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
IOBuffer & getBuffer();
 int HeaderSize;
 int ReadHeader();
 int WriteHeader();
public:
	BufferFile(IOBuffer &);
	BufferFile();
	/**
	 *lee un registro en el buffer
	 *@autor oscar
	 *@return si se usa sin parametros retorna en siguiente registro del archivo
	 *@return retorna la direccion del registro
	 */
	int read(int addr = -1);

	virtual ~BufferFile();
	int open(char* filename, int mode);
	int close();
	int write(int addr = -1);
	int append();
	int create(char* filename,int mode);
	int ReWind();

};

#endif /* BUFFERFILE_H_ */
