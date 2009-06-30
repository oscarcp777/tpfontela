/*
 * ControladorColisiones.cpp
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */
#include "Escenario.h"
#include "Figura.h"
#include "Tejo.h"
#include "Define.h"
#include "Rectangulo.h"
#include "ControladorColisiones.h"
#include "CalculosMatematicos.h"
#include<math.h>
#include <iostream>

ControladorColisiones::ControladorColisiones() {


}

void reboteArriba(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==PI/2){
		tejo->getDireccion()->setFi(anguloDeltejo+(PI));
	}else {
		if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){
			tejo->getDireccion()->setFi((2*PI)-anguloDeltejo);
		}else{
			if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
				tejo->getDireccion()->setFi(anguloDeltejo+2*(PI-anguloDeltejo));
			}
		}
	}
}
void reboteAbajo(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==3*PI/2){
		tejo->getDireccion()->setFi(anguloDeltejo-(PI));
	}else if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
		tejo->getDireccion()->setFi(anguloDeltejo-2*(anguloDeltejo-PI));
	}else{
		if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
			tejo->getDireccion()->setFi(2*PI-anguloDeltejo);
		}}
}
void reboteDerecha(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==0.0){

		tejo->getDireccion()->setFi(anguloDeltejo+(PI));
	}else {
		if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){

			tejo->getDireccion()->setFi(anguloDeltejo+(PI-2*anguloDeltejo));
		}else{
			if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
				tejo->getDireccion()->setFi(PI+(2*PI-anguloDeltejo));
			}         }
	}
}
void reboteIzquierda(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==PI){
		tejo->getDireccion()->setFi(anguloDeltejo-(PI));
	}else if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
		tejo->getDireccion()->setFi(PI-anguloDeltejo);
	}else{
		if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
			tejo->getDireccion()->setFi(anguloDeltejo+2*(3*PI/2-anguloDeltejo));
		}
	}

}
void ControladorColisiones::decidirDireccionPrimerCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY){
	double nuevaDireccion;
	double anguloDeltejo=tejo->getDireccion()->getFi();
	int xTejo=tejo->getX(),yTejo=tejo->getY(),radioTejo=tejo->getRadio();
	Recta*  rectaDireccionTejo= tejo->getRectaDireccion();
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(anguloDeltejo-PI));
	}else{

		if(rectaDeColision->getPendiente()>=0){
			if(CalculosMatematicos::verificarDireccionRectasPositivas(rectaDeColision,rectaDireccionTejo)==-1){
				nuevaDireccion=PI-((anguloDeltejo)+(anguloConAbcisa));
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion PrimerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}


			}else{

				nuevaDireccion=((anguloDeltejo)+(anguloConAbcisa));
				nuevaDireccion=PI-(2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion PrimerCuadrante 2  :"<<(nuevaDireccion*180)/PI<<endl;
				}




			}
		}else{
			if(posicionY<yTejo){
				nuevaDireccion=anguloDeltejo -anguloConAbcisa;
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=anguloDeltejo-2*nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  PrimerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;
					system("PAUSE");
				}






			}else{
				nuevaDireccion=(anguloConAbcisa-anguloDeltejo);
				if(nuevaDireccion<0){
					nuevaDireccion=nuevaDireccion*-1;
				}
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){

					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  PrimerCuadrante 4  "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;
					system("PAUSE");
				}




			}

		}
		delete rectaDireccionTejo;

	}
}
void ControladorColisiones::decidirDireccionSegundoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY){
	double nuevaDireccion;
	double anguloDeltejo=tejo->getDireccion()->getFi();
	int xTejo=tejo->getX(),yTejo=tejo->getY(),radioTejo=tejo->getRadio();
	Recta*  rectaDireccionTejo= tejo->getRectaDireccion();
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(anguloDeltejo-PI));
	}else{

		if(rectaDeColision->getPendiente()<0){
			if(CalculosMatematicos::verificarDireccionRectasNegativas(rectaDeColision,rectaDireccionTejo)==-1){
				nuevaDireccion=PI-(anguloDeltejo);
				nuevaDireccion=(anguloConAbcisa+nuevaDireccion);
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}



			}else{
				nuevaDireccion=(anguloDeltejo-anguloConAbcisa);
				nuevaDireccion=(PI-2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 2 "<<(nuevaDireccion*180)/PI<<endl;
				}



			}
		}else{
			if(yTejo>posicionY){
				nuevaDireccion=PI/2-((anguloDeltejo-PI/2)+anguloConAbcisa);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion+PI/12);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;
					system("PAUSE");
				}



			}else{
				nuevaDireccion=(anguloDeltejo-PI/2)-(PI/2-anguloConAbcisa);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 4 "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;
					system("PAUSE");
				}



			}
		}
	}
	delete rectaDireccionTejo;

}
void ControladorColisiones::decidirDireccionTercerCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	double nuevaDireccion,anguloAux;
	int xTejo=tejo->getX(),yTejo=tejo->getY(),radioTejo=tejo->getRadio();
	Recta*  rectaDireccionTejo= tejo->getRectaDireccion();
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(anguloDeltejo-PI));
	}else{

		if(rectaDeColision->getPendiente()>=0){
			if(CalculosMatematicos::verificarDireccionRectasPositivas(rectaDeColision,rectaDireccionTejo)==-1){

				nuevaDireccion=((anguloDeltejo-PI)+anguloConAbcisa);
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}


			}else{
				nuevaDireccion=((anguloDeltejo-PI)+anguloConAbcisa);
				nuevaDireccion=(PI-nuevaDireccion);
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 2  : "<<(nuevaDireccion*180)/PI<<endl;
				}



			}
		}else{
			if(posicionY<yTejo){
				anguloAux=(anguloDeltejo-PI);
				nuevaDireccion=anguloConAbcisa-anguloAux;
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=anguloDeltejo+2*nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();
				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;
					system("PAUSE");
				}



			}else{
				anguloAux=(anguloDeltejo-PI);
				nuevaDireccion=PI/2-anguloAux;
				nuevaDireccion=PI/2-(anguloConAbcisa+nuevaDireccion);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=anguloDeltejo-2*nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();

				if(DEBUG==1){
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 4  "<<(nuevaDireccion*180)/PI<<endl;
					system("PAUSE");
				}





			}
		}
	}
	delete rectaDireccionTejo;
}
void ControladorColisiones::decidirDireccionCuartoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	double nuevaDireccion;
	int xTejo=tejo->getX(),yTejo=tejo->getY(),radioTejo=tejo->getRadio();
	Recta*  rectaDireccionTejo= tejo->getRectaDireccion();
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(anguloDeltejo-PI));
	}else{
		if(rectaDeColision->getPendiente()<=0){
			if(CalculosMatematicos::verificarDireccionRectasNegativas(rectaDeColision,rectaDireccionTejo)==-1){
				nuevaDireccion=(2*PI-anguloDeltejo)+anguloConAbcisa;
				nuevaDireccion=(anguloDeltejo-PI)-(PI-(2*nuevaDireccion));
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();

				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}

			}else{
				nuevaDireccion=(anguloDeltejo-3*PI/2)+(PI/2-anguloConAbcisa);
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();

				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 2"<<(nuevaDireccion*180)/PI<<endl;
				}

			}
		}else{
			if(posicionY<yTejo){
				nuevaDireccion=anguloConAbcisa-(2*PI-anguloDeltejo);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();

				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y figura :   "<<posicionY<<endl;
					system("PAUSE");
				}
			}else{
				nuevaDireccion=((2*PI-anguloDeltejo)-anguloConAbcisa);
				if(nuevaDireccion<0){
					nuevaDireccion=nuevaDireccion*-1;
				}
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);

				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				tejo->moverTejo();

				if(DEBUG==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 4 "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y :  figura "<<posicionY<<endl;
					system("PAUSE");
				}
			}
		}

	}
	delete rectaDireccionTejo;
}
ControladorColisiones::~ControladorColisiones() {

}
bool ControladorColisiones::verificarExcepciones(Recta* rectaEntreRadios,Tejo* tejo,Circulo* figura){
	bool    condision=false;
	if(rectaEntreRadios->getPendiente()==0){
		condision=true;
		if(tejo->getX()<=figura->getX()){
			if(tejo->getDireccion()->getFi()==0){
				tejo->getDireccion()->setFi(PI);
			}


		}
		else{
			if(tejo->getDireccion()->getFi()==PI){
				tejo->getDireccion()->setFi(0);
			}
		}
	}
	if(rectaEntreRadios->getInfinito()==-1){
		condision=true;
		if(tejo->getY()<=figura->getY()){
			tejo->getDireccion()->setFi(PI/3);
		}
		else{
			tejo->getDireccion()->setFi(4*PI/3);
		}
	}
	return condision;
}
void sacarDelAmbitoDelCirculo(Tejo* tejo,Circulo* figura){
	int distanciaMinimaEntreRadios=tejo->getRadio()+figura->getRadio();
	int distanciaEntreRadios=CalculosMatematicos::calcularDistancia(tejo->getX(),tejo->getY(),figura->getX(),figura->getY());
	if(distanciaMinimaEntreRadios>=distanciaEntreRadios){
		while(distanciaMinimaEntreRadios>=distanciaEntreRadios){
			tejo->moverTejo();
			distanciaEntreRadios=CalculosMatematicos::calcularDistancia(tejo->getX(),tejo->getY(),figura->getX(),figura->getY());
			if(DEBUG==1){
				std::cout<<"distanciaMinimaEntreRadios   :"<<distanciaMinimaEntreRadios<<endl;
				std::cout<<"distanciaEntreRadios  :"<<distanciaEntreRadios<<endl;
			}
		}
	}
}
void ControladorColisiones::colisionCirculo(Tejo* tejo,Circulo* figura){
	int xTejo=tejo->getX(),yTejo=tejo->getY(),xCirculo=figura->getX(),yCirculo=figura->getY();
	double anguloDeltejo=tejo->getDireccion()->getFi();
	Posicion* pos = CalculosMatematicos::getInterseccionEsferas(tejo,figura);//punto de interseccion entre esferas
	Recta* rectaEntreRadios=new Recta(xTejo,xCirculo,yTejo,yCirculo);//recta entre los centros de las esferas;
	Recta*  rectaDeColision=rectaEntreRadios->getRectaPerpendicular(pos->getX(),pos->getY());//recta perpendicular en punto de interseccion


	int distanciaMinimaEntreRadios=tejo->getRadio()+figura->getRadio();
	int distanciaEntreRadios=CalculosMatematicos::calcularDistancia(tejo->getX(),tejo->getY(),figura->getX(),figura->getY());
	if(DEBUG==1){
		std::cout<<"distanciaMinimaEntreRadios   :"<<distanciaMinimaEntreRadios<<endl;
		std::cout<<"distanciaEntreRadios  :"<<distanciaEntreRadios<<"  -- "<<endl;
	}
	if(distanciaMinimaEntreRadios>=distanciaEntreRadios){

		if(figura->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);

		}
		if(!verificarExcepciones(rectaEntreRadios,tejo,figura)){
			if(DEBUG==1){
				std::cout<<"rectaEntreRadios";
				rectaEntreRadios->toString();
				std::cout<<"rectaDeColision";
				rectaDeColision->toString();
			}

			if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
				decidirDireccionCuartoCuadrante(rectaDeColision,tejo,yCirculo);

			}
			if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
				decidirDireccionTercerCuadrante(rectaDeColision,tejo,yCirculo);
			}
			if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
				decidirDireccionSegundoCuadrante(rectaDeColision,tejo,yCirculo);
			}
			if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){
				decidirDireccionPrimerCuadrante(rectaDeColision,tejo,yCirculo);
			}
		}
	}
	sacarDelAmbitoDelCirculo(tejo,figura);
	delete rectaEntreRadios;
	delete rectaDeColision;
	delete pos;
}

