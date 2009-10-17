/*
 * EstrategiaAlmacenamientoRegistros.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoRegistros.h"
#include "../Modelo/Alumno.h"

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
	if(donde->getExisteMetaData() == 0){
		metaData = this->generarMetadata((Componente*)*iter);
		donde->escribirMetadata(metaData);
	}
	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
		componente = (Componente*)*iter;
		donde->guardar(componente->getDatosRegistro().c_str(),donde->getTamanio());
		iter++;
		i++;
	}

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

//std::string EstrategiaAlmacenamientoRegistros::getMetaData(Componente* componente){
//	 std::string metaData="";
//	 std::map<std::string,std::string>::iterator it;
//
//	 for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){
//
//		 metaData+= it->first + DELIMITADOR;
//	 }
//
//	 return metaData;
//}

void EstrategiaAlmacenamientoRegistros::busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave){

	// Creo buffer de tamanio length.
	char* buffer = new char[donde->getTamanio() + 1];
	bool encontrado = false;
	std::string datos="";
    std::string valor="" ;
    std::string metaData="";
    int i = 0;
    vector<string> tokens;
    vector<string> tags;
	Archivo* archivo=(Archivo*)donde;
	 vector<string>::iterator the_iterator;

	archivo->abrir();
	archivo->irAlPrincipio();
	metaData = archivo->leerMetadata();
	StringUtils::Tokenize(metaData,tags,DELIMITADOR);

	while(!archivo->fin() && !encontrado){
		i=0;
		tokens.clear();
		archivo->leer(buffer,donde->getTamanio());
		datos="";
		datos=buffer;
		std::cout<<"DATOS del registro: "<<datos<<std::endl;

		StringUtils::Tokenize(datos,tokens,DELIMITADOR);
		the_iterator = tokens.begin();
		while( the_iterator != tokens.end() ) {
			valor = *the_iterator;
			++the_iterator;
			cout<<"tag: "<<tags.at(i);
			cout<<"  dato: "<<valor<<endl;
			componente->cargarAtributo(tags.at(i),valor);

			if(valor.compare(clave) == 0)
				encontrado = true;

			i++;
		}
		if(encontrado)
			componente->hidratar();

		}

	// Libero el buffer
	delete[] buffer;
	archivo->cerrar();


}
