/*
 * EstrategiaRecursoEscrituraDirecta.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoEscrituraDirecta.h"

EstrategiaRecursoEscrituraDirecta::EstrategiaRecursoEscrituraDirecta() {
	// TODO Auto-generated constructor stub

}

EstrategiaRecursoEscrituraDirecta::~EstrategiaRecursoEscrituraDirecta() {
	// TODO Auto-generated destructor stub
}
void EstrategiaRecursoEscrituraDirecta::buscar(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,
			list<Componente*> &resultadoDeLABusqueda,
			Componente* componente,
			vector<Almacenamiento*> almacenamientos,
			vector<EstrategiaIndice*> indices,
			string claves)
{

			vector<string> vecClaves;
			int tieneClavePrimaria = -1;
			int posCaracterIgual = -1;
			string etiquetaCampo = "";
			string campo = "";
			StringUtils::Tokenize(claves,vecClaves,DELIMITADOR);
			vector<string> vecCampos ((int)vecClaves.size());
			vector<int> vecEtiquetasCampos ((int)vecClaves.size());
			cout<<" claves para buscar: "<<claves<<endl;
			cout<<"etiqueta clave primaria: "<<almacenamientos.at(1)->getMetadata()->getClavePrimaria()<<endl;
			string etiquetaClavePrimaria = almacenamientos.at(1)->getMetadata()->getClavePrimaria();
			string campoclavePrimaria = "";
			tieneClavePrimaria = claves.find(etiquetaClavePrimaria,0);
			cout<<" tieneClavePrimaria: "<<tieneClavePrimaria<<endl;

			for( int i = 0; i<(int)vecClaves.size(); i++){
				posCaracterIgual = vecClaves.at(i).find_first_of('=',0);
				etiquetaCampo = vecClaves.at(i).substr(0,posCaracterIgual);
				campo = vecClaves.at(i).substr(posCaracterIgual+1,vecClaves.at(i).length());
				if(etiquetaCampo.compare(etiquetaClavePrimaria) == 0)
					campoclavePrimaria = campo;
	//			std::cout<<"etiquetaCampo: "<<etiquetaCampo<<std::endl;
	//			std::cout<<"campo: "<<campo<<std::endl;
	//			cout<<"this->metadata->getNumeroEtiqueta(etiquetaCampo): "<<estrategiaAlmacenamiento->getMetadata()->getNumeroEtiqueta(etiquetaCampo)<<endl;
				vecEtiquetasCampos[i] = almacenamientos.at(1)->getMetadata()->getNumeroEtiqueta(etiquetaCampo);
				vecCampos[i]= campo;
				std::cout<<"vecEtiquetasCampos[i]: "<<vecEtiquetasCampos.at(i)<<std::endl;
				std::cout<<"vecCampos[i]: "<<vecCampos.at(i)<<std::endl;
			}

			//Si el string claves que me pasan por parametro contiene la clave primaria, busco en el arbol, sino busco secuencialmente
			almacenamientos.at(1)->abrir();
			if(tieneClavePrimaria == 0){
				std::cout<<"campoclavePrimaria: "<<campoclavePrimaria<<std::endl;
				int numClavePrimaria = almacenamientos.at(1)->getMetadata()->getNumeroEtiqueta(etiquetaClavePrimaria);
				cout<<"numClavePrimaria "<<numClavePrimaria<<endl;
				EstrategiaIndice* estrategiaIndice=indices.at(1);
				estrategiaIndice->abrir();
				int pos = estrategiaIndice->buscar((char*)campoclavePrimaria.c_str());
				cout<<" registro encontrado posicion :"<<pos<<endl;
				estrategiaAlmacenamiento->hidratarComponente(almacenamientos.at(1),resultadoDeLABusqueda,componente,pos,vecCampos,vecEtiquetasCampos);
				estrategiaIndice->cerrar();


			}
			else{
				cout<<" else claves: "<<claves<<endl;
				estrategiaAlmacenamiento->busquedaSecuencial(resultadoDeLABusqueda,componente,almacenamientos.at(1),vecCampos,vecEtiquetasCampos);

			}
			almacenamientos.at(1)->cerrar();




}
int EstrategiaRecursoEscrituraDirecta::altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	int i=0;

	for(i=0;i<2;i++){
		Almacenamiento* almacenamiento=   almacenamientos.at(i);
		EstrategiaIndice* estrategiaIndice=indices.at(i);
		string clave=componente->getClave();
		almacenamiento->abrir();
		int pos = estrategiaAlmacenamiento->altaComponente(almacenamiento, componente);
		almacenamiento->cerrar();
		estrategiaIndice->abrir();
		estrategiaIndice->insertar((char*)clave.c_str(),pos);
		estrategiaIndice->cerrar();
	}
	return 0;
}

int EstrategiaRecursoEscrituraDirecta::bajaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	int i=0;
	for(i=0;i<2;i++){
		Almacenamiento* almacenamiento=   almacenamientos.at(i);
		EstrategiaIndice* estrategiaIndice=indices.at(i);
		estrategiaIndice->abrir();
		int pos = estrategiaIndice->buscar((char*)componente->getClave().c_str());
		estrategiaIndice->cerrar();
		almacenamiento->abrir();
		estrategiaAlmacenamiento->quitarComponente(almacenamiento, componente, pos);
		almacenamiento->cerrar();
	}
	return 0;
}
int EstrategiaRecursoEscrituraDirecta::actualizarComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	int i=0;
	for(i=0;i<2;i++){
		Almacenamiento* almacenamiento=   almacenamientos.at(i);
		EstrategiaIndice* estrategiaIndice=indices.at(i);
		estrategiaIndice->abrir();
		int pos = estrategiaIndice->buscar((char*)componente->getClave().c_str());
		estrategiaIndice->cerrar();
		almacenamiento->abrir();
		estrategiaAlmacenamiento->actualizarComponente(almacenamiento, componente, pos);
		almacenamiento->cerrar();
	}
	return 0;
}
std::string EstrategiaRecursoEscrituraDirecta::toString(){
	return "EstrategiaRecursoEscrituraDirecta";
}

void EstrategiaRecursoEscrituraDirecta::busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave){
	Almacenamiento* buffer=   almacenamientos.at(ALMACENAMIENTO_BUFFER);
	componente->setTamanio(buffer->getTamanio());
	buffer->abrir();
	//estrategiaAlmacenamiento->busquedaSecuencial(resultadoDeLABusqueda,componente, buffer, clave);
	buffer->cerrar();
}