bool ControladorColisiones::posibilidadDeColisionDispersores(){
	bool posibilidadColision= false;
	Figura *figura;
	Tejo *tejo = Escenario::obtenerInstancia()->getTejo();
	std::list<Figura*>::iterator iter;
	iter = Escenario::obtenerInstancia()->iteratorListaFiguras();

	int wTejo, hTejo, wFigura, hFigura, xTejo, yTejo, xFigura, yFigura,xAnteriorTejo,yAnteriorTejo;
	wTejo = hTejo = tejo->getRadio()*2;
	xTejo = tejo->getX()-tejo->getRadio();
	yTejo = tejo->getY()-tejo->getRadio();
	xAnteriorTejo=tejo->getXAnterior()-tejo->getRadio();
	yAnteriorTejo=tejo->getYAnterior()-tejo->getRadio();

	int i=1;

	while(i <= Escenario::obtenerInstancia()->sizeListaFiguras()){
		figura=*iter;
		wFigura = figura->getAnchoInfluencia();
		hFigura = figura->getAltoInfluencia();
		xFigura = figura->getXInfluencia();
		yFigura = figura->getYInfluencia();


		if(!(tejo->getChoco())&&((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){

			if(figura->getTipo().compare(RECTANGULO)==0){
				ControladorColisiones::colisionRectangulo(  (Rectangulo*)figura,tejo);
			}
			if(figura->getTipo().compare(CIRCULO)==0){
				ControladorColisiones::colisionCirculo( tejo, (Circulo*)figura);

			}
			if(figura->getTipo().compare(CUADRADO)==0){
				ControladorColisiones::colisionCuadrado(  (Cuadrado*)figura,tejo);
			}
			if(figura->getTipo().compare(TRIANGULO)==0){
				ControladorColisiones::colisionTriangulo(  (Triangulo*)figura,tejo);
			}
			tejo->setChoco(true);
			return true;
		}else{
			tejo->setChoco(false);

		}
		i++;
		iter++;
	}



	return posibilidadColision;
}
double ControladorColisiones::hallarDistancia(Recta* recta, int x, int y){

	double rectaEvaluada;

	if (recta->getInfinito() == -1)
		return (abs(recta->getOrdenada()-x));
	rectaEvaluada = abs(recta->getPendiente()*x + recta->getOrdenada() - y);
	return (rectaEvaluada /sqrt(pow(recta->getPendiente(),2)+1));


}


void sacarDelAmbitoDelTriangulo(Tejo* tejo,Triangulo* figura){
	int wTejo, hTejo, wFigura, hFigura, xTejo, yTejo, xFigura, yFigura;
	wTejo = hTejo = tejo->getRadio()*2;
	xTejo = tejo->getX()-tejo->getRadio();
	yTejo = tejo->getY()-tejo->getRadio();
	   wFigura = figura->getAnchoInfluencia();
		hFigura = figura->getAltoInfluencia();
		xFigura = figura->getXInfluencia();
		yFigura = figura->getYInfluencia();
		while(((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){
			tejo->moverTejo();
			wTejo = hTejo = tejo->getRadio()*2;
			xTejo = tejo->getX()-tejo->getRadio();
			yTejo = tejo->getY()-tejo->getRadio();

		}
	}
void asignarDireccionTrianguloConPendienteInfinito(Tejo* tejo,Recta* recta,Triangulo* triangulo){
if (tejo->getY()>=triangulo->getYInfluencia()&&
		tejo->getY()<=(triangulo->getYInfluencia()+triangulo->getAltoInfluencia())){
	if (recta->getOrdenada() > tejo->getX()){
		reboteDerecha(tejo);
		std::cout<<"DERECHA"<<endl;
	}
	else{
		reboteIzquierda(tejo);
		std::cout<<"IZQUIERDA"<<endl;
	}
}
}
void asignarDireccionTrianguloConPendienteCero(Tejo* tejo,Recta* recta){
if (recta->getOrdenada() > tejo->getY()){
	reboteAbajo(tejo);
	std::cout<<"ABAJO"<<endl;
}
else{
	reboteArriba(tejo);
	std::cout<<"ARRIBA"<<endl;
}
}
void ControladorColisiones::asignarDireccionTrianguloConPendiente(Tejo* tejo,Recta* recta,Triangulo* triangulo){
	double anguloDeltejo = tejo->getDireccion()->getFi();
	if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
		decidirDireccionCuartoCuadrante(recta,tejo,0);
		 sacarDelAmbitoDelTriangulo(tejo, triangulo);
	}else
		if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
			decidirDireccionTercerCuadrante(recta,tejo,0);
			 sacarDelAmbitoDelTriangulo(tejo, triangulo);
		}else
			if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
				decidirDireccionSegundoCuadrante(recta,tejo,0);
				 sacarDelAmbitoDelTriangulo(tejo, triangulo);
			}else
				if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){
					decidirDireccionPrimerCuadrante(recta,tejo,0);
					 sacarDelAmbitoDelTriangulo(tejo, triangulo);
				}

}
Posicion* ControladorColisiones::hallarPuntoTriangulo(Recta* recta, int x, int y){

	Recta aux;
	int xAux, yAux;

	aux.setPendiente(-1/recta->getPendiente());
	aux.setOrdenada(y - (x*aux.getPendiente()));

	xAux = (aux.getOrdenada()-recta->getOrdenada())/(recta->getPendiente()-aux.getPendiente());
	yAux = aux.getPendiente()*xAux+aux.getOrdenada();
	return new Posicion(xAux,yAux);


}
bool  ControladorColisiones::isPuntoZonaDeInfluenciaTejo(Posicion* posicion,Tejo* tejo ){
	bool fueraDeZonaInfluencia;

	int wFigura, hFigura, xFigura, yFigura;
			wFigura = tejo->getRadio()*2-tejo->getRadio()*2*0.1;
			hFigura = tejo->getRadio()*2-tejo->getRadio()*2*0.1;
			xFigura = tejo->getX()-tejo->getRadio();
			yFigura = tejo->getY()-tejo->getRadio();
			if(DEBUG==1){
			std::cout << "x  " << posicion->getX()<<"y " << posicion->getX()<<endl;
			std::cout << "wFigura  " << wFigura<<"hFigura   " << hFigura<<endl;
			std::cout << "xFigura  " << xFigura<<"yFigura   " << yFigura<<endl;
			}
			if((posicion->getX() >= xFigura) && (posicion->getY()>= yFigura) && ((xFigura + wFigura) >= posicion->getX()) && ((yFigura + hFigura) >= posicion->getY())){
				fueraDeZonaInfluencia=true;
			}
			else{
				fueraDeZonaInfluencia = false;
			}
			return fueraDeZonaInfluencia;

}
bool  ControladorColisiones::getZonaDeInfluencia(Recta* rectaDireccionTejo,Recta*recta,Triangulo* triangulo,Tejo*tejo ){
	bool fueraDeZonaInfluencia;
	//si la colision se da fuera de la zona de infl. no se evalua

//	Posicion* posicion = rectaDireccionTejo->getInterseccion(recta);
	Posicion* posicion = hallarPuntoTriangulo(recta,tejo->getX(),tejo->getY());
	std::cout<<"punto del triangulo"<<posicion->getX()<<"-:"<<posicion->getY()<<endl;
		if (posicion->getX()< triangulo->getXInfluencia()
				|| posicion->getY()< triangulo->getYInfluencia()
				|| posicion->getX()>(triangulo->getXInfluencia()+triangulo->getAnchoInfluencia())
				|| posicion->getY()>(triangulo->getYInfluencia()+triangulo->getAltoInfluencia()))
			fueraDeZonaInfluencia = true;
		else
			fueraDeZonaInfluencia = false;
		delete posicion;
return fueraDeZonaInfluencia;
}
bool ControladorColisiones::isPuntoZonaDeInfluenciaTriangulo(Posicion* posicion,Triangulo* triangulo ){
	bool fueraDeZonaInfluencia=false;

          if(DEBUG==1)
            std::cout<<"interseccion     punto x "<<posicion->getX()<<"punto y  "<<posicion->getY()<<endl;
	int wFigura, hFigura, xFigura, yFigura;
			wFigura = triangulo->getAnchoInfluencia();
			hFigura = triangulo->getAltoInfluencia();
			xFigura = triangulo->getXInfluencia();
			yFigura = triangulo->getYInfluencia();


			if((posicion->getX() >= xFigura) && (posicion->getY()>= yFigura) && ((xFigura + wFigura) >= posicion->getX()) && ((yFigura + hFigura) >= posicion->getY())){
				fueraDeZonaInfluencia=true;
			}
			else{
				fueraDeZonaInfluencia = false;
				}

			return fueraDeZonaInfluencia;


}

