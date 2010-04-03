/*
 * Table.h
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#ifndef TABLE_H_
#define TABLE_H_


#include "../src.datos.utils/Object.h"
#include "../src.datos.buffer/LengthFieldBuffer.h"
#include "../src.datos.buffer/BufferFile.h"

class Cube;
class CubeBuffer;
using namespace std;
class Table {
public:
	Table(int maxCubeKeys = -1);
	virtual ~Table();
	int open(string name);
	int create(string name);
	int close();
	int insert(char* key, int recAddr);
	int remove(char* key);
	int search(char* key);// return recAddr for key
	void print();
	int getDepth();
protected:
	int depth;
	int numCells; //number of entries, = 2*depth
	int* cubeAddr; //array of Cube addresses
	int doubleSize();//double the size of the Table
	int collapse(); //collapse, halve the size
	int insertCube(int cubeAddr, int first, int last);
	int removeCube(int cubeIndex, int cubeDepth);
	int find(char* key); //return cubeAddr for key
	int storeCube(Cube* cube); //update or append Cube from file
	int loadCube(Cube* cube, int cubeAddr);//load Cube from file
	int maxCubeKeys;
	BufferFile* tableFile;
	LengthFieldBuffer* tableBuffer;
	CubeBuffer* theCubeBuffer;
	BufferFile* cubeFile;
	int pack() const;
	int unPack();
	Cube* printCube;
	Cube* currentCube;

	friend class Cube;
};

#endif /* TABLE_H_ */
