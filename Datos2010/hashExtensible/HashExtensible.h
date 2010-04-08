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
using namespace std;
class HashExtensible {
private:
	fstream* fileTable;
	fstream* fileCubes;
	fstream* fileCubesFree;
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


    fstream *getFileCubes() const
    {
        return fileCubes;
    }

    fstream *getFileCubesFree() const
    {
        return fileCubesFree;
    }

    fstream *getFileTable() const
    {
        return fileTable;
    }

    Table *getTable() const
    {
        return table;
    }

    void setFileCubes(fstream *fileCubes)
    {
        this->fileCubes = fileCubes;
    }

    void setFileCubesFree(fstream *fileCubesFree)
    {
        this->fileCubesFree = fileCubesFree;
    }

    void setFileTable(fstream *fileTable)
    {
        this->fileTable = fileTable;
    }

    void setTable(Table *table)
    {
        this->table = table;
    }

};

#endif /* HASHEXTENSIBLE_H_ */
