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
	int incUnTercioDeRadio=this->getRadioAnterior()+this->getRadioAnterior()/3;
	int incMax = this->getRadioAnterior() + (5/3)*this->getRadioAnterior();


		if(incUnTercioDeRadio>incMax) //si ya se aplico, no se puede volver a aplicar el bonus
		return -1;
		tejo->setModificarRadio(true);
		tejo->setRadio(incUnTercioDeRadio);

	return 0;
	}


IncRadioTejo::~IncRadioTejo()
{

}
