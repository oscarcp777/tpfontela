/*
 * EstrategiaAlmacenamientoRegistros.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoRegistros.h"

EstrategiaAlmacenamientoRegistros::EstrategiaAlmacenamientoRegistros() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoRegistros::~EstrategiaAlmacenamientoRegistros() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoRegistros::guardar(Almacenamiento* donde){

	    std::string metaData;
		 int i=1;
		std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
	    Componente* componente;
		Archivo* archivo=(Archivo*)donde;
		    archivo->abrirArchivo();
		    if(archivo->getExisteMetaData()==1){
			metaData = this->getMetaData((Componente*)*iter);
			archivo->guardar(metaData.c_str(),donde->getTamanio());
			archivo->setExisteMetaData(0);
		    }
		    archivo->irAlFinal();
			while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
				componente = (Componente*)*iter;
				archivo->guardar(componente->getDatosRegistro().c_str(),donde->getTamanio());
				iter++;
				i++;
			}

		archivo->cerrarArchivo();


}

std::string EstrategiaAlmacenamientoRegistros::toString(){
   	return "EstrategiaAlmacenamientoRegistros";
   }

std::string EstrategiaAlmacenamientoRegistros::generarRegistro(Componente* componente){
	std::string registro="";
	registro = EstrategiaAlmacenamiento::generarRegistro(componente);
	return registro;
}

void EstrategiaAlmacenamientoRegistros::agregarComponente(Almacenamiento* donde, Componente* componente){

	    int tamanio=0;
		std::string registro=this->generarRegistro(componente);
		tamanio=((int)registro.length());
		std::cout<<registro<<std::endl;
		if(tamanio<donde->getTamanio()){
			componente->setDatosRegistro(registro);
			donde->agregarComponente(componente);
		}


}
std::string EstrategiaAlmacenamientoRegistros::getMetaData(Componente* componente){
	 std::string metaData="";
	 std::map<std::string,std::string>::iterator it;

	 for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){

		 metaData+= it->first + DELIMITADOR;
	 }

	 return metaData;
}

void EstrategiaAlmacenamientoRegistros::busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave){



}
