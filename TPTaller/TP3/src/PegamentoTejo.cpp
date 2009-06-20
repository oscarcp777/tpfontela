// PegamentoTejo.cpp: implementation of the PegamentoTejo class.
//
//////////////////////////////////////////////////////////////////////

#include "PegamentoTejo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PegamentoTejo::PegamentoTejo()
{

}

int PegamentoTejo::aplicar(){
	Tejo* tejo = Escenario::obtenerInstancia()->getTejo();
	
	if(this->getActivo()==0){
		tejo->setMover(-1); //le seteo -1 para que no se mueva el tejo, cuando este en 0, se movera
		return 0;
	}
	
		return -1;
}

PegamentoTejo::~PegamentoTejo()
{

}
