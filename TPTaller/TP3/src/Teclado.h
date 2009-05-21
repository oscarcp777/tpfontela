/*
 * Teclado.h
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#ifndef TECLADO_H_
#define TECLADO_H_
#include <SDL.h>
const int NUM_TECLAS = 9;
class Teclado {
public:
	Teclado();
	virtual ~Teclado();
	enum teclas_configuradas {
		TECLA_SALIR,
		//un pad usa una tecla de subir y bajar y el otro usa la a y la z
		TECLA_SUBIR_PAD1,
		TECLA_BAJAR_PAD1,
		TECLA_SUBIR_PAD2,
		TECLA_BAJAR_PAD2,
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
