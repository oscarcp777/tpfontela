/*
 * Juego.h
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#ifndef JUEGO_H_
#define JUEGO_H_

#include "Escenario.h"
#include "ControladorColisiones.h"
#include "Define.h"
#include "GraficadorPuntajes.h"
#include <windows.h>

class Juego {
public:

	virtual ~Juego();
	static Juego* obtenerInstancia();
	bool arrancado();
	bool cancelado();
    void setJuegoArrancado(bool juegoArrancado);
	Escenario* getEscenario();
	void setEscenario(Escenario* escenario);
	int getNumeroNivel();
	void incrementarNivel();
	int getTejosRestantes();
	void decrementarTejosRestantes();
	void setJuegoCancelado(bool cancelado);
	void update();
    std::string getEstado();
	void setEstado(std::string estado);

protected:
	Juego();

private:
    bool juegoArrancado;
    bool juegoCancelado;
	std::string estado;
	Escenario* escenario;
	int numeroNivel;
	int tejosRestantes;
	static Juego *unicaInstanciaJuego;


};

#endif /* JUEGO_H_ */
