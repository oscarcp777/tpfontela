// DecLongPad.h: interface for the DecLongPad class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DECLONGPAD_H__
#define __DECLONGPAD_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bonus.h"

class DecLongPad : public Bonus{

public:
	DecLongPad();
	int aplicar();
	~DecLongPad();

};

#endif