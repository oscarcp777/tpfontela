// DecRadioTejo.cpp: implementation of the DecRadioTejo class.
//
//////////////////////////////////////////////////////////////////////

#include "DecRadioTejo.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DecRadioTejo::DecRadioTejo()
{

}


int DecRadioTejo::aplicar(){
	Tejo* tejo = Escenario::obtenerInstancia()->getTejo();
	int decUnTercioDeRadio=tejo->getRadio()-this->getRadioAnterior()/3;
	int decMax = tejo->getRadio()/3;
    	
	if(this->getActivo()==0){

		if(decUnTercioDeRadio<decMax) //si ya se aplico, no se puede volver a aplicar el bonus 
		return -1;

		tejo->setRadio(decUnTercioDeRadio);

	return 0;
	}

	return -1;
}

DecRadioTejo::~DecRadioTejo()
{

}
