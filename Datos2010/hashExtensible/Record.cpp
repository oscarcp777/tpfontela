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
int Record::getSizeDataRecord(){
	std::string cadena = this->data;
    return cadena.length();
}
int Record::getSizeRecord(){
	std::string cadena = this->data;
    return 2*sizeof(this->key)+cadena.length();
}
