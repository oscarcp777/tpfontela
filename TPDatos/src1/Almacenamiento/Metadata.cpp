/*
 * Metadata.cpp
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */

#include "Metadata.h"
#include <iostream>

using namespace std;

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

    string Metadata::getContenido()
    {
        return contenido;
    }


    string Metadata::getNombreArchivo()
    {
        return nombreArchivo;
    }

    void Metadata::setAtributoFijos(string clave,string valor)
    {
        this->mapaAtributosFijos[clave] = valor;
    }

    void Metadata::setAtributoVariable(string clave,string valor)
    {
        this->mapaAtributosVariables[clave] = valor;
    }

    void Metadata::setMetadataSize(int metadataSize)
    {
        this->metadataSize = metadataSize;
    }

    void Metadata::setNombreArchivo(string nombreArchivo)
    {
        this->nombreArchivo = nombreArchivo+METADATA;
    }


    void Metadata::crearArchivo(){

    	/* limpia los flags de control de estado del archivo */
    	this->archivo.clear();

    	/* crea el archivo */
    	this->archivo.open(this->nombreArchivo.c_str(),ios::out | ios::binary);
    	this->archivo.close();

    	/* reabre el archivo para lectura - escritura binario */
    	this->archivo.open(this->nombreArchivo.c_str(),ios::in|ios::out|ios::binary);

    	/* verifica que haya podido crear el archivo */
    	if (! this->archivo.is_open()){
    		cout<<"El archivo no pudo ser abierto "<<endl;
    		/* arroja una excepción */
    		throw string("El archivo no pudo ser abierto");
    	}


    }
    void Metadata::abrirArchivo(){

    	/* abre el archivo en modo lectura - escritura binario*/
    	this->archivo.open(this->nombreArchivo.c_str(),ios::in |ios::out |ios::binary);
    	/* verifica que haya podido crear el archivo */
    	if (! this->archivo.is_open()){
    		cout<<"El archivo no pudo ser abierto "<<endl;
    		/* arroja una excepción */
    		throw string("El archivo no pudo ser abierto");
    	}


    }
    void Metadata::cerrarArchivo(){
    	this->archivo.close();

    }
