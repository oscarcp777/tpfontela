/*
 * ControladorColisiones.cpp
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */
#include "Escenario.h"
#include "Figura.h"
#include "Tejo.h"
#include "ControladorColisiones.h"

ControladorColisiones::ControladorColisiones() {
	// TODO Auto-generated constructor stub

}

ControladorColisiones::~ControladorColisiones() {
	// TODO Auto-generated destructor stub
}
bool ControladorColisiones::posibilidadDeColisionDispersores(){
	bool posibilidadColision= false;
	Figura *figura;
	Tejo *tejo = Escenario::obtenerInstancia()->getTejo();
	std::list<Figura*>::iterator iter;
	iter = Escenario::obtenerInstancia()->iteratorListaFiguras();

	int w1, h1, w2, h2, x1, y1, x2, y2;
	w1 = h1 = tejo->getRadio()*2;
	x1 = tejo->getX()-tejo->getRadio();
	y1 = tejo->getY()-tejo->getRadio();
	int i=1;

	while(i <= Escenario::obtenerInstancia()->sizeListaFiguras()){
			figura=*iter;
			w2 = figura->getAnchoInfluencia();
			h2 = figura->getAltoInfluencia();
			x2 = figura->getXInfluencia();
			y2 = figura->getYInfluencia();

			if( ((x1 + w1) > x2) && ((y1 + h1) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1)){
				std::cout<<"puntos de influencia "<<"("<<x2<<","<<y2<<")"<<"abcho"<<w2<<h2<<endl;
				system("PAUSE");

			 return true;
			}
			i++;
			iter++;
		}



	return posibilidadColision;
}
