/*
 * EstrategiaAlmacenamientoTexto.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoTexto.h"
#include "../Modelo/Alumno.h"

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

int EstrategiaAlmacenamientoTexto::altaComponente(Almacenamiento* donde, Componente* componente){
	vector<int> vecPosiciones;
	int cantCaracteresRegistro = 0;
	int tamanioLibre = 0;
	vecPosiciones.clear();
	componente->serializar(TEXTO);
	donde->agregarComponente(componente);
	string bufferString = "";
	bufferString = componente->getBuffer();
	//cout<<"bufferString: "<<bufferString<<endl;
	cantCaracteresRegistro = bufferString.length();
	this->metadata->getPosicionLibreEnTexto(cantCaracteresRegistro ,vecPosiciones);
	int posicionAEscribir = vecPosiciones.at(0);
	tamanioLibre = vecPosiciones.at(1);
	//cout<<"cantCaracteresRegistro: "<<cantCaracteresRegistro<<endl;
	//cout<<"posicionAEscribir: "<<posicionAEscribir<<endl;
	//cout<<"tamanioLibre: "<<tamanioLibre<<endl;
	if(posicionAEscribir != -1){
		while((int)bufferString.length() < tamanioLibre){
			bufferString+=" ";
		}
	}
	 if(DEBUG == 0){
		 if(posicionAEscribir == -1)
			 cout<<"registro "<<bufferString<<" guardado en la ultima posicion "<<endl;
		 else
			 cout<<"registro "<<bufferString<<" guardado en la pos "<<posicionAEscribir<<endl;

	 }
	posicionAEscribir = donde->guardar(bufferString, posicionAEscribir); //si pos=-1 guarda al final, sino se para en la linea pos y escribe
	return posicionAEscribir;
}

void EstrategiaAlmacenamientoTexto::quitarComponente(Almacenamiento* donde, Componente* componente, int pos){
	//guardo en metadata la posicion del componente a borrar (luego en el alta de un nuevo componente
	//se escribe en esta posicion)
//	int numEtiquta = this->metadata->getNumeroEtiqueta(this->metadata->getClavePrimaria());
	string clave = componente->getClave();
	//cout<<"this->metadata->getClavePrimaria() "<<this->metadata->getClavePrimaria()<<endl;
	//cout<<"numEtiquta "<<numEtiquta<<endl;
	//cout<<"componente->getClave() "<<componente->getClave()<<endl;
	string registro = "";
	donde->leer(registro,pos);
	//cout<<"pos "<<pos<<endl;
	//cout<<"registro leido en pos: "<<registro<<endl;
	componente->hidratar(registro);
	if(DEBUG == 0)
		cout<<"registro borrardo: "<<registro<< " de la pos "<<pos<<endl;
	//cout<<"registro.length() "<<registro.length()<<endl;
	this->metadata->setPosicionLibreEnTexto(pos,(int)registro.length());
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
	int pos = 0;
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
		pos += bufferAux.length() + 1;
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
void EstrategiaAlmacenamientoTexto::hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,string clavePrimaria, int numEtiquetaClave){

}
