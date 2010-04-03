/*
 * Bucket.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "../src.datos.utils/Object.h"
#include "../src.datos.buffer/TextIndex.h"
#include "Hash2.h"

const int defaultMaxKeys = 100;

class Table;

class Cube: public TextIndex {

protected:
	Cube(Table & table, int maxKeys = defaultMaxKeys);
	virtual ~Cube();
	int insert(char* key, int recAddr);
	int remove(char* key);
	Cube* split();
	int newRange(int & newStart, int & newEnd);
	int redistribute(Cube & newCube);
	int find(const char* key);
	int findBuddy();
	int tryCombine();
	int combine(Cube* buddy, int buddyIndex);
	void print();
	int depth;
	Table  &table;
	int cubeAddr;

	friend class Table;
	friend class CubeBuffer;
};

#endif /* CUBE_H_ */
