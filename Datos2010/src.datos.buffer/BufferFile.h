/*
 * BufferFile.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef BUFFERFILE_H_
#define BUFFERFILE_H_
#include "IOBuffer.h"

class BufferFile {
public:
	BufferFile(IOBuffer &);
	BufferFile();
	/**
	 *lee un registro en el buffer
	 *@autor oscar
	 *@param
	 *@return retorna la direccion del registro
	 */
	virtual ~BufferFile();
	int open(char* filename, int mode);
	int close();
	int read(int addr = -1);
	int write(int addr = -1);
	int append();
	int create(char* filename,int mode);
	int ReWind();

};

#endif /* BUFFERFILE_H_ */
