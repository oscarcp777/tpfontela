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
	return this->table->openFiles(fileName);
}



int HashExtensible::create(string fileName){
	this->table->createFiles(fileName);
	return 1;
}



int HashExtensible::insert(int key, char *data)
{
   cout<<"########################################"<<endl;
   cout<<"inserto el :"<<key<<endl;
   cout<<"########################################"<<endl;
	Record* record = new Record(key,data);
	this->table->insert(record);
	return 1;
}



int HashExtensible::remove(int key)
{cout<<"########################################"<<endl;
cout<<"remove el :"<<key<<endl;
cout<<"########################################"<<endl;
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


