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
	else{
		string cadena = "NO SE ENCONTRO LA CLAVE";
		return (char*)cadena.c_str();
	}
}



int HashExtensible::open(string fileName)
{
	return this->table->openFiles(fileName);
}



int HashExtensible::create(string fileName){
	this->table->createFiles(fileName);
	return 1;
}

bool HashExtensible::isCreated(string fileName){
	return this->table->isCreated(fileName);
}


int HashExtensible::insert(int key, char *data){
	Record* record = new Record(key,data);
	return this->table->insert(record);

}

int HashExtensible::update(int key,char* data){
	Record* record = new Record(key,data);
	this->table->update(record);
	return 1;
}

int HashExtensible::remove(int key){
return this->table->remove(key);

}



void HashExtensible::print(string fileName){

	this->table->print(fileName,true);
}

int HashExtensible::close()
{
	this->table->close();
	return 1;
}
