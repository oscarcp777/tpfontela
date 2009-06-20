// Puntaje.h: interface for the Puntaje class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __PUNTAJE_H__
#define __PUNTAJE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Define.h"

class Puntaje
{
public:
	Puntaje();
	int getCantPuntosJugador();
	void setCantPuntosJugador(int cantPuntos);
	virtual ~Puntaje();
private:
	int cantPuntosJugador;

};

#endif // !defined(AFX_PUNTAJE_H__5D003F4C_8244_4124_8453_272C81C02400__INCLUDED_)
