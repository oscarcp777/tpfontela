/*
 * EstrategiaAlmacenamientoTexto.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoTexto.h"

EstrategiaAlmacenamientoTexto::EstrategiaAlmacenamientoTexto() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoTexto::~EstrategiaAlmacenamientoTexto() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoTexto::guardar(Almacenamiento* donde){
	std::string metaData;
	 int i=1;
	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
    Componente* componente;
	Archivo* archivo=(Archivo*)donde;
	    archivo->abrirArchivo();
	    if(archivo->getExisteMetaData()==1){
		metaData = this->getMetaData((Componente*)*iter);
		archivo->guardar(metaData);
	    }
	    archivo->irAlFinal();
		while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
			componente = (Componente*)*iter;
			archivo->guardar(componente->getDatosRegistro());
			iter++;
			i++;
		}

	archivo->cerrarArchivo();

}

void EstrategiaAlmacenamientoTexto::agregarComponente(Almacenamiento* donde, Componente* componente){
	std::string datos=this->generarRegistro(componente);
	componente->setDatosRegistro(datos);
	std::cout<<datos<<std::endl;
	donde->agregarComponente(componente);
}



std::string EstrategiaAlmacenamientoTexto::toString(){
   	return "EstrategiaAlmacenamientoTexto";
   }

std::string EstrategiaAlmacenamientoTexto::generarRegistro(Componente* componente){

	std::string registro="";
	registro = EstrategiaAlmacenamiento::generarRegistro(componente);
	registro+="\n";
	return registro;
}
std::string EstrategiaAlmacenamientoTexto::getMetaData(Componente* componente){
	 std::string metaData="";
	 std::map<std::string,std::string>::iterator it;

	 for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){

		 metaData+= it->first + DELIMITADOR;
	 }
	 metaData+="\n";
	 return metaData;
}

void EstrategiaAlmacenamientoTexto::busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave){



}
