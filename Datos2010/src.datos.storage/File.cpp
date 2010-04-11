/*
 * Archivo.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
 */

#include "File.h"

using namespace std;


File::File():Storage(){
}

File::~File() {
}
void File::flush(){
    this->file.flush();
}
void File::read(std::string& datos){

	/* verifica que el file esté abierto */
	if (this->file.is_open()) {
		/* lee del file una linea */
		getline(this->file, datos);
		/* chequea si se ha producido un error */
		if (this->file.fail())
			/* arroja una excepción ante la imposibilidad de leer un reg */
			throw string("Read line error");
	}
	else {
		/* arroja una excepción porque el file no está abierto */
		throw string("File not open");
	}
}


void File::read(char* buffer, int tamanio, int pos){

	if (this->file.is_open()) {
		if(pos>=0)
			this->file.seekg(pos);
		this->file.read(buffer,tamanio);
	}
	else {
		/* arroja una excepción porque el file no está abierto */
		throw string("File not open");
	}

}



int File::write(std::string registro){

	if (this->file.is_open()) {
		this->irAlFinal();
		this->file << registro<<endl;

		if (this->file.fail())
			// si se produjo un error, arroja una excepción
			throw std::ios_base::failure("Write line error");

	} else {
		/* arroja una excepción porque el file no está abierto */
		throw string("File not open");
	}
	return 1;
}


void File::write(char* buffer, int tamanio, int pos){

	if (this->file.is_open()) {
		if (pos >= 0)
			this->file.seekp(pos);
		this->file.write(buffer,tamanio);


	}

}

void File::close(){
	this->file.close();

}


std::string File::toString(){
	return "File";
}



/**
 * Posiciona el cursor al comienzo del File
 */
void File::irAlPrincipio() {
	this->file.tellg();
	this->file.clear();
	this->file.seekg(0);
	this->file.seekp(0);
	this->file.tellg();
}

/**
 * Posiciona el cursor al final del file
 */
void File::irAlFinal() {
	this->file.tellg();
	this->file.clear();
	this->file.seekg(0, ios::end);
	this->file.seekp(0, ios::end);
	this->file.tellg();
}



