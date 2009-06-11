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
	this->puntajeJugador1 = 0;
	this->puntajeJugador2 = 0;
	this->numeroNivel = 1;
	this->tejosRestantes = 7;
	this->nivelTerminado = false;
	this->cantGolesJugador1 = 0;
	this->cantGolesJugador2 = 0;
	
	
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

bool Juego::getNivelTerminado(){
	return this->nivelTerminado;	
}

int Juego::getPuntajeJugador1(){
	return this->puntajeJugador1;
}

int Juego::getPuntajeJugador2(){
	
	return this->puntajeJugador2;
}
void Juego::setPuntajeJugador1(int puntos){
	
	this->puntajeJugador1 = puntos; 

}
void Juego::setPuntajeJugador2(int puntos){

	this->puntajeJugador2 = puntos; 
}

void Juego::setNivelTerminado(bool nivelTerminado){
	this->nivelTerminado = nivelTerminado;
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

void Juego::incrementarCantGolesJugador1(){
	this->cantGolesJugador1++;
}

void Juego::incrementarCantGolesJugador2(){
	this->cantGolesJugador2++;
}

int Juego::getCantGolesJugador1(){
	return this->cantGolesJugador1;
}
int Juego::getCantGolesJugador2(){
	return this->cantGolesJugador2;
}

void Juego::setJuegoCancelado(bool cancelado){
	this->juegoCancelado = cancelado;
}