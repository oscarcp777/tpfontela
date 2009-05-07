#include "Triangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"


#define PENDIENTE_RECTAX 9999


Triangulo::Triangulo(){
}

Triangulo::Triangulo(std::string id,Posicion *ver1,Posicion *ver2,Posicion *ver3){
	this->id = id;
	this->vertice1 = ver1;
	this->vertice2 = ver2;
	this->vertice3 = ver3;
	
}


Posicion* hallarEjeDeCordenadas(Posicion* pos1,Posicion* pos2,Posicion* pos3){
	
	Posicion* ejeCordenadas = new Posicion (0,0);
	if (pos1->getX()<pos2->getX()){
		if (pos1->getX()<pos3->getX())
			ejeCordenadas->setX(pos1->getX());
		else
			ejeCordenadas->setX(pos3->getX());
	}
	else{
		if (pos2->getX()<pos3->getX())
			ejeCordenadas->setX(pos2->getX());
		else
			ejeCordenadas->setX(pos3->getX());
	}
	if (pos1->getY()>pos2->getY()){
		if (pos1->getY()>pos3->getY())
			ejeCordenadas->setY(pos1->getY());
		else
			ejeCordenadas->setY(pos3->getY());
	}
	else{
		if (pos2->getY()>pos3->getY())
			ejeCordenadas->setY(pos2->getY());
		else
			ejeCordenadas->setY(pos3->getY());
	}


	return ejeCordenadas;
}


Posicion* cambioCoordenadas(Posicion* ejeDeCordenadas, Posicion* pto){

	Posicion* pos = new Posicion(0,0);
	pos->setX(pto->getX()-ejeDeCordenadas->getX());
	pos->setY(ejeDeCordenadas->getY() - pto->getY());
	
	return pos;
}
	

int hallarDominio(int z1,int z2,int z3){

	int mayor = 0;
	if (abs(z1 - z2) > abs(z1 - z3)){
		if (abs(z2 - z3)> abs(z1 - z2))
			mayor = abs(z2 - z3);
		else
			mayor = abs(z1 - z2);
	}
	else{
		if (abs(z2 - z3)> abs(z1 - z3))
			mayor = abs(z2 - z3);
		else
			mayor = abs(z1 - z3);
	}
	
	return mayor;

}

float calcularPendiente (Posicion* pos1,Posicion* pos2){
	
	if (pos1->getX()-pos2->getX() == 0)
		return (float)PENDIENTE_RECTAX;
	else
		return ( (float)(pos1->getY()-pos2->getY())/(float)(pos1->getX()-pos2->getX()) );

}

float calcularOrdenada ( int x, int y, float pend){

	if (pend == PENDIENTE_RECTAX)
		return x;
	else
		return ( y - (pend*x) ); 

}

void hallarVertices(Posicion* ver1, Posicion* ver2, Posicion* ver3, int maxValorX,
					Posicion* &verticeCentral, Posicion* &verticeInicial, Posicion* &verticeFinal){

	
	if (ver1->getX()==0 || ver1->getX()==maxValorX){
			if (ver1->getX()==0)
				verticeInicial = ver1;
			else
				if (ver1->getX()==maxValorX)
					verticeFinal = ver1;
	}
	else
			verticeCentral = ver1;
	
	if (ver2->getX()==0 || ver2->getX()==maxValorX){
			if (ver2->getX()==0)
					verticeInicial = ver2;
			else
				if (ver2->getX()==maxValorX)
					verticeFinal = ver2;
	}
	else
		verticeCentral = ver2;
	
	if (ver3->getX()==0 || ver3->getX()==maxValorX){
			if (ver3->getX()==0)
					verticeInicial = ver3;
			else
				if (ver3->getX()==maxValorX)
					verticeFinal = ver3;
	}
	else
			verticeCentral = ver3;

}


bool estaEnRecta (Posicion* pos,float m, float k){

	if ( (m*pos->getX()+k - pos->getY() < 0.05) &&  (m*pos->getX()+k - pos->getY() > -0.05) )
		return true;

	else return false;
}

