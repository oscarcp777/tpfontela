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

	this->file.open(fileName.c_str(),ios::in |ios::out |ios::binary);
	if (! this->file.is_open()){
		this->file.open(fileName.c_str(),ios::out | ios::binary);
	}
}

void BinaryFile::open(string fileName){

	this->file.open(fileName.c_str(),ios::in |ios::out |ios::binary);
	if (! this->file.is_open()){
		throw string("File not Found");
	}

}
