/*
 * Pad.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Pad.h"
#include "Rectangulo.h"
Pad::Pad() {

}
Pad::Pad(int base,int altura,Posicion * posicion){
	this->figura=new Rectangulo("pad",base,altura,posicion);
}
Pad::~Pad() {
	// TODO Auto-generated destructor stub
}
int Pad::mover(Posicion* posicion){
  return 0;
}
