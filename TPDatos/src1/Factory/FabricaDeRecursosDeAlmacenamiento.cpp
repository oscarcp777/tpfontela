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
		string nombreArchivo,string clavePrimaria,string tipoIndexacion){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Almacenamiento* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
	archivo->setTamanio(tamanio);
	archivo->setTipoArchivo(estrategiaAlmacenamiento);
	archivo->setRuta(ruta);
	archivo->setNombreArchivo(nombreArchivo);
	archivo->setClavePrimaria(clavePrimaria);
	archivo->getMetadata()->setNombreArchivo(ruta+nombreArchivo);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	EstrategiaIndice* estrategiaIndice=(EstrategiaIndice*)this->getFabrica(tipoIndexacion)->fabricar();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,NULL,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;
}

RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::crearRecursoDeAlmacenamientoEnBuffer(string estrategiaAlmacenamiento,int tamanio,string clavePrimaria){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Almacenamiento* buffer=(Buffer*)this->getFabrica(BUFFER)->fabricar();
	buffer->setTamanio(tamanio);
	buffer->setClavePrimaria(clavePrimaria);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, NULL,buffer,unAlmacenamiento,NULL);
	return rAlmacenamiento;
}



RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::crearRecursoDeAlmacenamientoEnArchivoConBuffer(string estrategiaAlmacenamiento,int tamanio,string ruta
		,int cantidadRegistrosEnMemoria,string nombreArchivo,string clavePrimaria,string tipoIndexacion){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Buffer* buffer=(Buffer*)this->getFabrica(BUFFER)->fabricar();
	Archivo* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
	buffer->setTamanio(tamanio);
	buffer->setClavePrimaria(clavePrimaria);
	buffer->setCantidadRegistrosEnMemoria(cantidadRegistrosEnMemoria);
	archivo->setTamanio(tamanio);
	archivo->setTipoArchivo(estrategiaAlmacenamiento);
	archivo->setRuta(ruta);
	archivo->setNombreArchivo(nombreArchivo);
	archivo->setClavePrimaria(clavePrimaria);

	EstrategiaRecursoEscrituraDirecta* unAlmacenamiento=new EstrategiaRecursoEscrituraDirecta();
	EstrategiaIndice* estrategiaIndice=(EstrategiaIndice*)this->getFabrica(tipoIndexacion)->fabricar();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,buffer,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;


	return rAlmacenamiento;
}
RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::abrirRecursoDeAlmacenamientoEnArchivo(string ruta,string nombreArchivo){

	/*    EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
		Almacenamiento* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
		archivo->setTamanio(tamanio);
		archivo->setTipoArchivo(estrategiaAlmacenamiento);
		archivo->setRuta(ruta);
		archivo->setNombreArchivo(nombreArchivo);
		archivo->setClavePrimaria(clavePrimaria);
		EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
		EstrategiaIndice* estrategiaIndice=(EstrategiaIndice*)this->getFabrica(tipoIndexacion)->fabricar();
		RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,NULL,unAlmacenamiento,estrategiaIndice);*/
		return new RecursoDeAlmacenamiento();


}
RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::abrirRecursoDeAlmacenamientoEnArchivoConBuffer(string ruta,string nombreArchivo,int cantidadRegistrosEnMemoria){
	return new RecursoDeAlmacenamiento();
}