void ControladorColisiones::asignarDireccionTriangulo(Tejo* tejo,Recta* recta,Triangulo* triangulo){

	//analisis con recta paralela al eje Y
	if (recta->getInfinito() == -1){
		asignarDireccionTrianguloConPendienteInfinito(tejo,recta,triangulo);
		if(triangulo->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);
		}
	}
	else{
			if (recta->getPendiente() == 0){
				asignarDireccionTrianguloConPendienteCero(tejo,recta);
				if(triangulo->getTieneBonus()){
					tejo->setChocoFiguraConBonus(true);
				}
			}
			else{

				asignarDireccionTrianguloConPendiente(tejo,recta,triangulo);
				if(triangulo->getTieneBonus()){
					tejo->setChocoFiguraConBonus(true);
				}



		}
	}

}
Recta* ControladorColisiones::getRectaDeColision(Triangulo* triangulo,Tejo* tejo){
	Recta* recta=NULL; //Recta con la que estoy mas cerca
	Recta* recta1=triangulo->getRecta1();
	Recta* recta2=triangulo->getRecta2();
	Recta* recta3=triangulo->getRecta3();
	Recta*  rectaDireccionTejo=tejo->getRectaDireccion();
	if(DEBUG==1){
				recta3->toString();
				recta2->toString();
				recta1->toString();
				rectaDireccionTejo->toString();
			}


	Posicion* posicion1=rectaDireccionTejo->getInterseccion(recta1);
	Posicion* posicion2=rectaDireccionTejo->getInterseccion(recta2);
	Posicion* posicion3=rectaDireccionTejo->getInterseccion(recta3);
	if(DEBUG==1){
		 if(posicion1!=NULL)
		std::cout<<"posicion1 X "<<posicion1->getX()<<" y: "<<posicion1->getX()<<endl;
		 if(posicion2!=NULL)
		std::cout<<"posicion2 X "<<posicion2->getX()<<" y: "<<posicion2->getX()<<endl;
		 if(posicion3!=NULL)
		std::cout<<"posicion3 X "<<posicion3->getX()<<" y: "<<posicion3->getX()<<endl;

	}

	double d_r1 = hallarDistancia(recta1, tejo->getX(),tejo->getY());
	double d_r2 = hallarDistancia(recta2, tejo->getX(),tejo->getY());
	double d_r3 = hallarDistancia(recta3, tejo->getX(),tejo->getY());

	if(isPuntoZonaDeInfluenciaTriangulo(posicion1,triangulo)){
		if (d_r1 < d_r2 && d_r1 < d_r3){
			if(DEBUG==1){
				recta1->toString();
				std::cout<<"posicion1 X "<<posicion1->getX()<<" y: "<<posicion1->getX()<<" distancia "<<d_r1<<endl;
			}
			recta1->setDistancia(d_r1);
			delete posicion1;
			delete posicion2;
			delete posicion3;
			delete rectaDireccionTejo;
			return recta1;
		}
	}
	if(isPuntoZonaDeInfluenciaTriangulo(posicion2,triangulo)){
		if (d_r2 < d_r1 && d_r2 < d_r3){
			if(DEBUG==1){
				recta2->toString();
				std::cout<<"posicion1 X "<<posicion2->getX()<<" y: "<<posicion2->getX()<<" distancia "<<d_r2<<endl;
				system("PAUSE");
			}
			recta1->setDistancia(d_r2);
			delete posicion1;
			delete posicion2;
			delete posicion3;
			delete rectaDireccionTejo;
			return recta2;
		}
	}
	if(isPuntoZonaDeInfluenciaTriangulo(posicion3,triangulo)){
		if (d_r3 < d_r1 && d_r3 < d_r2){
			if(DEBUG==1){
				recta3->toString();
				std::cout<<"posicion1 X "<<posicion3->getX()<<" y: "<<posicion3->getX()<<" distancia "<<d_r3<<endl;
				system("PAUSE");
			}
			recta1->setDistancia(d_r3);
			delete posicion1;
			delete posicion2;
			delete posicion3;
			delete rectaDireccionTejo;
			return recta3;
		}
	}

	             delete posicion1;
				delete posicion2;
				delete posicion3;
				delete rectaDireccionTejo;
				return NULL;
}
void ControladorColisiones::colisionTriangulo(Triangulo* triangulo,Tejo* tejo){


	double anguloDeltejo = tejo->getDireccion()->getFi();
	int radioTejo = tejo->getRadio();
	int xTejo=tejo->getX();
	int yTejo=tejo->getY();
	bool fueraDeZonaInfluencia = false;
	bool colisionVertice = false;
	Recta*  rectaDireccionTejo=tejo->getRectaDireccion();

	//Recta* rectaDireccionTejoArriba= new Recta(xTejo,(int)(radioTejo*cos(anguloDelTejo));
	//	Recta* rectaDireccionTejoAbajo = rectaDireccionTejo->getRectaPerpendicular(xTejo,yTejo);

	Recta* recta1=triangulo->getRecta1();
	Recta* recta2=triangulo->getRecta2();
	Recta* recta3=triangulo->getRecta3();
	if(DEBUG==1){
		recta3->toString();
		recta2->toString();
		recta1->toString();
		rectaDireccionTejo->toString();
	}
	Recta* recta=recta3; //Recta con la que estoy mas cerca
	Recta* rectaColision=NULL;
	//Hallo las distancias de la posicion del tejo con respecto a las rectas del triangulo
	double d_r1 = hallarDistancia(recta1, tejo->getX(),tejo->getY());
	double d_r2 = hallarDistancia(recta2, tejo->getX(),tejo->getY());
	double d_r3 = hallarDistancia(recta3, tejo->getX(),tejo->getY());
	double dMenor;
	int numeroRecta=0;

	if (d_r1 < radioTejo && d_r2 < radioTejo && d_r1 < d_r3){
		colisionVertice = true;
		dMenor = d_r1;
		recta = recta1;
	}
	else{
		if(d_r1 < radioTejo && d_r3 < radioTejo && d_r1 < d_r2){
			colisionVertice = true;
			dMenor = d_r1;
			recta = recta1;
		}
		else{
			if (d_r2 < radioTejo && d_r3 < radioTejo && d_r2 < d_r1){
				colisionVertice = true;
				dMenor = d_r2;
				recta = recta2;
			}
			else{
				if (d_r1 < d_r2){
					if (d_r1 < d_r3){
						recta = recta1;
						dMenor = d_r1;
						numeroRecta=1;
					}
					else{
						recta = recta3;
						dMenor = d_r3;
						numeroRecta=3;
					}
				}
				else{
					if (d_r2 < d_r3){
						recta = recta2;
						dMenor = d_r2;
						numeroRecta=2;
					}
					else{
						recta = recta3;
						dMenor = d_r3;
						numeroRecta=3;
					}
				}
			}
		}
	}

	Posicion* posicion2 = rectaDireccionTejo->getInterseccion(recta);
	if(!isPuntoZonaDeInfluenciaTriangulo(posicion2,triangulo)&&posicion2!=NULL&&recta->getInfinito()!=-1&&recta->getPendiente()!=0){
		if(DEBUG==1){
		std::cout<<"entra con esta recta :";
		recta->toString();
		std::cout<<"distancia con recta :"<<dMenor<<endl;
		}
		if(numeroRecta==1){
			if (d_r2 < d_r3){
				recta = recta2;
				dMenor = d_r2;
			}else{
				recta = recta3;
				dMenor = d_r3;
			}
		}else{
			if(numeroRecta==2){

				if (d_r1 < d_r3){
					recta = recta1;
					dMenor = d_r1;

				}
				else{
					recta = recta3;
					dMenor = d_r3;

				}

			}else{
				if(numeroRecta==3){
					if (d_r1 < d_r2){

						recta = recta1;
						dMenor = d_r1;

					}
					else{
						recta = recta3;
						dMenor = d_r3;

					}
				}

			}
		}
		if(DEBUG==1){
		std::cout<<"sale con esta recta :";
				recta->toString();
				std::cout<<"distancia con recta :"<<dMenor<<endl;
				system("PAUSE");
		}
	}

	if(dMenor<=radioTejo){
		if(DEBUG==1){
		std::cout<<"if(dMenor<=radioTejo){  :"<<endl;
					system("PAUSE");
		}
		//analisis colision con vertices, totalmente arbitrario el angulo de salida
		if (colisionVertice){
			bool puntoTriangulo=true;

			Posicion* posicion3 = rectaDireccionTejo->getInterseccion(recta);
			if(isPuntoZonaDeInfluenciaTriangulo(posicion3,triangulo)){
				puntoTriangulo=true;
			}

			if(DEBUG==1){
				std::cout<<"colisionVertice  :"<<puntoTriangulo<<endl;
				system("PAUSE");
			}

			if(isPuntoZonaDeInfluenciaTejo(triangulo->getVertice1(),tejo)){
				if(DEBUG==1){
					std::cout << "getVertice1  " << endl;
					system("PAUSE");
				}
				if(triangulo->getTieneBonus()){
					tejo->setChocoFiguraConBonus(true);
				}
				if(puntoTriangulo){
					tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(anguloDeltejo+PI));
					sacarDelAmbitoDelTriangulo(tejo,triangulo);
				}
			}else{
				if(isPuntoZonaDeInfluenciaTejo(triangulo->getVertice2(),tejo)){
					if(DEBUG==1){
						std::cout << "getVertice2  " << endl;
						system("PAUSE");
					}
					if(triangulo->getTieneBonus()){
						tejo->setChocoFiguraConBonus(true);
					}
					if(puntoTriangulo){
						tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(anguloDeltejo+PI));
						sacarDelAmbitoDelTriangulo(tejo,triangulo);
					}
				}else{
					if(isPuntoZonaDeInfluenciaTejo(triangulo->getVertice3(),tejo)){

						if(puntoTriangulo){
							tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(anguloDeltejo+PI));
							sacarDelAmbitoDelTriangulo(tejo,triangulo);
						}		if(DEBUG==1){
							std::cout << "getVertice3  " << endl;
							system("PAUSE");
						}
						if(triangulo->getTieneBonus()){
							tejo->setChocoFiguraConBonus(true);
						}
					}
				}
			}

		}
		else{
			if(DEBUG==1){
						std::cout<<"recta de colision :";
						recta->toString();
						std::cout<<"distancia con recta :"<<dMenor<<endl;
						system("PAUSE");
					}
			//analisis con recta paralela al eje Y
			if (recta->getInfinito() == -1){
				if(triangulo->getTieneBonus()){
					tejo->setChocoFiguraConBonus(true);
				}

				if (tejo->getY()>=triangulo->getYInfluencia()&&
						tejo->getY()<=(triangulo->getYInfluencia()+triangulo->getAltoInfluencia())){
					if (recta->getOrdenada() > tejo->getX()){
						reboteDerecha(tejo);
						std::cout<<"DERECHA"<<endl;
					}
					else{
						reboteIzquierda(tejo);
						std::cout<<"IZQUIERDA"<<endl;
					}
				}
			}
			else{
				//analisis resto de las rectas posibles
				Posicion* posicion = rectaDireccionTejo->getInterseccion(recta);
//				Posicion* posicion = hallarPuntoTriangulo(recta,tejo->getX(),tejo->getY());
//					if(getZonaDeInfluencia(rectaDireccionTejo,recta,triangulo,tejo)&&posicion!=NULL){
				if(isPuntoZonaDeInfluenciaTriangulo(posicion,triangulo)&&posicion!=NULL){
				if (recta->getPendiente() == 0){
					if(triangulo->getTieneBonus()){
						tejo->setChocoFiguraConBonus(true);
					}

						if (recta->getOrdenada() > tejo->getY()){
							reboteAbajo(tejo);
							std::cout<<"ABAJO"<<endl;
						}
						else{
							reboteArriba(tejo);
							std::cout<<"ARRIBA"<<endl;
						}
					}
					else{

						if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
							decidirDireccionCuartoCuadrante(recta,tejo,0);
						}else
							if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
								decidirDireccionTercerCuadrante(recta,tejo,0);
							}else
								if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
									decidirDireccionSegundoCuadrante(recta,tejo,0);
								}else
									if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){
										decidirDireccionPrimerCuadrante(recta,tejo,0);
									}
						if(triangulo->getTieneBonus()){
							tejo->setChocoFiguraConBonus(true);
						}

					}
				}
				delete posicion;
			}
		}
	}
	delete rectaDireccionTejo;


}
void ControladorColisiones::colisionCuadrado(Cuadrado* cuadrado,Tejo* tejo){
	int wTejo, hTejo, wFigura, hFigura, xTejo, yTejo, xFigura, yFigura,xAnteriorTejo,yAnteriorTejo,radioTejo;
	wTejo = hTejo = tejo->getRadio()*2;
	xTejo = tejo->getX()-tejo->getRadio();
	yTejo= tejo->getY()-tejo->getRadio();
	radioTejo=tejo->getRadio();
	double anguloDeltejo=tejo->getDireccion()->getFi();
	xAnteriorTejo=tejo->getXAnterior()-tejo->getRadio();
	yAnteriorTejo=tejo->getYAnterior()-tejo->getRadio();
	wFigura= cuadrado->getLado();
	hFigura=cuadrado->getLado();
	xFigura= cuadrado->getX();
	yFigura= cuadrado->getY();
	if( ((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){
		if(cuadrado->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);
		}
		if(xAnteriorTejo<=xFigura&&yAnteriorTejo<yFigura+hFigura&&yAnteriorTejo>yFigura-wTejo){
			if(yTejo>yFigura+hFigura){

				if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
					tejo->getDireccion()->setFi(5*PI/4);
				}else{
					tejo->getDireccion()->setFi(3*PI/4);
				}

			}else{
				if(yTejo<yFigura-radioTejo){

					if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
						tejo->getDireccion()->setFi(5*PI/4);
					}else{
						tejo->getDireccion()->setFi(3*PI/4);
					}

				}else{

					reboteDerecha(tejo);
				}
			}


		}else{

			if(yAnteriorTejo<=yFigura&&xAnteriorTejo+wTejo>xFigura&&xAnteriorTejo<xFigura+wFigura){
				reboteAbajo(tejo);
			}else{

				if(yAnteriorTejo>=yFigura+hFigura&&xFigura<xAnteriorTejo+wTejo&&xAnteriorTejo<xFigura+wFigura){
					reboteArriba(tejo);
				}
			}

		}

		if(xAnteriorTejo>=xFigura+wFigura&&yAnteriorTejo<yFigura+hFigura+hTejo&&yAnteriorTejo>yFigura-hTejo){
			if(yTejo<yFigura-radioTejo){

				if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
					tejo->getDireccion()->setFi(PI/4);
				}else{
					tejo->getDireccion()->setFi(3*PI/4);
				}
			}else{

				if(yTejo>yFigura+hFigura+radioTejo){
					if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
						tejo->getDireccion()->setFi(PI/4);
					}else{
						tejo->getDireccion()->setFi(5*PI/4);
					}

				}else{

					reboteIzquierda(tejo);
				}
			}

		}


	}
}
void ControladorColisiones::colisionRectangulo(Rectangulo* rectangulo,Tejo* tejo){
	int wTejo, hTejo, wFigura, hFigura, xTejo, yTejo, xFigura, yFigura,xAnteriorTejo,yAnteriorTejo,radioTejo;
	wTejo = hTejo = tejo->getRadio()*2;
	xTejo = tejo->getX()-tejo->getRadio();
	yTejo= tejo->getY()-tejo->getRadio();
	radioTejo=tejo->getRadio();
	double anguloDeltejo=tejo->getDireccion()->getFi();
	xAnteriorTejo=tejo->getXAnterior()-tejo->getRadio();
	yAnteriorTejo=tejo->getYAnterior()-tejo->getRadio();
	wFigura= rectangulo->getBase();
	hFigura=rectangulo->getAltura();
	xFigura= rectangulo->getX();
	yFigura= rectangulo->getY();
	if( ((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){
		if(rectangulo->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);

		}
		if(xAnteriorTejo<=xFigura&&yAnteriorTejo<yFigura+hFigura&&yAnteriorTejo>yFigura-wTejo){
			if(yTejo>yFigura+hFigura){

				if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
					tejo->getDireccion()->setFi(5*PI/4);
				}else{
					tejo->getDireccion()->setFi(3*PI/4);
				}

			}else{
				if(yTejo<yFigura-radioTejo){

					if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
						tejo->getDireccion()->setFi(5*PI/4);
					}else{
						tejo->getDireccion()->setFi(3*PI/4);
					}

				}else{

					reboteDerecha(tejo);
				}
			}


		}else{

			if(yAnteriorTejo<=yFigura&&xAnteriorTejo+wTejo>xFigura&&xAnteriorTejo<xFigura+wFigura){
				reboteAbajo(tejo);
			}else{

				if(yAnteriorTejo>=yFigura+hFigura&&xFigura<xAnteriorTejo+wTejo&&xAnteriorTejo<xFigura+wFigura){
					reboteArriba(tejo);
				}
			}

		}

		if(xAnteriorTejo>=xFigura+wFigura&&yAnteriorTejo<yFigura+hFigura+hTejo&&yAnteriorTejo>yFigura-hTejo){
			if(yTejo<yFigura-radioTejo){

				if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
					tejo->getDireccion()->setFi(PI/4);
				}else{
					tejo->getDireccion()->setFi(3*PI/4);
				}
			}else{

				if(yTejo>yFigura+hFigura+radioTejo){
					if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
						tejo->getDireccion()->setFi(PI/4);
					}else{
						tejo->getDireccion()->setFi(5*PI/4);
					}

				}else{

					reboteIzquierda(tejo);
				}
			}

		}

		if(rectangulo->getTipo().compare(PAD_DERECHA)==0){
			tejo->setUltimaColisionPad(PAD_CLIENTE1);
			if(tejo->getPegajoso()){
				if(tejo->getPadPegajoso().compare(PAD_CLIENTE1) == 0){
					tejo->setMover(false);
				}
			}
		}
		else if(rectangulo->getTipo().compare(PAD_IZQUIERDA)==0){
			tejo->setUltimaColisionPad(PAD_CLIENTE2);
			if(tejo->getPegajoso()){
				if(tejo->getPadPegajoso().compare(PAD_CLIENTE2) == 0){
					tejo->setMover(false);
				}

			}
		}


	}
}

