/*
 * AbstractTest.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "AbstractTest.h"

AbstractTest::AbstractTest() {
	// TODO Auto-generated constructor stub

}

AbstractTest::~AbstractTest() {
	// TODO Auto-generated destructor stub
}

string AbstractTest::getRuta(){
	return this->ruta;
}
void AbstractTest::setRuta(string ruta){
	this->ruta = ruta;

}
