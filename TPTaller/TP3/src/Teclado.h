/*
 * Teclado.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#ifndef __TECLADO_H__
#define __TECLADO_H__
#include <SDL.h>
#include "Define.h"

class Teclado {
public:
	Teclado();
	virtual ~Teclado();
	enum teclas_configuradas {
		TECLA_SALIR,
		//un pad usa una tecla de subir y bajar y el otro usa la a y la z
		TECLA_SUBIR,
		TECLA_BAJAR,
		TECLA_ACEPTAR,
		TECLA_DISPARAR,
		TECLA_IZQUIERDA,
		TECLA_DERECHA,
		TECLA_SALTAR,
	};
	void actualizar(void);
    bool pulso(enum teclas_configuradas tecla);
private:
	Uint8* teclas;
	SDLKey teclas_configuradas[NUM_TECLAS];
};

#endif /* TECLADO_H_ */
