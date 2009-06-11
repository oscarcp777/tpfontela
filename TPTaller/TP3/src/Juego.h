/*
 * Juego.h
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#ifndef JUEGO_H_
#define JUEGO_H_

#include "Escenario.h"

class Juego {
public:
	
	virtual ~Juego();
	static Juego* obtenerInstancia();
	bool arrancado();
	bool cancelado();
    void setJuegoArrancado(bool juegoArrancado);
	Escenario* getEscenario();
	void setEscenario(Escenario* escenario);
	bool getNivelTerminado();
	int getPuntajeJugador1();
	int getPuntajeJugador2();
	void setPuntajeJugador1(int puntos);
	void setPuntajeJugador2(int puntos);
	void setNivelTerminado(bool nivelTerminado);
	int getNumeroNivel();
	void incrementarNivel();
	int getTejosRestantes();
	void decrementarTejosRestantes();
	void incrementarCantGolesJugador1();
	void incrementarCantGolesJugador2();
	int getCantGolesJugador1();
	int getCantGolesJugador2();
	void setJuegoCancelado(bool cancelado);

protected:
	Juego();

private:
    bool juegoArrancado;
    bool juegoCancelado;
	Escenario* escenario;
	int puntajeJugador1;
	int puntajeJugador2;
	int numeroNivel;
	int tejosRestantes;
	bool nivelTerminado;
	static Juego *unicaInstanciaJuego;
	int cantGolesJugador1;
	int cantGolesJugador2;

};

#endif /* JUEGO_H_ */
