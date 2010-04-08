#include "Cubo.h"

Cubo::Cubo(unsigned int numero, unsigned int td){
	this->numero=numero;
	this->td=td;
	this->claves=new vector<unsigned long int>();
}

Cubo::~Cubo(){
	delete this->claves;
}

void Cubo::InsertarClave(unsigned long int claveAInsertar){
	this->claves->push_back(claveAInsertar);
}

void Cubo::EliminarClave(unsigned long int claveAEliminar){
	unsigned int i=0;
	bool encontrado=false;
	while ((i<this->claves->size()) && (!encontrado)){
		if (claveAEliminar==*(this->claves->begin()+i)){
			this->claves->erase(this->claves->begin()+i);
			encontrado=true;
		}else{
			i++;
		}
	}	
}

bool Cubo::estaVacio(){
	return (this->claves->empty());
}

void Cubo::setTd(unsigned int tamanio){
	this->td=tamanio;
}

unsigned int Cubo::getTd(){
	return this->td;
}

std::vector<unsigned long int>* Cubo::getClaves(){
	return this->claves;
}
