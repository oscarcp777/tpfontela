/*
 * EstrategiaAlmacenamientoRegistros.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoRegistros.h"
#include "../Modelo/Alumno.h"
#include "../Modelo/Alumno.h"

EstrategiaAlmacenamientoRegistros::EstrategiaAlmacenamientoRegistros() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoRegistros::~EstrategiaAlmacenamientoRegistros() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoRegistros::guardar(Almacenamiento* donde){

//	std::string metaData;
//	int i=1;
//	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
//	Componente* componente;
//	if(donde->getExisteMetaData() == 0){
//		metaData = this->generarMetadata((Componente*)*iter);
//		donde->escribirMetadata(metaData);
//	}
//	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
//		componente = (Componente*)*iter;
//		donde->guardar(componente->getDatosRegistro().c_str(),donde->getTamanio());
//		iter++;
//		i++;
//	}

}

std::string EstrategiaAlmacenamientoRegistros::toString(){
   	return "EstrategiaAlmacenamientoRegistros";
   }



int EstrategiaAlmacenamientoRegistros::altaComponente(Almacenamiento* donde, Componente* componente){
		int posAEscribir = this->metadata->getPosicionLibreRegistro();
		componente->serializar(BINARIO);				//genera el buffer (registro) en binario
	    donde->agregarComponente(componente);  			//agrega el componente a la lista de componentes
	    if(DEBUG == 0){
	    	if(posAEscribir == -1)
	    		cout<<"registro guardado en la ultima posicion, tamaño "<<componente->getTamanio()<<endl;
	    	else
	    		cout<<"registro guardado en la pos "<<posAEscribir<<" tamaño "<<componente->getTamanio()<<endl;
	    }
	    posAEscribir = donde->guardar(componente->getBuffer(),posAEscribir); //guarda en almacenamiento si pos es < 0 guarda al final
	   	return posAEscribir;
}

void EstrategiaAlmacenamientoRegistros::quitarComponente(Almacenamiento* donde, Componente* componente, int pos){
	int numEtiquta = this->metadata->getNumeroEtiqueta(this->metadata->getClavePrimaria());
	string clave = componente->getClave();
	cout<<"this->metadata->getClavePrimaria() "<<this->metadata->getClavePrimaria()<<endl;
	cout<<"numEtiquta "<<numEtiquta<<endl;
	cout<<"componente->getClave() "<<componente->getClave()<<endl;

	//guardo en metadata la posicion del componente a borrar (luego en el alta de un nuevo componente
	//se escribe en esta posicion)
	if(DEBUG == 0)
			cout<<"registro borrardo de la pos "<<pos<<" tamaño "<<componente->getTamanio()<<endl;
	this->metadata->setPosicionLibreRegistro(pos);
	//TODO actualizar indice..... o actualizar cuando hago IndiceBuscarComponente(clave)
}


void EstrategiaAlmacenamientoRegistros::busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,std::string clave){

	int pos = 0;
	vector<string> vecClaves;
	string aux;
	int posCaracterIgual = -1;
	string etiquetaCampo = "";
	string campo = "";
	int resCompare = 0;
	char* bufferAux = new char [donde->getTamanio()];
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
		donde->leer(bufferAux, pos);
		componente->setBuffer(bufferAux);
		componente->hidratar(BINARIO);

		for(int k = 0; k< (int)vecCampos.size();k++){
			if(resCompare == 0)//solo compara si la comparacion anterior dio =
				resCompare+=componente->compareTo(vecCampos.at(k),vecEtiquetasCampos.at(k));
//			cout<<"vecCampos.at(k): "<<vecCampos.at(k)<<endl;
//			cout<<"vecEtiquetasCampos.at(k): "<<vecEtiquetasCampos.at(k)<<endl;
		}
//		cout<<"nombre: "<<((Alumno*)componente)->getNombre()<<endl;
//		cout<<"padron: "<<((Alumno*)componente)->getPadron()<<endl;
//		cout<<"dni: "<<((Alumno*)componente)->getDni()<<endl;
		if (resCompare == 0){
			resultadoDeLABusqueda.push_back(componente);
			componente = componente->obtenerNuevaInstancia();
			componente->setTamanio(donde->getTamanio());
		}
		memset(bufferAux,0,donde->getTamanio());
		pos += donde->getTamanio();

	}

	delete bufferAux;

}
void EstrategiaAlmacenamientoRegistros::hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,string clavePrimaria, int numEtiquetaClave){

}
