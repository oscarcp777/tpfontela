/*
 * Record.cpp
 *
 *  Created on: 07/04/2010
 *      Author: oscar
 */

#include "Record.h"

Record::Record() {
	// TODO Auto-generated constructor stub
}
Record::Record(int key,char* data){
	this->key =key;
	this->data=data;

}
Record::~Record() {
	// TODO Auto-generated destructor stub
}
void Record::clear(){
	this->data.clear();
}

int Record::getSizeDataRecord(){
	return this->data.length();
}
int Record::getSizeRecord(){
	int lenght=2*sizeof(this->key)+this->data.length();
	cout<<" tamanio del registro "<<lenght<<endl;
	return lenght;
}
