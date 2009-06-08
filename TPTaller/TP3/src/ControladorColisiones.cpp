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
void decidirDireccion(std::string posicionRectangulo,Tejo* tejo){
	if(posicionRectangulo.compare(ARRIBA)==0){
		reboteArriba(tejo);
	}else{
		if(posicionRectangulo.compare(ABAJO)==0){
			reboteAbajo(tejo);
		}else{
			if(posicionRectangulo.compare(DERECHA)==0){
				reboteDerecha(tejo);
			}else{
				if(posicionRectangulo.compare(IZQUIERDA)==0){
					reboteIzquierda(tejo);
				}
			}
		}
	}
}
ControladorColisiones::~ControladorColisiones() {
	// TODO Auto-generated destructor stub
}
void ControladorColisiones::colisionCirculo(Tejo* tejo,Figura* figura){
	int w1, h1, w2, h2, x1, y1, x2, y2;

	w1 = h1 = tejo->getRadio()*2;
	x1 = tejo->getX()-tejo->getRadio();
	y1 = tejo->getY()-tejo->getRadio();
	RectanguloInfluencia* rectangulo ;
	std::list<RectanguloInfluencia*>::iterator iter;
	iter = figura->iteratorRectangulosDeInfluencia();
	int i = 1;

	while(i<=figura->sizeListaRectangulos()){
		rectangulo = *iter;

		std::cout<<"tamanio"<<rectangulo->getX()<<endl;
		std::cout<<"tamanio"<<rectangulo->getY()<<endl;
		std::cout<<"tamanio"<<rectangulo->getH()<<endl;
		std::cout<<"tamanio"<<rectangulo->getW()<<endl;

		w2 =rectangulo->getW();
		h2 = rectangulo->getH();
		x2 = rectangulo->getX() ;
		y2 =rectangulo->getY();

		// Si existe colisión entre alguno de los
		// rectángulos paramos los bucles
		if( ((x1 + w1) > x2) &&	((y1 + h1) > y2) &&	((x2 + w2) > x1) &&	((y2 + h2) > y1)){
			decidirDireccion(rectangulo->getPosicionRectangulo(),tejo);
		}
		iter++;
		i++;
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
			pad1->getPuntaje()->setCantPuntosJugador(pad1->getPuntaje()->getCantPuntosJugador()+PUNTAJE_GOL);
			return 0;
		}
	}
	if(arcoDerecha->getY()+tejo->getRadio()<=tejo->getY()&&arcoDerecha->getY()+arcoDerecha->getAltura()-tejo->getRadio()>=tejo->getY()&&
			tejo->getX()>escenario->getAncho()-tejo->getRadio()*4){
		if(tejo->getX() >= arcoDerecha->getX()- tejo->getRadio()){
			//			std::cout<<"  GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<endl;
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

