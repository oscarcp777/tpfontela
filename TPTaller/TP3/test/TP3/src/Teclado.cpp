/*
 * Teclado.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */
#include <iostream>
#include "Teclado.h"
using namespace std;
Teclado::Teclado() {
	// Configuramos la teclas que usaremos en la aplicación

	teclas_configuradas[TECLA_SALIR] = SDLK_ESCAPE;
	teclas_configuradas[TECLA_SUBIR] = SDLK_UP;
	teclas_configuradas[TECLA_BAJAR] = SDLK_DOWN;
	teclas_configuradas[TECLA_ACEPTAR] = SDLK_RETURN;
	teclas_configuradas[TECLA_DISPARAR] = SDLK_SPACE;
	teclas_configuradas[TECLA_IZQUIERDA] = SDLK_LEFT;
	teclas_configuradas[TECLA_DERECHA] = SDLK_RIGHT;
	teclas_configuradas[TECLA_SALTAR] = SDLK_UP;
	teclas_configuradas[TECLA_GUARDAR] = SDLK_s;

}

Teclado::~Teclado() {
	// TODO Auto-generated destructor stub
}
void Teclado::actualizar(void) {

	// Actualizamos el estado del teclado mediante mapeo
	teclas = SDL_GetKeyState(NULL);
}
;bool Teclado::pulso(enum teclas_configuradas tecla) {

	if(teclas[teclas_configuradas[tecla]])
		return true;
	else
		return false;
}
