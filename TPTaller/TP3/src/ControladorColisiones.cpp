/*
 * ControladorColisiones.cpp
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */
#include "Escenario.h"
#include "Figura.h"
#include "Tejo.h"
#include "Rectangulo.h"
#include "ControladorColisiones.h"

const double PI=3.14159265358979323846;

ControladorColisiones::ControladorColisiones() {
	// TODO Auto-generated constructor stub

}
void reboteArriba(Tejo* tejo){
	if (tejo->getDireccion()->getFi()==PI/2){
		tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI));
	}else {
		if (tejo->getDireccion()->getFi()<PI/2&&tejo->getDireccion()->getFi()>=0){
			tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(3*PI/2));
		}else{
			if (tejo->getDireccion()->getFi()>PI/2&&tejo->getDireccion()->getFi()<=PI){
				tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI/2));
			}
		}
	}
}
void reboteAbajo(Tejo* tejo){
	if (tejo->getDireccion()->getFi()==3*PI/2){
		tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI));
	}else if (tejo->getDireccion()->getFi()<3*PI/2&&tejo->getDireccion()->getFi()>=PI){
		tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI/2));
	}else{
		if (tejo->getDireccion()->getFi()>3*PI/2&&tejo->getDireccion()->getFi()<=2*PI){
			tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(3*PI/2));
		}}
}
void reboteDerecha(Tejo* tejo){
	if (tejo->getDireccion()->getFi()==0.0){

		tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI));
	}else {
		if (tejo->getDireccion()->getFi()<PI/2&&tejo->getDireccion()->getFi()>=0.0){

			tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI/2));
		}else{
			if (tejo->getDireccion()->getFi()>3*PI/2&&tejo->getDireccion()->getFi()<=2*PI){
				tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI/2));
			}         }
	}
}
void reboteIzquierda(Tejo* tejo){

	if (tejo->getDireccion()->getFi()==PI){
		tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI));
	}else if (tejo->getDireccion()->getFi()<PI&&tejo->getDireccion()->getFi()>=PI/2){
		tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()-(PI/2));
	}else{
		if (tejo->getDireccion()->getFi()>PI&&tejo->getDireccion()->getFi()<=3*PI/2){
			tejo->getDireccion()->setFi(tejo->getDireccion()->getFi()+(PI/2));
		}}

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

		if( ((x1 + w1) >= x2) && ((y1 + h1) >= y2) && ((x2 + w2) >= x1) && ((y2 + h2) >= y1)){
//			std::cout<<"colisiono con : :"<<figura->getId()<<endl;

			if(tejo->getX()-tejo->getRadio() ==x2+w2){
				reboteIzquierda(tejo);
			}
			if(tejo->getX()+tejo->getRadio() == x2){
				reboteDerecha(tejo);
			}

			if(tejo->getY()- tejo->getRadio()==y2+h2){

				reboteArriba(tejo);
			}
			if(tejo->getY()+tejo->getRadio() == y2){
				reboteAbajo(tejo);
			}


			return true;
		}
		i++;
		iter++;
	}



	return posibilidadColision;
}

void ControladorColisiones::colisionesPads(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Tejo* tejo = escenario->getTejo();
	Pad* padIzquierda=escenario->getPadCliente1();
	Pad* padDerecha=escenario->getPadCliente2();

	if(padIzquierda->getY()-tejo->getRadio()<=tejo->getY()&&padIzquierda->getY()+padIzquierda->getAltura()+tejo->getRadio()>=tejo->getY()){
		if(tejo->getX() ==padIzquierda->getBase()+ padIzquierda->getX()+tejo->getRadio()){

			reboteIzquierda(tejo);
		}
		if(tejo->getX() == padIzquierda->getX()- tejo->getRadio()){
			reboteDerecha(tejo);
		}
	}
	if(padDerecha->getY()-tejo->getRadio()<=tejo->getY()&&padDerecha->getY()+padDerecha->getAltura()+tejo->getRadio()>=tejo->getY()){
		if(tejo->getX() == padDerecha->getX()- tejo->getRadio()){
			reboteDerecha(tejo);
		}
		if( tejo->getX() == padDerecha->getX()+padDerecha->getBase()+tejo->getRadio()){

			reboteIzquierda(tejo);
		}
	}
}
int ControladorColisiones::colisionesArcos(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Tejo* tejo = escenario->getTejo();
	Rectangulo* arcoDerecha = escenario->getArcoDerecha();
	Rectangulo* arcoIzquierda = escenario->getArcoIzquierda();

	if(arcoIzquierda->getY()+tejo->getRadio()<=tejo->getY()&&arcoIzquierda->getY()+arcoIzquierda->getAltura()-tejo->getRadio()>=tejo->getY()&&
			tejo->getX()<tejo->getRadio()*4){
		if(tejo->getX() <=arcoIzquierda->getBase()+ arcoIzquierda->getX()+tejo->getRadio()){
//			std::cout<<"  GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<endl;
			return 0;
		}
	}
	if(arcoDerecha->getY()+tejo->getRadio()<=tejo->getY()&&arcoDerecha->getY()+arcoDerecha->getAltura()-tejo->getRadio()>=tejo->getY()&&
			tejo->getX()>escenario->getAncho()-tejo->getRadio()*4){
		if(tejo->getX() >= arcoDerecha->getX()- tejo->getRadio()){
//			std::cout<<"  GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<endl;
			return 0;
		}
	}
	return -1;
}
void ControladorColisiones::calcularDireccion(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Tejo* tejo = escenario->getTejo();


	if(tejo->getY() <= 0  + tejo->getRadio()){
		reboteArriba(tejo);
	}else{
		if(tejo->getY() >= escenario->getAlto()-tejo->getRadio()){
			reboteAbajo( tejo);
		}else{

			if(tejo->getX() >= escenario->getAncho()-tejo->getRadio()){
				reboteDerecha(tejo);
			}else{
				if(tejo->getX() <= 0 + tejo->getRadio()){
					reboteIzquierda(tejo);
				}
			}
		}
	}
}

