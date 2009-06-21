// IncLongPadVs.cpp: implementation of the IncLongPadVs class.
//
//////////////////////////////////////////////////////////////////////

#include "IncLongPadVs.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IncLongPadVs::IncLongPadVs()
{

}

int IncLongPadVs::aplicar(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Pad*pad=NULL;
	int incUnTercioDeAltura=0;
	int incMax = this->getAlturaAnterior() + (5/3)*this->getAlturaAnterior();
    std::string padUltimaColision = escenario->getTejo()->obtenerUltimaColisionPad();
	
	if(this->getActivo()==0){

		if(padUltimaColision.compare(PAD_CLIENTE1)==0)
			pad = escenario->getPadCliente2();
		else if(padUltimaColision.compare(PAD_CLIENTE2)==0)
			pad = escenario->getPadCliente1();

		if((pad==NULL)||(pad->getAltura()<incMax)) //si ya se aplico, no se puede volver a aplicar el bonus 
		return -1;

		incUnTercioDeAltura = pad->getAltura()+this->getAlturaAnterior()/3;

		if(incUnTercioDeAltura>incMax)
			return -1;

		pad->setAltura(incUnTercioDeAltura);

	return 0;
	}

	return -1;
}

IncLongPadVs::~IncLongPadVs()
{

}
