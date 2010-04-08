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

Cubo Cubo::GetCubo(int offsetCubo){
    //ir al archivo y traer el la data del cubo y castearlo
    //en un objeto cubo
return Cubo(0,0);
}

void Cubo::AddClave(string clave, int offset){
   RegistroClaveHash reg = RegistroClaveHash();
   reg.setClave(clave);
   reg.setOffset(offset);
   claves.push_back(reg);
}

list<RegistroClaveHash> Cubo::GetClaves(){
	return this->claves;
}

bool Cubo::TieneEspacio(){
	if(this->cantClaves < maxClaves)
		return true;
	return false;
}

void Cubo::GuardarCubo(){

}

Cubo::~Cubo() {
	// TODO Auto-generated destructor stub
}
