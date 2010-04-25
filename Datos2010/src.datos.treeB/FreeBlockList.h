/*
 * FreeBlockList.h
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#ifndef FREEBLOCKLIST_H_
#define FREEBLOCKLIST_H_

#include "../src.datos.buffer/FixedFieldBuffer.h"
#include "../src.datos.buffer/BufferFile.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class FreeBlockList {
public:
	FreeBlockList(int blocksize);
	virtual ~FreeBlockList();

	int open(string name, ios_base::openmode mode);
	int create(string name, ios_base::openmode mode);
	int close();
	void add(int blockId);
	int get();
	int writeSimpleBlock(int addr);
	int readSimpleBlock(int addr);


private:
	FixedFieldBuffer buffer;			//Buffer que contiene el bloque doble inicial
	FixedFieldBuffer simpleBuffer;		//Buffer de bloques simples
	BufferFile bTreeFile;
	int blockSize;
	vector<int> freeBlocks;		//vector con todos los bloques libres
	unsigned int maxFields;		//Maximo numero de bloques por bloque del archivo de libres
	int nBlocks;				//Cantidad de bloques libres
	bool overflow,underflow;

	int pack();
	int unpack();


};

#endif /* FREEBLOCKLIST_H_ */
