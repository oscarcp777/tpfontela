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
	int incUnTercioDeVelocidad=tejo->getVelocidad()+ tejo->getVelocidadDefault()/3;
	int incMax = 5*(tejo->getVelocidadDefault()/3);



		if(incUnTercioDeVelocidad>incMax) //si ya se aplico, no se puede volver a aplicar el bonus
		return -1;

		tejo->setVelocidad(incUnTercioDeVelocidad);

	return 0;
	}



IncVelocidadTejo::~IncVelocidadTejo()
{
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de IncVelocidadTejo"<<endl;

}