void ControladorColisiones::colisionesPads(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Tejo* tejo = escenario->getTejo();
	Pad* padIzquierda=escenario->getPadCliente2();
	Pad* padDerecha=escenario->getPadCliente1();


	ControladorColisiones::colisionRectangulo(padIzquierda->getFigura(),tejo);
	ControladorColisiones::colisionRectangulo(padDerecha->getFigura(),tejo);
}
int ControladorColisiones::colisionesArcos(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Tejo* tejo = escenario->getTejo();
	Pad* pad1 = escenario->getPadCliente1();
	Pad* pad2 = escenario->getPadCliente2();
	Rectangulo* arcoDerecha = escenario->getArcoDerecha();
	Rectangulo* arcoIzquierda = escenario->getArcoIzquierda();

	if(arcoIzquierda->getY()+tejo->getRadio()<=tejo->getY()&&arcoIzquierda->getY()+arcoIzquierda->getAltura()-tejo->getRadio()>=tejo->getY()&&
			tejo->getX()<tejo->getRadio()*4){
		if(tejo->getX() <=arcoIzquierda->getBase()+ arcoIzquierda->getX()+tejo->getRadio()){
			//			std::cout<<"  GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<endl;
			//se incrementan los puntos del jugador 1 y su cantidad de goles en el nivel
			pad1->getPuntaje()->setCantPuntosJugador(pad1->getPuntaje()->getCantPuntosJugador()+PUNTAJE_GOL);
			escenario->getPadCliente1()->setCantGoles(escenario->getPadCliente1()->getCantGoles()+1);
			escenario->setGolDe("PAD1");
			return 0;
		}
	}
	if(arcoDerecha->getY()+tejo->getRadio()<=tejo->getY()&&arcoDerecha->getY()+arcoDerecha->getAltura()-tejo->getRadio()>=tejo->getY()&&
			tejo->getX()>escenario->getAncho()-tejo->getRadio()*4){
		if(tejo->getX() >= arcoDerecha->getX()- tejo->getRadio()){
			//			std::cout<<"  GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<endl;
			//se incrementan los puntos del jugador 2 y su cantidad de goles en el nivel
			pad2->getPuntaje()->setCantPuntosJugador(pad2->getPuntaje()->getCantPuntosJugador()+PUNTAJE_GOL);
			escenario->getPadCliente2()->setCantGoles(escenario->getPadCliente2()->getCantGoles()+1);
			escenario->setGolDe("PAD2");
			return 0;
		}
	}
	return -1;
}
void ControladorColisiones::calcularDireccion(){
	Escenario* escenario = Escenario::obtenerInstancia();
	Tejo* tejo = escenario->getTejo();
	if(tejo->getY() <=tejo->getRadio()){
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

