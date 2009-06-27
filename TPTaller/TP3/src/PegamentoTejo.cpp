// PegamentoTejo.cpp: implementation of the PegamentoTejo class.
//
//////////////////////////////////////////////////////////////////////

#include "PegamentoTejo.h"
#include "Escenario.h"
#include "Define.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PegamentoTejo::PegamentoTejo()
{

}

int PegamentoTejo::aplicar(){
		Tejo* tejo = Escenario::obtenerInstancia()->getTejo();
	
		
		tejo->setPadPegajoso(tejo->obtenerUltimaColisionPad());
		tejo->setPegajoso(true);
		return 0;

}

PegamentoTejo::~PegamentoTejo()
{
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de PegamentoTejo"<<endl;

}
