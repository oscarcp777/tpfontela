// FrenoTejo.cpp: implementation of the FrenoTejo class.
//
//////////////////////////////////////////////////////////////////////

#include "FrenoTejo.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FrenoTejo::FrenoTejo()
{

}
int getTipoBonus(){
	return 	FRENO_TEJO;
}
int FrenoTejo::aplicar(){
	Tejo* tejo = Escenario::obtenerInstancia()->getTejo();
	int decUnTercioVelocidad=tejo->getVelocidad()- tejo->getVelocidadDefault()/3;
	int decMax = (1/3)*tejo->getVelocidadDefault();
    

		if(decUnTercioVelocidad<decMax) //si ya se aplico, no se puede volver a aplicar el bonus 
		return -1;

		tejo->setVelocidad(decUnTercioVelocidad);

	return 0;

}

FrenoTejo::~FrenoTejo()
{

}
