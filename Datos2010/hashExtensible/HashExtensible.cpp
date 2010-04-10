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
	char var1='a';
	char* var=&var1;
	return var;
}



int HashExtensible::open(string fileName)
{
	return 0;
}



int HashExtensible::create(string fileName){
	this->table->createFiles(fileName);
	return 0;
}



int HashExtensible::insert(int key, char *data)
{
	return 0;
}



int HashExtensible::remove(int key)
{
	return 0;
}



void HashExtensible::print(fstream *output)
{
}



int HashExtensible::close()
{
	return 0;
}


