/*
 * HashExtensible.h
 *
 *  Created on: 08/04/2010
 *      Author: oscar
 */

#ifndef HASHEXTENSIBLE_H_
#define HASHEXTENSIBLE_H_
#include <fstream>
#include <string>
#include "Table.h"
#include "../src.datos.storage/BinaryFile.h"

using namespace std;
class HashExtensible {
private:
	BinaryFile* fileTable;
	BinaryFile* fileCubes;
	BinaryFile* fileCubesFree;
	Table* table;
public:
	HashExtensible();
	virtual ~HashExtensible();
	int open(string fileName);
	int create(string fileName);
	int close();
	int insert(int key,char* data);
	int remove(int key);
	char* search(int key);
	void print(fstream* output);


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

    Table *getTable() const
    {
        return table;
    }

    void setFileCubes(BinaryFile *fileCubes)
    {
        this->fileCubes = fileCubes;
    }

    void setFileCubesFree(BinaryFile *fileCubesFree)
    {
        this->fileCubesFree = fileCubesFree;
    }

    void setFileTable(BinaryFile *fileTable)
    {
        this->fileTable = fileTable;
    }

    void setTable(Table *table)
    {
        this->table = table;
    }

};

#endif /* HASHEXTENSIBLE_H_ */
