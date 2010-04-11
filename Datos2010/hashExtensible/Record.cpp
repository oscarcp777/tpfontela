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
	this->key;
	this->data=data;
}
Record::~Record() {
	// TODO Auto-generated destructor stub
}
int Record::getSizeRecord(){
    return sizeof(this->data);
}
