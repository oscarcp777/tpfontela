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
	donde->getMetadata()->getPosicionLibreEnTexto(cantCaracteresRegistro ,vecPosiciones);
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
//	int numEtiquta = donde->getMetadata()->getNumeroEtiqueta(donde->getMetadata()->getClavePrimaria());
	string clave = componente->getClave();
	//cout<<"donde->getMetadata()->getClavePrimaria() "<<donde->getMetadata()->getClavePrimaria()<<endl;
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
	donde->getMetadata()->setPosicionLibreEnTexto(pos,(int)registro.length());
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


void EstrategiaAlmacenamientoTexto::busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,vector<string> vecCampos, vector<int> vecEtiquetasCampos){

	int resCompare = 0;
	string bufferAux ="";
	componente->setTamanio(donde->getTamanio());
	int pos = 0;

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
void EstrategiaAlmacenamientoTexto::hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,vector<string> vecCampos, vector<int> vecEtiquetasCampos){
	int resCompare = 0;
	string bufferAux ="";
	componente->setTamanio(donde->getTamanio());

	donde->leer(bufferAux, pos);
	componente->setBuffer((char*)bufferAux.c_str());
	componente->hidratar(TEXTO);

	for(int k = 0; k< (int)vecCampos.size();k++){
		if(resCompare == 0)//solo compara si la comparacion anterior dio =
			resCompare+=componente->compareTo(vecCampos.at(k),vecEtiquetasCampos.at(k));
	}

	//cout<<"resCompare: "<<resCompare<<endl;
	if (resCompare == 0){
		resultadoDeLABusqueda.push_back(componente);
	}


}
