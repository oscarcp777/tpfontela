/*
 * Recta.cpp
 *
 *  Created on: 11/06/2009
 *      Author: oscar
 */

#include "Recta.h"

Recta::Recta(){

}
Recta::Recta(int x1,int x2,int y1,int y2){
	if ((y2 - y1) != 0){
	    // como la ecuacion de la recta es y = mx +b, necesito los valores de m y b
	   this->pendiente =((y2 - y1)/(x2 - x1));
	   this->ordenada= y1 - this->pendiente*x1;

	  }

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
	  // hallo el punto de cruce
	  // de las rectas
	 float Xc = (b2 - b1)/(m1 - m2);
	 float Yc = (b2*m1 - b1*m2)/(m1 - m2);
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
	float m=(-1/this->pendiente);
    float b=y - m*x;
    rectaPerpependicular->setPendiente(m);
    rectaPerpependicular->setOrdenada(b);
	return rectaPerpependicular;
}
int Recta::getValor(int x){
	float  valor=this->pendiente*x+this->ordenada;
	return (int)valor;

}
Recta::~Recta() {
	// TODO Auto-generated destructor stub
}
float Recta::getPendiente()
 {
     return pendiente;
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
