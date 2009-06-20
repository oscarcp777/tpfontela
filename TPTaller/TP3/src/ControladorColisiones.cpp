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
ControladorColisiones::ControladorColisiones() {
	// TODO Auto-generated constructor stub

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
	Recta*  rectaDireccionTejo= new Recta(xTejo,(int)(radioTejo*cos(anguloDeltejo)),yTejo,(int)(radioTejo*sin(anguloDeltejo)));
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(anguloDeltejo-PI);
	}else{

		if(rectaDeColision->getPendiente()>=0){
			if(CalculosMatematicos::verificarDireccionRectasPositivas(rectaDeColision,rectaDireccionTejo)==-1){
				nuevaDireccion=PI-((anguloDeltejo)+(anguloConAbcisa));
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion PrimerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				tejo->getDireccion()->setFi(nuevaDireccion);
			}else{

				nuevaDireccion=((anguloDeltejo)+(anguloConAbcisa));
				nuevaDireccion=PI-(2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion PrimerCuadrante 2  :"<<(nuevaDireccion*180)/PI<<endl;
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
			    tejo->setY(tejo->getY()+5);
				tejo->getDireccion()->setFi(nuevaDireccion);
			}
		}else{
			if(posicionY<yTejo){
				nuevaDireccion=PI-((PI-anguloDeltejo)+anguloConAbcisa);
				nuevaDireccion=(PI-2*nuevaDireccion);
				nuevaDireccion=(PI+anguloDeltejo)+nuevaDireccion;
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				tejo->setX(tejo->getXAnterior());
				tejo->setY(tejo->getY()+5);
				tejo->getDireccion()->setFi(nuevaDireccion);
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion  PrimerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;
			}else{
				nuevaDireccion=(anguloConAbcisa-anguloDeltejo);
				nuevaDireccion=(anguloConAbcisa+nuevaDireccion);
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				tejo->getDireccion()->setFi(nuevaDireccion);
				std::cout<<"nuevaDireccion PrimerCuadrante 4"<<nuevaDireccion<<"anguloConAbcisa"<<anguloConAbcisa<<endl;

			}

		}
		//		 delete rectaDireccionTejo;

	}
}
void ControladorColisiones::decidirDireccionSegundoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY){
	double nuevaDireccion;
	double anguloDeltejo=tejo->getDireccion()->getFi();
	int xTejo=tejo->getX(),yTejo=tejo->getY(),radioTejo=tejo->getRadio();
	Recta*  rectaDireccionTejo= new Recta(xTejo,(int)(radioTejo*cos(anguloDeltejo)),yTejo,(int)(radioTejo*sin(anguloDeltejo)));
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(anguloDeltejo-PI);
	}else{

		if(rectaDeColision->getPendiente()<0){
			if(CalculosMatematicos::verificarDireccionRectasNegativas(rectaDeColision,rectaDireccionTejo)==-1){
				nuevaDireccion=PI-(anguloDeltejo);
				nuevaDireccion=(anguloConAbcisa+nuevaDireccion);
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion  SegundoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				tejo->getDireccion()->setFi(nuevaDireccion);
			}else{
				nuevaDireccion=(anguloDeltejo-anguloConAbcisa);
				nuevaDireccion=(PI-2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion  SegundoCuadrante 2 "<<(nuevaDireccion*180)/PI<<endl;
				tejo->setX(tejo->getXAnterior());
				tejo->getDireccion()->setFi(nuevaDireccion);
			}
		}else{
			if(yTejo>posicionY){
			nuevaDireccion=PI/2-((anguloDeltejo-PI/2)+anguloConAbcisa);
			nuevaDireccion=(anguloDeltejo+2*nuevaDireccion+PI/12);
			if(nuevaDireccion>=2*PI){
				nuevaDireccion=nuevaDireccion-2*PI;
			}
			std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
			std::cout<<"nuevaDireccion  SegundoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;

			tejo->getDireccion()->setFi(nuevaDireccion);
			}else{
				nuevaDireccion=(anguloDeltejo-PI/2)-(PI/2-anguloConAbcisa);
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion  SegundoCuadrante 4 "<<(nuevaDireccion*180)/PI<<endl;
				tejo->getDireccion()->setFi(nuevaDireccion);

			}
		}
	}
	//		 delete rectaDireccionTejo;

}
void ControladorColisiones::decidirDireccionTercerCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	double nuevaDireccion,anguloAux;
	int xTejo=tejo->getX(),yTejo=tejo->getY(),radioTejo=tejo->getRadio();
	Recta*  rectaDireccionTejo= new Recta(xTejo,(int)(radioTejo*cos(anguloDeltejo)),yTejo,(int)(radioTejo*sin(anguloDeltejo)));
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(anguloDeltejo-PI);
	}else{

		if(rectaDeColision->getPendiente()>=0){
			if(CalculosMatematicos::verificarDireccionRectasPositivas(rectaDeColision,rectaDireccionTejo)==-1){

				nuevaDireccion=((anguloDeltejo-PI)+anguloConAbcisa);
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion TercerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				tejo->getDireccion()->setFi(nuevaDireccion);
			}else{
				nuevaDireccion=((anguloDeltejo-PI)+anguloConAbcisa);
				nuevaDireccion=(PI-nuevaDireccion);
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion TercerCuadrante 2  : "<<(nuevaDireccion*180)/PI<<endl;
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				tejo->setX(tejo->getXAnterior());
				tejo->setY(tejo->getYAnterior());
				tejo->getDireccion()->setFi(nuevaDireccion);
			}
		}else{
			if(posicionY<yTejo){
			  	anguloAux=(anguloDeltejo-PI);
				nuevaDireccion=anguloConAbcisa-anguloAux;
				nuevaDireccion=anguloDeltejo+2*nuevaDireccion;
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion TercerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;
				if(nuevaDireccion>=2*PI){
								nuevaDireccion=nuevaDireccion-2*PI;
							}
				tejo->setX(tejo->getX()-8);
				tejo->setY(tejo->getY()+8);
				tejo->getDireccion()->setFi(nuevaDireccion);
			}else{
				anguloAux=(anguloDeltejo-PI);
				nuevaDireccion=PI/2-anguloAux;
				nuevaDireccion=PI/2-(anguloConAbcisa+nuevaDireccion);
				nuevaDireccion=anguloDeltejo-2*nuevaDireccion;
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion TercerCuadrante 4  "<<(nuevaDireccion*180)/PI<<endl;
				if(nuevaDireccion>=2*PI){
								nuevaDireccion=nuevaDireccion-2*PI;
							}
				tejo->setX(tejo->getXAnterior());
				tejo->setY(tejo->getY()-5);
				tejo->getDireccion()->setFi(nuevaDireccion);
			}
		}
	}
	//	 delete rectaDireccionTejo;
}
void ControladorColisiones::decidirDireccionCuartoCuadrante(Recta* rectaDeColision,Tejo* tejo,int posicionY){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	  double nuevaDireccion;
	int xTejo=tejo->getX(),yTejo=tejo->getY(),radioTejo=tejo->getRadio();
	Recta*  rectaDireccionTejo= new Recta(xTejo,(int)(radioTejo*cos(anguloDeltejo)),yTejo,(int)(radioTejo*sin(anguloDeltejo)));
	double anguloConAbcisa=rectaDeColision->getAnguloConAbcisa();
	//	verifico si la recta con la que choca es perpendicular
	if(CalculosMatematicos::verificarPerpendicularidad(rectaDeColision,rectaDireccionTejo)){
		tejo->getDireccion()->setFi(anguloDeltejo-PI);
	}else{
		if(rectaDeColision->getPendiente()<=0){
			if(CalculosMatematicos::verificarDireccionRectasNegativas(rectaDeColision,rectaDireccionTejo)==-1){
			 nuevaDireccion=(2*PI-anguloDeltejo)+anguloConAbcisa;
			 nuevaDireccion=(anguloDeltejo-PI)-(PI-(2*nuevaDireccion));
			std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
			std::cout<<"nuevaDireccion CuartoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
			if(nuevaDireccion>=2*PI){
							nuevaDireccion=nuevaDireccion-2*PI;
						}
			tejo->getDireccion()->setFi(nuevaDireccion);
			}else{
				nuevaDireccion=(anguloDeltejo-3*PI/2)+(PI/2-anguloConAbcisa);
			   nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion CuartoCuadrante 2"<<(nuevaDireccion*180)/PI<<endl;
				if(nuevaDireccion>=2*PI){
								nuevaDireccion=nuevaDireccion-2*PI;
							}
				tejo->setX(tejo->getXAnterior());
				tejo->setY(tejo->getYAnterior());
				 tejo->getDireccion()->setFi(nuevaDireccion);
				}
		}else{
			if(posicionY<yTejo){
				nuevaDireccion=PI/2-((anguloDeltejo-3*PI/2)+anguloConAbcisa);
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				if(nuevaDireccion>=2*PI){
					nuevaDireccion=nuevaDireccion-2*PI;
				}
				tejo->getDireccion()->setFi(nuevaDireccion);
				std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
				std::cout<<"nuevaDireccion CuartoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;
			}else{
			nuevaDireccion=PI/2-((anguloDeltejo-3*PI/2)+anguloConAbcisa);
			nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
			if(nuevaDireccion>=2*PI){
				nuevaDireccion=nuevaDireccion-2*PI;
			}
			tejo->setX(tejo->getX()+5);
			tejo->setY(tejo->getY()-8);
			tejo->getDireccion()->setFi(nuevaDireccion);
			std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
			std::cout<<"nuevaDireccion CuartoCuadrante 4 "<<(nuevaDireccion*180)/PI<<endl;}
		}

	}
//	 delete rectaDireccionTejo;
}
ControladorColisiones::~ControladorColisiones() {
	// TODO Auto-generated destructor stub
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
			system("PAUSE");
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
void ControladorColisiones::colisionCirculo(Tejo* tejo,Circulo* figura){
	 int xTejo=tejo->getX(),yTejo=tejo->getY(),xCirculo=figura->getX(),yCirculo=figura->getY();
	 double anguloDeltejo=tejo->getDireccion()->getFi();
	 Posicion* pos = CalculosMatematicos::getInterseccionEsferas(tejo,figura);//punto de interseccion entre esferas
	 Recta* rectaEntreRadios=new Recta(xTejo,xCirculo,yTejo,yCirculo);//recta entre los centros de las esferas;
	 Recta*  rectaDeColision=rectaEntreRadios->getRectaPerpendicular(pos->getX(),pos->getY());//recta perpendicular en punto de interseccion


	int distanciaMinimaEntreRadios=tejo->getRadio()+figura->getRadio();
	int distanciaEntreRadios=CalculosMatematicos::calcularDistancia(tejo->getX(),tejo->getY(),figura->getX(),figura->getY());
	if(distanciaMinimaEntreRadios>distanciaEntreRadios){

		if(!verificarExcepciones(rectaEntreRadios,tejo,figura)){

         std::cout<<"rectaEntreRadios";
         rectaEntreRadios->toString();

         std::cout<<"rectaDeColision";
         rectaDeColision->toString();
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

        //      delete rectaEntreRadios;
       //      delete rectaDeColision;
       //      delete pos;
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
//					std::cout<<"colisiono con : :"<<figura->getId()<<endl;

			if(figura->getTipo().compare(CIRCULO)==0){
				ControladorColisiones::colisionCirculo( tejo, (Circulo*)figura);
			}
			if(figura->getTipo().compare(RECTANGULO)==0){
				ControladorColisiones::colisionRectangulo(  (Rectangulo*)figura,tejo);
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
 void ControladorColisiones::colisionTriangulo(Triangulo* Triangulo,Tejo* tejo){

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
			escenario->getPadCliente1()->setCantGoles(escenario->getPadCliente1()->getCantGoles()+1);

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

