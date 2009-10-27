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
			componente->serializar(BINARIO);	//genera el buffer (registro) en binario
		    int pos = this->posicionarEnBloque(componente->getTamanioBuffer());
			if ( pos >= 0){
		    	//el registro entra en algun bloque existente

				//lee el archivo desde la pos especificada y guarda en el bloque
				//el buffer leido
				donde->leer(bufferAux,pos);
				bloque->setBuffer(bufferAux);
			}

		    	//agrego registro a lista del bloque
		    	bloque->agregarComponente(componente);
		    	//agrego al buffer del bloque dicho registro anteponiendo su tamanio
		    	bloque->serializar();
		    	//agrego bloque a lista de componentes
		    	donde->agregarComponente(bloque);

	    	 	//guardo en almacenamiento el ultimo bloque agregado
		      	donde->guardar(bloque->getBuffer(),pos);

		    	//falta guardar en un archivo el bloque con un id y su espacio libre
		    	//este espacio es igual a: donde->getTamanio() - bloque->getTamanioBuffer()


//	Bloque* bloque = NULL;
//	int i=0;
//
//	std::string registro = generarRegistro(componente);
//	componente->setDatosRegistro(registro);
//	int cargado = 0;
//
//	if(donde->getCompuesto()->getCantidadDeElelmentos() == 0){
//		bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
//		donde->getCompuesto()->agregarComponente(bloque);
//	}
//	std::list<Componente*>::iterator iter = donde->getCompuesto()->iteratorListaDeComponetes();
//
//
//	while(cargado == 0){
//		i++;
//		bloque = (Bloque*)*iter;
//		int length=(int)registro.length();
//		//componente->setId(bloque->getCantidadDeElelmentos()+1);
//		if(bloque->getTamanio()-bloque->getPosicionActual()>length){
//			bloque->agregarComponente(componente);
//			bloque->setPosicionActual(bloque->getPosicionActual()+registro.length());
//			cargado = 1;
//		}else{
//			if(i<donde->getCompuesto()->getCantidadDeElelmentos())
//				iter++;
//			else{
//				bloque = new Bloque(donde->getTamanio(),donde->getCompuesto()->getCantidadDeElelmentos()+1);
//				donde->getCompuesto()->agregarComponente(bloque);
//				bloque->agregarComponente(componente);
//				bloque->setPosicionActual(bloque->getPosicionActual()+registro.length());
//				cargado = 1;
//			}
//
//		}
//	}

}

void EstrategiaAlmacenamientoBloques::quitarComponente(Almacenamiento* donde, Componente* componente){

}



std::string EstrategiaAlmacenamientoBloques::toString(){
   	return "EstrategiaAlmacenamientoBloques";
   }



void EstrategiaAlmacenamientoBloques::busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,std::string clave){

	int pos = 0;
	vector<string> vecClaves;
	char* bufferAux = new char [donde->getTamanio()];
	memset(bufferAux,0,donde->getTamanio());
	StringUtils::Tokenize(clave,vecClaves,DELIMITADOR);


	while (!donde->fin()){
		Bloque* bloque = new Bloque(donde->getTamanio());
		donde->leer(bufferAux, pos);
		bloque->setBuffer(bufferAux);
		bloque->agregarComponente(componente);
		bloque->hidratar();//TODO
		//		for( int i = 0; i<(int)vecClaves.size(); i++){
		//			//TODO osky tiene que devolver la posicion de la etiqueda
		//			//y tenemos que hacer varios compareTo......
		//			std::cout<<"vecClaves[i]: "<<vecClaves.at(i)<<std::endl;
		//		}
		memset(bufferAux,0,donde->getTamanio());
		pos += donde->getTamanio();



		//recorro la lista de componentes del bloque para comparar con la clave y
		//si tiene la clave agrego a la lista que me pasan por parametro
		std::list<Componente*>::iterator iteraRegistros = bloque->iteratorListaDeComponetes();
		int i=0;

		while (i<bloque->getCantidadDeElelmentos()){
			componente = (Componente*)*iteraRegistros;
			if (componente->compareTo(clave,0) == 0){
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
