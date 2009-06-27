// PegamentoTejo.h: interface for the PegamentoTejo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __PEGAMENTOTEJO_H__
#define __PEGAMENTOTEJO_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bonus.h"

class PegamentoTejo: public Bonus{
public:
	PegamentoTejo();
	int aplicar();
	~PegamentoTejo();

};

#endif // !defined(AFX_PEGAMENTOTEJO_H__82CDCC96_D699_403A_BC6B_07177CA8A989__INCLUDED_)
