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


			for( int j=0 ; j< donde->getTamanio(); j++){

				if (componente->getBuffer()[j] == Define::DELIMITADOR1){
					cantCaracteresRegistro = j;
				}

			}
			cantCaracteresRegistro++; //le sumo 1 porque empieza en 0 el for entonces tiene uno menos
			cantCaracteresRegistro += 5; // le sumo 5 pq le agrego un int adelante (4bits) mas un pipe

			donde->getMetadata()->getPosicionBloque(cantCaracteresRegistro ,vecPosiciones);
			int posicionBloque = vecPosiciones.at(0);


		    if ( posicionBloque >= 0){
		    	//si pos es >= 0 el registro entra en algun bloque existente
				//lee el archivo desde la pos especificada y guarda en el bloque
				//el buffer leido

				donde->leer(bufferAux,posicionBloque);

				bloque->setBuffer(bufferAux);
				bloque->agregarComponente(componente);
				bloque->hidratar(BINARIO);
				bloque->agregarComponente(componente);

			}else
				bloque->agregarComponente(componente);
		    //si no entro al if es porque pos = -1 y tengo que guardar en un nuevo bloque
		    	//agrego registro a lista del bloque


		    	//agrego al buffer del bloque dicho registro anteponiendo su tamanio
		    	bloque->serializar();
		    	//agrego bloque a lista de componentes
		    	donde->agregarComponente(bloque);

	    	 	//guardo en almacenamiento el ultimo bloque agregado
		    	posicionBloque = donde->guardar(bloque->getBuffer(),posicionBloque);

		    	//falta guardar en un archivo el bloque con un id y su espacio libre
		    	//este espacio es igual a: donde->getTamanio() - bloque->getTamanioBuffer()

		      	delete bloque;
		      	delete bufferAux;
		      	return posicionBloque;
}

void EstrategiaAlmacenamientoBloques::quitarComponente(Almacenamiento* donde, Componente* componente, int pos){
	int numEtiquta = donde->getMetadata()->getNumeroEtiqueta(donde->getMetadata()->getClavePrimaria());
	string clave = componente->getClave();
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
					if (componente->getBuffer()[x] == Define::DELIMITADOR1){
						cantCaracteresRegistro = x;
					}

				}
				cantCaracteresRegistro++; //le sumo 1 porque empieza en 0 el for entonces tiene uno menos
				cantCaracteresRegistro += 5; // le sumo 5 pq le agrego un int adelante (4bits) mas un pipe
				donde->getMetadata()->actualizarMapaAtributosVariables(pos,cantCaracteresRegistro);
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
		cout<<"el componente a borrar no existe"<<endl;

}

