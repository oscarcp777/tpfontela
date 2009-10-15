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
	if(donde->getExisteMetaData() == 0){
		metaData = this->generarMetadata((Componente*)*iter);
		metaData += "\n";
		donde->escribirMetadata(metaData);
	}
	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
		componente = (Componente*)*iter;
		donde->guardar(componente->getDatosRegistro());
		iter++;
		i++;
	}




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

//std::string EstrategiaAlmacenamientoTexto::getMetaData(Componente* componente){
//	 std::string metaData="";
//	 std::map<std::string,std::string>::iterator it;
//
//	 for( it=componente->iteratorCampos() ; it != componente->finIteratorCampos(); ++it ){
//
//		 metaData+= it->first + DELIMITADOR;
//	 }
//	 metaData+="\n";
//	 return metaData;
//}

void EstrategiaAlmacenamientoTexto::busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave){

		std::string datos="";
	    std::string valor="";

	    vector<string> tokens;
		Archivo* archivo=(Archivo*)donde;
		 vector<string>::iterator the_iterator;
		archivo->abrir();
		archivo->irAlPrincipio();
		while(!archivo->fin()){
			tokens.clear();
			archivo->leer(datos);
			std::cout<<"DATOS de la linea: "<<datos<<std::endl;

			StringUtils::Tokenize(datos,tokens,DELIMITADOR);
			the_iterator = tokens.begin();
			while( the_iterator != tokens.end() ) {
				valor = *the_iterator;
				++the_iterator;
				cout<<"dato del campo :"<<valor<<endl;
			}

		}

		// Libero el buffer
		//delete[] buffer;
		archivo->cerrar();


}
