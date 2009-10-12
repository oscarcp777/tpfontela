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

		Archivo* archivo=(Archivo*)donde;
		std::string metaData;
		archivo->abrirArchivo();
		int i=1;
			std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
			Componente* componente;
			metaData = this->getMetaData((Componente*)*iter);
			archivo->guardar(metaData.c_str(),donde->getTamanio());


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
			  std::map<std::string,std::string>::iterator it;

			  for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){

				  registro+= it->second + DELIMITADOR;
			  }

			return registro;
}

void EstrategiaAlmacenamientoRegistros::agregarComponente(Almacenamiento* donde, Componente* componente){
	    componente->serializar();
	    int tamanio=0;
		std::string datos=this->generarRegistro(componente);
		tamanio=((int)datos.length());
		std::cout<<datos<<std::endl;
		if(tamanio<donde->getTamanio()){
			componente->setDatosRegistro(datos);
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