int compararPosicionConRecta (float m , float k,int i, int j){
	int comp;
	if(m*i+k==j) comp = 0; //si el punto pertenece a la recta
	else if (m*i+k<j) comp = -1; //si el punto esta por debajo de la recta
		else comp = 1; //si el punto esta por encima de la recta
		
		
		return comp;
}
int mayor(int x, int y){
	if (x>y)
		return x;
	else 
		return y;

}

void Triangulo::graficarPixel(SDL_Surface *screen, int i, int j, Posicion* ejeDeCoordenadas){

	if(this->imagen != NULL)
			this->color = this->getpixel(this->imagen,i,this->imagen->h - 1 - j);			
	this->putpixel(screen,i+ejeDeCoordenadas->getX(),ejeDeCoordenadas->getY()-j,this->color);

}



int Triangulo::dibujar(SDL_Surface *screen){

	this->color = Escenario::obtenerInstancia()->getColorLinea();
	
	this->dibujarLinea(color,screen ,this->getVertice1()->getX(),  this->getVertice1()->getY(), this->getVertice2()->getX(), this->getVertice2()->getY());
	this->dibujarLinea(color,screen ,this->getVertice1()->getX(),  this->getVertice1()->getY(), this->getVertice3()->getX(), this->getVertice3()->getY()); 
	this->dibujarLinea(color,screen ,this->getVertice2()->getX(),  this->getVertice2()->getY(), this->getVertice3()->getX(), this->getVertice3()->getY());
	
	this->color = Escenario::obtenerInstancia()->getColorFondoFiguras();

	Posicion* ejeDeCordenadas;
	Posicion* ver1;
	Posicion* ver2;
	Posicion* ver3;
	int maxValorX = 0;
	int maxValorY = 0;
	float m1,m2,m3;  //pendientes de las tres rectas;
	float k1,k2,k3; //ordenadas de las tres rectas
	int i = 0;
	int j = 0;
	bool rectaEnX = false;

	ejeDeCordenadas = hallarEjeDeCordenadas(this->getVertice1(),this->getVertice2(),this->getVertice3());
	ver1 = cambioCoordenadas(ejeDeCordenadas, this->getVertice1());
	ver2 = cambioCoordenadas(ejeDeCordenadas, this->getVertice2());
	ver3 = cambioCoordenadas(ejeDeCordenadas, this->getVertice3());


	maxValorX = hallarDominio(this->getVertice1()->getX(),this->getVertice2()->getX(),this->getVertice3()->getX());
	maxValorY = hallarDominio(this->getVertice1()->getY(),this->getVertice2()->getY(),this->getVertice3()->getY());

	m1 = calcularPendiente (ver1,ver2);
	m2 = calcularPendiente (ver1,ver3);
	m3 = calcularPendiente (ver2,ver3);

	if (m1 == PENDIENTE_RECTAX || m2 == PENDIENTE_RECTAX || m3 == PENDIENTE_RECTAX)
		rectaEnX = true;
	
	k1 =  calcularOrdenada (ver1->getX(), ver1->getY(), m1) ;
	k2 =  calcularOrdenada (ver1->getX(), ver1->getY(), m2) ;
	k3 =  calcularOrdenada (ver2->getX(), ver2->getY(), m3) ;

	bool perteneceAR1 = false;
	bool perteneceAR2 = false;
	bool perteneceAR3 = false;
	bool primeraEntrada = true;
	int resComp1;	
	int resComp2;
	Posicion* verticeCentral;
	Posicion* verticeInicial;
	Posicion* verticeFinal;
	
	
	hallarVertices(ver1, ver2, ver3, maxValorX, verticeCentral, verticeInicial, verticeFinal);

				
	perteneceAR1 = estaEnRecta (verticeInicial,m1,k1);
	perteneceAR2 = estaEnRecta (verticeInicial,m2,k2);
	perteneceAR3 = estaEnRecta (verticeInicial,m3,k3);
	
	std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());

	this->imagen = IMG_Load (path.begin());
	int mayorDeXY = mayor(maxValorX, maxValorY); 
	this->imagen = ScaleSurface(this->imagen, mayorDeXY, mayorDeXY);

	//recorro la imagen y grafico los pixeles, en las posiciones que pertenecen al triangulo
	for(i = 0;i<maxValorX;i++){
         
  	   for(j = 0; j<maxValorY; j++){
		  
		   if (!rectaEnX){

			if ( i<verticeCentral->getX() ){
								
				if(perteneceAR1 && perteneceAR2){
					resComp1 = compararPosicionConRecta (m1 ,k1,i,j);
					resComp2 = compararPosicionConRecta (m2 ,k2,i,j);
					if (resComp1*resComp2<0)
							graficarPixel(screen, i, j, ejeDeCordenadas);						
				}
				else 
					if(perteneceAR1 && perteneceAR3){
						resComp1 = compararPosicionConRecta (m1 ,k1,i,j);
						resComp2 = compararPosicionConRecta (m3 ,k3,i,j);
							if (resComp1*resComp2<0)
								graficarPixel(screen, i, j, ejeDeCordenadas);
					}
					else{
						resComp1 = compararPosicionConRecta (m2 ,k2,i,j);
						resComp2 = compararPosicionConRecta (m3 ,k3,i,j);
						if (resComp1*resComp2<0)
							graficarPixel(screen, i, j, ejeDeCordenadas);
					}	
				
			}else{
				if(primeraEntrada){					
					perteneceAR1 = estaEnRecta (verticeFinal,m1,k1);
					perteneceAR2 = estaEnRecta (verticeFinal,m2,k2);
					perteneceAR3 = estaEnRecta (verticeFinal,m3,k3);
					primeraEntrada = false;
				}
				if(perteneceAR1 && perteneceAR2){
					resComp1 = compararPosicionConRecta (m1 ,k1,i,j);
					resComp2 = compararPosicionConRecta (m2 ,k2,i,j);
					if (resComp1*resComp2<0)
						graficarPixel(screen, i, j, ejeDeCordenadas);
				}
				else if(perteneceAR1 && perteneceAR3){
					resComp1 = compararPosicionConRecta (m1 ,k1,i,j);
					resComp2 = compararPosicionConRecta (m3 ,k3,i,j);
					if (resComp1*resComp2<0)
						graficarPixel(screen, i, j, ejeDeCordenadas);
				}
				else{
					resComp1 = compararPosicionConRecta (m2 ,k2,i,j);
					resComp2 = compararPosicionConRecta (m3 ,k3,i,j);
					if (resComp1*resComp2<0)
						graficarPixel(screen, i, j, ejeDeCordenadas);
				}
			}
		   }
		   else
		   {
			   if (m1 == PENDIENTE_RECTAX && i!=k1){
					resComp1 = compararPosicionConRecta (m2 ,k2,i,j);
					resComp2 = compararPosicionConRecta (m3 ,k3,i,j);
					if (resComp1*resComp2<0)
							graficarPixel(screen, i, j, ejeDeCordenadas);
			   }
			   if (m2 == PENDIENTE_RECTAX && i!=k2){
					resComp1 = compararPosicionConRecta (m1 ,k1,i,j);
					resComp2 = compararPosicionConRecta (m3 ,k3,i,j);
					if (resComp1*resComp2<0)
							graficarPixel(screen, i, j, ejeDeCordenadas);
			   }
			   if (m3 == PENDIENTE_RECTAX && i!=k3){
					resComp1 = compararPosicionConRecta (m1 ,k1,i,j);
					resComp2 = compararPosicionConRecta (m2 ,k2,i,j);
					if (resComp1*resComp2<0)
							graficarPixel(screen, i, j, ejeDeCordenadas);
			   }
					



		   }
			   


	   }			
		
	}



	
	return 0;
}

Posicion* Triangulo::getVertice1(){
		
	return this->vertice1;
}

Posicion* Triangulo::getVertice2(){
		
	return this->vertice2;
}

Posicion* Triangulo::getVertice3(){
		
	return this->vertice3;
}

void Triangulo::setVertice1(Posicion * posicion){
	this->vertice1 = posicion;
}

void Triangulo::setVertice2(Posicion * posicion){
	this->vertice2 = posicion;
}

void Triangulo::setVertice3(Posicion * posicion){
	this->vertice3 = posicion;
}

