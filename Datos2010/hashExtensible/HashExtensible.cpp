/*
 * HashExtensible.cpp
 *
 *  Created on: 08/04/2010
 *      Author: oscar
 */

#include "HashExtensible.h"

HashExtensible::HashExtensible() {
	this->table = new Table();

}

HashExtensible::~HashExtensible() {
	delete this->table;
}

char *HashExtensible::search(int key)
{
	Record* record = this->table->search(key);
	if(record != NULL)
		return record->getData();
	else
		return NULL;
}



int HashExtensible::open(string fileName)
{
	this->table->openFiles(fileName);
	return 0;
}



int HashExtensible::create(string fileName){
	this->table->createFiles(fileName);
	return 0;
}



int HashExtensible::insert(int key, char *data)
{

	Record* record = new Record(key,data);
	this->table->insert(record);
	return 0;
}



int HashExtensible::remove(int key)
{
	this->table->remove(key);
	return 0;
}



void HashExtensible::print(fstream *output){
	//TODO
}

int HashExtensible::close()
{
	this->table->close();
	return 0;
}


