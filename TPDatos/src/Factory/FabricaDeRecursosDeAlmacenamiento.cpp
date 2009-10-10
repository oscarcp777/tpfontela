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
#include "../fabricas/FabricaArchivo.h"
#include "../fabricas/FabricaBuffer.h"
FabricaDeRecursosDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica=NULL;
FabricaDeRecursosDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::obtenerInstancia(){

       if(!FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica){
    	   FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica= new FabricaDeRecursosDeAlmacenamiento();
       }
       return FabricaDeRecursosDeAlmacenamiento::unicaInstanciaFabrica;
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

/**
 *std::string estrategiaAlmacenamiento puede ser de tipo: texto,registros,bloques
 *std::string almacenamiento pude ser del tipo archivo ,buffer
 *  ,
    		   (Almacenamiento*));
 */
RecursoDeAlmacenamiento* FabricaDeRecursosDeAlmacenamiento::RecursoDeAlmacenamientoEnArchivo(std::string estrategiaAlmacenamiento,std::string almacenamiento ,Componente* componente){
    EstrategiaAlmacenamiento* estrategiaAlmac=( EstrategiaAlmacenamiento* )this->getFabrica(estrategiaAlmacenamiento)->fabricar();
    Almacenamiento* almac=(Almacenamiento*)this->getFabrica(almacenamiento)->fabricar(componente);
    RecursoDeAlmacenamiento* rAlmacenamiento=
    		   new RecursoDeAlmacenamiento(new Componente(200),new EstrategiaRecurso(),estrategiaAlmac, almac);


  return rAlmacenamiento;
}

FabricaDeRecursosDeAlmacenamiento::~FabricaDeRecursosDeAlmacenamiento() {
	// TODO Auto-generated destructor stub
}
