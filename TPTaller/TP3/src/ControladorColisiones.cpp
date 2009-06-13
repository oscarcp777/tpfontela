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
#include "Juego.h"
ControladorColisiones::ControladorColisiones() {
	// TODO Auto-generated constructor stub

}

void reboteArriba(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==PI/2){
		tejo->getDireccion()->setFi(anguloDeltejo+(PI));
	}else {
		if (anguloDeltejo<PI/2&&anguloDeltejo>=0){
			tejo->getDireccion()->setFi((2*PI)-anguloDeltejo);
		}else{
			if (anguloDeltejo>PI/2&&anguloDeltejo<PI){
				tejo->getDireccion()->setFi(anguloDeltejo+2*(PI-anguloDeltejo));
			}
		}
	}
}
void reboteAbajo(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==3*PI/2){
		tejo->getDireccion()->setFi(anguloDeltejo-(PI));
	}else if (anguloDeltejo<3*PI/2&&anguloDeltejo>=PI){
		tejo->getDireccion()->setFi(anguloDeltejo-2*(anguloDeltejo-PI));
	}else{
		if (anguloDeltejo>3*PI/2&&anguloDeltejo<=2*PI){
			tejo->getDireccion()->setFi(2*PI-anguloDeltejo);
		}}
}
void reboteDerecha(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==0.0){

		tejo->getDireccion()->setFi(anguloDeltejo+(PI));
	}else {
		if (anguloDeltejo<PI/2&&anguloDeltejo>=0.0){

			tejo->getDireccion()->setFi(anguloDeltejo+(PI-2*anguloDeltejo));
		}else{
			if (anguloDeltejo>3*PI/2&&anguloDeltejo<=2*PI){
				tejo->getDireccion()->setFi(PI+(2*PI-anguloDeltejo));
			}         }
	}
}
void reboteIzquierda(Tejo* tejo){
	double anguloDeltejo=tejo->getDireccion()->getFi();
	if (anguloDeltejo==PI){
		tejo->getDireccion()->setFi(anguloDeltejo-(PI));
	}else if (anguloDeltejo<=PI&&anguloDeltejo>PI/2){
		tejo->getDireccion()->setFi(PI-anguloDeltejo);
	}else{
		if (anguloDeltejo>PI&&anguloDeltejo<=3*PI/2){
			tejo->getDireccion()->setFi(anguloDeltejo+2*(3*PI/2-anguloDeltejo));
		}
		}

}
void ControladorColisiones::decidirDireccion(Recta* rectaPerpendicular,Tejo* tejo){
	 double anguloDeltejo=tejo->getDireccion()->getFi();
	 double anguloConAbcisa= rectaPerpendicular->getAnguloConAbcisa();
	 double nuevaDireccion;
	 if (anguloDeltejo<=2*PI&&anguloDeltejo>3*PI/2){
		 nuevaDireccion=2*PI-((anguloDeltejo-2*PI)+anguloConAbcisa);
		tejo->getDireccion()->setFi(PI-anguloDeltejo);
	}
}
ControladorColisiones::~ControladorColisiones() {
	// TODO Auto-generated destructor stub
}
void ControladorColisiones::colisionCirculo(Tejo* tejo,Circulo* circulo){
	 int xTejo,yTejo,xCirculo,yCirculo,radioTejo,radioCirculo;
	 Recta* recta;
	 Recta* rectaPerpendicular;
	 Posicion* pos;
	xTejo=tejo->getX();
	yTejo=tejo->getY();
	xCirculo=circulo->getX();
	yCirculo=circulo->getY();
	radioTejo=tejo->getRadio();
	radioCirculo=circulo->getRadio();
	int distanciaMinimaEntreRadios=tejo->getRadio()+circulo->getRadio();
	int distanciaEntreRadios=CalculosMatematicos::calcularDistancia(tejo->getX(),tejo->getY(),circulo->getX(),circulo->getY());
	if(distanciaMinimaEntreRadios>distanciaEntreRadios){
		 recta= new Recta(xTejo,xCirculo,yTejo,yCirculo);//recta entre los centros de las esferas
         pos = CalculosMatematicos::getInterseccionEsferas(tejo,circulo);//punto de interseccion entre esferas
         rectaPerpendicular=recta->getRectaPerpendicular(pos->getX(),pos->getY());//recta perpendicular en punto de interseccion


     }


}
bool ControladorColisiones::posibilidadDeColisionDispersores(){
	bool posibilidadColision= false;
	Figura *figura;
	Tejo *tejo = Escenario::obtenerInstancia()->getTejo();
	std::list<Figura*>::iterator iter;
	iter = Escenario::obtenerInstancia()->iteratorListaFiguras();

	int wTejo, hTejo, wFigura, hFigura, xTejo, yTejo, xFigura, yFigura,xAnteriorTejo,yAnteriorTejo,radioTejo;
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

		if( ((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){
//					std::cout<<"colisiono con : :"<<figura->getId()<<endl;

            if(figura->getTipo().compare("circulo")==0){
            	ControladorColisiones::colisionCirculo( tejo, (Circulo*)figura);
            }else{
			if(xAnteriorTejo<=xFigura&&yAnteriorTejo<yFigura+hFigura&&yAnteriorTejo>yFigura-wTejo){
					reboteDerecha(tejo);
				}else{
					if(yAnteriorTejo<=yFigura+hFigura&&xAnteriorTejo+wTejo>xFigura&&xAnteriorTejo<xFigura+wFigura){
						reboteAbajo(tejo);
					}else{

						if(yAnteriorTejo>=yFigura+hFigura&&xAnteriorTejo+wTejo>xFigura&&xAnteriorTejo<xFigura+wFigura){
							reboteArriba(tejo);
						}
					}

				}
				if(xAnteriorTejo>=xFigura+wFigura&&yAnteriorTejo<yFigura+hFigura&&yAnteriorTejo>yFigura-wTejo){
					reboteIzquierda(tejo);
				}

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
	int wTejo, hTejo, wPad, hPad, xTejo, yTejo, xPadDer, yPadDer,xPadIzq, yPadIzq,xAnteriorTejo,yAnteriorTejo,radioTejo;
	wTejo = hTejo = tejo->getRadio()*2;
	xTejo = tejo->getX()-tejo->getRadio();
	yTejo= tejo->getY()-tejo->getRadio();
	radioTejo=tejo->getRadio();
	xAnteriorTejo=tejo->getXAnterior()-tejo->getRadio();
	yAnteriorTejo=tejo->getYAnterior()-tejo->getRadio();
	Pad* padIzquierda=escenario->getPadCliente2();
	Pad* padDerecha=escenario->getPadCliente1();
	wPad= padDerecha->getBase();
	hPad=padDerecha->getAltura();
	xPadDer= padDerecha->getX();
	yPadDer= padDerecha->getY();
	xPadIzq= padIzquierda->getX();
	yPadIzq= padIzquierda->getY();

	if( ((xTejo + wTejo) >= xPadDer) && ((yTejo + hTejo) >= yPadDer) && ((xPadDer + wPad) >= xTejo) && ((yPadDer + hPad) >= yTejo)){

		if(xAnteriorTejo<=xPadDer&&yAnteriorTejo<yPadDer+hPad&&yAnteriorTejo>yPadDer-wTejo){
			reboteDerecha(tejo);
		}else{
			if(yAnteriorTejo<=yPadDer&&xAnteriorTejo+wTejo>xPadDer&&xAnteriorTejo<xPadDer+wPad){
						reboteAbajo(tejo);
					}else{

						if(yAnteriorTejo>=yPadDer+hPad&&xPadDer<xAnteriorTejo+wTejo&&xAnteriorTejo<xPadDer+wPad){
							reboteArriba(tejo);
						}
		}

		}
		if(xAnteriorTejo>=xPadDer+wPad){
					reboteIzquierda(tejo);
				}

	}
	if( ((xTejo + wTejo) >= xPadIzq) && ((yTejo + hTejo) >= yPadIzq) && ((xPadIzq + wPad) >= xTejo) && ((yPadIzq + hPad) >= yTejo)){
		if(xAnteriorTejo<=xPadIzq&&yAnteriorTejo<yPadIzq+hPad&&yAnteriorTejo>yPadIzq-wTejo){
					reboteDerecha(tejo);
				}else{
					if(yAnteriorTejo<=yPadIzq&&xAnteriorTejo+2*radioTejo>xPadIzq&&xAnteriorTejo<xPadIzq+wPad){
								reboteAbajo(tejo);
							}else{

								if(yAnteriorTejo>=yPadIzq+hPad&&xAnteriorTejo+wTejo>xPadIzq&&xAnteriorTejo<xPadIzq+wPad){
									reboteArriba(tejo);
								}
				}

				}
		if(xAnteriorTejo>=xPadIzq+wPad){
							reboteIzquierda(tejo);
						}

	}
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

