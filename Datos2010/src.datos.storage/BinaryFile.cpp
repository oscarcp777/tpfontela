/*
 * BinaryFile.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
 */

#include "BinaryFile.h"

BinaryFile::BinaryFile() {


}

BinaryFile::~BinaryFile() {

}

//ios::trunc crea si no existe o lo abre ver para unificar create y open

void BinaryFile::create(string fileName){

	/* limpia los flags de control de estado del file */
	//this->file.clear();

	this->getFile()->open(fileName.c_str(),ios::out | ios::binary);
	if (! this->getFile()->is_open())
		cout<<"El file no pudo ser creado "<<endl;
	else
		this->getFile()->close();



}

void BinaryFile::open(string fileName){


	this->getFile()->open(fileName.c_str(),ios::in |ios::out |ios::binary);
	if (! this->getFile()->is_open()){
		cout<<"El file no pudo ser abierto "<<endl;
		/* arroja una excepción */
		throw string("El file no pudo ser abierto");
	}


}
