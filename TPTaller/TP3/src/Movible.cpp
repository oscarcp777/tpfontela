/*
 * Movible.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Movible.h"

Movible::Movible() {
}

Movible::~Movible() {
	// TODO Auto-generated destructor stub
}
Figura* Movible::getFigura()
{
	return this->figura;
}

void Movible::setFigura(Figura *figura)
{
	this->figura = figura;
}
int Movible::getPos_x(){
	return this->posicion->getX();
}
int Movible::getPos_y(){
	return this->posicion->getY();
}
void Movible::setPos_x(int x){
	this->posicion->setX(x);
}
void Movible::setPos_y(int y){
	this->posicion->setY(y);
}
// El movimiento de la imagen se establece
// de 4 en 4 píxeles
void Movible::avanzar_x() {
	int x =this->posicion->getX();
	x += 4;
	this->posicion->setX(x);
}
void Movible::retrasar_x() {
	int x =this->posicion->getX();
	x -= 4;
	this->posicion->setX(x);
}
void Movible::bajar_y() {
	int y =this->posicion->getY();
	y += 4;
	this->posicion->setY(y);
}
void Movible::subir_y() {
	int y =this->posicion->getY();
	y -= 4;
	this->posicion->setY(y);
}
