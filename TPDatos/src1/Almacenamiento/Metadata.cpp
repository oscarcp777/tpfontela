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
    	this->archivo.open(this->nombreArchivo.c_str(),ios::out);
    	this->archivo.close();

    	/* reabre el archivo para lectura - escritura binario */
    	this->archivo.open(this->nombreArchivo.c_str(),ios::in|ios::out);

    	/* verifica que haya podido crear el archivo */
    	if (! this->archivo.is_open()){
    		cout<<"El archivo no pudo ser abierto "<<endl;
    		/* arroja una excepción */
    		throw string("El archivo no pudo ser abierto");
    	}


    }
    void Metadata::abrirArchivo(){

    	/* abre el archivo en modo lectura - escritura binario*/
    	this->archivo.open(this->nombreArchivo.c_str(),ios::in |ios::out);
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

    void Metadata::guardarPrimeraLinea(std::string registro){
    	/* verifica que el archivo esta abierto */
        	if (this->archivo.is_open()) {
        		this->irAlPrincipio();
        		//intenta escribir la cadena en el archivo
        		this->archivo << registro;

        		if (archivo.fail())
        			// si se produjo un error, arroja una excepción
        			throw std::ios_base::failure("No se pudo escribir correctamente la cadena");
        	} else {
        		/* arroja una excepción porque el archivo no está abierto */
        		throw string("El archivo no esta abierto");
        	}
    }

    void Metadata::guardar(std::string registro){
    	/* verifica que el archivo esta abierto */
    	if (this->archivo.is_open()) {
    		this->irAlFinal();
    		//intenta escribir la cadena en el archivo
    		this->archivo << registro;

    		if (archivo.fail())
    			// si se produjo un error, arroja una excepción
    			throw std::ios_base::failure("No se pudo escribir correctamente la cadena");
    	} else {
    		/* arroja una excepción porque el archivo no está abierto */
    		throw string("El archivo no esta abierto");
    	}

    }
    void Metadata::irAlPrincipio() {
    	this->archivo.tellg();
    	this->archivo.clear();
    	this->archivo.seekg(0);
    	this->archivo.seekp(0);
    	this->archivo.tellg();
    }


    void Metadata::irAlFinal() {
    	this->archivo.tellg();
    	this->archivo.clear();
    	this->archivo.seekg(0, ios::end);
    	this->archivo.seekp(0, ios::end);
    	this->archivo.tellg();
    }


