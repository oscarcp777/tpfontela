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


void File::close(){
	this->file.close();

}



int File::write(std::string registro){

	if (this->file.is_open()) {
		this->irAlFinal();
		this->file << registro<<endl;

		if (this->file.fail())
			// si se produjo un error, arroja una excepción
			throw std::ios_base::failure("No se pudo escribir correctamente la cadena");

	} else {
		/* arroja una excepción porque el file no está abierto */
		throw string("El file no esta abierto");
	}
	return 1;
}

//int File::write(char* buffer, int pos){
//
//     int dir=-1;
//	if (this->file.is_open()) {
//
//		if (pos < 0)
//			this->irAlFinal();
//		else{
//			this->file.seekp(pos);
//			//this->file.seekg(pos);
//		}
//		int dir = this->file.tellg();
//
//		this->file.write(buffer,this->getSize());
//		return dir;
//
//	}
// return dir;
//}
void File::write(char* buffer, int pos,int tamanio){

	if (this->file.is_open()) {

		if (pos < 0)
			this->irAlFinal();
		else{
			this->file.seekp(pos);
			//	this->file.seekg(pos);
		}
		this->file.write(buffer,tamanio);


	}

}
bool File::fin() {

	/* para comprobar el fin lee un char del buffer, sin retirarlo y lo
     compara con el fin de file */
	bool esEof = (this->file.peek() == char_traits<char>::eof());

	if (esEof)
		/* si llegó al fin del file limpia los flags */
		this->file.clear();

	return esEof;
}

void File::read(std::string& datos){

	/* verifica que el file esté abierto */
	if (this->file.is_open()) {
		/* lee del file una linea */
		getline(this->file, datos);
		/* chequea si se ha producido un error */
		if (this->file.fail())
			/* arroja una excepción ante la imposibilidad de leer un reg */
			throw string("No se pudo leer correctamente el registro");
	}
	else {
		/* arroja una excepción porque el file no está abierto */
		throw string("El file no está abierto");
	}
}


//void File::read(char* buffer, int pos){
//
//
//	  if (this->file.is_open()) {
//		  if(pos>=0)
//		  this->file.seekg(pos);
//		  this->file.read(buffer,this->getSize());
//
//	  }
//	  else {
//	      /* arroja una excepción porque el file no está abierto */
//	      throw string("El file no está abierto");
//	    }
//
//}
void File::read(char* buffer, int pos,int tamanio){


	if (this->file.is_open()) {
		if(pos>=0)
			this->file.seekg(pos);
		this->file.read(buffer,tamanio);
	}
	else {
		/* arroja una excepción porque el file no está abierto */
		throw string("El file no está abierto");
	}

}


File::~File() {

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
/*----------------------------------------------------------------------------*/
long int File::posicion(int tamanioRegistro) {

	long int pos = 0;

	/* verifica que el file esté abierto */
	if (this->file.is_open())

		/* calcula el número de registro según la posición del byte actual */
		pos = this->file.tellg() / tamanioRegistro;

	else
		/* arroja una excepción porque el file no está abierto */
		throw string("El file no está abierto");

	return pos;
}
/*----------------------------------------------------------------------------*/
void File::posicionarse(long int posicion,int tamanioRegistro) {

	/* verifica que el file esté abierto */
	if (this->file.is_open()) {

		/* mueve la posición actual según sea el tamano del registro */
		this->file.seekg(posicion * tamanioRegistro,ios_base::beg);

		/* chequea si se ha producido un error */
		if (this->file.fail())
			/* arroja una excepción ante la imposibilidad de leer un reg */
			throw string("No se pudo posicionar correctamente el registro");
	}
	else
		/* arroja una excepción porque el file no está abierto */
		throw string("El file no está abierto");
}
int File::leerRegistroVariable(string& registro,int posicion){
	int tamanioRegistro=0;
	this->read((char*)&tamanioRegistro,posicion,sizeof(tamanioRegistro));
	char* buffer = new char[tamanioRegistro];
	memset(buffer,0,tamanioRegistro);
	this->read(buffer,-1,tamanioRegistro);
	registro=buffer;
	registro= registro.substr(0,tamanioRegistro);
	delete buffer;
	return this->file.tellp();
}


void File::escribirRegistroVariable(string registro){
	int tamanioRegistro;
	tamanioRegistro =registro.length();
	this->write((char*)&tamanioRegistro,-1,sizeof(tamanioRegistro));
	this->write((char*)registro.c_str(),-1,tamanioRegistro);
}
void File::escribirRegistroVariableConPosicion(string registro,int pos){
	int tamanioRegistro;
	tamanioRegistro =registro.length();
	this->write((char*)&tamanioRegistro,pos,sizeof(tamanioRegistro));
	this->write((char*)registro.c_str(),pos+sizeof(tamanioRegistro),tamanioRegistro);
}