int EstrategiaAlmacenamientoBloques::actualizarComponente(Almacenamiento* donde, Componente* componente, int pos){

	int numEtiquta = donde->getMetadata()->getNumeroEtiqueta(donde->getMetadata()->getClavePrimaria());
		string clave = componente->getClave();
	   char* bufferAux = new char[donde->getTamanio()];
		memset(bufferAux,0,donde->getTamanio());
		int j=0;
		bool modificado = false;
		int resCompare = -1;
		int cantCaracteresRegistro= 0;
		//Busco En Indice La Posicion Del Bloque Que Contiene El Registro Con Esa Clave
		//pos = BuscoEnIndiceLaPosicionDelBloqueQueContieneElRegistroConEsaClave();
		//¿? si no se encuentra en el indice tengo que hacer busqueda secuencial??
		if(pos >= 0){
			Componente* unComponente = componente->obtenerNuevaInstancia();
			unComponente->setTamanio(donde->getTamanio());
			//leo en esa pos
			Bloque* bloque = new Bloque(donde->getTamanio());
			donde->leer(bufferAux,pos);
			bloque->setBuffer(bufferAux);
			//agrego el componente para que pueda crear nuevas instancias
			bloque->agregarComponente(unComponente);
			bloque->hidratar(BINARIO);

			std::list<Componente*>::iterator iteraRegistros = bloque->iteratorListaDeComponetes();
			//recorro la lista de componentes del bloque y comparo con la clave si la encuentro
			//borro el componente y salgo del while
			while (modificado == false && j<bloque->getCantidadDeElelmentos()){
				unComponente = (Componente*)*iteraRegistros;
				resCompare=unComponente->compareTo(clave,numEtiquta);
				//la siguiente linea queda solo para probar la busqueda, despues borrarla y borrar
				//tambien el #include Alumno que esta en esta clase ES SOLO PARA PROBAR

				if (resCompare == 0){
					//para no hacer el proximo codigo feo tendria que implementar un clone en componente

					for( int x=0 ; x< donde->getTamanio(); x++){
						if (unComponente->getBuffer()[x] == Define::DELIMITADOR1){
							cantCaracteresRegistro = x;
						}

					}
					cantCaracteresRegistro++; //le sumo 1 porque empieza en 0 el for entonces tiene uno menos
					cantCaracteresRegistro += 5; // le sumo 5 pq le agrego un int adelante (4bits) mas un pipe


					donde->getMetadata()->actualizarMapaBloques(pos,cantCaracteresRegistro);
					bloque->removerComponente(unComponente);
					componente->serializar(BINARIO);
					for( int x=0 ; x< donde->getTamanio(); x++){
						if (componente->getBuffer()[x] == Define::DELIMITADOR1){
							cantCaracteresRegistro = x;
						}

					}
					cantCaracteresRegistro++; //le sumo 1 porque empieza en 0 el for entonces tiene uno menos
					cantCaracteresRegistro += 5; // le sumo 5 pq le agrego un int adelante (4bits) mas un pipe
					donde->getMetadata()->actualizarMapaBloques(pos,-cantCaracteresRegistro);
					bloque->agregarComponente(componente);
					modificado = true;
				}

				iteraRegistros++;
				j++;
			}

			if(modificado == true){
				//si lo encontro vuelvo a guardar el bloque sin el componente borrado, sino NO porque queda como estaba
				bloque->serializar();
				//agrego bloque a lista de componentes del almacenamiento
				donde->agregarComponente(bloque);
				//guardo en almacenamiento el ultimo bloque agregado
				donde->guardar(bloque->getBuffer(),pos);

			}

			delete bloque;
			delete bufferAux;
		}
		else
			cout<<"el componente a modificar no existe"<<endl;
	return pos;
}

std::string EstrategiaAlmacenamientoBloques::toString(){
   	return "EstrategiaAlmacenamientoBloques";
   }



void EstrategiaAlmacenamientoBloques::busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,vector<string> vecCampos, vector<int> vecEtiquetasCampos){
	int pos = 0;
	int resCompare = 0;
	char* bufferAux = new char [donde->getTamanio()];
	memset(bufferAux,0,donde->getTamanio());

	Bloque* bloque = new Bloque(donde->getTamanio());
	while (!donde->fin()){
		donde->leer(bufferAux, pos);
		bloque->setBuffer(bufferAux);
		bloque->agregarComponente(componente);
		bloque->hidratar(BINARIO);
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
			}

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
		memset(bufferAux,0,donde->getTamanio());
		pos += donde->getTamanio();
	}
	delete bufferAux;
	delete bloque;
}
void EstrategiaAlmacenamientoBloques::hidratarComponente(Almacenamiento* donde, list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,vector<string> vecCampos, vector<int> vecEtiquetasCampos){

		int resCompare = -1;
		char* bufferAux = new char [donde->getTamanio()];

		memset(bufferAux,0,donde->getTamanio());
		bool encontrado = false;
		Bloque* bloque = new Bloque(donde->getTamanio());
		donde->leer(bufferAux, pos);
		bloque->setBuffer(bufferAux);
		bloque->agregarComponente(componente);
		bloque->hidratar(BINARIO);
		//recorro la lista de componentes del bloque para comparar con la clave y
		//si tiene la clave agrego a la lista que me pasan por parametro
		std::list<Componente*>::iterator iteraRegistros = bloque->iteratorListaDeComponetes();
		int i=0;
		while (i<bloque->getCantidadDeElelmentos() && encontrado==false){
			resCompare = 0;
			componente = (Componente*)*iteraRegistros;
			for(int k = 0; k< (int)vecCampos.size();k++){
				if(resCompare == 0)//solo compara si la comparacion anterior dio =
					resCompare+=componente->compareTo(vecCampos.at(k),vecEtiquetasCampos.at(k));
			}
			//la siguiente linea queda solo para probar la busqueda, despues borrarla y borrar
			//tambien el #include Alumno que esta en esta clase ES SOLO PARA PROBAR

			if (resCompare == 0){
				resultadoDeLABusqueda.push_back(componente);
				//para no hacer el proximo codigo feo tendria que implementar un clone en componente
				encontrado = true;
				bloque->removerComponente(componente);
				i--;
				iteraRegistros--;
			}

			iteraRegistros++;
			i++;
		}

		delete bufferAux;
		delete bloque;
}
