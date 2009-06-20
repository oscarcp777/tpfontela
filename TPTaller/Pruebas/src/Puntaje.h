// Puntaje.h: interface for the Puntaje class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUNTAJE_H__5D003F4C_8244_4124_8453_272C81C02400__INCLUDED_)
#define AFX_PUNTAJE_H__5D003F4C_8244_4124_8453_272C81C02400__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Puntaje
{
public:
	Puntaje();
	int getCantPuntosJugador();
	void setCantPuntosJugador(int cantPuntos);
	int Puntaje::getPuntajeTotal();
	virtual ~Puntaje();
private:
	int cantPuntosJugador;

};

#endif // !defined(AFX_PUNTAJE_H__5D003F4C_8244_4124_8453_272C81C02400__INCLUDED_)
