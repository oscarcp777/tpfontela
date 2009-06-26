// Puntaje.cpp: implementation of the Puntaje class.
//
//////////////////////////////////////////////////////////////////////

#include "Puntaje.h"
#include "Define.h"
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Puntaje::Puntaje()
{
	this->cantPuntosJugador=0;

}

int Puntaje::getCantPuntosJugador(){
	return this->cantPuntosJugador;
}

void Puntaje::setCantPuntosJugador(int cantPuntos){
	this->cantPuntosJugador=cantPuntos;
}


Puntaje::~Puntaje()
{
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Puntaje"<<std::endl;

}
