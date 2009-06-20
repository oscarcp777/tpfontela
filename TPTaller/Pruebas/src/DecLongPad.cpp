// DecLongPad.cpp: implementation of the DecLongPad class.
//
//////////////////////////////////////////////////////////////////////

#include "DecLongPad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "Escenario.h"
#include "Define.h"
DecLongPad::DecLongPad()
{

}

int DecLongPad::aplicar(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Pad*pad=NULL;
	int decUnTercioDeAltura=0;
	int decMax = this->getAlturaAnterior()/3;
    std::string padUltimaColision = escenario->getTejo()->obtenerUltimaColisionPad();
	
	if(this->getActivo()==0){

		if(padUltimaColision.compare(PAD_CLIENTE1)==0)
			pad = escenario->getPadCliente1();
		else if(padUltimaColision.compare(PAD_CLIENTE2)==0)
			pad = escenario->getPadCliente2();

		if(pad==NULL) //si ya se aplico, no se puede volver a aplicar el bonus 
			return -1;

		decUnTercioDeAltura=pad->getAltura()-this->getAlturaAnterior()/3;

		if(decUnTercioDeAltura < decMax)
			return -1;

		pad->setAltura(decUnTercioDeAltura);

	return 0;
	}

	return -1;
}

DecLongPad::~DecLongPad()
{

}
