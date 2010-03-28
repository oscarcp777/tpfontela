/*
 * BufferFile.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef BUFFERFILE_H_
#define BUFFERFILE_H_


class BufferFile {
public:
	BufferFile();
	virtual ~BufferFile();
	int open(char* name, int mode);
	int close();
	int read(int addr = -1);
	int write(int addr = -1);
	int append();
	int create(char* name,int mode);
	int reWind();
};

#endif /* BUFFERFILE_H_ */
