#include "Triangulo.h"
#include <string>
#include <iostream>
#include "Escenario.h"


#define PENDIENTE_RECTAX 9999

Triangulo::Triangulo(){
	this->escalada = false;
}
Triangulo::~Triangulo(){
	delete this->vertice1;
	delete this->vertice2;
	delete this->vertice3;
	delete this->recta1;
	delete this->recta2;
	delete this->recta3;
	delete this->x1;
	delete this->x2;
	delete this->y1;
	delete this->y2;
	if(this->imagenAuxiliar!=NULL)
	SDL_FreeSurface(this->imagenAuxiliar);
	  if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Triangulo"<<endl;


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

int Triangulo::getLado()
    {
        return lado;
    }

    void Triangulo::setLado(int lado)
    {
        this->lado = lado;
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

/* Devuelve 1 si posicion en x es mayor a otraPosicion en x
 * Devuelve -1 si posicion en x es menor a otraPosicion en x
 * Devuelve 0 si posicion en x es igual a otraPosicion en x
 */
int diferenciaEnX(Posicion*posicion,Posicion*otraPosicion){
	if((posicion->getX()-otraPosicion->getX())>0)
		return 1;
	else if((posicion->getX()-otraPosicion->getX())<0)
			return -1;
	else
				return 0;

}

/* Devuelve 1 si posicion en y es mayor a otraPosicion en y
 * Devuelve -1 si posicion en y es menor a otraPosicion en y
 * Devuelve 0 si posicion en y es igual a otraPosicion en y
 */
int diferenciaEnY(Posicion*posicion,Posicion*otraPosicion){
	if((posicion->getY()-otraPosicion->getY())>0)
		return 1;
	else if((posicion->getY()-otraPosicion->getY())<0)
			return -1;
	else
				return 0;

}

/* int variante: 0 x constante e y variando, 1 x variando e y constante.
 * posicion , otraPosicion son las posiciones a comparar para ver si ambas cumplen con la condicion variante
 * devuelve 0 en caso que ambos vertices cumplan con la condición variante
 * devuelve -1 en caso que ambos vertices no cumplan con la condición variante
 * devuelve -2 en caso de no ingresar correctamente el int variante que puede ser 0 o 1
 */
int verificarCondicionVertices(Posicion*posicion,Posicion*otraPosicion,int variante){
	if(variante==0){ //x constante, y variando
		if(diferenciaEnX(posicion,otraPosicion)==0)
			if(diferenciaEnY(posicion,otraPosicion)!=0)
			   return 0;

			return -1;
	}else if(variante==1){ //x variando, y constante
		if(diferenciaEnY(posicion,otraPosicion)==0)
			if(diferenciaEnX(posicion,otraPosicion)!=0)
				return 0;

			return -1;
	}
	return -2; //la variante debe ser 0 o 1.
}

void Triangulo::setBase(std::string base){
	this->base = base;
}

int Triangulo::isBase(Recta*recta){
//	system("PAUSE");
//	std::cout<<"recta->x1=="<<recta->getX1()<<" vert->x1=="<<*this->x1<<endl;
//	std::cout<<"recta->x2=="<<recta->getX2()<<" vert->x2=="<<*this->x2<<endl;
//	std::cout<<"recta->y1=="<<recta->getY1()<<" vert->y1=="<<*this->y1<<endl;
//	std::cout<<"recta->y2=="<<recta->getY2()<<" vert->y2=="<<*this->y2<<endl;
//	system("PAUSE");
	if((recta->getX1()==*this->x1) && (recta->getX2()==*this->x2) && (recta->getY1()==*this->y1) && (recta->getY2()==*this->y2))
		return 0; //es base
	else return -1; //no es base
}

void Triangulo::asignarPuntosRectaBase(Recta*recta){
	*this->x1 = recta->getX1();
	*this->x2 = recta->getX2();
	*this->y1 = recta->getY1();
	*this->y2 = recta->getY2();
}

//posicion1, posicion2 y posicion3 se corresponden a los vertices vert1, vert2 y vert3 del triangulo
void Triangulo::darNombreBaseTriangulo(Posicion*posicion1,Posicion*posicion2,Posicion*posicion3){

	int vert12Yvariando=verificarCondicionVertices(posicion1,posicion2,0);
	int vert23Yvariando=verificarCondicionVertices(posicion2,posicion3,0);
	int vert13Yvariando=verificarCondicionVertices(posicion1,posicion3,0);

	int vert12Xvariando=verificarCondicionVertices(posicion1,posicion2,1);
	int vert23Xvariando=verificarCondicionVertices(posicion2,posicion3,1);
	int vert13Xvariando=verificarCondicionVertices(posicion1,posicion3,1);

	//Hasta aca tengo las 3 rectas del triangulo, solo me falta ver cual es cual

	if(recta1->getInfinito()==-1 || recta2->getInfinito()==-1 || recta3->getInfinito()==-1){ //alguna de las 3 rectas es vertical

		if(vert12Yvariando==0){
			int diferenciaPosX = diferenciaEnX(posicion1,posicion3); //podria haber sido con 2 y 3 dado que el vert 1 y 2 tienen la misma coordenada x
			if(diferenciaPosX==1){
			setBase(BASE_TRIANGULO_DERECHA);
			asignarPuntosRectaBase(recta1);

			}else if(diferenciaPosX==-1){
				setBase(BASE_TRIANGULO_IZQUIERDA);
				asignarPuntosRectaBase(recta1);

			}
		}else if(vert23Yvariando==0){
			int diferenciaPosX = diferenciaEnX(posicion1,posicion3); //podria haber sido con 1 y 2 dado que el vert 2 y 3 tienen la misma coordenada x
			if(diferenciaPosX==1){
			setBase(BASE_TRIANGULO_DERECHA);
			asignarPuntosRectaBase(recta2);

			}else if(diferenciaPosX==-1){
				setBase(BASE_TRIANGULO_IZQUIERDA);
				asignarPuntosRectaBase(recta2);

			}
		}else if(vert13Yvariando==0){
			int diferenciaPosX = diferenciaEnX(posicion1,posicion2); //podria haber sido con 3 y 2 dado que el vert 1 y 3 tienen la misma coordenada x
			if(diferenciaPosX==1){
			setBase(BASE_TRIANGULO_DERECHA);
			asignarPuntosRectaBase(recta3);

			}else if(diferenciaPosX==-1){
				setBase(BASE_TRIANGULO_IZQUIERDA);
				asignarPuntosRectaBase(recta3);

			}
		}
	}else{ //ninguna de las 3 rectas es vertical, por lo que el triangulo esta mirando con la punta hacia abajo o hacia arriba

		if(vert12Xvariando==0){
			int diferenciaPosY = diferenciaEnY(posicion1,posicion3); //podria haber sido con 2 y 3 dado que el vert 1 y 2 tienen la misma coordenada y
			if(diferenciaPosY==1){
			setBase(BASE_TRIANGULO_ABAJO);
			asignarPuntosRectaBase(recta1);

			}
			else if(diferenciaPosY==-1){
				setBase(BASE_TRIANGULO_ARRIBA);
				asignarPuntosRectaBase(recta1);

			}
		}else if(vert23Xvariando==0){
			int diferenciaPosY = diferenciaEnY(posicion1,posicion3); //podria haber sido con 1 y 2 dado que el vert 2 y 3 tienen la misma coordenada y
			if(diferenciaPosY==1){
			setBase(BASE_TRIANGULO_ABAJO);
			asignarPuntosRectaBase(recta2);

			}else if(diferenciaPosY==-1){
				setBase(BASE_TRIANGULO_ARRIBA);
				asignarPuntosRectaBase(recta2);

			}
		}else if(vert13Xvariando==0){
			int diferenciaPosY = diferenciaEnY(posicion1,posicion2); //podria haber sido con 3 y 2 dado que el vert 1 y 3 tienen la misma coordenada y
			if(diferenciaPosY==0){
			setBase(BASE_TRIANGULO_ABAJO);
			asignarPuntosRectaBase(recta3);

			}
			else if(diferenciaPosY==-1){
				setBase(BASE_TRIANGULO_ARRIBA);
				asignarPuntosRectaBase(recta3);

			}
		}

	}

}

Recta* Triangulo::getRecta1(){
	return this->recta1;
}

Recta* Triangulo::getRecta2(){
	return this->recta2;
}

Recta* Triangulo::getRecta3(){
	return this->recta3;
}

int calcularVerticesBaseAbajo(Posicion*vertice1,Posicion*vertice2,Posicion*vertice3,int lado){

	double xVert1 = vertice1->getX();
	double yVert1 = vertice1->getY();
	double xVert2 = vertice2->getX();
	double yVert2 = vertice2->getY();
	double xVert3 = vertice3->getX();
	double yVert3 = vertice3->getY();

	double lado_inicial = 0;
	double altura_inicial = 0;
	double altura_final = 0;


		if(diferenciaEnX(vertice1,vertice2)==1){ //x1>x2
			lado_inicial = xVert1 - xVert2;
			if(lado_inicial<lado){ //expandir triangulo
				xVert2=(xVert3-(lado/2));
				xVert1=(xVert3+(lado/2));
				//xVert3 = xVert3 + (xVert1-xVert2)/2;
			}else if(lado_inicial>lado){ //contraer triangulo
				xVert2=(xVert3+(lado/2));
				xVert1=(xVert3-(lado/2));
				//xVert3= xVert3 + (xVert1-xVert2)/2;
		    }

		}else{ //x1<x2
			lado_inicial = xVert2 - xVert1;
			std::cout<<lado_inicial<<"lado"<<lado<<endl;
			if(lado_inicial<lado){ //expandir triangulo
				xVert1=(xVert3-(lado/2));
				xVert2=(xVert3+(lado/2));

			}else if(lado_inicial>lado){ //contraer triangulo
				xVert1=(xVert3+(lado/2));
				xVert2=(xVert3-(lado/2));

			}


		}

		altura_inicial = (lado_inicial * sqrt(3))/2;
		altura_final = (lado * sqrt(3))/2;

		if(altura_inicial<altura_final){ //expande
			yVert1 =(yVert1+(altura_final-altura_inicial));
			yVert2 = yVert1;
		}else if(altura_inicial>altura_final){ //contrae
			yVert1 =(yVert1-(altura_inicial-altura_final));
			yVert2 = yVert1;
		}

		vertice1->setX(xVert1);
		vertice1->setY(yVert1);
		vertice2->setX(xVert2);
		vertice2->setY(yVert2);
		vertice3->setX(xVert3);
		vertice3->setY(yVert3);

		return 0;

}

int calcularVerticesBaseArriba(Posicion*vertice1,Posicion*vertice2,Posicion*vertice3,int lado){

	double xVert1 = vertice1->getX();
	double yVert1 = vertice1->getY();
	double xVert2 = vertice2->getX();
	double yVert2 = vertice2->getY();
	double xVert3 = vertice3->getX();
	double yVert3 = vertice3->getY();

	double lado_inicial = 0;
	double altura_inicial = 0;
	double altura_final = 0;


		if(diferenciaEnX(vertice1,vertice2)==1){ //x1>x2
			lado_inicial = xVert1 - xVert2;
			if(lado_inicial<lado){ //expandir triangulo
				xVert2=(xVert3-(lado/2));
				xVert1=(xVert3+(lado/2));
				//xVert3 = xVert3 + (xVert1-xVert2)/2;
			}else if(lado_inicial>lado){ //contraer triangulo
				xVert2=(xVert3+(lado/2));
				xVert1=(xVert3-(lado/2));
				//xVert3= xVert3 + (xVert1-xVert2)/2;
		    }

		}else{ //x1<x2
			lado_inicial = xVert2 - xVert1;
			std::cout<<lado_inicial<<"lado"<<lado<<endl;
			if(lado_inicial<lado){ //expandir triangulo
				xVert1=(xVert3-(lado/2));
				xVert2=(xVert3+(lado/2));

			}else if(lado_inicial>lado){ //contraer triangulo
				xVert1=(xVert3+(lado/2));
				xVert2=(xVert3-(lado/2));

			}


		}

		altura_inicial = (lado_inicial * sqrt(3))/2;
		altura_final = (lado * sqrt(3))/2;

		if(altura_inicial<altura_final){ //expande
			yVert1 =(yVert1-(altura_final-altura_inicial));
			yVert2 = yVert1;
		}else if(altura_inicial>altura_final){ //contrae
			yVert1 =(yVert1+(altura_inicial-altura_final));
			yVert2 = yVert1;
		}

		vertice1->setX(xVert1);
		vertice1->setY(yVert1);
		vertice2->setX(xVert2);
		vertice2->setY(yVert2);
		vertice3->setX(xVert3);
		vertice3->setY(yVert3);

		return 0;

}

int calcularVerticesBaseDerecha(Posicion*vertice1,Posicion*vertice2,Posicion*vertice3,int lado){

	double xVert1 = vertice1->getX();
	double yVert1 = vertice1->getY();
	double xVert2 = vertice2->getX();
	double yVert2 = vertice2->getY();
	double xVert3 = vertice3->getX();
	double yVert3 = vertice3->getY();

	double lado_inicial = 0;
	double altura_inicial = 0;
	double altura_final = 0;


		if(diferenciaEnY(vertice1,vertice2)==1){ //y1>y2
			lado_inicial = yVert1 - yVert2;
			if(lado_inicial<lado){ //expandir triangulo
				yVert2=(yVert3-(lado/2));
				yVert1=(yVert3+(lado/2));
				//xVert3 = xVert3 + (xVert1-xVert2)/2;
			}else if(lado_inicial>lado){ //contraer triangulo
				yVert2=(yVert3+(lado/2));
				yVert1=(yVert3-(lado/2));
				//xVert3= xVert3 + (xVert1-xVert2)/2;
		    }

		}else{ //x1<x2
			lado_inicial = yVert2 - yVert1;
			std::cout<<lado_inicial<<"lado"<<lado<<endl;
			if(lado_inicial<lado){ //expandir triangulo
				yVert1=(yVert3-(lado/2));
				yVert2=(yVert3+(lado/2));

			}else if(lado_inicial>lado){ //contraer triangulo
				yVert1=(yVert3+(lado/2));
				yVert2=(yVert3-(lado/2));

			}


		}

		altura_inicial = (lado_inicial * sqrt(3))/2;
		altura_final = (lado * sqrt(3))/2;

		if(altura_inicial<altura_final){ //expande
			xVert1 =(xVert1+(altura_final-altura_inicial));
			xVert2 = xVert1;
		}else if(altura_inicial>altura_final){ //contrae
			xVert1 =(xVert1-(altura_inicial-altura_final));
			xVert2 = xVert1;
		}

		vertice1->setX(xVert1);
		vertice1->setY(yVert1);
		vertice2->setX(xVert2);
		vertice2->setY(yVert2);
		vertice3->setX(xVert3);
		vertice3->setY(yVert3);

		return 0;

}

int calcularVerticesBaseIzquierda(Posicion*vertice1,Posicion*vertice2,Posicion*vertice3,int lado){

	double xVert1 = vertice1->getX();
	double yVert1 = vertice1->getY();
	double xVert2 = vertice2->getX();
	double yVert2 = vertice2->getY();
	double xVert3 = vertice3->getX();
	double yVert3 = vertice3->getY();

	double lado_inicial = 0;
	double altura_inicial = 0;
	double altura_final = 0;

		if(diferenciaEnY(vertice1,vertice2)==1){ //y1>y2
			lado_inicial = yVert1 - yVert2;
			if(lado_inicial<lado){ //expandir triangulo
				yVert2=(yVert3-(lado/2));
				yVert1=(yVert3+(lado/2));
				//xVert3 = xVert3 + (xVert1-xVert2)/2;
			}else if(lado_inicial>lado){ //contraer triangulo
				yVert2=(yVert3+(lado/2));
				yVert1=(yVert3-(lado/2));
				//xVert3= xVert3 + (xVert1-xVert2)/2;
		    }

		}else{ //x1<x2
			lado_inicial = yVert2 - yVert1;
			std::cout<<lado_inicial<<"lado"<<lado<<endl;
			if(lado_inicial<lado){ //expandir triangulo
				yVert1=(yVert3-(lado/2));
				yVert2=(yVert3+(lado/2));

			}else if(lado_inicial>lado){ //contraer triangulo
				yVert1=(yVert3+(lado/2));
				yVert2=(yVert3-(lado/2));

			}


		}

		altura_inicial = (lado_inicial * sqrt(3))/2;
		altura_final = (lado * sqrt(3))/2;

		if(altura_inicial<altura_final){ //expande
			xVert1 =(xVert1-(altura_final-altura_inicial));
			xVert2 = xVert1;
		}else if(altura_inicial>altura_final){ //contrae
			xVert1 =(xVert1+(altura_inicial-altura_final));
			xVert2 = xVert1;
		}

		vertice1->setX(xVert1);
		vertice1->setY(yVert1);
		vertice2->setX(xVert2);
		vertice2->setY(yVert2);
		vertice3->setX(xVert3);
		vertice3->setY(yVert3);

		return 0;

}

int Triangulo::calcularVerticesSegunLado(){




	//recta1 formado por vert1 y vert2
	//recta2 formado por vert2 y vert3
	//recta3 formado por vert1 y vert3

	if(isBase(this->recta1)==0){
		if(getBase().compare(BASE_TRIANGULO_ABAJO)==0)
		calcularVerticesBaseAbajo(this->vertice1,this->vertice2,this->vertice3,this->lado);
			else if(getBase().compare(BASE_TRIANGULO_ARRIBA)==0)
			calcularVerticesBaseArriba(this->vertice1,this->vertice2,this->vertice3,this->lado);
				else if(getBase().compare(BASE_TRIANGULO_DERECHA)==0)
				calcularVerticesBaseDerecha(this->vertice1,this->vertice2,this->vertice3,this->lado);
					else if(getBase().compare(BASE_TRIANGULO_IZQUIERDA)==0)
						calcularVerticesBaseIzquierda(this->vertice1,this->vertice2,this->vertice3,this->lado);
		return 0;
	}else if(isBase(this->recta2)==0){
		if(getBase().compare(BASE_TRIANGULO_ABAJO)==0)
		calcularVerticesBaseAbajo(this->vertice2,this->vertice3,this->vertice1,this->lado);
			else if(getBase().compare(BASE_TRIANGULO_ARRIBA)==0)
			calcularVerticesBaseArriba(this->vertice2,this->vertice3,this->vertice1,this->lado);
				else if(getBase().compare(BASE_TRIANGULO_DERECHA)==0)
				calcularVerticesBaseDerecha(this->vertice2,this->vertice3,this->vertice1,this->lado);
					else if(getBase().compare(BASE_TRIANGULO_IZQUIERDA)==0)
						calcularVerticesBaseIzquierda(this->vertice2,this->vertice3,this->vertice1,this->lado);
		return 0;
	}else if(isBase(this->recta3)==0){
		if(getBase().compare(BASE_TRIANGULO_ABAJO)==0)
		calcularVerticesBaseAbajo(this->vertice1,this->vertice3,this->vertice2,this->lado);
			else if(getBase().compare(BASE_TRIANGULO_ARRIBA)==0)
			calcularVerticesBaseArriba(this->vertice1,this->vertice3,this->vertice2,this->lado);
				else if(getBase().compare(BASE_TRIANGULO_DERECHA)==0)
				calcularVerticesBaseDerecha(this->vertice1,this->vertice3,this->vertice2,this->lado);
					else if(getBase().compare(BASE_TRIANGULO_IZQUIERDA)==0)
						calcularVerticesBaseIzquierda(this->vertice1,this->vertice3,this->vertice2,this->lado);
		return 0;

	}

	return -1; //el triangulo no tiene una base bien definida, por lo que no se pueden modificar los vertices y por ende su lado
}


Triangulo::Triangulo(std::string id,Posicion *ver1,Posicion *ver2,Posicion *ver3,int lado){
	this->id = id;
	this->vertice1 = ver1;
	this->vertice2 = ver2;
	this->vertice3 = ver3;
	this->lado = lado;

	this->x1 = new int(0);
	this->x2 = new int(0);
	this->y1 = new int(0);
	this->y2 = new int(0);

	this->recta1 = new Recta(ver1->getX(),ver2->getX(),ver1->getY(),ver2->getY());
	this->recta2 = new Recta(ver1->getX(),ver3->getX(),ver1->getY(),ver3->getY());
	this->recta3 = new Recta(ver2->getX(),ver3->getX(),ver2->getY(),ver3->getY());

	darNombreBaseTriangulo(ver1,ver2,ver3);

	calcularVerticesSegunLado();

	Posicion*  ejeDeCordenadas = hallarEjeDeCordenadas(this->getVertice1(),this->getVertice2(),this->getVertice3());

	int maxValorX = hallarDominio(this->getVertice1()->getX(),this->getVertice2()->getX(),this->getVertice3()->getX());
	int	maxValorY = hallarDominio(this->getVertice1()->getY(),this->getVertice2()->getY(),this->getVertice3()->getY());
	this->setAltoInfluencia(maxValorY);
	this->setAnchoInfluencia(maxValorX);
	this->setXInfluencia(ejeDeCordenadas->getX());
	this->setYInfluencia(ejeDeCordenadas->getY()-maxValorY);
	delete this->recta1;
	delete this->recta2;
	delete this->recta3;
	this->recta1 = new Recta(this->vertice1->getX(),this->vertice2->getX(),this->vertice1->getY(),this->vertice2->getY());
	this->recta2 = new Recta(this->vertice1->getX(),this->vertice3->getX(),this->vertice1->getY(),this->vertice3->getY());
	this->recta3 = new Recta(this->vertice2->getX(),this->vertice3->getX(),this->vertice2->getY(),this->vertice3->getY());


}



std::string Triangulo::getBase(){
	return this->base;
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

	if( i+ejeDeCoordenadas->getX()>=0 && i+ejeDeCoordenadas->getX()<= Escenario::obtenerInstancia()->getAncho() && ejeDeCoordenadas->getY()-j>=0 && ejeDeCoordenadas->getY()-j < Escenario::obtenerInstancia()->getAlto() )
		this->putpixel(screen,i+ejeDeCoordenadas->getX(),ejeDeCoordenadas->getY()-j,this->color);

}



int Triangulo::dibujar(SDL_Surface *screen){



//	this->dibujarLinea(getColorLinea()->getColor(),screen ,this->getVertice1()->getX(),  this->getVertice1()->getY(), this->getVertice2()->getX(), this->getVertice2()->getY());
//	this->dibujarLinea(getColorLinea()->getColor(),screen ,this->getVertice1()->getX(),  this->getVertice1()->getY(), this->getVertice3()->getX(), this->getVertice3()->getY());
//	this->dibujarLinea(getColorLinea()->getColor(),screen ,this->getVertice2()->getX(),  this->getVertice2()->getY(), this->getVertice3()->getX(), this->getVertice3()->getY());

	this->color = getColorFigura()->getColor();

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


	int mayorDeXY = mayor(maxValorX, maxValorY);
	 SDL_Surface* image;
		//	 Cargamos la imagen
		if(this->imagen==NULL){
	//si la textura no es NULL es porque le seteo algun idTextura
	if(this->getIdTextura().compare("NULL") != 0){
		//si se le seteo algun idTextura busco el path
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->getIdTextura());

		//si el path NO es NULL intento levantar la imagen
		if(path.compare("NULL") != 0){
			image = IMG_Load (path.begin());

			//si la imagen no es null (es decir si la levanto bien) la escalo
			if(image != NULL){
				image = ScaleSurface(image, mayorDeXY, mayorDeXY);
			}
			//si no la levanto es porque el path no es correcto o la imagen no existe
			else{
				escribirMensajeLog(*Escenario::obtenerInstancia()->getLog(),"error al intentar cargar la imagen: "+path);
			}


		}
		//si el path ES null, tiro error (no existe path para dicho idTextura)
		else{

			escribirMensajeLog(*Escenario::obtenerInstancia()->getLog(),"no se encontro el path correspondiente al idTextura: "+this->getIdTextura());
		}

	}
	//si el idTextura es NULL intento levantar la imagen del escenario por default
	else{
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(Escenario::obtenerInstancia()->getTexturaFig());
		image = IMG_Load (path.begin());
		if(image != NULL){
						image = ScaleSurface(image, mayorDeXY, mayorDeXY);
	  }

	}
//	SDL_SetColorKey(image,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(image->format,255 ,255, 255));
			this->imagen = SDL_DisplayFormat(image);
			this->imagenAuxiliar=this->imagen;
			  SDL_FreeSurface(image);
		}
		//aca verifico si el bonus esta activo y le seteo la imagen del dispersor
		if(this->imagenBonus!=NULL && !this->getEscalada()){
				this->imagenBonus=ScaleSurface(this->imagenBonus, mayorDeXY, mayorDeXY);
				this->imagen = SDL_DisplayFormat(this->imagenBonus);
				this->setEscalada(true);
			}

				if(this->imagenBonus==NULL){
					this->imagen=this->imagenAuxiliar;
				}



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

	delete ejeDeCordenadas;
	delete ver1;
	delete ver2;
	delete ver3;


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


void Triangulo::calcularRadioDeInfluencia(){

	//TODO
}
