/*
 * KeyPar.cpp
 *
 *  Created on: 07/04/2010
 *      Author: oscar
 */

#include "KeyPar.h"

KeyPar::KeyPar() {
	// TODO Auto-generated constructor stub

}
KeyPar::KeyPar(INT_UNSIGNED position,INT_UNSIGNED offsetCube) {
	this->position=position;
	this->offsetCube=offsetCube;

}
KeyPar::~KeyPar() {
	// TODO Auto-generated destructor stub
}

KeyPar* KeyPar::clone(){
	KeyPar* newKeyPar = new KeyPar();
	newKeyPar->setOffsetCube(this->getOffsetCube());
	newKeyPar->setPosition(this->getPosition());
	return newKeyPar;

}
