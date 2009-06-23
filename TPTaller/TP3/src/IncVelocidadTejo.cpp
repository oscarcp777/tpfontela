// IncVelocidadTejo.cpp: implementation of the IncVelocidadTejo class.
//
//////////////////////////////////////////////////////////////////////

#include "IncVelocidadTejo.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IncVelocidadTejo::IncVelocidadTejo()
{

}

int IncVelocidadTejo::aplicar(){
	Tejo* tejo = Escenario::obtenerInstancia()->getTejo();
	int incUnTercioDeVelocidad=tejo->getVelocidad()+this->getVelocidadAnterior()/3;
	int incMax = this->getVelocidadAnterior() + (5/3)*this->getVelocidadAnterior();
    	


		if(incUnTercioDeVelocidad>incMax) //si ya se aplico, no se puede volver a aplicar el bonus 
		return -1;

		tejo->setVelocidad(incUnTercioDeVelocidad);

	return 0;
	}



IncVelocidadTejo::~IncVelocidadTejo()
{

}
