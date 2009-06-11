/*
 * Juego.h
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#ifndef JUEGO_H_
#define JUEGO_H_

class Juego {
public:
	Juego();
	virtual ~Juego();
	bool arrancado();
	bool cancelado();
    void setJuegoArrancado(bool juegoArrancado);

private:
    bool juegoArrancado;
    bool juegoCancelado;
};

#endif /* JUEGO_H_ */
