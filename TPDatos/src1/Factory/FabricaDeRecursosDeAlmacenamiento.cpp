/*
 * FabricaDeRecursosDeAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "FabricaDeRecursosDeAlmacenamiento.h"
#include "../utils/Define.h"
#include "../fabricas/FabricaEstrategiaAlmacenamientoTexto.h"
#include "../fabricas/FabricaEstrategiaAlmacenamientoRegistros.h"
#include "../fabricas/FabricaEstrategiaAlmacenamientoBloques.h"
#include "../Estrategy/EstrategiaRecursoUnAlmacenamiento.h"
#include "../Estrategy/EstrategiaRecursoEscrituraDirecta.h"
#include "../fabricas/FabricaArchivo.h"
#include "../fabricas/FabricaBuffer.h"
#include "../fabricas/FabricaIndexadoBSharp.h"
#include "../fabricas/FabricaIndexadoHashExtensible.h"
FabricaDeRecursosDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica=NULL;
FabricaDeRecursosDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::obtenerInstancia(){

	if(!FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica){
		FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica= new FabricaDeRecursosDeAlmacenamiento();
	}
	return FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica;
}
FabricaDeRecursosDeAlmacenamiento::~FabricaDeRecursosDeAlmacenamiento() {
	// TODO Auto-generated destructor stub
}

FabricaAbstracta* FabricaDeRecursosDeAlmacenamiento::getFabrica(std::string clave){

	return this->mapaFabricas[clave];

}
FabricaDeRecursosDeAlmacenamiento::FabricaDeRecursosDeAlmacenamiento() {
	this->mapaFabricas[ESTRATEGIA_ALMACENAMIENTO_TEXTO] = new FabricaEstrategiaAlmacenamientoTexto();
	this->mapaFabricas[ESTRATEGIA_ALMACENAMIENTO_REGISTROS] = new FabricaEstrategiaAlmacenamientoRegistros();
	this->mapaFabricas[ESTRATEGIA_ALMACENAMIENTO_BLOQUES] = new FabricaEstrategiaAlmacenamientoBloques();
	this->mapaFabricas[ARCHIVO] = new FabricaArchivo();
	this->mapaFabricas[BUFFER] = new FabricaBuffer();
	this->mapaFabricas[INDEXADO_BSHARP] = new FabricaIndexadoBSharp();
	this->mapaFabricas[INDEXADO_HASH_EXTENSIBLE] = new FabricaIndexadoHashExtensible();


}


RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::crearRecursoDeAlmacenamientoEnArchivo(string estrategiaAlmacenamiento,int tamanio,string ruta,
		string nombreArchivo,string clavePrimaria,string tipoIndexacion,Componente* componente){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Almacenamiento* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
	Metadata* metadata=new Metadata();
	archivo->setTamanio(tamanio);
	archivo->setTipoArchivo(estrategiaAlmacenamiento);
	archivo->setRuta(ruta);
	metadata->setRuta(ruta);
	metadata->setNombreArchivo(nombreArchivo+METADATA);
	archivo->setNombreArchivo(nombreArchivo);
	archivo->setClavePrimaria(clavePrimaria);
	archivo->crear();
	metadata->crear();

	Registro* registro=(Registro*)componente;
	registro->setTamanio(tamanio);
	registro->serializarTexto();
	metadata->abrir();
	metadata->escribirMetadata(estrategiaAlmacenamiento,tamanio,clavePrimaria,tipoIndexacion,componente->getNombreAtributos());
	metadata->cerrar();
	metadata->abrir();
	metadata->hidratarMetadata();
	metadata->cerrar();
	estrategiaAlmac->setMetadata(metadata);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	EstrategiaIndice* estrategiaIndice=(EstrategiaIndice*)this->getFabrica(tipoIndexacion)->fabricar();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,NULL,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;
}

RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::crearRecursoDeAlmacenamientoEnBuffer(string estrategiaAlmacenamiento,int tamanio,
		string clavePrimaria,Componente* componente){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Almacenamiento* buffer=(Buffer*)this->getFabrica(BUFFER)->fabricar();
	Metadata* metadata=new Metadata();
	metadata->setArchivo(false);
	buffer->setTamanio(tamanio);
	buffer->setClavePrimaria(clavePrimaria);
	metadata->setPosicionLibreRegistro(-1);
	Registro* registro=(Registro*)componente;
	registro->setTamanio(tamanio);
	registro->serializarTexto();
	metadata->hidratarMetadataEnBuffer(componente->getNombreAtributos(), tamanio);
	estrategiaAlmac->setMetadata(metadata);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, NULL,buffer,unAlmacenamiento,NULL);
	return rAlmacenamiento;
}



RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::crearRecursoDeAlmacenamientoEnArchivoConBuffer(string estrategiaAlmacenamiento,int tamanio,string ruta
		,int cantidadRegistrosEnMemoria,string nombreArchivo,string clavePrimaria,string tipoIndexacion,Componente* componente){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Buffer* buffer=(Buffer*)this->getFabrica(BUFFER)->fabricar();
	Archivo* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
	Metadata* metadata=new Metadata();
	buffer->setTamanio(tamanio);
	buffer->setClavePrimaria(clavePrimaria);
	buffer->setCantidadRegistrosEnMemoria(cantidadRegistrosEnMemoria);
	archivo->setTamanio(tamanio);
	archivo->setTipoArchivo(estrategiaAlmacenamiento);
	archivo->setRuta(ruta);
	archivo->setNombreArchivo(nombreArchivo);
	archivo->setClavePrimaria(clavePrimaria);
	Registro* registro=(Registro*)componente;
	registro->setTamanio(tamanio);
	registro->serializarTexto();
	archivo->crear();
	metadata->setRuta(ruta);
	metadata->setNombreArchivo(nombreArchivo+METADATA);
	metadata->crear();
	metadata->abrir();
	metadata->escribirMetadata(estrategiaAlmacenamiento,tamanio,clavePrimaria,tipoIndexacion,componente->getNombreAtributos());
	metadata->cerrar();
	metadata->abrir();
	metadata->hidratarMetadata();
	metadata->cerrar();
	estrategiaAlmac->setMetadata(metadata);
	EstrategiaRecursoEscrituraDirecta* unAlmacenamiento=new EstrategiaRecursoEscrituraDirecta();
	EstrategiaIndice* estrategiaIndice=(EstrategiaIndice*)this->getFabrica(tipoIndexacion)->fabricar();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,buffer,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;


	return rAlmacenamiento;
}
RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::abrirRecursoDeAlmacenamientoEnArchivo(string ruta,string nombreArchivo){
	Metadata* metadata=new Metadata();
	metadata->setRuta(ruta);
	metadata->setNombreArchivo(nombreArchivo+METADATA);
	metadata->abrir();
	metadata->hidratarMetadata();
	metadata->cerrar();
	string estrategiaAlmacenamiento= metadata->getValorAtributosFijos(ESTRATEGIA_ALMACENAMIENTO);
	string clavePrimaria= metadata->getValorAtributosFijos(CLAVE_PRIMARIA);
	string tipoIndexacion=metadata->getValorAtributosFijos(TIPO_INDEXACION);
	int tamanio=atoi(metadata->getValorAtributosFijos(TAMANIO).c_str());
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Almacenamiento* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
	archivo->setTamanio(tamanio);
	archivo->setTipoArchivo(estrategiaAlmacenamiento);
	archivo->setRuta(ruta);
	archivo->setNombreArchivo(nombreArchivo);
	archivo->setClavePrimaria(clavePrimaria);
	estrategiaAlmac->setMetadata(metadata);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	EstrategiaIndice* estrategiaIndice=(EstrategiaIndice*)this->getFabrica(tipoIndexacion)->fabricar();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,NULL,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;


}
RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::abrirRecursoDeAlmacenamientoEnArchivoConBuffer(string ruta,string nombreArchivo,int cantidadRegistrosEnMemoria){
	Metadata* metadata=new Metadata();
	metadata->setRuta(ruta);
	metadata->setNombreArchivo(nombreArchivo+METADATA);
	metadata->abrir();
	string estrategiaAlmacenamiento= metadata->getValorAtributosFijos(ESTRATEGIA_ALMACENAMIENTO);
	string clavePrimaria= metadata->getValorAtributosFijos(CLAVE_PRIMARIA);
	string tipoIndexacion=metadata->getValorAtributosFijos(TIPO_INDEXACION);
	int tamanio=atoi(metadata->getValorAtributosFijos(TAMANIO).c_str());
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Almacenamiento* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
	Buffer* buffer=(Buffer*)this->getFabrica(BUFFER)->fabricar();
	buffer->setTamanio(tamanio);
	buffer->setClavePrimaria(clavePrimaria);
	buffer->setCantidadRegistrosEnMemoria(cantidadRegistrosEnMemoria);
	archivo->setTamanio(tamanio);
	archivo->setTipoArchivo(estrategiaAlmacenamiento);
	archivo->setRuta(ruta);
	archivo->setNombreArchivo(nombreArchivo);
	archivo->setClavePrimaria(clavePrimaria);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	EstrategiaIndice* estrategiaIndice=(EstrategiaIndice*)this->getFabrica(tipoIndexacion)->fabricar();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,buffer,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;
}
