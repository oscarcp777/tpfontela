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
#include "Cube.h"
#include <vector>
using namespace std;
typedef struct metadataTable {
	INT_UNSIGNED countsCubes;
	INT_UNSIGNED sizeTable;

}METADATA_TABLE;
class Table {
private:
	INT_UNSIGNED countsCubes;
	Cube* currentCube;
	INT_UNSIGNED sizeTable;
	list<INT_UNSIGNED> offsetCubesFree;
	vector<int> element;
public:
	Table();
	virtual ~Table();
	int hash(int key);
	int readTable(fstream* fileTable);
	int writeTable(fstream* fileTable);
	int duplicateTable();
	int redispersableCubes(INT_UNSIGNED offsetCube);
	int insert(int key, char* data);
	int deleteCube(INT_UNSIGNED offsetCube);
	Record* search(int key);
	void print(fstream* output);
	Cube* getNewCube(fstream* fileCubes);
	Cube* getCurrentCube(INT_UNSIGNED offsetCube,fstream* fileCubo);


	INT_UNSIGNED getCountsCubes() const
    {
		return countsCubes;
    }

    list<INT_UNSIGNED> getOffsetCubesFree() const
    {
        return offsetCubesFree;
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

    void setOffsetCubesFree(list<INT_UNSIGNED> offsetCubesFree)
    {
        this->offsetCubesFree = offsetCubesFree;
    }

    void setSizeTable(INT_UNSIGNED sizeTable)
    {
        this->sizeTable = sizeTable;
    }

};

#endif /* TABLE_H_ */
