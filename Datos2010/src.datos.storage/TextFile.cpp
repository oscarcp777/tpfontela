/*
 * TextFile.cpp
 *
 *  Created on: 25/03/2010
 *      Author: oscar
 */

#include "TextFile.h"

TextFile::TextFile() {

}

TextFile::~TextFile() {

}

void TextFile::create(string fileName){

}

void TextFile::open(string fileName){

	Logger* logger = Logger::getUnicaInstancia();

	logger->debug(this,"Se intenta abrir el archivo de texto en modo lectura-escritura");
	this->file.open(fileName.c_str(), ios::in | ios::out);

	if (!this->file.is_open()){
		logger->debug(this,"No se pudo abrir el archivo texto ... se limpian los flags de control del estado del archivo");
		this->file.clear();

		logger->debug(this,"Se crea el archivo de texto");
		this->file.open(fileName.c_str(), ios::out);
		logger->debug(this,"Se cierra el archivo de texto para su utilizacion");
		this->file.close();

		logger->debug(this,"Se reabre el archivo texto para lectura - escritura");
		this->file.open(fileName.c_str(), ios::in | ios::out);

		if (!this->file.is_open()){

			logger->debug(this,"No se pudo abrir el archivo de texto ... Se arroja una excepcion");
			logger->error(this,"No se pudo abrir el archivo de texto ... Se arroja una excepcion");
			throw ios_base::failure("El archivo texto no pudo ser abierto");
		}
	}

	if (!this->file.is_open()){

		logger->debug(this,"No se pudo abrir el archivo de texto ... Se arroja una excepcion");
		logger->error(this,"No se pudo abrir el archivo de texto ... Se arroja una excepcion");
		throw ios_base::failure("El archivo no pudo ser abierto");
	}
}
