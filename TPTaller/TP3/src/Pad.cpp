/*
 * Pad.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Pad.h"
#include "Rectangulo.h"
#include "Escenario.h"
#include "Define.h"
Pad::Pad() {

}
Rectangulo* Pad::getFigura(){
	return this->rectangulo;
}
Pad::Pad(Rectangulo* rectangulo,Puntaje* puntaje){
	this->rectangulo=rectangulo;
	this->puntaje = puntaje;
	this->cantGoles = 0;
	std::cout<< "padv1: "  <<this->rectangulo->getIdTextura()<< endl;


}
int Pad::getVelocidad()
    {
        return velocidad;
    }

    void Pad::setVelocidad(int velocidad)
    {
        this->velocidad = velocidad;
    }
Pad::~Pad() {
	// TODO Auto-generated destructor stub
}
void Pad::dibujar(SDL_Surface *pantalla){
	this->getFigura()->dibujar(pantalla);
}
int Pad::getX(){
	return this->rectangulo->getPosicion()->getX();
}
int Pad::getY(){
	return this->rectangulo->getPosicion()->getY();
}
void Pad::setX(int x){
	this->rectangulo->getPosicion()->setX(x);
}
void Pad::setY(int y){
	this->rectangulo->getPosicion()->setY(y);
}

int Pad::getBase(){
	return this->rectangulo->getBase();
}
int Pad::getAltura(){
	return this->rectangulo->getAltura();
}
void Pad::setAltura(int altura){
	this->rectangulo->setAltura(altura);
}
// El movimiento de la imagen se establece
// de 4 en 4 píxeles
void Pad::avanzar_x() {
	int x =this->getX();
	x += this->velocidad;
	this->setX(x);
}
void Pad::retrasar_x() {
	int x =this->getX();
	x -= this->velocidad;
	this->setX(x);
}
void Pad::bajar_y() {
	int y =this->getY();
	y += this->velocidad;
	this->setY(y);
}
void Pad::subir_y() {
	int y =this->getY();
	y -= this->velocidad;
	this->setY(y);
}

Puntaje* Pad::getPuntaje(){
	return this->puntaje;
}

int Pad::getCantGoles()
{
	return cantGoles;
}

void Pad::setCantGoles(int cantGoles)
{
	this->cantGoles = cantGoles;
}


