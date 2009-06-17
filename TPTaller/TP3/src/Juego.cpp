/*
 * Juego.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "Juego.h"

Juego::Juego() {
	// TODO Auto-generated constructor stub
	this->juegoArrancado=false;
	this->juegoCancelado=false;
	this->numeroNivel = 1;
	this->tejosRestantes = 7;
	this->estado = "CORRIENDO";


}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
}

Juego* Juego::unicaInstanciaJuego = NULL;

Juego* Juego::obtenerInstancia(){

	if(!Juego::unicaInstanciaJuego){
		Juego::unicaInstanciaJuego = new Juego();
	}

	return Juego::unicaInstanciaJuego;
}

bool Juego::arrancado()
{
	return juegoArrancado;
}

bool Juego::cancelado()
{
	return juegoCancelado;
}

void Juego::setJuegoArrancado(bool juegoArrancado)
{
	this->juegoArrancado = juegoArrancado;
}

Escenario* Juego::getEscenario(){

	return this->escenario;

}
void Juego::setEscenario(Escenario* escenario){
	this->escenario = escenario;

}


int Juego::getNumeroNivel(){

	return this->numeroNivel;
}

void Juego::incrementarNivel(){

	this->numeroNivel++;
}

int Juego::getTejosRestantes(){
	return this->tejosRestantes;
}

void Juego::decrementarTejosRestantes(){
	this->tejosRestantes--;
}

void Juego::setJuegoCancelado(bool cancelado){
	this->juegoCancelado = cancelado;
}

std::string Juego::getEstado()
{
	return estado;
}

void Juego::update(){


		SDL_Event evento;

		// Actualizamos el estado del teclado
		this->escenario->getTejo()->mover_x();
		this->escenario->getTejo()->mover_y();
		//me fijo si hay colisiones

		ControladorColisiones::colisionesPads();
		ControladorColisiones::posibilidadDeColisionDispersores();
		/*############################################################################################################################*/
		/*############      si hubo gol repinto el tejo lo cambio de posicion                                                            ##########*/
		/*############################################################################################################################*/

	/*				if(ControladorColisiones::colisionesArcos()==0){
					this->escenario->getPadCliente1()->setY(this->escenario->getAlto()/2);
					this->escenario->getPadCliente1()->setX((int)this->escenario->getAncho()*POS_PAD1_Y_PORCENTAJE);
					this->escenario->getPadCliente2()->setY(this->escenario->getAlto()/2);
					this->escenario->getPadCliente2()->setX((int)this->escenario->getAncho()*POS_PAD2_Y_PORCENTAJE);
					this->escenario->getTejo()->setY(this->escenario->getAlto()/2);
					this->escenario->getTejo()->setX(this->escenario->getPadCliente2()->getX()+this->escenario->getPadCliente2()->getBase()+this->escenario->getTejo()->getRadio());
					this->escenario->getTejo()->getDireccion()->setFi(PI/4);
					this->estado="GOL";
					GraficadorPuntajes::obtenerInstancia()->inicializarFuente(this->escenario->getPadCliente1()->getPuntaje()->getCantPuntosJugador(),this->escenario->getPadCliente2()->getPuntaje()->getCantPuntosJugador());
					GraficadorPuntajes::obtenerInstancia()->decrementarCantidadTejos();


				}*/

		ControladorColisiones::calcularDireccion();


		//si fue gol espero 2 segundos antes de empezar otra partida
					if(this->estado.compare("GOL")==0){
					    Sleep(1000);
						//tejosRestantes se inicializa en 7 en el constructor de Juego, cuando se hace un gol se decrementa
						this->decrementarTejosRestantes();
						if(this->getTejosRestantes() < 0){
							//si no quedan tejos por jugar en el nivel, el nivel esta terminado y se pasa al siguiente
							this->estado="NIVEL_TERMINADO";
							this->incrementarNivel();
							//como termina el nivel se incrementan (en 70) los puntos del jugador que gano el nivel (el que hizo mas goles)
							if(this->escenario->getPadCliente1()->getCantGoles()  >  this->escenario->getPadCliente2()->getCantGoles()){
								this->escenario->getPadCliente1()->getPuntaje()->setCantPuntosJugador(this->escenario->getPadCliente1()->getPuntaje()->getCantPuntosJugador()+70);
							}
							else{
								this->escenario->getPadCliente2()->getPuntaje()->setCantPuntosJugador(this->escenario->getPadCliente2()->getPuntaje()->getCantPuntosJugador()+70);
							}

						}
						this->estado="CORRIENDO";

					}

}
