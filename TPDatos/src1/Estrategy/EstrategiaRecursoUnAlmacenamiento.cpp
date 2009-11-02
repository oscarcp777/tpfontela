/*
 * EstrategiaRecursoUnAlmacenamiento.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoUnAlmacenamiento.h"


int EstrategiaRecursoUnAlmacenamiento::altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	EstrategiaIndice* estrategiaIndice=indices.at(0);
	string clave=componente->getClave();
	almacenamiento->abrir();
	int pos = estrategiaAlmacenamiento->altaComponente(almacenamiento, componente);
	almacenamiento->cerrar();
	estrategiaIndice->abrir();
	estrategiaIndice->insertar((char*)clave.c_str(),pos);
	estrategiaIndice->cerrar();
	return pos;
}
int EstrategiaRecursoUnAlmacenamiento::bajaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente, vector<EstrategiaIndice*> indices){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	EstrategiaIndice* estrategiaIndice=indices.at(0);
	estrategiaIndice->abrir();
	int pos = estrategiaIndice->buscar((char*)componente->getClave().c_str());
	estrategiaIndice->cerrar();
	almacenamiento->abrir();
	estrategiaAlmacenamiento->quitarComponente(almacenamiento, componente, pos);
	almacenamiento->cerrar();
	return 0;
}
int EstrategiaRecursoUnAlmacenamiento::actualizarComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente,vector<EstrategiaIndice*> indices){
	Almacenamiento* almacenamiento=   almacenamientos.at(0);
	EstrategiaIndice* estrategiaIndice=indices.at(0);
	estrategiaIndice->abrir();
	int pos = estrategiaIndice->buscar((char*)componente->getClave().c_str());
	estrategiaIndice->cerrar();
	almacenamiento->abrir();
	estrategiaAlmacenamiento->actualizarComponente(almacenamiento, componente, pos);
	almacenamiento->cerrar();
	return 0;
}
EstrategiaRecursoUnAlmacenamiento::EstrategiaRecursoUnAlmacenamiento() {

}

EstrategiaRecursoUnAlmacenamiento::~EstrategiaRecursoUnAlmacenamiento() {
	// TODO Auto-generated destructor stub
}
std::string EstrategiaRecursoUnAlmacenamiento::toString(){
	return "EstrategiaRecursoUnAlmacenamiento";
}
void EstrategiaRecursoUnAlmacenamiento::buscar(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,
		list<Componente*> &resultadoDeLABusqueda,
		Componente* componente,
		vector<Almacenamiento*> almacenamientos,
		vector<EstrategiaIndice*> indices,
		string claves){

		vector<string> vecClaves;
		int tieneClavePrimaria = -1;
		int posCaracterIgual = -1;
		string etiquetaCampo = "";
		string campo = "";
		StringUtils::Tokenize(claves,vecClaves,DELIMITADOR);
		vector<string> vecCampos ((int)vecClaves.size());
		vector<int> vecEtiquetasCampos ((int)vecClaves.size());
		string etiquetaClavePrimaria = almacenamientos.at(0)->getMetadata()->getClavePrimaria();
		string campoclavePrimaria = "";
		tieneClavePrimaria = claves.find(etiquetaClavePrimaria,0);

		for( int i = 0; i<(int)vecClaves.size(); i++){
			posCaracterIgual = vecClaves.at(i).find_first_of('=',0);
			etiquetaCampo = vecClaves.at(i).substr(0,posCaracterIgual);
			campo = vecClaves.at(i).substr(posCaracterIgual+1,vecClaves.at(i).length());
			if(etiquetaCampo.compare(etiquetaClavePrimaria) == 0)
				campoclavePrimaria = campo;
			vecEtiquetasCampos[i] = almacenamientos.at(0)->getMetadata()->getNumeroEtiqueta(etiquetaCampo);
			vecCampos[i]= campo;
		}

		//Si el string claves que me pasan por parametro contiene la clave primaria, busco en el arbol, sino busco secuencialmente
		almacenamientos.at(0)->abrir();
		if(tieneClavePrimaria == 0){
			int numClavePrimaria = almacenamientos.at(0)->getMetadata()->getNumeroEtiqueta(etiquetaClavePrimaria);
			EstrategiaIndice* estrategiaIndice=indices.at(0);
			estrategiaIndice->abrir();
			int pos = estrategiaIndice->buscar((char*)campoclavePrimaria.c_str());
			estrategiaAlmacenamiento->hidratarComponente(almacenamientos.at(0),resultadoDeLABusqueda,componente,pos,vecCampos,vecEtiquetasCampos);
			estrategiaIndice->cerrar();


		}
		else{
			estrategiaAlmacenamiento->busquedaSecuencial(resultadoDeLABusqueda,componente,almacenamientos.at(0),vecCampos,vecEtiquetasCampos);

		}
		almacenamientos.at(0)->cerrar();

}

