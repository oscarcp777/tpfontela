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
	
	//	tejo->setPegajoso(true); 
		return 0;

}

PegamentoTejo::~PegamentoTejo()
{

}