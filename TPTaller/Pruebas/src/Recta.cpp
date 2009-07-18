/*
 * Recta.cpp
 *
 *  Created on: 11/06/2009
 *      Author: oscar
 */

#include "Recta.h"

#include<math.h>
#include "Define.h"

Recta::Recta(){

}
void Recta::toString(){
std::cout<<" y = "<<this->pendiente<<"*x + "<<this->ordenada<<" infinito"<<this->infinito<<std::endl;
}

Recta::Recta(int x1,int x2,int y1,int y2){
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
	int equis=(x2 - x1);
	
	if ( equis== 0){
		 this->pendiente=NUMERO_PEQUENIO;
		 this->ordenada= x1; //aca dejo el valor de x por donde pasa la recta
		 this->infinito=-1;
	}else{
	    // como la ecuacion de la recta es y = mx +b, necesito los valores de m y b
	   this->pendiente =(((double)(y2 - y1))/(double)equis);
	   this->ordenada= y1 - this->pendiente*x1;
	   this->infinito=0;
	}




}
double Recta::getDistancia(){
	return this->distancia;
}
       void Recta::setDistancia(double distancia){
    	   this->distancia=distancia;
       }

int Recta::isPuntoDeRecta(Posicion*posicion){
	if((posicion->getX()==this->getX1() && posicion->getY()==this->getY1())||(posicion->getX()==this->getX2() && posicion->getY()==this->getY2()) )
		return 0;
	else return -1;
}

int Recta::getInfinito()
   {
       return infinito;
   }

   void Recta::setInfinito(int infinito)
   {
       this->infinito = infinito;
   }
   Posicion* Recta::getInterseccion(Recta* recta){

	   // si m1 y m2 son iguales (si las pendientes son iguales), entonces las
	   // rectas son paralelas.no considero el hecho de calcular si dos rectas paralelas
	   // son o no la misma devuleve una interseccion furea dela pantalla
	   if (recta->getInfinito() == this->infinito&&this->infinito==-1){
		   return new Posicion(-1,-1);
	   }else{
		   if (recta->getPendiente() == this->pendiente){
			   return new Posicion(-1,-1);
		   }else{
			   if (recta->getPendiente() ==0&& this->infinito==-1){
				   return (new Posicion(this->ordenada,recta->getOrdenada()));
			   }else{
				   if (recta->getInfinito() ==-1&& this->pendiente==0){
					   return (new Posicion(recta->getOrdenada(),this->ordenada));
				   }else{
					   if (this->infinito == -1){
						   return (new Posicion(this->ordenada,recta->getPendiente()*this->ordenada+recta->getOrdenada()));
				   }else{
					   if(this->infinito==0){
						   float b1,b2,m1,m2;
						   m1=recta->getPendiente();
						   m2=this->pendiente;
						   b2=this->ordenada;
						   b1=recta->getOrdenada();

						   // hallo el punto de cruce
						   // de las rectas
						   float Xc = (float)(b2 - b1)/(float)(m1 - m2);
						   float Yc = (float)(b2*m1 - b1*m2)/(float)(m1 - m2);
						   Posicion* interseccion= new Posicion((int)Xc,(int)Yc);
						   return interseccion;
					   }
				   }
			   }
		   }
	   }
   }
//	   if (this->infinito == -1)
//		   return (new Posicion(this->ordenada,recta->getPendiente()*this->ordenada+recta->getOrdenada()));

}
/**
 * devuelve una recta perpendicular a actual necesita que se le pase el
 * punto de interseccionde las rectas
 */
Recta* Recta::getRectaPerpendicular(int x,int y){
	Recta* rectaPerpependicular = new Recta();
//	la pendiente de una recta perpendicular es la inversa de la otra m1=-1/m2
    if(this->infinito==-1){
    	rectaPerpependicular->setPendiente(0);
    	rectaPerpependicular->setOrdenada(y);
    	 rectaPerpependicular->setInfinito(0);
    	return rectaPerpependicular;
    }
    if(this->pendiente==0){
    	     rectaPerpependicular->setInfinito(-1);
        	rectaPerpependicular->setPendiente(0);
        	rectaPerpependicular->setOrdenada(y);
        	return rectaPerpependicular;
        }
	float m=-1*(1/this->pendiente);
    float b=y - m*x;
    rectaPerpependicular->setPendiente(m);
    rectaPerpependicular->setOrdenada(b);
    rectaPerpependicular->setInfinito(0);
	return rectaPerpependicular;
}
int Recta::getValor(int x){

	float  valor=this->pendiente*x+this->ordenada;
	return (int)valor;

}
int Recta::getValorInverso(int y){
	if(this->pendiente==0){
			 this->pendiente= NUMERO_PEQUENIO;
		 }
	float  valor=((float)y-this->ordenada)/this->pendiente;
	return (int)valor;

}
int Recta::getCortaX(){

	float cortaX=((-1*this->ordenada)/	this->pendiente);
	 if(this->pendiente==0){
		 this->pendiente= NUMERO_PEQUENIO;
	 }

	return (int)cortaX;
}
Recta::~Recta() {
	// TODO Auto-generated destructor stub
}
float Recta::getPendiente()
 {
    return pendiente;
 }
int Recta::getX1(){
	return x1;
}
int Recta::getX2(){
	return x2;
}
int Recta::getY1(){
	return y1;
}
int Recta::getY2(){
	return y2;
}
double Recta::getAnguloConAbcisa(){
	int cortaY=abs(this->getValor(0));
	    int cortaX=abs(this->getCortaX());
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
