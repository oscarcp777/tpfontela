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
	recta3->toString();
	recta2->toString();
	recta1->toString();
	rectaDireccionTejo->toString();
	Recta* recta=NULL; //Recta con la que estoy mas cerca

	//Hallo las distancias de la posicion del tejo con respecto a las rectas del triangulo
	double d_r1 = hallarDistancia(recta1, tejo->getX(),tejo->getY());
	double d_r2 = hallarDistancia(recta2, tejo->getX(),tejo->getY());
	double d_r3 = hallarDistancia(recta3, tejo->getX(),tejo->getY());
	double dMenor;

	if (d_r1 < radioTejo && d_r2 < radioTejo && d_r1 < d_r3){
		colisionVertice = true;
		dMenor = d_r1;
	}
	else{
		if(d_r1 < radioTejo && d_r3 < radioTejo && d_r1 < d_r2){
			colisionVertice = true;
			dMenor = d_r1;
		}
		else{
			if (d_r2 < radioTejo && d_r3 < radioTejo && d_r2 < d_r1){
				colisionVertice = true;
				dMenor = d_r2;
			}
			else{
				if (d_r1 < d_r2){
					if (d_r1 < d_r3){
						recta = recta1;
						dMenor = d_r1;
					}
					else{
						recta = recta3;
						dMenor = d_r3;
					}
				}
				else{
					if (d_r2 < d_r3){
						recta = recta2;
						dMenor = d_r2;
					}
					else{
						recta = recta3;
						dMenor = d_r3;
					}
				}
			}
		}
	}



	if(dMenor<=radioTejo){
		//analisis colision con vertices, totalmente arbitrario el angulo de salida
		if (colisionVertice){
		 	if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
					tejo->getDireccion()->setFi(anguloDeltejo-PI);
			}else
				if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
					tejo->getDireccion()->setFi(anguloDeltejo-PI);
				}else
					if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
						tejo->getDireccion()->setFi(anguloDeltejo+PI);
					}else
						if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){
							tejo->getDireccion()->setFi(anguloDeltejo+PI);
						}
		}
		else{
			//analisis con recta paralela al eje Y
			if (recta->getInfinito() == -1){
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
				if (posicion->getX()< triangulo->getXInfluencia()
						|| posicion->getY()< triangulo->getYInfluencia()
						|| posicion->getX()>(triangulo->getXInfluencia()+triangulo->getAnchoInfluencia())
						|| posicion->getY()>(triangulo->getYInfluencia()+triangulo->getAltoInfluencia()))
					fueraDeZonaInfluencia = true; //si la colision se da fuera de la zona de infl. no se evalua
				if (!fueraDeZonaInfluencia){
					if (recta->getPendiente() == 0){
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
					}
				}
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
	double anguloDeltejo=tejo->getDireccion()->getFi();
	radioTejo=tejo->getRadio();
	xAnteriorTejo=tejo->getXAnterior()-tejo->getRadio();
	yAnteriorTejo=tejo->getYAnterior()-tejo->getRadio();
	wFigura= cuadrado->getLado();
	hFigura=cuadrado->getLado();
	xFigura= cuadrado->getX();
	yFigura= cuadrado->getY();
	if( ((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){

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

			return 0;
		}
	}
	if(arcoDerecha->getY()+tejo->getRadio()<=tejo->getY()&&arcoDerecha->getY()+arcoDerecha->getAltura()-tejo->getRadio()>=tejo->getY()&&
			tejo->getX()>escenario->getAncho()-tejo->getRadio()*4){
		if(tejo->getX() >= arcoDerecha->getX()- tejo->getRadio()){
			//			std::cout<<"  GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<endl;
			//se incrementan los puntos del jugador 2 y su cantidad de goles en el nivel
			pad2->getPuntaje()->setCantPuntosJugador(pad2->getPuntaje()->getCantPuntosJugador()+PUNTAJE_GOL);


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

