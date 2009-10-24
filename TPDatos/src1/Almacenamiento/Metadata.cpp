/*
 * Metadata.cpp
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */

#include "Metadata.h"

Metadata::Metadata() {
	this->metadataSize = -1;
}

Metadata::~Metadata() {
	// TODO Auto-generated destructor stub
}

std::string Metadata::leer(){
////	unsigned short metaDataSize;
	std::string datos = "";
////
////	this->archivo.read((char*)&metaDataSize,sizeof(metaDataSize));
////	this->metadataSize = metaDataSize;
////
////	char* buffer = new char[metaDataSize];
////	memset(buffer,' ',metaDataSize);
////	this->leer(buffer,this->metadataSize);
////	datos = buffer;
////	delete buffer;
////
////	std::cout<<"Metadata: " << datos <<endl;
	return datos;
}

void Metadata::escribir(std::string dato){
////	unsigned short metaDataSize;
////	std::stringstream flujo;
////	int tamanio = metadata.length();
////
////	this->metadataSize = tamanio;
////	metaDataSize = tamanio;
////	this->guardar((char*)&metaDataSize,sizeof(metaDataSize));
////
////	//flujo<< tamanio;
////	this->metaData = /*flujo.str() + DELIMITADOR +*/ metadata;
////	this->guardar(this->metaData.c_str(),this->metaData.length());
//
}
int Metadata::getSize(){
	return this->metadataSize;
}
