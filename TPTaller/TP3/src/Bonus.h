// Bonus.h: interface for the Bonus class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __BONUS_H__
#define __BONUS_H__


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Escenario.h"
#include "Define.h"

class Bonus  
{
public:
	virtual int aplicar()=0;
	int getActivo();
	/* 0  si esta activo
	 * -1 si no esta activo
	 */
	void setActivo(int activo);
	/*
	 * Metodos para guardar el estado anterior del tejo y de los pad
	 */
	void setVelocidadAnterior(int velocidadAnterior);
	int getVelocidadAnterior();
	void setAlturaAnterior(int alturaAnterior);
	int getAlturaAnterior();
	void setRadioAnterior(int radioAnterior);
	int getRadioAnterior();
	Bonus();
	virtual ~Bonus();

private:
	int activo;
	int velocidadAnterior;
	int alturaAnterior;
	int radioAnterior;
	
};

#endif // !defined(AFX_BONUS_H__FE1BDB9A_EE48_46F7_B182_55414A9B1645__INCLUDED_)
