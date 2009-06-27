// DecLongPadVs.cpp: implementation of the DecLongPadVs class.
//
//////////////////////////////////////////////////////////////////////

#include "DecLongPadVs.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DecLongPadVs::DecLongPadVs()
{

}


int DecLongPadVs::aplicar(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Pad*pad=NULL;
	int decUnTercioDeAltura=0;
	
    std::string padUltimaColision = escenario->getTejo()->obtenerUltimaColisionPad();



		if(padUltimaColision.compare(PAD_CLIENTE1)==0)
			pad = escenario->getPadCliente2();
		else if(padUltimaColision.compare(PAD_CLIENTE2)==0)
			pad = escenario->getPadCliente1();

		if(pad==NULL) //si ya se aplico, no se puede volver a aplicar el bonus
		return -2;
		
		int decMax = pad->getAlturaDefault()/3;
		decUnTercioDeAltura = pad->getAltura()-pad->getAlturaDefault()/3;

		if(decUnTercioDeAltura < decMax)
			return -1;
	    pad->setModificar(true);
		pad->setAltura(decUnTercioDeAltura);

	return 0;

}


DecLongPadVs::~DecLongPadVs()
{
	 if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de DecLongPadVs"<<endl;
}
