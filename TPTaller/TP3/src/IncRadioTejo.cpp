// IncRadioTejo.cpp: implementation of the IncRadioTejo class.
//
//////////////////////////////////////////////////////////////////////

#include "IncRadioTejo.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IncRadioTejo::IncRadioTejo()
{

}

int IncRadioTejo::aplicar(){
	Tejo* tejo = Escenario::obtenerInstancia()->getTejo();
	int incUnTercioDeRadio= tejo->getRadio() + tejo->getRadioDefault()/3;
	int incMax = tejo->getRadioDefault() + 5*(tejo->getRadioDefault()/3);

	std::cout<<"INC RADIO "<<incUnTercioDeRadio<<endl;
	std::cout<<"incMax"<<incMax<<endl;
		if(incUnTercioDeRadio>incMax) //si ya se aplico, no se puede volver a aplicar el bonus
		return -1;
		tejo->setModificarRadio(true);
		tejo->setRadio(incUnTercioDeRadio);

	return 0;
	}


IncRadioTejo::~IncRadioTejo()
{
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de IncRadioTejo"<<endl;

}
