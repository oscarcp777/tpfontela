// IncLongPad.cpp: implementation of the IncLongPad class.
//
//////////////////////////////////////////////////////////////////////

#include "IncLongPad.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IncLongPad::IncLongPad()
{

}

int IncLongPad::aplicar(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Pad*pad=NULL;
	int incUnTercioDeAltura=0;
	int incMax = this->getAlturaAnterior() + (5/3)*this->getAlturaAnterior();
    std::string padUltimaColision = escenario->getTejo()->obtenerUltimaColisionPad();

		if(padUltimaColision.compare(PAD_CLIENTE1)==0)
			pad = escenario->getPadCliente1();
		else if(padUltimaColision.compare(PAD_CLIENTE2)==0)
			pad = escenario->getPadCliente2();

		if((pad==NULL)||(pad->getAltura()<incMax)) //si ya se aplico, no se puede volver a aplicar el bonus
		return -1;

		incUnTercioDeAltura=pad->getAltura()+this->getAlturaAnterior()/3;
		if(incUnTercioDeAltura>incMax)
			return -1;
	    pad->setModificar(true);
		pad->setAltura(incUnTercioDeAltura);

	return 0;

}

IncLongPad::~IncLongPad()
{

}
