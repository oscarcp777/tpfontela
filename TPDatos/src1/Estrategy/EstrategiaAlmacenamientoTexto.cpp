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
//	std::string metaData;
//	int i=1;
//	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
//	Componente* componente;
//	if(donde->getExisteMetaData() == 0){
//		metaData = this->generarMetadata((Componente*)*iter);
//		metaData += "\n";
//		donde->escribirMetadata(metaData);
//	}
//	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
//		componente = (Componente*)*iter;
//		donde->guardar(componente->getDatosRegistro());
//		iter++;
//		i++;
//	}




}

void EstrategiaAlmacenamientoTexto::altaComponente(Almacenamiento* donde, Componente* componente){
	int pos = -1;
	componente->serializar(TEXTO);
	donde->agregarComponente(componente);
	string bufferString = "";
	bufferString = componente->getBuffer();
	cout<<"bufferString: "<<bufferString<<endl;
	donde->guardar(bufferString, pos); //si pos=-1 guarda al final, sino se para en la linea pos y escribe
}

void EstrategiaAlmacenamientoTexto::quitarComponente(Almacenamiento* donde, Componente* componente, string clave){
	//int pos = 0; // = IndiceBuscarComponente(clave);
	//guardo en metadata la posicion del componente a borrar (luego en el alta de un nuevo componente
	//se escribe en esta posicion)
	//this->metadata->setPosicionLineaLibre(pos);
	//TODO actualizar indice..... o actualizar cuando hago IndiceBuscarComponente(clave)
}



std::string EstrategiaAlmacenamientoTexto::toString(){
   	return "EstrategiaAlmacenamientoTexto";
   }

std::string EstrategiaAlmacenamientoTexto::generarRegistro(Componente* componente){

	std::string registro="";
//	registro = EstrategiaAlmacenamiento::generarRegistro(componente);
//	registro+="\n";
	return registro;
}


void EstrategiaAlmacenamientoTexto::busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,std::string clave){

	vector<string> vecClaves;
	string aux;
	int posCaracterIgual = -1;
	string etiquetaCampo = "";
	string campo = "";
	int resCompare = 0;
	string bufferAux ="";
	componente->setTamanio(donde->getTamanio());
	StringUtils::Tokenize(clave,vecClaves,DELIMITADOR);
	vector<string> vecCampos ((int)vecClaves.size());
	vector<int> vecEtiquetasCampos ((int)vecClaves.size());

	for( int i = 0; i<(int)vecClaves.size(); i++){
			posCaracterIgual = vecClaves.at(i).find_first_of('=',0);
			etiquetaCampo = vecClaves.at(i).substr(0,posCaracterIgual);
			campo = vecClaves.at(i).substr(posCaracterIgual+1,vecClaves.at(i).length());
//			std::cout<<"etiquetaCampo: "<<etiquetaCampo<<std::endl;
//			std::cout<<"campo: "<<campo<<std::endl;
//			cout<<"this->metadata->getNumeroEtiqueta(etiquetaCampo): "<<this->metadata->getNumeroEtiqueta(etiquetaCampo)<<endl;
			vecEtiquetasCampos[i] = this->metadata->getNumeroEtiqueta(etiquetaCampo);
			vecCampos[i]= campo;
//			std::cout<<"vecEtiquetasCampos[i]: "<<vecEtiquetasCampos.at(i)<<std::endl;
//			std::cout<<"vecCampos[i]: "<<vecCampos.at(i)<<std::endl;
//			std::cout<<"vecEtiquetasCampos[i]: "<<vecCampos[i]<<endl;
		}


	while (!donde->fin()){
		resCompare = 0;
		donde->leer(bufferAux);
		//cout<<"bufferAux: "<<bufferAux<<endl;
		componente->setBuffer((char*)bufferAux.c_str());
		componente->hidratar(TEXTO);

		for(int k = 0; k< (int)vecCampos.size();k++){
			if(resCompare == 0)//solo compara si la comparacion anterior dio =
				resCompare+=componente->compareTo(vecCampos.at(k),vecEtiquetasCampos.at(k));
		}

		//cout<<"resCompare: "<<resCompare<<endl;
		if (resCompare == 0){
			resultadoDeLABusqueda.push_back(componente);
			componente = componente->obtenerNuevaInstancia();
			componente->setTamanio(donde->getTamanio());
		}
		bufferAux = "";
	}

}
