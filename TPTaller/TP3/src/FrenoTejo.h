// FrenoTejo.h: interface for the FrenoTejo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __FRENOTEJO_H__
#define __FRENOTEJO_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bonus.h"

class FrenoTejo: public Bonus{
public:
	FrenoTejo();
	int aplicar();
	virtual ~FrenoTejo();
	int getTipoBonus();

};

#endif // !defined(AFX_FRENOTEJO_H__370BB283_42D4_4770_B709_4609497D92B4__INCLUDED_)
