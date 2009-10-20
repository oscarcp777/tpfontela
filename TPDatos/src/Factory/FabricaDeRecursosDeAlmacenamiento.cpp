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


}


RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::RecursoDeAlmacenamientoEnArchivo(std::string estrategiaAlmacenamiento,int tamanio){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Almacenamiento* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
	archivo->setTamanio(tamanio);
	archivo->setTipoArchivo(estrategiaAlmacenamiento);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	EstrategiaIndice* estrategiaIndice= new EstrategiaIndice();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,NULL,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;
}

RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::RecursoDeAlmacenamientoEnBuffer(std::string estrategiaAlmacenamiento,int tamanio){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
	Buffer* buffer=(Buffer*)this->getFabrica(BUFFER)->fabricar();
	buffer->setTamanio(tamanio);
	EstrategiaRecursoUnAlmacenamiento* unAlmacenamiento=new EstrategiaRecursoUnAlmacenamiento();
	EstrategiaIndice* estrategiaIndice= new EstrategiaIndice();
	RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, NULL,buffer,unAlmacenamiento,estrategiaIndice);
	return rAlmacenamiento;
}



RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::RecursoDeAlmacenamientoEnArchivoConBuffer(std::string estrategiaAlmacenamiento,int tamanio){
	EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
		Buffer* buffer=(Buffer*)this->getFabrica(BUFFER)->fabricar();
		Archivo* archivo=(Archivo*)this->getFabrica(ARCHIVO)->fabricar();
		buffer->setTamanio(tamanio);
		archivo->setTipoArchivo(estrategiaAlmacenamiento);
		archivo->setTamanio(tamanio);
		EstrategiaRecursoEscrituraDirecta* unAlmacenamiento=new EstrategiaRecursoEscrituraDirecta();
		EstrategiaIndice* estrategiaIndice= new EstrategiaIndice();
		RecursoDeAlmacenamiento* rAlmacenamiento= new RecursoDeAlmacenamiento(estrategiaAlmac, archivo,buffer,unAlmacenamiento,estrategiaIndice);
		return rAlmacenamiento;


	return rAlmacenamiento;
}
