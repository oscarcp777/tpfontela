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
	void print(string fileName);
	bool isCreated(string fileName);

    Table *getTable() const
    {
        return table;
    }

    void setTable(Table *table)
    {
        this->table = table;
    }

};

#endif /* HASHEXTENSIBLE_H_ */
