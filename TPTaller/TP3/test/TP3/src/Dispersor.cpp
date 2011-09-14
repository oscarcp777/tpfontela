/*
 * Dispersor.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Dispersor.h"

Dispersor::Dispersor() {
	// TODO Auto-generated constructor stub

}
Dispersor::Dispersor(Figura* figura) {
	this->figura=figura;
	}

Dispersor::~Dispersor() {
	// TODO Auto-generated destructor stub
}
Figura* Dispersor::getFigura()
    {
        return this->figura;
    }

void Dispersor::setFigura(Figura *figura)
    {
        this->figura = figura;
    }
