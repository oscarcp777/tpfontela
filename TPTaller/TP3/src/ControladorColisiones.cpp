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

const double PI=3.14159265;

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
				std::cout<<"posibilidad de colision contra la figura: "<<figura->getId()<<endl;


			 return true;
			}
			i++;
			iter++;
		}



	return posibilidadColision;
}

void ControladorColisiones::calcularDireccion(){
			Escenario* escenario = Escenario::obtenerInstancia();
			Tejo* tejo = escenario->getTejo();


			if(tejo->getY() <= 0  + tejo->getRadio())
				if (tejo->getDireccion()->getFi()<PI/2)
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(3*PI/2));
				else
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI/2));

			if(tejo->getY() >= escenario->getAlto()-tejo->getRadio())
				if (tejo->getDireccion()->getFi()<3*PI/2)
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI/2));
				else
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(3*PI/2));


			if(tejo->getX() >= escenario->getAncho()-tejo->getRadio())
				if (tejo->getDireccion()->getFi()<PI/2)
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI/2));
				else
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI/2));

			if(tejo->getX() <= 0 + tejo->getRadio())
				if (tejo->getDireccion()->getFi()<PI)
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI/2));
				else
					tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI/2));


}
