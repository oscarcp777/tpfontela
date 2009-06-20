// Bonus.cpp: implementation of the Bonus class.
//
//////////////////////////////////////////////////////////////////////

#include "Bonus.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Bonus::Bonus() {
	// TODO Auto-generated constructor stub

}

Bonus::~Bonus() {
	// TODO Auto-generated destructor stub
}


int Bonus::getActivo(){
	return this->activo;
}

void Bonus::setActivo(int activo){
	this->activo = activo;
}
	
void Bonus::setVelocidadAnterior(int velocidadAnterior){
	this->velocidadAnterior = velocidadAnterior;
}

int Bonus::getVelocidadAnterior(){
	return this->velocidadAnterior;
}

void Bonus::setAlturaAnterior(int alturaAnterior){
	this->alturaAnterior = alturaAnterior;
}

int Bonus::getAlturaAnterior(){
	return this->alturaAnterior;
}

void Bonus::setRadioAnterior(int radioAnterior){
	this->radioAnterior = radioAnterior;
}

int Bonus::getRadioAnterior(){
	return this->radioAnterior;
}


