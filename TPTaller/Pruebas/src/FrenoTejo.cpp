// FrenoTejo.cpp: implementation of the FrenoTejo class.
//
//////////////////////////////////////////////////////////////////////

#include "FrenoTejo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FrenoTejo::FrenoTejo()
{

}

int FrenoTejo::aplicar(){
	Tejo* tejo = Escenario::obtenerInstancia()->getTejo();
	int decUnTercioVelocidad=tejo->getVelocidad()-this->getVelocidadAnterior()/3;
	int decMax = (1/3)*this->getVelocidadAnterior();
    	
	if(this->getActivo()==0){

		if(decUnTercioVelocidad<decMax) //si ya se aplico, no se puede volver a aplicar el bonus 
		return -1;

		tejo->setVelocidad(decUnTercioVelocidad);

	return 0;
	}

	return -1;
}

FrenoTejo::~FrenoTejo()
{

}
