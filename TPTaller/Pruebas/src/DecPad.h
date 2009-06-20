// DecPad.h: interface for the DecPad class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DECPAD_H__
#define __DECPAD_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bonus.h"

class DecPad: public Bonus{
public:
	DecPad();
	int aplicar();
	~DecPad();

};

#endif // !defined(AFX_DECPAD_H__B27EF502_DA06_4C37_8154_FD439C555058__INCLUDED_)
