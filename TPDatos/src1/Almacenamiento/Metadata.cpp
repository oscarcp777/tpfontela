/*
 * Metadata.cpp
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */

#include "Metadata.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "../utils/StringUtils.h"
using namespace std;

Metadata::Metadata() {
	this->metadataSize = -1;
	this->archivo=true;
	this->setTipoArchivo(ESTRATEGIA_ALMACENAMIENTO);
}

Metadata::~Metadata() {

}
void  Metadata::actualizarMetadata(string estrategiaAlmacenamiento){
	  if(estrategiaAlmacenamiento.compare(ESTRATEGIA_ALMACENAMIENTO_BLOQUES)==0)
       this->guardarMapaAtributosVariables(this->mapaTamanioBloques);
	  if(estrategiaAlmacenamiento.compare(ESTRATEGIA_ALMACENAMIENTO_TEXTO)==0)
       this->guardarMapaAtributosVariables(this->mapaPosicionesAInsertarTexto);
	  if(estrategiaAlmacenamiento.compare(ESTRATEGIA_ALMACENAMIENTO_REGISTROS)==0)
       this->guardarVectorAtributosVariables();
}
void Metadata::actualizarMapaAtributosVariables(int posicion,int espacioLiberado){
	int tamanioBloque,indice,espacioLibre;
	tamanioBloque=atoi(StringUtils::getValorTag(TAMANIO,this->mapaAtributosFijos).c_str());
	indice=posicion/tamanioBloque;
	cout<<" metadata       indice "<<indice<<endl;
	espacioLibre=this->mapaTamanioBloques[indice];
	cout<<"espacioLibre: "<<espacioLibre<<endl;
	cout<<"espacioLiberado"<<espacioLiberado<<endl;
	this->mapaTamanioBloques[indice]=espacioLibre+espacioLiberado;
	cout<<"this->mapaTamanioBloques[indice]"<<this->mapaTamanioBloques[indice]<<endl;
	//escribir a disco :P :P :P GIL!!


}
void Metadata::guardarVectorAtributosVariables(){
	vector<string>::iterator the_iterator;
	string valor ;
	int tamanioRegistro=0;
	string registro="-1|";
	the_iterator = this->vectorAtributosVariables.begin();
	while( the_iterator != this->vectorAtributosVariables.end() ) {
		valor = *the_iterator;
		//		cout<<"valor :"<<valor<<endl;
		if(valor.compare("-1")!=0){
			registro=registro+valor+DELIMITADOR;
		}
		++the_iterator;

	}
	cout<<registro<<endl;
	tamanioRegistro =registro.length();
	this->guardar((char*)&tamanioRegistro,this->metadataSize,sizeof(tamanioRegistro));
	this->guardar((char*)registro.c_str(),this->metadataSize+sizeof(tamanioRegistro),tamanioRegistro);

}
int Metadata::getPosicionLibreRegistro(){
	vector<string>::iterator the_iterator;
	string valor ;
	int retorno=-1;
	bool isEncontro=false;
	the_iterator = this->vectorAtributosVariables.begin();
	while( the_iterator != this->vectorAtributosVariables.end() ) {
		valor = *the_iterator;
		//		cout<<"valor :"<<valor<<endl;
		if(atoi(valor.c_str())>=0&&!isEncontro){
			retorno=atoi(valor.c_str());
			*the_iterator="-1";
			isEncontro=true;
		}
		++the_iterator;

	}


	return retorno;
}
void Metadata::setPosicionLibreRegistro(int posicionRegistroLibre){
	this->vectorAtributosVariables.push_back(StringUtils::convertirAString(posicionRegistroLibre));
}
void Metadata::guardarMapaAtributosVariables(map<int,int> mapaAtributosVariables){
	map<int,int>::iterator it;
	string registro="";
	int tamanioRegistro=0;
	string clave;
	string valor;
	string sep="=";
	for( it=mapaAtributosVariables.begin(); it != mapaAtributosVariables.end(); ++it ){
		if(it->second>0){
			clave=StringUtils::convertirAString(it->first);
			valor=StringUtils::convertirAString(it->second);
			registro=registro+clave+sep+DELIMITADOR+valor+DELIMITADOR;
		}
	}
	tamanioRegistro =registro.length();

	this->guardar((char*)&tamanioRegistro,this->metadataSize,sizeof(tamanioRegistro));
	this->guardar((char*)registro.c_str(),this->metadataSize+sizeof(tamanioRegistro),tamanioRegistro);
}
void Metadata::escribirMetadata(string estrAlmacenamiento,int tamanioAGuardar,string clavePrimaria,string tipoIndexacion,string nombreAtributos){
	string almacenamiento=CLAVE_ALMACENAMIENTO+estrAlmacenamiento;
	string tamanio=CLAVE_TAMANIO+StringUtils::convertirAString(tamanioAGuardar);
	string clave=CLAVE_TAG_PRIMARIA+clavePrimaria;
	string indice=CLAVE_INDEXACION+tipoIndexacion;
	this->escribirRegistroVariable(almacenamiento+tamanio+clave+indice);
	this->escribirRegistroVariable(nombreAtributos);
	this->escribirRegistroVariable(PRIMER_REGISTRO);
}
void Metadata::setPosicionLibreEnTexto(int posicionEnDisco,int espacioOcupado){
	this->mapaPosicionesAInsertarTexto[posicionEnDisco]=espacioOcupado;

}
void Metadata::getPosicionLibreEnTexto(int tamanioBuscado,vector<int>& posiciones){
	map<int,int>::iterator it;
	for( it=this->mapaPosicionesAInsertarTexto.begin(); it != this->mapaPosicionesAInsertarTexto.end(); ++it ){
		//		cout<<"it->first (posicion inicio bloque) "<<it->first<<endl;
		//		cout<<"it->second (espacio libre en bloque)"<<it->second<<endl;
		if(tamanioBuscado<=(it->second)){
			posiciones.push_back(it->first);
			posiciones.push_back(it->second);
			this->mapaTamanioBloques[it->first]=-1;
			break;
		}
	}
	//devuelvo -1 en el vector de posiciones por que no hay espacio libre
	posiciones.push_back(-1);
	posiciones.push_back(0);
}
void Metadata::getPosicionBloque(int tamanioBuscado,vector<int>& posiciones){
	//cout<<"tamanio mapa2"<<this->mapaTamanioBloques.size()<<endl;
	bool encontro=false;
	int cont=0;
	map<int,int>::iterator it;
	int tamanioBloque=atoi(StringUtils::getValorTag(TAMANIO,this->mapaAtributosFijos).c_str());
	int porcentajeLibre=tamanioBloque*PORCENTAJE_ESPACIO_LIBRE_BLOQUE;
	int posicionBloque=0,posicionAEscribir=0;

	if(this->mapaTamanioBloques.size() == 0&&tamanioBuscado<tamanioBloque){
		//guardo la posicion del nuevo bloque y le resto el tamaño de registro
		this->mapaTamanioBloques[0] = tamanioBloque - tamanioBuscado;

		//devuelvo -1 en el vector de posiciones para que en la estrategia genere un nuevo bloque
		posiciones.push_back(-1);
		posiciones.push_back(0);
		return;

	}
	for( it=this->mapaTamanioBloques.begin(); it != this->mapaTamanioBloques.end(); ++it ){

		//		cout<<"it->first (posicion inicio bloque) "<<it->first<<endl;
		//		cout<<"it->second (espacio libre en bloque)"<<it->second<<endl;
		//cout<<"cont  :"<<cont<<endl;
		cont++;
		if(tamanioBuscado<(it->second-porcentajeLibre)){
			posicionBloque=it->first*tamanioBloque;
			posiciones.push_back(posicionBloque);
			posicionAEscribir=tamanioBloque-it->second;
			posiciones.push_back(posicionAEscribir);
			//¿seEncontroLugar¿¿¿???? ESTA BIEN LA SIGUIENTE LINEA?=¿?¿?¿?¿? no es this->mapaTamanioBloques[it->first]=it->second-tamanioBuscado;
			//this->mapaTamanioBloques[it->first]=posicionAEscribir+tamanioBuscado;
			this->mapaTamanioBloques[it->first]=it->second-tamanioBuscado;
			encontro=true;
			break;
		}
	}

	if(!encontro){
		this->mapaTamanioBloques[cont]=tamanioBloque-tamanioBuscado;
		//devuelvo -1 en el vector de posiciones para que en la estrategia genere un nuevo bloque
		posiciones.push_back(-1);
		posiciones.push_back(0);
	}
}
void mostarVector( vector<string> vec){
	vector<string>::iterator the_iterator;
	string valor ;
	the_iterator = vec.begin();
	while( the_iterator != vec.end() ) {
		valor = *the_iterator;
		cout<<"nombre atributo :"<<valor<<endl;
		++the_iterator;

	}
}
string Metadata::getValorAtributosFijos(string clave){
	return StringUtils::getValorTag(clave,this->mapaAtributosFijos);
}
string Metadata::getClavePrimaria(){
	return StringUtils::getValorTag(CLAVE_PRIMARIA,this->mapaAtributosFijos);
}
int Metadata::getEspacioLibreEnBloque(int bloque){
	return  this->mapaTamanioBloques[bloque];
}
void Metadata::hidratarMetadataEnBuffer(string registroAtributos,int tamanio){
	this->mapaAtributosFijos.push_back("tamanio=");
	this->mapaAtributosFijos.push_back(StringUtils::convertirAString(tamanio));
	StringUtils::Tokenize(registroAtributos,this->atributosRegistro,DELIMITADOR);
}
void Metadata::hidratarMetadata(){
	int i=0,size=0,espacio=0,cont=0;
	string valor="", num="";
	this->leerMetadata();
	StringUtils::Tokenize(this->primerRegistro,this->mapaAtributosFijos,DELIMITADOR);
	StringUtils::Tokenize(this->segundoRegistro,this->atributosRegistro,DELIMITADOR);
	StringUtils::Tokenize(this->tercerRegistro,this->vectorAtributosVariables,DELIMITADOR);
	if(this->getValorAtributosFijos(ESTRATEGIA_ALMACENAMIENTO).compare(ESTRATEGIA_ALMACENAMIENTO_BLOQUES)==0){
		size=this->vectorAtributosVariables.size()/2;
		//cout<<"size: "<<size<<endl;
		for(i=0;i<size;i++){
			num=StringUtils::convertirAString(i);
			valor= StringUtils::getValorTag(num,this->vectorAtributosVariables);
			cout<<valor<<endl;
			espacio=atoi(valor.c_str());
			cout<<espacio<<endl;
			this->mapaTamanioBloques[i]=espacio;
		}
	}
	if(this->getValorAtributosFijos(ESTRATEGIA_ALMACENAMIENTO).compare(ESTRATEGIA_ALMACENAMIENTO_TEXTO)==0){
		size=this->vectorAtributosVariables.size()/2;
		//cout<<"size: "<<size<<endl;
		for(i=0;i<size;i++){
			num=this->vectorAtributosVariables.at(cont);
			valor= StringUtils::getValorTag(num,this->vectorAtributosVariables);
			cout<<valor<<endl;
			espacio=atoi(valor.c_str());
			cout<<espacio<<endl;
			this->mapaPosicionesAInsertarTexto[atoi(num.c_str())]=espacio;
			cont++;
			cont++;
		}
	}

	//    mostarVector(this->atributosRegistro);
	//    mostarVector(this->mapaAtributosFijos);
	//	cout<<this->vectorAtributosVariables.size()<<endl;
	//	cout<<"tamanio mapa"<<this->mapaTamanioBloques.size()<<endl;
	//	mostarVector(this->vectorAtributosVariables);


}


int Metadata::getSize(){
	return this->metadataSize;
}



void Metadata::setMetadataSize(int metadataSize)
{
	this->metadataSize = metadataSize;
}

void Metadata::leerMetadata(){
	this->leerRegistroVariable(this->primerRegistro,-1);
	this->metadataSize=this->leerRegistroVariable(this->segundoRegistro,-1);
	this->leerRegistroVariable(this->tercerRegistro,-1);
	cout<<"Posicion del tercer registro"<<this->tercerRegistro<<endl;
}
int Metadata::getNumeroEtiqueta(std::string etiqueta){
	int i = 0;
	bool encontrado = false;

	while(i < (int)this->atributosRegistro.size() && encontrado == false){
		if(etiqueta.compare(this->atributosRegistro.at(i).c_str()) == 0){
			encontrado = true;
			return i;
		}
		i++;
	}
	return -1; //si no lo encontro devuelve -1

}


