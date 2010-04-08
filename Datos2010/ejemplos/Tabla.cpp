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

Cubo Tabla::GetCubo(int offsetCubo){
	return Cubo(0,0); //va al archivo busca la data correspondiente
}

void Tabla::AddClave(string clave, int offset){
	int indiceCubo= Hash(clave);
    Cubo cubo = GetCubo(offsetCubos[indiceCubo]); //obtiene el cubo del archivo de cubos
    if (cubo.TieneEspacio()) {
    	cubo.AddClave(clave,offset);
    	cubo.GuardarCubo(); //guarda el cubo en el archivo
    }
    else{
       Redispersar(indiceCubo);  //duplica la tabla y acomoda todo de nuevo
    }
}

void Tabla::DuplicarTabla(int indiceCubo){
	int i;
		for(i=0; i<(int)offsetCubos.size(); i++){
		    offsetCubos.push_back(offsetCubos[i]); //duplica
		}
		offsetCubos[indiceCubo] = (int)offsetCubos.size() - 1; //aca va el nuevo offset del cubo ver como traerlo
}

void Tabla::Redispersar(int indiceCubo){
	Cubo cuboOverFlow = GetCubo(offsetCubos[indiceCubo]);
	if ((int)offsetCubos.size()== cuboOverFlow.GetTamanioDispersion()){
	     DuplicarTabla(indiceCubo);
	}

	offsetCubos[indiceCubo] = (int)offsetCubos.size() - 1; //aca va el nuevo offset del cubo ver como traerlo

	Cubo nuevoCubo = Cubo(0,(int)offsetCubos.size()); //new cubo y lo tengo ahi no lo agrego todavia

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
	//offsetCubos[offsetCubo] = dirNuevoCubo;
	//grabo en los archivos
}


Tabla::~Tabla() {
	// TODO Auto-generated destructor stub
}
