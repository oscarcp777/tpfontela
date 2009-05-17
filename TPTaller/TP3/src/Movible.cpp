/*
 * Movible.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Movible.h"

Movible::Movible() {
	// TODO Auto-generated constructor stub

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

