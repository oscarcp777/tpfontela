/*
 * EstrategiaAlmacenamientoBloques.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoBloques.h"
#include "../Composite/Bloque/Bloque.h"
#include "stdlib.h"
using namespace std;
EstrategiaAlmacenamientoBloques::EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated constructor stub

}

EstrategiaAlmacenamientoBloques::~EstrategiaAlmacenamientoBloques() {
	// TODO Auto-generated destructor stub
}

void EstrategiaAlmacenamientoBloques::guardar(Almacenamiento* donde){
//	int i=1;
//	std::list<Componente*>::iterator iteraBloques;
//	Bloque* bloque;
//	std::string metaData;
//
//	iteraBloques = donde->getCompuesto()->iteratorListaDeComponetes();
//	if(donde->getExisteMetaData() == 0){
//		metaData = this->generarMetadata((Componente*)*((Bloque*)*iteraBloques)->iteratorListaDeComponetes());
//		donde->escribirMetadata(metaData);
//	}
//
//	while(i<=donde->getCompuesto()->getCantidadDeElelmentos()){
//		bloque = (Bloque*)*iteraBloques;
//		donde->guardar(bloque->getDatosRegistro().c_str(),bloque->getTamanio());
//		iteraBloques++;
//		i++;
//	}



}

int EstrategiaAlmacenamientoBloques::posicionarEnBloque(int tamanioRegistro){
	return -1;
}



void EstrategiaAlmacenamientoBloques::altaComponente(Almacenamiento* donde, Componente* componente){

	//no esta terminado, hasta ahora por cada registro agrega un bloque

			//necesito un nuevo bloque
			Bloque* bloque = new Bloque(donde->getTamanio());
			char* bufferAux = new char [donde->getTamanio()];
			vector<int> vecPosiciones (2);
			componente->serializar(BINARIO);	//genera el buffer (registro) en binario


		    this->metadata->getPosicionBloque(29/*strlen(componente->getBuffer())*/,vecPosiciones);
			int posicionBloque = vecPosiciones.at(0);
			int posicionAPartirDeDondeEscribo = vecPosiciones.at(1);
			cout<<"posicionInicioBloque: "<<posicionBloque<<endl;
			cout<<"posicionEnElBloqueAPartirDeDondeEscribo: "<<posicionAPartirDeDondeEscribo<<endl;

			//DECIRLE A OSKY QUE APENAS CREA LA METADATA (POR PRIMERA VEZ) QUE PONGA -1 -1 EN EL MAPA
			//ASI NO ENTRA A ESTE IF Y LA PRIMERA VEZ QUE ESCRIBE GENERA UN NUEVO BLOQUE
			//PARA VOLVER A COMO ESTABA ANTES CAMBIAR posicionBloque POR pos
		    if ( posicionBloque >/*=*/ 0){
		    	//si pos es >= 0 el registro entra en algun bloque existente
				//lee el archivo desde la pos especificada y guarda en el bloque
				//el buffer leido
				donde->leer(bufferAux,posicionBloque);
				bloque->setBuffer(bufferAux);
				bloque->hidratar(BINARIO);
			}

		    //si no entro al if es porque pos = -1 y tengo que guardar en un nuevo bloque
		    	//agrego registro a lista del bloque
		    	bloque->agregarComponente(componente);
		    	//agrego al buffer del bloque dicho registro anteponiendo su tamanio
		    	bloque->serializar();
		    	//agrego bloque a lista de componentes
		    	donde->agregarComponente(bloque);

	    	 	//guardo en almacenamiento el ultimo bloque agregado
		      	donde->guardar(bloque->getBuffer(),posicionBloque);

		    	//falta guardar en un archivo el bloque con un id y su espacio libre
		    	//este espacio es igual a: donde->getTamanio() - bloque->getTamanioBuffer()

				cout<<endl;
		      	cout<<endl;

		      	delete bloque;
		      	delete bufferAux;
}

void EstrategiaAlmacenamientoBloques::quitarComponente(Almacenamiento* donde, Componente* componente){

}



std::string EstrategiaAlmacenamientoBloques::toString(){
   	return "EstrategiaAlmacenamientoBloques";
   }



void EstrategiaAlmacenamientoBloques::busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,std::string clave){

	int pos = 0;
	vector<string> vecClaves;
	string aux;
	int posCaracterIgual = -1;
	string etiquetaCampo = "";
	string campo = "";
	int resCompare = 0;
	char* bufferAux = new char [donde->getTamanio()];
	memset(bufferAux,0,donde->getTamanio());
	StringUtils::Tokenize(clave,vecClaves,DELIMITADOR);
	vector<string> vecCampos ((int)vecClaves.size());
	vector<int> vecEtiquetasCampos ((int)vecClaves.size());

	for( int i = 0; i<(int)vecClaves.size(); i++){
		posCaracterIgual = vecClaves.at(i).find_first_of('=',0);
		etiquetaCampo = vecClaves.at(i).substr(0,posCaracterIgual);
		campo = vecClaves.at(i).substr(posCaracterIgual+1,vecClaves.at(i).length());
//		std::cout<<"etiquetaCampo: "<<etiquetaCampo<<std::endl;
//		std::cout<<"campo: "<<campo<<std::endl;
//		cout<<"this->metadata->getNumeroEtiqueta(etiquetaCampo): "<<this->metadata->getNumeroEtiqueta(etiquetaCampo)<<endl;
		vecEtiquetasCampos[i] = this->metadata->getNumeroEtiqueta(etiquetaCampo);
		vecCampos[i]= campo;
//		std::cout<<"vecEtiquetasCampos[i]: "<<vecEtiquetasCampos.at(i)<<std::endl;
//		std::cout<<"vecCampos[i]: "<<vecCampos.at(i)<<std::endl;
//		std::cout<<"vecEtiquetasCampos[i]: "<<vecCampos[i]<<endl;
	}

	while (!donde->fin()){
		resCompare = 0;
		Bloque* bloque = new Bloque(donde->getTamanio());
		donde->leer(bufferAux, pos);
		bloque->setBuffer(bufferAux);
		bloque->agregarComponente(componente);
		bloque->hidratar();
		memset(bufferAux,0,donde->getTamanio());
		pos += donde->getTamanio();

		//recorro la lista de componentes del bloque para comparar con la clave y
		//si tiene la clave agrego a la lista que me pasan por parametro
		std::list<Componente*>::iterator iteraRegistros = bloque->iteratorListaDeComponetes();
		int i=0;

		while (i<bloque->getCantidadDeElelmentos()){
			componente = (Componente*)*iteraRegistros;
			for(int k = 0; k< (int)vecCampos.size();k++){
				if(resCompare == 0)//solo compara si la comparacion anterior dio =
				resCompare+=componente->compareTo(vecCampos.at(k),vecEtiquetasCampos.at(k));
			}

			if ( resCompare == 0){
				resultadoDeLABusqueda.push_back(componente);
			}
			bloque->removerComponente(componente);
			iteraRegistros++;
			i++;
		}
		delete bloque;
	}
	delete bufferAux;
}
