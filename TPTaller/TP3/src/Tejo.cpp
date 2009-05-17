/*
 * Tejo.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Tejo.h"
#include "Circulo.h"
Tejo::Tejo() {
	// TODO Auto-generated constructor stub

}
Tejo::Tejo(int radio,Posicion * posicion){
this->figura= new Circulo("tejo",radio,posicion);
}
Tejo::~Tejo() {
	// TODO Auto-generated destructor stub
}
int Tejo::mover(Posicion* posicion){
  return 0;
}



