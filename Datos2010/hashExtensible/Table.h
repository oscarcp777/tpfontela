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
#include "../src.datos.storage/TextFile.h"
#include "../src.datos.treeB/FreeBlockController.h"
#include "Cube.h"
#include "Hash.h"
#include <vector>
using namespace std;
typedef struct metadataTable {
	int countsCubes;
	int sizeTable;

}METADATA_TABLE;
class Table {
private:
	BinaryFile* fileTable;
	BinaryFile* fileCubes;
	TextFile* output;
	//BinaryFile* fileCubesFree;
	int countsCubes;
	Cube* currentCube;
	Cube* SecondarycurrentCube;
	int sizeTable;
	int countCubeFileTable;
	//vector<int> offsetFreeCubes;
	FreeBlockController* offsetFreeCubes;
	vector<int> offsetCubes;
	int diferentDispersionAndSizeTable(int index);
	int equalsDispersionAndSizeTable(int index);
	int calculateIndex(int* indexUp, int* indexDown, int index);
	void printCubes();
	int packCubeTable(Buffer* buffer,int countElement, int* indexOffset);
	string fileNameOutput;
public:
	Table();
	virtual ~Table();
	bool existOverflow(int offsetCube,Record*  record);
	int overFlowInCube(int index,int offsetCubeOverFlow);
	int reallocate(int offsetCubeOverFlow);
	int duplicateTable();
	int insert(Record* record);
	int update(Record* record);
	int remove(int key);
	int loadCube(int offset,Cube* cube);
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
	int writeFirstCube();
	void print(string output,bool cubes);
	bool isCreated(string fileName);

	int getCountsCubes() const
    {
		return countsCubes;
    }

    int getSizeTable() const
    {
        return sizeTable;
    }

    void setCountsCubes(int countsCubes)
    {
        this->countsCubes = countsCubes;
    }

    void setCurrentCube(Cube *currentCube)
    {
        this->currentCube = currentCube;
    }


    void setSizeTable(int sizeTable)
    {
        this->sizeTable = sizeTable;
    }
	BinaryFile *getFileCubes() const
    {
        return fileCubes;
    }

//	BinaryFile *getFileCubesFree() const
//    {
//        return fileCubesFree;
//    }

	BinaryFile *getFileTable() const
    {
        return fileTable;
    }

};

#endif /* TABLE_H_ */
