/*
 * Tabla.cpp
 *
 *  Created on: 31/10/2009
 *      Author: santiago
 */

#include "Tabla.h"
#define maxvalue 20000
#define cantClaves 5


Tabla::Tabla() {
	this->cantCubos = -1;
	this->offsetCubos = vector<int>();
}

int Tabla::GetCantCubos(){
	return this->cantCubos;
}

void Tabla::SetCantCubos(int cantCubos){
	this->cantCubos = cantCubos;
}

int Tabla::ClaveToInt(string key){
	int sum = 0;
		int len = key.size();
		if (len % 2 == 1)
			len++;
		for(int j = 0; j < len; j+= 2)
			sum = (sum + 100 * key[j] * key[j+1]) % maxvalue;
		return sum;
}

int Tabla::Hash(string clave){
	int c = this->ClaveToInt(clave);
	return c % cantCubos;
}

Cubo Tabla::GetCubo(fstream fileCubo, int offsetCubo, int longclave){
	Cubo cubo = Cubo();
	return cubo.GetCubo(offsetCubo, fileCubo, longclave);
}

void Tabla::AddClave(RegistroClaveHash *reg){
	int indiceCubo= Hash(reg->clave);
    Cubo cubo = GetCubo(offsetCubos[indiceCubo]); //obtiene el cubo del archivo de cubos

    if (cubo.TieneEspacio()) {
    	cubo.AddClave(reg);
    	cubo.GuardarCubo(); //guarda el cubo en el archivo
    }
    else{
       //Crear nuevo cubo guaedarlo en el archivo
       //agregar elnuevo cubo a la lista de cubos
       DuplicarTabla
       Redispersar(indiceCubo);  //duplica la tabla y acomoda todo de nuevo
    }
}

void Tabla::DuplicarTabla(int offsetNewCubo){
	int i;
		for(i=0; i<(int)offsetCubos.size(); i++){
		    offsetCubos.push_back(offsetCubos[i]); //duplica
		}
		i = (int)offsetCubos.size()/2 -1;
		offsetCubos[i] = offsetNewCubo;
		//persistir la tabla
}

void Tabla::Redispersar(int indiceCubo){
	Cubo cuboOverFlow = GetCubo(offsetCubos[indiceCubo]);
	if ((int)offsetCubos.size()== cuboOverFlow.GetTamanioDispersion()){
	     DuplicarTabla(indiceCubo);
	}
	offsetCubos[(int)offsetCubos.size()/2 -1] =

	Cubo nuevoCubo = Cubo(0,(int)offsetCubos.size()); //new cubo
	list<RegistroClaveHash> claves = cuboOverFlow.GetClaves();
	for (list<RegistroClaveHash>::iterator i = claves.begin(); i != claves.end(); ++i){
		    int ubicacion= Hash(i->getClave());
			int indice = offsetCubos[ubicacion];
			if (indice == indiceCubo){
				cuboOverFlow.AddClave(i->getClave(), i->getOffset());
			}
	    	else{
	    		nuevoCubo.AddClave(i->getClave(),i->getOffset());
	    	}
		}
	nuevoCubo.SetTamanioDispersion((int)offsetCubos.size());
	cuboOverFlow.SetTamanioDispersion((int)offsetCubos.size());
	//persisto los cubos
}

Tabla Tabla::CargarTabla(fstream* fileTabla){
	int offsetCubo;
	fileTabla->seekp(0);
	this->fileTabla->read(reinterpret_cast<int>(this.tamanioTabla), sizeof(this.tamanioTabla));
	for(int i = 0; i < this->tamanioTabla; ++i) {
		this->fileTabla->read(reinterpret_cast<int>(offsetCubo), sizeof(offsetCubo));
		this->tabla.offsetCubos.push_back(offsetCubo);
	}
	return this;
}

void Tabla::SaveTabla(fstream* fileTabla) throw (exception){  //ver si esta pisando el archivo bien
	try{
	   fileTabla->seekp(0);
	   fileTabla->write((char*)(&(this->cantCubos)), sizeof(int));
	   for(unsigned int i = 0; i< this->offsetCubos.size();i++){
          fileTabla->write((char*)(&(this->offsetCubos[i])), sizeof(int));
	   }
	}catch (exception e){
		throw e;
	}
}

Tabla::~Tabla() {
	// TODO Auto-generated destructor stub
}
