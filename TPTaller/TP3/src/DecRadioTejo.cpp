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
	int decUnTercioDeRadio= tejo->getRadio()- tejo->getRadioDefault()/3;
	int decMax = tejo->getRadioDefault()/3;

		if(decUnTercioDeRadio<decMax) //si ya se aplico, no se puede volver a aplicar el bonus
		return -1;
         tejo->setModificarRadio(true);
		tejo->setRadio(decUnTercioDeRadio);
		std::cout<<"radio en DEC"<<decUnTercioDeRadio<<endl;
	return 0;
	
}

DecRadioTejo::~DecRadioTejo()
{

}
