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
	cantCaracteresRegistro = bufferString.length();
	donde->getMetadata()->getPosicionLibreEnTexto(cantCaracteresRegistro ,vecPosiciones);
	int posicionAEscribir = vecPosiciones.at(0);
	tamanioLibre = vecPosiciones.at(1);
	if(posicionAEscribir != -1){
		while((int)bufferString.length() < tamanioLibre){
			bufferString+=" ";
		}
	}
	posicionAEscribir = donde->guardar(bufferString, posicionAEscribir); //si pos=-1 guarda al final, sino se para en la linea pos y escribe
	return posicionAEscribir;
}

void EstrategiaAlmacenamientoTexto::quitarComponente(Almacenamiento* donde, Componente* componente, int pos){
	//guardo en metadata la posicion del componente a borrar (luego en el alta de un nuevo componente
	//se escribe en esta posicion)
//	int numEtiquta = donde->getMetadata()->getNumeroEtiqueta(donde->getMetadata()->getClavePrimaria());
	string clave = componente->getClave();
	string registro = "";
	donde->leer(registro,pos);
	componente->hidratar(registro);
	cout<<"registro borrardo: "<<registro<< " de la pos "<<pos<<endl;
	donde->getMetadata()->setPosicionLibreEnTexto(pos,(int)registro.length());
	//TODO actualizar indice..... o actualizar cuando hago IndiceBuscarComponente(clave)
}

int EstrategiaAlmacenamientoTexto::actualizarComponente(Almacenamiento* donde, Componente* componente, int pos){
	cout<<"modificar el componente en la posicion: "<<pos<<endl;
	string registro = "";
	donde->leer(registro,pos);
	donde->getMetadata()->setPosicionLibreEnTexto(pos,(int)registro.length());
	string bufferString = "";
	componente->serializar(TEXTO);
	bufferString = componente->getBuffer();
	cout<<"bufferString "<<bufferString<<endl;
	donde->guardar(bufferString, -1); //agrego al final
	return 0;
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

	if (resCompare == 0){
		resultadoDeLABusqueda.push_back(componente);
	}


}
