/*
 * FreeBlockList.h
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#ifndef FREEBLOCKCONTROLLER_H_
#define FREEBLOCKCONTROLLER_H_

#include "../src.datos.buffer/FixedFieldBuffer.h"
#include "../src.datos.buffer/BufferFile.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class FreeBlockController {
public:
	FreeBlockController(int blocksize);
	virtual ~FreeBlockController();

	int open(string name, ios_base::openmode mode);
	int create(string name, ios_base::openmode mode);
	bool isCreated(string fileName);
	int close();
	void add(int blockId);
	int get();
	int getSize();
	void print(ostream&);

private:
	FixedFieldBuffer buffer;			//Buffer que contiene el bloque doble inicial
	FixedFieldBuffer simpleBuffer;		//Buffer de bloques simples
	BufferFile bTreeFile;
	int blockSize;
	vector<int> freeBlocks;		//vector con todos los bloques libres
	unsigned int maxFields;		//Maximo numero de bloques por bloque del archivo de libres
	int nBlocks;				//Cantidad de bloques cargados en la lista
	int nBlocksDoubleBuffer;	//Cantidad de bloques cargados en el buffer doble

	int pack();
	int unpack();
	int writeSimpleBlock(int addr);
	int readSimpleBlock(int addr);
	void printSimpleBlock(ostream &, int addr);

};

#endif /* FREEBLOCKCONTROLLER_H_ */
