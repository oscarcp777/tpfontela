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

	bool flag = false;
	Logger* logger = Logger::getUnicaInstancia();
	logger->debug(this->toString(),"Se intenta crear un archivo binario");
	this->file.open(fileName.c_str(),ios::in |ios::out |ios::binary);

	if (! this->file.is_open()){
		flag = true;
		logger->debug(this->toString(),"Se crea el archivo binario");
		this->file.open(fileName.c_str(),ios::out | ios::binary);
	}
}

void BinaryFile::open(string fileName){

	bool flag = false;
	Logger* logger = Logger::getUnicaInstancia();
	logger->debug(this->toString(),"Se intenta abrir el archivo binario en modo lectura-escritura");
	this->file.open(fileName.c_str(),ios::in |ios::out |ios::binary);
	if (! this->file.is_open()){

		logger->debug(this->toString(),"No se pudo abrir el archivo binario ... Se arroja una excepcion");
		logger->error(this->toString(),"No se pudo abrir el archivo binario ... Se arroja una excepcion");
		throw string("File not Found");
	}

	if(!flag){

		logger->debug(this->toString(),"El archivo fue abierto con exito");
	}

}
