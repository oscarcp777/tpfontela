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

    std::string padUltimaColision = escenario->getTejo()->obtenerUltimaColisionPad();

	
		if(padUltimaColision.compare(PAD_CLIENTE1)==0)
			pad = escenario->getPadCliente2();
		else if(padUltimaColision.compare(PAD_CLIENTE2)==0)
			pad = escenario->getPadCliente1();

		int incMax = pad->getAlturaDefault() + 5*(pad->getAlturaDefault()/3);

		if(pad==NULL) 
		return -1;
			
		incUnTercioDeAltura = pad->getAltura() + pad->getAlturaDefault()/3;

		if(incUnTercioDeAltura>incMax)
			return -1;

	    pad->setModificar(true);
		pad->setAltura(incUnTercioDeAltura);

	return 0;

}

IncLongPadVs::~IncLongPadVs()
{

}