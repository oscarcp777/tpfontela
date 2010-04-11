/*
 * Table.h
 *
 *  Created on: 24/03/2010
 *      Author: Oscar
 */

#ifndef TABLE_H_
#define TABLE_H_
#include "Record.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.storage/BinaryFile.h"
#include "Cube.h"
#include "Hash.h"
#include <vector>
using namespace std;
typedef struct metadataTable {
	INT_UNSIGNED countsCubes;
	INT_UNSIGNED sizeTable;

}METADATA_TABLE;
class Table {
private:
	BinaryFile* fileTable;
	BinaryFile* fileCubes;
	BinaryFile* fileCubesFree;
	INT_UNSIGNED countsCubes;
	Cube* currentCube;
	INT_UNSIGNED sizeTable;
	vector<int> offsetFreeCubes;
	vector<int> offsetCubes;
public:
	Table();
	virtual ~Table();
	int duplicateTable();
	int insert(Record* record);
	int remove(int key);
	int loadCube(int offset);
	Record* search(int key);
	int isTableDuplicate();
	void collapse();
	int close();
	int createFiles(string fileName);
	int openFiles(string fileName);
	int readTable();
	int writeTable();
	int readFreeCubes();
	int writeFreeCubes();
	void print(fstream* output);

	INT_UNSIGNED getCountsCubes() const
    {
		return countsCubes;
    }

    INT_UNSIGNED getSizeTable() const
    {
        return sizeTable;
    }

    void setCountsCubes(INT_UNSIGNED countsCubes)
    {
        this->countsCubes = countsCubes;
    }

    void setCurrentCube(Cube *currentCube)
    {
        this->currentCube = currentCube;
    }


    void setSizeTable(INT_UNSIGNED sizeTable)
    {
        this->sizeTable = sizeTable;
    }
	BinaryFile *getFileCubes() const
    {
        return fileCubes;
    }

	BinaryFile *getFileCubesFree() const
    {
        return fileCubesFree;
    }

	BinaryFile *getFileTable() const
    {
        return fileTable;
    }

};

#endif /* TABLE_H_ */
