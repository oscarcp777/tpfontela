// Puntaje.cpp: implementation of the Puntaje class.
//
//////////////////////////////////////////////////////////////////////

#include "Puntaje.h"
#include "Define.h"
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

}
