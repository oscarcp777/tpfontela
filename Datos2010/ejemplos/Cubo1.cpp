/*
 * Cubo.cpp
 *
 *  Created on: 31/10/2009
 *      Author: santiago
 */

#include "Cubo.h"

Cubo::Cubo(int cantClaves, int tamanioDispersion){
	this->cantClaves = cantClaves;
    this->tamanioDispersion = tamanioDispersion;
}

int Cubo::GetTamanioDispersion(){
	return this->tamanioDispersion;
}

void Cubo::SetTamanioDispersion(int newDispersion){
	this->tamanioDispersion = newDispersion;
}

int Cubo::GetCantClaves(){
	return this->cantClaves;
}

void Cubo::SetCantClaves(int newCantClaves){
    this->cantClaves = newCantClaves;
}

Cubo Cubo::GetCubo(int offsetCubo, fstream* fileCubo, int longClave){
	Cubo cubo = Cubo(0,0);
	char s[longClave];
	int offsetTemp;
	fileCubo->flush();
	fileCubo->seekg(offsetCubo, ios::beg);
	fileCubo->read(reinterpret_cast<char*>(&(cubo.tamanioDispersion)), sizeof(int));
    fileCubo->read(reinterpret_cast<char*>(&(cubo.cantClaves)), sizeof(int));
    for (int i=0; i< this->cantClaves; i++){
    	fileCubo->read(s,longClave);
    	fileCubo->read(reinterpret_cast<char*>(&(offsetTemp)), sizeof(int));
    	RegistroClaveHash reg = RegistroClaveHash();
    	reg.setClave(string(s));
    	reg.setOffset(offsetTemp);
    	cubo.claves.push_back(reg);
    }
return cubo;
}

void Cubo::SaveCubo(fstream* fileCubo, int offsetCubo) throw(exception) {
	try{
	fileCubo->seekp(offsetCubo, ios::beg);
	fileCubo->write((char*)(&(this->tamanioDispersion)), sizeof(int));
	fileCubo->write((char*)(&(this->cantClaves)), sizeof(int));
	for (list<RegistroClaveHash>::iterator i = claves.begin(); i != claves.end(); ++i){
	       fileCubo->write(i->getClave().c_str(), sizeof(i->getClave().c_str()));
	       fileCubo->write((char*)((i->getOffset())), sizeof(int));
	}
	}catch(exception e){
		throw e;
	}
}

void Cubo::AgregarClave(RegistroClaveHash* reg){
	claves.push_back(*reg);
}

list<RegistroClaveHash> Cubo::GetClaves(){
	return this->claves;
}

bool Cubo::TieneEspacio(){ //ver esta condicion puede ser long variable
	if(this->cantClaves < maxClaves)
		return true;
	return false;
}

int Cubo::Buscar(string clave){
   list<RegistroClaveHash> claves= this->claves;
   for (list<RegistroClaveHash>::iterator i = claves.begin(); i != claves.end(); ++i){
		   if (clave == i->getClave())
			   return i->getOffset();
   }
   return 0;
}

Cubo::~Cubo() {
	// TODO Auto-generated destructor stub
}
