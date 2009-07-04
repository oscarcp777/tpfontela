/*
 * CalculosMatematicos.cpp
 *
 *  Created on: 10/06/2009
 *      Author: oscar
 */

#include "CalculosMatematicos.h"
#include "Define.h"
#include<math.h>
#include <stdlib.h>
#include <time.h>
CalculosMatematicos::CalculosMatematicos() {
	// TODO Auto-generated constructor stub

}
int CalculosMatematicos::ramdom(int numeroMaximo){
	 srand ( time(NULL) );
	int devolver=0;
    if (numeroMaximo > 0) {
        devolver = (rand() % numeroMaximo) + 1;

    }
    return devolver;
}
double CalculosMatematicos::getAnguloValido(double direcion){
	double devolver=direcion;
	if(direcion<0){
			devolver=2*PI+direcion;
		}
	if(direcion>=2*PI){
		devolver=direcion-2*PI;
	}

	return devolver;
}
int CalculosMatematicos::verificarDireccionRectasPositivas(Recta* rectaDeChoque,Recta* rectaTejo){
	Posicion* pos=rectaTejo->getInterseccion(rectaDeChoque);
	int valorTejoY=rectaTejo->getValor(pos->getX()+30);
	int valorChoqueY=rectaDeChoque->getValor(pos->getX()+30);
	int valorChoqueX=rectaDeChoque->getValorInverso(valorTejoY);
	if(valorChoqueX>=pos->getX()){
     return 1;
	}else{
		  return -1;
	}
}
int CalculosMatematicos::verificarDireccionRectasNegativas(Recta* rectaDeChoque,Recta* rectaTejo){
	Posicion* pos=rectaTejo->getInterseccion(rectaDeChoque);
	int valorTejoX=rectaTejo->getValorInverso(pos->getY()-30);
	int valorChoqueX=rectaDeChoque->getValorInverso(pos->getY()-30);
	int valorChoqueY=rectaDeChoque->getValor(valorTejoX);
	if(valorChoqueY>=pos->getY()){
     return 1;
	}else{
		  return -1;
	}
}
CalculosMatematicos::~CalculosMatematicos() {
	// TODO Auto-generated destructor stub
}
 bool CalculosMatematicos::isPrimerCuadrante(double direccion){
	return (direccion>=0&&direccion<=PI/2);
}
 bool CalculosMatematicos::isSegundoCuadrante(double direccion){
	return (direccion>=PI/2&&direccion<=PI);
}
 bool CalculosMatematicos::isTercerCuadrante(double direccion){
	return (direccion>=PI&&direccion<=3*PI/2);
}
 bool CalculosMatematicos::isCuartoCuadrante(double direccion){
	return (direccion>=3*PI/2&&direccion<=2*PI);
}
bool  CalculosMatematicos::verificarPerpendicularidad(Recta* recta1,Recta* recta2){
  return (recta1->getPendiente()*recta2->getPendiente()==-1);
}
int CalculosMatematicos::calcularDistancia(int izqX, int izqY,int derX, int derY){
	int  x,y;
	int raiz=0;
	x=derX-izqX;
	y=derY-izqY;
	if(x<0)x=x*-1;
	if(y<0)y=y*-1;
		raiz=(int)sqrt(pow(x,2)+pow(y,2));
	return raiz;
}

Posicion* CalculosMatematicos::getInterseccionEsferas(Tejo* tejo,Circulo* circulo){
     int xTejo,yTejo,xCirculo,yCirculo,xInicial,yInicial,radioTejo,radioCirculo,radio,factorX=1,factorY=1;
     xTejo=tejo->getX();
     yTejo=tejo->getY();
     xCirculo=circulo->getX();
     yCirculo=circulo->getY();
     radioTejo=tejo->getRadio();
     radioCirculo=circulo->getRadio();
     if(xTejo<=xCirculo&&yTejo<=yCirculo){
    	 xInicial=xTejo;
    	 yInicial=yTejo;
    	 radio=radioTejo;
     }else{
    	 if(xTejo>=xCirculo&&yTejo>=yCirculo){
    		 xInicial=xCirculo;
    		 yInicial=yCirculo;
    		 radio=radioCirculo;
    	 }else{
    		 if(xTejo>=xCirculo&&yTejo<=yCirculo){
    			 xInicial=xTejo;
    			 yInicial=yTejo;
    			 radio=radioTejo;
    			 factorX=-1;
    		 }else{
    			 if(xTejo<=xCirculo&&yTejo>=yCirculo){
    				 xInicial=xCirculo;
    				 yInicial=yCirculo;
    				 radio=radioCirculo;
    				 factorX=-1;
    			 }

    		 }
    	 }
     }

     float cosx,senx,raiz,interX,interY;
     raiz=calcularDistancia(xTejo,yTejo,xCirculo,yCirculo);
     cosx=abs(xCirculo-xTejo)/raiz;
     senx=abs(yCirculo-yTejo)/raiz;
     interX=radio*cosx*factorX+xInicial;
     interY=radio*senx*factorY+yInicial;
     return new Posicion((int)interX,(int)interY);
}
