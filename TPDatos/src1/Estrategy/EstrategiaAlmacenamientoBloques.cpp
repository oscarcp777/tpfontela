/*
 * EstrategiaAlmacenamientoBloques.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaAlmacenamientoBloques.h"
#include "../Composite/Bloque/Bloque.h"
#include "../Modelo/Alumno.h"
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

int iBorrar = 0;

int EstrategiaAlmacenamientoBloques::altaComponente(Almacenamiento* donde, Componente* componente){

			//necesito un nuevo bloque
			Bloque* bloque = new Bloque(donde->getTamanio());
			char* bufferAux = new char [donde->getTamanio()];
			vector<int> vecPosiciones;
			int cantCaracteresRegistro = 0;
			vecPosiciones.clear();

			componente->serializar(BINARIO);	//genera el buffer (registro) en binario
			//cout<<"componente->getBuffer(): "<<componente->getBuffer()<<endl;
			iBorrar++;

			cout<<"Entro "<<iBorrar<<" veces"<<endl;
			for( int j=0 ; j< donde->getTamanio(); j++){
				//cout<<"componente->getBuffer()[j]: "<<componente->getBuffer()[j]<<endl;
				if (componente->getBuffer()[j] == Define::DELIMITADOR1){
					cantCaracteresRegistro = j;
				}

			}
			cantCaracteresRegistro++; //le sumo 1 porque empieza en 0 el for entonces tiene uno menos
			cantCaracteresRegistro += 5; // le sumo 5 pq le agrego un int adelante (4bits) mas un pipe
			cout<<"cantCaracteresRegistro: "<<cantCaracteresRegistro<<endl;
			this->metadata->getPosicionBloque(cantCaracteresRegistro ,vecPosiciones);
			int posicionBloque = vecPosiciones.at(0);

			int posicionAPartirDeDondeEscribo = vecPosiciones.at(1);
			cout<<"posicionInicioBloque: "<<posicionBloque<<endl;
			cout<<"posicionEnElBloqueAPartirDeDondeEscribo: "<<posicionAPartirDeDondeEscribo<<endl;

		    if ( posicionBloque >= 0){
		    	//si pos es >= 0 el registro entra en algun bloque existente
				//lee el archivo desde la pos especificada y guarda en el bloque
				//el buffer leido
		    	//cout<<"entro aL if (o sea guarda en un bloque existente)"<<endl;
				donde->leer(bufferAux,posicionBloque);

				bloque->setBuffer(bufferAux);
				bloque->agregarComponente(componente);
				bloque->hidratar(BINARIO);
				bloque->agregarComponente(componente);
				//cout<<"bloque->getBuffer()"<<bloque->getBuffer()<<endl;
			}else
				bloque->agregarComponente(componente);
		    //si no entro al if es porque pos = -1 y tengo que guardar en un nuevo bloque
		    	//agrego registro a lista del bloque

		    	//cout<<"Cantidad elementos lista: "<<bloque->getCantidadDeElelmentos()<<endl;
		    	//agrego al buffer del bloque dicho registro anteponiendo su tamanio
		    	bloque->serializar();
		    	//agrego bloque a lista de componentes
		    	donde->agregarComponente(bloque);

	    	 	//guardo en almacenamiento el ultimo bloque agregado
		    	posicionBloque = donde->guardar(bloque->getBuffer(),posicionBloque);

		    	//falta guardar en un archivo el bloque con un id y su espacio libre
		    	//este espacio es igual a: donde->getTamanio() - bloque->getTamanioBuffer()

				cout<<endl;
		      	cout<<endl;

		      	delete bloque;
		      	delete bufferAux;
		      	return posicionBloque;
}

void EstrategiaAlmacenamientoBloques::quitarComponente(Almacenamiento* donde, Componente* componente, int pos){
	int numEtiquta = this->metadata->getNumeroEtiqueta(this->metadata->getClavePrimaria());
	string clave = componente->getClave();
	cout<<"this->metadata->getClavePrimaria() "<<this->metadata->getClavePrimaria()<<endl;
	cout<<"numEtiquta "<<numEtiquta<<endl;
	cout<<"componente->getClave() "<<componente->getClave()<<endl;
	char* bufferAux = new char[donde->getTamanio()];
	memset(bufferAux,0,donde->getTamanio());
	int j=0;
	bool borrado = false;
	int resCompare = -1;
	int cantCaracteresRegistro= 0;
	//Busco En Indice La Posicion Del Bloque Que Contiene El Registro Con Esa Clave
	//pos = BuscoEnIndiceLaPosicionDelBloqueQueContieneElRegistroConEsaClave();
	//¿? si no se encuentra en el indice tengo que hacer busqueda secuencial??
	if(pos >= 0){
		//leo en esa pos
		Bloque* bloque = new Bloque(donde->getTamanio());
		donde->leer(bufferAux,pos);
		bloque->setBuffer(bufferAux);
		//agrego el componente para que pueda crear nuevas instancias
		bloque->agregarComponente(componente);
		bloque->hidratar(BINARIO);

		std::list<Componente*>::iterator iteraRegistros = bloque->iteratorListaDeComponetes();
		//recorro la lista de componentes del bloque y comparo con la clave si la encuentro
		//borro el componente y salgo del while
		while (borrado == false && j<bloque->getCantidadDeElelmentos()){
			componente = (Componente*)*iteraRegistros;
			resCompare=componente->compareTo(clave,numEtiquta);
			//la siguiente linea queda solo para probar la busqueda, despues borrarla y borrar
			//tambien el #include Alumno que esta en esta clase ES SOLO PARA PROBAR

			if (resCompare == 0){
				//para no hacer el proximo codigo feo tendria que implementar un clone en componente

				for( int x=0 ; x< donde->getTamanio(); x++){
					//cout<<"componente->getBuffer()[j]: "<<componente->getBuffer()[j]<<endl;
					//cout<<"componente->getBuffer()[j]: "<<componente->getBuffer()[j]<<endl;
					if (componente->getBuffer()[x] == Define::DELIMITADOR1){
						cantCaracteresRegistro = x;
					}

				}
				cantCaracteresRegistro++; //le sumo 1 porque empieza en 0 el for entonces tiene uno menos
				cantCaracteresRegistro += 5; // le sumo 5 pq le agrego un int adelante (4bits) mas un pipe
				cout<<"cantCaracteresRegistro reg a borrar: "<<cantCaracteresRegistro<<endl;
				cout<<"Se borra el componente con nombre: "<<((Alumno*)componente)->getNombre()<<endl;
				cout<<"pos bloque a actualizar tamaño libre "<<pos<<endl;
				this->metadata->actualizarMapaAtributosVariables(pos,cantCaracteresRegistro);
				bloque->removerComponente(componente);
				borrado = true;
				j--;
				iteraRegistros--;
			}

			iteraRegistros++;
			j++;
		}

		if(borrado == true){
			//si lo encontro vuelvo a guardar el bloque sin el componente borrado, sino NO porque queda como estaba
			bloque->serializar();
			//agrego bloque a lista de componentes del almacenamiento
			donde->agregarComponente(bloque);
			//guardo en almacenamiento el ultimo bloque agregado
			donde->guardar(bloque->getBuffer(),pos);
		}

		delete bloque;
		delete bufferAux;
		//delete vecCampos; se tienen que borrar estos vectores?? porque creo que hacen new cuando le pasas la cantidad de elementos por parametro
		//delete vecClaves;
	}
	else
		cout<<"no se encontro el componente"<<endl;

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

	Bloque* bloque = new Bloque(donde->getTamanio());
	while (!donde->fin()){
		donde->leer(bufferAux, pos);
		bloque->setBuffer(bufferAux);
		bloque->agregarComponente(componente);
		bloque->hidratar(BINARIO);

		memset(bufferAux,0,donde->getTamanio());
		pos += donde->getTamanio();

		//recorro la lista de componentes del bloque para comparar con la clave y
		//si tiene la clave agrego a la lista que me pasan por parametro
		std::list<Componente*>::iterator iteraRegistros = bloque->iteratorListaDeComponetes();
		int i=0;
		while (i<bloque->getCantidadDeElelmentos()){
			resCompare = 0;
			componente = (Componente*)*iteraRegistros;
			for(int k = 0; k< (int)vecCampos.size();k++){
				if(resCompare == 0)//solo compara si la comparacion anterior dio =
					resCompare+=componente->compareTo(vecCampos.at(k),vecEtiquetasCampos.at(k));
//				cout<<"vecCampos.at(k): "<<vecCampos.at(k)<<endl;
//				cout<<"vecEtiquetasCampos.at(k): "<<vecEtiquetasCampos.at(k)<<endl;
			}
			//la siguiente linea queda solo para probar la busqueda, despues borrarla y borrar
			//tambien el #include Alumno que esta en esta clase ES SOLO PARA PROBAR
			cout<<"nombre: "<<((Alumno*)componente)->getNombre()<<endl;
//			cout<<"padron: "<<((Alumno*)componente)->getPadron()<<endl;
//			cout<<"dni: "<<((Alumno*)componente)->getDni()<<endl;
			if (resCompare == 0){
				resultadoDeLABusqueda.push_back(componente);
				//para no hacer el proximo codigo feo tendria que implementar un clone en componente
				bloque->removerComponente(componente);
				i--;
				iteraRegistros--;
			}

			iteraRegistros++;
			i++;
		}
		bloque->vaciarListaComponentes();
	}
	delete bufferAux;
	delete bloque;
}
