/*
 * Recta.cpp
 *
 *  Created on: 11/06/2009
 *      Author: oscar
 */

#include "Recta.h"
#include<math.h>
Recta::Recta(){

}
void Recta::toString(){
std::cout<<" y = "<<this->pendiente<<"*x + "<<this->ordenada<<std::endl;
}
Recta::Recta(int x1,int x2,int y1,int y2){
	int equis=(x2 - x1);
	if ( equis== 0){
		equis=1;
	}
	    // como la ecuacion de la recta es y = mx +b, necesito los valores de m y b
	   this->pendiente =(((double)(y2 - y1))/(double)equis);
	   this->ordenada= y1 - this->pendiente*x1;



}
Posicion* Recta::getInterseccion(Recta* recta){

	  // si m1 y m2 son iguales (si las pendientes son iguales), entonces las
	  // rectas son paralelas.no considero el hecho de calcular si dos rectas paralelas
	  // son o no la misma devuleve una interseccion furea dela pantalla
	  if (recta->getPendiente() == this->pendiente){
	      return new Posicion(-1,-1);
	  }
     float b1,b2,m1,m2;
     m1=recta->getPendiente();
     m2=this->pendiente;
     b2=this->ordenada;
     b1=recta->getOrdenada();
     int difPendientes=(m1 - m2);
     	if ( difPendientes== 0){
     		difPendientes=1;
     	}
	  // hallo el punto de cruce
	  // de las rectas
	 float Xc = (float)(b2 - b1)/(float)difPendientes;
	 float Yc = (float)(b2*m1 - b1*m2)/(float)difPendientes;
	  Posicion* interseccion= new Posicion((int)Xc,(int)Yc);
	  return interseccion;
}
/**
 * devuelve una recta perpendicular a actual necesita que se le pase el
 * punto de interseccionde las rectas
 */
Recta* Recta::getRectaPerpendicular(int x,int y){
	Recta* rectaPerpependicular = new Recta();
//	la pendiente de una recta perpendicular es la inversa de la otra m1=-1/m2
	float pend=this->pendiente;
	if(pend==0){
		pend=1;
	}
	float m=-1*(1/pend);
    float b=y - m*x;
    rectaPerpependicular->setPendiente(m);
    rectaPerpependicular->setOrdenada(b);
	return rectaPerpependicular;
}
int Recta::getValor(int x){
	float  valor=this->pendiente*x+this->ordenada;
	return (int)valor;

}
int Recta::getCortaX(){
	float pend=this->pendiente;
		if(pend==0){
			pend=1;
		}
	float cortaX=((-1*this->ordenada)/pend);
	return (int)cortaX;
}
Recta::~Recta() {
	// TODO Auto-generated destructor stub
}
float Recta::getPendiente()
 {
     return pendiente;
 }
double Recta::getAnguloConAbcisa(){
	int cortaY=abs(this->getValor(0));
	    int cortaX=abs(this->getCortaX());
	    if(cortaX==0){
	    	cortaX=1;
	    		}
	    double div=(double)cortaY/(double)cortaX;
	    return atan(div);
}
 void Recta::setPendiente(float pendiente)
 {
     this->pendiente = pendiente;
 }

 float Recta::getOrdenada()
 {
     return ordenada;
 }

 void Recta::setOrdenada(float ordenada)
 {
     this->ordenada = ordenada;
 }
