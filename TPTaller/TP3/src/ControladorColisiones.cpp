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
#include <list>

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

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion PrimerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}


			}else{

				nuevaDireccion=((anguloDeltejo)+(anguloConAbcisa));
				nuevaDireccion=PI-(2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));

				if(DEBUG2==1){
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

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  PrimerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;

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

				if(DEBUG2==1){

					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  PrimerCuadrante 4  "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;

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

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}



			}else{
				nuevaDireccion=(anguloDeltejo-anguloConAbcisa);
				nuevaDireccion=(PI-2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));

				if(DEBUG2==1){
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

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;

				}



			}else{
				nuevaDireccion=(anguloDeltejo-PI/2)-(PI/2-anguloConAbcisa);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));

				if(DEBUG2==1){
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

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}


			}else{
				nuevaDireccion=((anguloDeltejo-PI)+anguloConAbcisa);
				nuevaDireccion=(PI-nuevaDireccion);
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));

				if(DEBUG2==1){
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

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y : figura  "<<posicionY<<endl;

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


				if(DEBUG2==1){
				    std::cout<<"posicsion Y : figura  "<<posicionY<<endl;
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 4  "<<(nuevaDireccion*180)/PI<<endl;

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


				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}

			}else{
				nuevaDireccion=(anguloDeltejo-3*PI/2)+(PI/2-anguloConAbcisa);
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));


				if(DEBUG2==1){
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


				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;
					std::cout<<"posicsion Y figura :   "<<posicionY<<endl;

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


				if(DEBUG2==1){
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




int ControladorColisiones::getTipoPendienteCeroOInfinito(Triangulo* triangulo){
		Recta* recta1=triangulo->getRecta1();
		Recta* recta2=triangulo->getRecta2();
		Recta* recta3=triangulo->getRecta3();
       if(recta1->getInfinito()==-1||recta2->getInfinito()==-1||recta3->getInfinito()==-1){
    	   if(DEBUG2==1){
    		   std::cout<<" tipo de pendiente infinito "<<endl;
    	   }
         return -1;
       }else{
    	   if(recta1->getPendiente()==0||recta2->getPendiente()==0||recta3->getPendiente()==0){
			   if(DEBUG2==1){
    		   std::cout<<" tipo de pendiente cero "<<endl;
    	   }
    		   return 0;
    	   }
       }
 }









void ControladorColisiones::acelerarTejo(Tejo* tejo){
	tejo->moverTejo();
	tejo->moverTejo();
	tejo->moverTejo();
}

void ControladorColisiones::decidirDireccionPrimerCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo){
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
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion PrimerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}


			}else{

				nuevaDireccion=((anguloDeltejo)+(anguloConAbcisa));
				nuevaDireccion=PI-(2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion PrimerCuadrante 2  :"<<(nuevaDireccion*180)/PI<<endl;
				}




			}
		}else{
			if(getTipoPendienteCeroOInfinito(triangulo)==-1){
				nuevaDireccion=anguloDeltejo -anguloConAbcisa;
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=anguloDeltejo-2*nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  PrimerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;


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
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){

					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  PrimerCuadrante 4  "<<(nuevaDireccion*180)/PI<<endl;


				}




			}

		}
		delete rectaDireccionTejo;

	}
}
void ControladorColisiones::decidirDireccionSegundoCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo){
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
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}



			}else{
				nuevaDireccion=(anguloDeltejo-anguloConAbcisa);
				nuevaDireccion=(PI-2*nuevaDireccion);
				nuevaDireccion=anguloDeltejo+PI+nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 2 "<<(nuevaDireccion*180)/PI<<endl;
				}



			}
		}else{
			if(getTipoPendienteCeroOInfinito(triangulo)==-1){
				nuevaDireccion=PI/2-((anguloDeltejo-PI/2)+anguloConAbcisa);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion+PI/12);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;


				}



			}else{
				nuevaDireccion=(anguloDeltejo-PI/2)-(PI/2-anguloConAbcisa);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion  SegundoCuadrante 4 "<<(nuevaDireccion*180)/PI<<endl;

					system("PAUSE");
				}



			}
		}
	}
	delete rectaDireccionTejo;

}
void ControladorColisiones::decidirDireccionTercerCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo){
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
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}


			}else{
				nuevaDireccion=((anguloDeltejo-PI)+anguloConAbcisa);
				nuevaDireccion=(PI-nuevaDireccion);
				nuevaDireccion=(anguloDeltejo+2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 2  : "<<(nuevaDireccion*180)/PI<<endl;
				}



			}
		}else{
			if(getTipoPendienteCeroOInfinito(triangulo)==0){
				anguloAux=(anguloDeltejo-PI);
				nuevaDireccion=anguloConAbcisa-anguloAux;
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=anguloDeltejo+2*nuevaDireccion;
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);
				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 3  "<<(nuevaDireccion*180)/PI<<endl;


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
				ControladorColisiones::acelerarTejo( tejo);

				if(DEBUG2==1){

					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion TercerCuadrante 4  "<<(nuevaDireccion*180)/PI<<endl;

				}





			}
		}
	}
	delete rectaDireccionTejo;
}
void ControladorColisiones::decidirDireccionCuartoCuadranteTriangulo(Recta* rectaDeColision,Tejo* tejo,Triangulo* triangulo){
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
				ControladorColisiones::acelerarTejo( tejo);

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 1 "<<(nuevaDireccion*180)/PI<<endl;
				}

			}else{
				nuevaDireccion=(anguloDeltejo-3*PI/2)+(PI/2-anguloConAbcisa);
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 2"<<(nuevaDireccion*180)/PI<<endl;
				}

			}
		}else{
			if(getTipoPendienteCeroOInfinito(triangulo)==0){
				nuevaDireccion=anguloConAbcisa-(2*PI-anguloDeltejo);
				if(nuevaDireccion<(5*PI)/180){
					nuevaDireccion=(5*PI)/180;
				}
				nuevaDireccion=(anguloDeltejo-2*nuevaDireccion);
				tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(nuevaDireccion));
				ControladorColisiones::acelerarTejo( tejo);

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 3 "<<(nuevaDireccion*180)/PI<<endl;


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
				ControladorColisiones::acelerarTejo( tejo);

				if(DEBUG2==1){
					std::cout<<"anguloConAbcisa  "<<(anguloConAbcisa*180)/PI<<endl;
					std::cout<<"nuevaDireccion CuartoCuadrante 4 "<<(nuevaDireccion*180)/PI<<endl;
				
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
			if(DEBUG2==1){
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
	if(DEBUG2==1){
		std::cout<<"distanciaMinimaEntreRadios   :"<<distanciaMinimaEntreRadios<<endl;
		std::cout<<"distanciaEntreRadios  :"<<distanciaEntreRadios<<"  -- "<<endl;
	}
	if(distanciaMinimaEntreRadios>=distanciaEntreRadios){

		if(figura->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);

		}
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


void sacarDelAmbitoDelTriangulo(Tejo* tejo,Triangulo* figura){
	int wTejo, hTejo, wFigura, hFigura, xTejo, yTejo, xFigura, yFigura;
	wTejo = hTejo = tejo->getRadio()*2;
	xTejo = tejo->getX()-tejo->getRadio();
	yTejo = tejo->getY()-tejo->getRadio();
	   wFigura = figura->getAnchoInfluencia();
		hFigura = figura->getAltoInfluencia();
		xFigura = figura->getXInfluencia();
		yFigura = figura->getYInfluencia();
		while(((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){
			tejo->moverTejo();
			wTejo = hTejo = tejo->getRadio()*2;
			xTejo = tejo->getX()-tejo->getRadio();
			yTejo = tejo->getY()-tejo->getRadio();

		}
	}
void asignarDireccionTrianguloConPendienteInfinito(Tejo* tejo,Recta* recta,Triangulo* triangulo){
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
void asignarDireccionTrianguloConPendienteCero(Tejo* tejo,Recta* recta){
if (recta->getOrdenada() > tejo->getY()){
	reboteAbajo(tejo);
	std::cout<<"ABAJO"<<endl;
}
else{
	reboteArriba(tejo);
	std::cout<<"ARRIBA"<<endl;
}
}
void ControladorColisiones::asignarDireccionTrianguloConPendiente(Tejo* tejo,Recta* recta,Triangulo* triangulo){
	double anguloDeltejo = tejo->getDireccion()->getFi();
	if (CalculosMatematicos::isCuartoCuadrante(anguloDeltejo)){
		decidirDireccionCuartoCuadrante(recta,tejo,0);
		 sacarDelAmbitoDelTriangulo(tejo, triangulo);
	}else
		if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
			decidirDireccionTercerCuadrante(recta,tejo,0);
			 sacarDelAmbitoDelTriangulo(tejo, triangulo);
		}else
			if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
				decidirDireccionSegundoCuadrante(recta,tejo,0);
				 sacarDelAmbitoDelTriangulo(tejo, triangulo);
			}else
				if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){
					decidirDireccionPrimerCuadrante(recta,tejo,0);
					 sacarDelAmbitoDelTriangulo(tejo, triangulo);
				}

}
Posicion* ControladorColisiones::hallarPuntoTriangulo(Recta* recta, int x, int y){

	Recta aux;
	int xAux, yAux;

	aux.setPendiente(-1/recta->getPendiente());
	aux.setOrdenada(y - (x*aux.getPendiente()));

	xAux = (aux.getOrdenada()-recta->getOrdenada())/(recta->getPendiente()-aux.getPendiente());
	yAux = aux.getPendiente()*xAux+aux.getOrdenada();
	return new Posicion(xAux,yAux);


}
bool  ControladorColisiones::isPuntoZonaDeInfluenciaTejo(Posicion* posicion,Tejo* tejo ){
	bool fueraDeZonaInfluencia;

	int wFigura, hFigura, xFigura, yFigura;
			wFigura = tejo->getRadio()*2-tejo->getRadio()*2*0.1;
			hFigura = tejo->getRadio()*2-tejo->getRadio()*2*0.1;
			xFigura = tejo->getX()-tejo->getRadio();
			yFigura = tejo->getY()-tejo->getRadio();
			if(DEBUG==1){
			std::cout << "x  " << posicion->getX()<<"y " << posicion->getX()<<endl;
			std::cout << "wFigura  " << wFigura<<"hFigura   " << hFigura<<endl;
			std::cout << "xFigura  " << xFigura<<"yFigura   " << yFigura<<endl;
			}
			if((posicion->getX() >= xFigura) && (posicion->getY()>= yFigura) && ((xFigura + wFigura) >= posicion->getX()) && ((yFigura + hFigura) >= posicion->getY())){
				fueraDeZonaInfluencia=true;
			}
			else{
				fueraDeZonaInfluencia = false;
			}
			return fueraDeZonaInfluencia;

}
bool  ControladorColisiones::getZonaDeInfluencia(Recta* rectaDireccionTejo,Recta*recta,Triangulo* triangulo,Tejo*tejo ){
	bool fueraDeZonaInfluencia;
	//si la colision se da fuera de la zona de infl. no se evalua

//	Posicion* posicion = rectaDireccionTejo->getInterseccion(recta);
	Posicion* posicion = hallarPuntoTriangulo(recta,tejo->getX(),tejo->getY());
	std::cout<<"punto del triangulo"<<posicion->getX()<<"-:"<<posicion->getY()<<endl;
		if (posicion->getX()< triangulo->getXInfluencia()
				|| posicion->getY()< triangulo->getYInfluencia()
				|| posicion->getX()>(triangulo->getXInfluencia()+triangulo->getAnchoInfluencia())
				|| posicion->getY()>(triangulo->getYInfluencia()+triangulo->getAltoInfluencia()))
			fueraDeZonaInfluencia = true;
		else
			fueraDeZonaInfluencia = false;
		delete posicion;
return fueraDeZonaInfluencia;
}
bool ControladorColisiones::isPuntoZonaDeInfluenciaTriangulo(Posicion* posicion,Triangulo* triangulo ){
	bool fueraDeZonaInfluencia=false;

          if(DEBUG==1)
            std::cout<<"interseccion     punto x "<<posicion->getX()<<"punto y  "<<posicion->getY()<<endl;
	int wFigura, hFigura, xFigura, yFigura;
			wFigura = triangulo->getAnchoInfluencia();
			hFigura = triangulo->getAltoInfluencia();
			xFigura = triangulo->getXInfluencia();
			yFigura = triangulo->getYInfluencia();


			if((posicion->getX() >= xFigura) && (posicion->getY()>= yFigura) && ((xFigura + wFigura) >= posicion->getX()) && ((yFigura + hFigura) >= posicion->getY())){
				fueraDeZonaInfluencia=true;
			}
			else{
				fueraDeZonaInfluencia = false;
				}

			return fueraDeZonaInfluencia;


}

void ControladorColisiones::asignarDireccionTriangulo(Tejo* tejo,Recta* recta,Triangulo* triangulo){

	//analisis con recta paralela al eje Y
	if (recta->getInfinito() == -1){
		asignarDireccionTrianguloConPendienteInfinito(tejo,recta,triangulo);
		if(triangulo->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);
		}
	}
	else{
			if (recta->getPendiente() == 0){
				asignarDireccionTrianguloConPendienteCero(tejo,recta);
				if(triangulo->getTieneBonus()){
					tejo->setChocoFiguraConBonus(true);
				}
			}
			else{

				asignarDireccionTrianguloConPendiente(tejo,recta,triangulo);
				if(triangulo->getTieneBonus()){
					tejo->setChocoFiguraConBonus(true);
				}



		}
	}

}
Recta* ControladorColisiones::getRectaDeColision(Triangulo* triangulo,Tejo* tejo){
	Recta* recta=NULL; //Recta con la que estoy mas cerca
	Recta* recta1=triangulo->getRecta1();
	Recta* recta2=triangulo->getRecta2();
	Recta* recta3=triangulo->getRecta3();
	Recta*  rectaDireccionTejo=tejo->getRectaDireccion();
	if(DEBUG==1){
				recta3->toString();
				recta2->toString();
				recta1->toString();
				rectaDireccionTejo->toString();
			}


	Posicion* posicion1=rectaDireccionTejo->getInterseccion(recta1);
	Posicion* posicion2=rectaDireccionTejo->getInterseccion(recta2);
	Posicion* posicion3=rectaDireccionTejo->getInterseccion(recta3);
	if(DEBUG==1){
		 if(posicion1!=NULL)
		std::cout<<"posicion1 X "<<posicion1->getX()<<" y: "<<posicion1->getX()<<endl;
		 if(posicion2!=NULL)
		std::cout<<"posicion2 X "<<posicion2->getX()<<" y: "<<posicion2->getX()<<endl;
		 if(posicion3!=NULL)
		std::cout<<"posicion3 X "<<posicion3->getX()<<" y: "<<posicion3->getX()<<endl;

	}

	double d_r1 = hallarDistancia(recta1, tejo->getX(),tejo->getY());
	double d_r2 = hallarDistancia(recta2, tejo->getX(),tejo->getY());
	double d_r3 = hallarDistancia(recta3, tejo->getX(),tejo->getY());

	if(isPuntoZonaDeInfluenciaTriangulo(posicion1,triangulo)){
		if (d_r1 < d_r2 && d_r1 < d_r3){
			if(DEBUG==1){
				recta1->toString();
				std::cout<<"posicion1 X "<<posicion1->getX()<<" y: "<<posicion1->getX()<<" distancia "<<d_r1<<endl;
			}
			recta1->setDistancia(d_r1);
			delete posicion1;
			delete posicion2;
			delete posicion3;
			delete rectaDireccionTejo;
			return recta1;
		}
	}
	if(isPuntoZonaDeInfluenciaTriangulo(posicion2,triangulo)){
		if (d_r2 < d_r1 && d_r2 < d_r3){
			if(DEBUG==1){
				recta2->toString();
				std::cout<<"posicion1 X "<<posicion2->getX()<<" y: "<<posicion2->getX()<<" distancia "<<d_r2<<endl;
				system("PAUSE");
			}
			recta1->setDistancia(d_r2);
			delete posicion1;
			delete posicion2;
			delete posicion3;
			delete rectaDireccionTejo;
			return recta2;
		}
	}
	if(isPuntoZonaDeInfluenciaTriangulo(posicion3,triangulo)){
		if (d_r3 < d_r1 && d_r3 < d_r2){
			if(DEBUG==1){
				recta3->toString();
				std::cout<<"posicion1 X "<<posicion3->getX()<<" y: "<<posicion3->getX()<<" distancia "<<d_r3<<endl;
				system("PAUSE");
			}
			recta1->setDistancia(d_r3);
			delete posicion1;
			delete posicion2;
			delete posicion3;
			delete rectaDireccionTejo;
			return recta3;
		}
	}

	             delete posicion1;
				delete posicion2;
				delete posicion3;
				delete rectaDireccionTejo;
				return NULL;
}

/* Los vertices 1 y 2 estarán en rectaBase, y el vertice 3 será el vertice opuesto */
void ControladorColisiones::asignarVerticesSegunBase(Recta*rectaBase, Triangulo*triangulo, Posicion*vertice1, Posicion*vertice2, Posicion*vertice3){
	int x1 = rectaBase->getX1();
	int y1 = rectaBase->getY1();
	int x2 = rectaBase->getX2();
	int y2 = rectaBase->getY2();
/*
	std::cout<<"x1: "<<x1<<endl;
	std::cout<<"x2: "<<x2<<endl;

	std::cout<<"y1: "<<x1<<endl;
	std::cout<<"y2: "<<x1<<endl;
*/
	if(triangulo->getVertice1()->getX()==x1 && triangulo->getVertice1()->getY()==y1){
		vertice1->setX(triangulo->getVertice1()->getX());
		vertice1->setY(triangulo->getVertice1()->getY());
		//std::cout<<"vertice1 es 1: "<<endl;
	}else if(triangulo->getVertice2()->getX()==x1 && triangulo->getVertice2()->getY()==y1){
		vertice1->setX(triangulo->getVertice2()->getX());
		vertice1->setY(triangulo->getVertice2()->getY());
		//std::cout<<"vertice1 es 2: "<<endl;
	}else if(triangulo->getVertice3()->getX()==x1 && triangulo->getVertice3()->getY()==y1){
		vertice1->setX(triangulo->getVertice3()->getX());
		vertice1->setY(triangulo->getVertice3()->getY());
		//std::cout<<"vertice1 es 3: "<<endl;
	}

	if(triangulo->getVertice1()->getX()==x2 && triangulo->getVertice1()->getY()==y2){
			vertice2->setX(triangulo->getVertice1()->getX());
			vertice2->setY(triangulo->getVertice1()->getY());
			//std::cout<<"vertice2 es 1: "<<endl;
	}else if(triangulo->getVertice2()->getX()==x2 && triangulo->getVertice2()->getY()==y2){
			vertice2->setX(triangulo->getVertice2()->getX());
			vertice2->setY(triangulo->getVertice2()->getY());
			//std::cout<<"vertice2 es 2: "<<endl;
	}else if(triangulo->getVertice3()->getX()==x2 && triangulo->getVertice3()->getY()==y2){
			vertice2->setX(triangulo->getVertice3()->getX());
			vertice2->setY(triangulo->getVertice3()->getY());
			//std::cout<<"vertice2 es 3: "<<endl;
	}

	if(vertice1->compare(triangulo->getVertice1())!=0 && vertice2->compare(triangulo->getVertice1())!=0){
		vertice3->setX(triangulo->getVertice1()->getX());
		vertice3->setY(triangulo->getVertice1()->getY());
		//std::cout<<"vertice3 es 1: "<<endl;
	}else if(vertice1->compare(triangulo->getVertice2())!=0 && vertice2->compare(triangulo->getVertice2())!=0){
		vertice3->setX(triangulo->getVertice2()->getX());
		vertice3->setY(triangulo->getVertice2()->getY());
		//std::cout<<"vertice3 es 2: "<<endl;
	}else if(vertice1->compare(triangulo->getVertice3())!=0 && vertice2->compare(triangulo->getVertice3())!=0){
		vertice3->setX(triangulo->getVertice3()->getX());
		vertice3->setY(triangulo->getVertice3()->getY());
		//std::cout<<"vertice3 es 3: "<<endl;
	}


std::cout<<"vertice1: "<<vertice1->getX()<<", "<<vertice1->getY()<<endl;
std::cout<<"vertice2: "<<vertice2->getX()<<", "<<vertice2->getY()<<endl;
std::cout<<"vertice3: "<<vertice3->getX()<<", "<<vertice3->getY()<<endl;

//system("PAUSE");

}

double  ControladorColisiones::colisionVerticeEnBaseDerecha(Triangulo*triangulo, Tejo*tejo, Posicion*verticeChoque, Posicion*vertice1, Posicion*vertice2, Posicion*vertice3){

	double anguloTejo = tejo->getDireccion()->getFi();


			std::cout<<"vertice1: "<<vertice1->getX()<<", "<<vertice1->getY()<<endl;
			std::cout<<"vertice2: "<<vertice2->getX()<<", "<<vertice2->getY()<<endl;
			std::cout<<"vertice3: "<<vertice3->getX()<<", "<<vertice3->getY()<<endl;
			std::cout<<"verticeChoque: "<<verticeChoque->getX()<<", "<<verticeChoque->getY()<<endl;

			if(vertice1->compare(verticeChoque)==0 || vertice2->compare(verticeChoque)==0){

				if(vertice2->compare(verticeChoque)==0){
					if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
						std::cout<<"1"<<endl;
						return tejo->getDireccion()->getFi() - (PI/8);
					}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
						std::cout<<"2"<<endl;
						return tejo->getDireccion()->getFi() + PI/2;
					}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
						std::cout<<"3"<<endl;
						return tejo->getDireccion()->getFi() + PI/2;
					}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
						std::cout<<"4"<<endl;
						return tejo->getDireccion()->getFi() + (3*PI/2);
					}
				}else{
					if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
						std::cout<<"5"<<endl;
						return tejo->getDireccion()->getFi() - (3*PI/2);
					}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
						std::cout<<"6"<<endl;
						return tejo->getDireccion()->getFi() - PI/2;
					}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
						std::cout<<"7"<<endl;
						return tejo->getDireccion()->getFi() - PI/2;
					}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
						std::cout<<"8"<<endl;
						return tejo->getDireccion()->getFi() + (PI/8);
					}
				}

			}else if(vertice3->compare(verticeChoque)==0){

				if(CalculosMatematicos::isSegundoCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"9"<<endl;
					return tejo->getDireccion()->getFi() + PI/8;
				}else if(CalculosMatematicos::isTercerCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"10"<<endl;
					return tejo->getDireccion()->getFi() - PI/8;
				}else if(CalculosMatematicos::isCuartoCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"11"<<endl;
					return tejo->getDireccion()->getFi() - (PI/2);
				}else if(CalculosMatematicos::isPrimerCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"12"<<endl;
					return tejo->getDireccion()->getFi()+(PI/2);
				}
			}

				return 0;
}

double  ControladorColisiones::colisionVerticeEnBaseIzquierda(Triangulo*triangulo, Tejo*tejo, Posicion*verticeChoque, Posicion*vertice1, Posicion*vertice2, Posicion*vertice3){

	double anguloTejo = tejo->getDireccion()->getFi();


			std::cout<<"vertice1: "<<vertice1->getX()<<", "<<vertice1->getY()<<endl;
			std::cout<<"vertice2: "<<vertice2->getX()<<", "<<vertice2->getY()<<endl;
			std::cout<<"vertice3: "<<vertice3->getX()<<", "<<vertice3->getY()<<endl;
			std::cout<<"verticeChoque: "<<verticeChoque->getX()<<", "<<verticeChoque->getY()<<endl;

			if(vertice1->compare(verticeChoque)==0 || vertice2->compare(verticeChoque)==0){

				if(vertice2->compare(verticeChoque)==0){
					if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
						std::cout<<"1"<<endl;
						return tejo->getDireccion()->getFi() - (PI/2);
					}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
						std::cout<<"2"<<endl;
						return tejo->getDireccion()->getFi() - PI/2;
					}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
						std::cout<<"3"<<endl;
						return tejo->getDireccion()->getFi() + PI/2;
					}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
						std::cout<<"4"<<endl;
						return tejo->getDireccion()->getFi() + (3*PI/2);
					}
				}else{
					if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
						std::cout<<"5"<<endl;
						return tejo->getDireccion()->getFi() - (3*PI/2);
					}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
						std::cout<<"6"<<endl;
						return tejo->getDireccion()->getFi() - PI/2;
					}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
						std::cout<<"7"<<endl;
						return tejo->getDireccion()->getFi() - PI/8;
					}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
						std::cout<<"8"<<endl;
						return tejo->getDireccion()->getFi() - (PI/2);
					}
				}

			}else if(vertice3->compare(verticeChoque)==0){

				if(CalculosMatematicos::isSegundoCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"9"<<endl;
					return tejo->getDireccion()->getFi() - PI/2;
				}else if(CalculosMatematicos::isTercerCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"10"<<endl;
					return tejo->getDireccion()->getFi() + PI/2;
				}else if(CalculosMatematicos::isCuartoCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"11"<<endl;
					return tejo->getDireccion()->getFi() + (PI/8);
				}else if(CalculosMatematicos::isPrimerCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"12"<<endl;
					return tejo->getDireccion()->getFi()-(PI/8);
				}
			}

				return 0;
}

double  ControladorColisiones::colisionVerticeEnBaseAbajo(Triangulo*triangulo, Tejo*tejo, Posicion*verticeChoque, Posicion*vertice1, Posicion*vertice2, Posicion*vertice3){

	double anguloTejo = tejo->getDireccion()->getFi();


		std::cout<<"vertice1: "<<vertice1->getX()<<", "<<vertice1->getY()<<endl;
		std::cout<<"vertice2: "<<vertice2->getX()<<", "<<vertice2->getY()<<endl;
		std::cout<<"vertice3: "<<vertice3->getX()<<", "<<vertice3->getY()<<endl;
		std::cout<<"verticeChoque: "<<verticeChoque->getX()<<", "<<verticeChoque->getY()<<endl;

		if(vertice1->compare(verticeChoque)==0 || vertice2->compare(verticeChoque)==0){

			if(vertice2->compare(verticeChoque)==0){
				if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
					std::cout<<"1"<<endl;
					return tejo->getDireccion()->getFi() + (PI/8);
				}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
					std::cout<<"2"<<endl;
					return tejo->getDireccion()->getFi() + PI/2;
				}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
					std::cout<<"3"<<endl;
					return tejo->getDireccion()->getFi() + PI/2;
				}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
					std::cout<<"4"<<endl;
					return tejo->getDireccion()->getFi() + (3*PI/2);
				}
			}else{
				if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
					std::cout<<"5"<<endl;
					return tejo->getDireccion()->getFi() - (PI/2);
				}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
					std::cout<<"6"<<endl;
					return tejo->getDireccion()->getFi() - PI/8;
				}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
					std::cout<<"7"<<endl;
					return tejo->getDireccion()->getFi() + PI/2;
				}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
					std::cout<<"8"<<endl;
					return tejo->getDireccion()->getFi() + PI/2;
				}
			}

		}else if(vertice3->compare(verticeChoque)==0){

			if(CalculosMatematicos::isSegundoCuadrante(tejo->getDireccion()->getFi())){
				std::cout<<"9"<<endl;
				return tejo->getDireccion()->getFi() - PI/2;
			}else if(CalculosMatematicos::isTercerCuadrante(tejo->getDireccion()->getFi())){
				std::cout<<"10"<<endl;
				return tejo->getDireccion()->getFi() - PI/2;
			}else if(CalculosMatematicos::isCuartoCuadrante(tejo->getDireccion()->getFi())){
				std::cout<<"11"<<endl;
				return tejo->getDireccion()->getFi() - (3*PI/2);
			}else if(CalculosMatematicos::isPrimerCuadrante(tejo->getDireccion()->getFi())){
				std::cout<<"12"<<endl;
				return tejo->getDireccion()->getFi()+(PI/8);
			}
		}

			return 0;

}

double  ControladorColisiones::colisionVerticeEnBaseArriba(Triangulo*triangulo, Tejo*tejo, Posicion*verticeChoque, Posicion*vertice1, Posicion*vertice2, Posicion*vertice3){

	double anguloTejo = tejo->getDireccion()->getFi();


			std::cout<<"vertice1: "<<vertice1->getX()<<", "<<vertice1->getY()<<endl;
			std::cout<<"vertice2: "<<vertice2->getX()<<", "<<vertice2->getY()<<endl;
			std::cout<<"vertice3: "<<vertice3->getX()<<", "<<vertice3->getY()<<endl;
			std::cout<<"verticeChoque: "<<verticeChoque->getX()<<", "<<verticeChoque->getY()<<endl;

			if(vertice1->compare(verticeChoque)==0 || vertice2->compare(verticeChoque)==0){

				if(vertice2->compare(verticeChoque)==0){
					if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
						std::cout<<"1"<<endl;
						return tejo->getDireccion()->getFi() - (3*PI/2);
					}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
						std::cout<<"2"<<endl;
						return tejo->getDireccion()->getFi() + PI/2;
					}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
						std::cout<<"3"<<endl;
						return tejo->getDireccion()->getFi() - PI/2;
					}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
						std::cout<<"4"<<endl;
						return tejo->getDireccion()->getFi() - (PI/8);
					}
				}else{
					if(CalculosMatematicos::isCuartoCuadrante(anguloTejo)){
						std::cout<<"5"<<endl;
						return tejo->getDireccion()->getFi() - (PI/2);
					}else if(CalculosMatematicos::isTercerCuadrante(anguloTejo)){
						std::cout<<"6"<<endl;
						return tejo->getDireccion()->getFi() - PI/2;
					}else if(CalculosMatematicos::isSegundoCuadrante(anguloTejo)){
						std::cout<<"7"<<endl;
						return tejo->getDireccion()->getFi() + PI/8;
					}else if(CalculosMatematicos::isPrimerCuadrante(anguloTejo)){
						std::cout<<"8"<<endl;
						return tejo->getDireccion()->getFi() + PI/2;
					}
				}

			}else if(vertice3->compare(verticeChoque)==0){

				if(CalculosMatematicos::isSegundoCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"9"<<endl;
					return tejo->getDireccion()->getFi() + PI/2;
				}else if(CalculosMatematicos::isTercerCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"10"<<endl;
					return tejo->getDireccion()->getFi() + PI/8;
				}else if(CalculosMatematicos::isCuartoCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"11"<<endl;
					return tejo->getDireccion()->getFi() - (PI/8);
				}else if(CalculosMatematicos::isPrimerCuadrante(tejo->getDireccion()->getFi())){
					std::cout<<"12"<<endl;
					return tejo->getDireccion()->getFi()+(3*PI/2);
				}
			}

				return 0;
}

double ControladorColisiones::obtenerAnguloSegunBase(Triangulo*triangulo,Tejo*tejo,Posicion*verticeChoque){
	bool base_derecha=false;
	bool base_izquierda=false;
	bool base_arriba=false;
	bool base_abajo=false;

	//vertice1 y vertice2 seran puntos de la base y vertice 3 el vertice opuesto a los vertices que forman la recta base
	Posicion* vertice1 = new Posicion(0,0);
	Posicion* vertice2 = new Posicion(0,0);
	Posicion* vertice3 = new Posicion(0,0);

	Recta* rectaBase;

	if(triangulo->isBase(triangulo->getRecta1())==0){
		rectaBase = triangulo->getRecta1();
	}

	if(triangulo->isBase(triangulo->getRecta2())==0){
		rectaBase = triangulo->getRecta2();
	}

	if(triangulo->isBase(triangulo->getRecta3())==0){
		rectaBase = triangulo->getRecta3();
	}

	if(triangulo->getBase()==BASE_TRIANGULO_DERECHA){
		base_derecha = true;
	}else if(triangulo->getBase()==BASE_TRIANGULO_IZQUIERDA){
		base_izquierda = true;
	}else if(triangulo->getBase()==BASE_TRIANGULO_ARRIBA){
		base_arriba = true;
	}else if(triangulo->getBase()==BASE_TRIANGULO_ABAJO)
		base_abajo = true;

	asignarVerticesSegunBase(rectaBase, triangulo, vertice1, vertice2, vertice3);

	if(base_derecha){
		return colisionVerticeEnBaseDerecha(triangulo, tejo, verticeChoque, vertice1, vertice2, vertice3);
	}else if(base_izquierda){
		return colisionVerticeEnBaseIzquierda(triangulo, tejo, verticeChoque, vertice1, vertice2, vertice3);
	}else if(base_abajo){
		return colisionVerticeEnBaseAbajo(triangulo, tejo, verticeChoque, vertice1, vertice2, vertice3);
	}else if(base_arriba){
		return colisionVerticeEnBaseArriba(triangulo, tejo, verticeChoque, vertice1, vertice2, vertice3);
	}

	delete vertice1;
	delete vertice2;
	delete vertice3;
}

double ControladorColisiones::obtenerAnguloTejo(Posicion*vertice,Posicion*posicionAcomparar,Recta*rectaDireccion,Tejo*tejo,Triangulo*triangulo){


	double anguloTejo;

	anguloTejo=obtenerAnguloSegunBase(triangulo,tejo,vertice);


	return anguloTejo;
}

int diferenciaEnXmodulo(int x, int otroX){
	int diferencia = x-otroX;

	if(diferencia<0)
		return otroX-x;

	return diferencia;
}

int diferenciaEnYmodulo(int y, int otroY){
	int diferencia = y-otroY;

	if(diferencia<0)
		return otroY-y;

	return diferencia;
}


void ControladorColisiones::colisionTriangulo(Triangulo* triangulo,Tejo* tejo){


	double anguloDeltejo = tejo->getDireccion()->getFi();
	int radioTejo = tejo->getRadio();
	int xTejo=tejo->getX();
	int yTejo=tejo->getY();
	bool fueraDeZonaInfluencia = false;
	bool colisionVertice = false;
	Recta*  rectaDireccionTejo=tejo->getRectaDireccion();
	Posicion* verticeDeChoque;

	//Recta* rectaDireccionTejoArriba= new Recta(xTejo,(int)(radioTejo*cos(anguloDelTejo));
	//	Recta* rectaDireccionTejoAbajo = rectaDireccionTejo->getRectaPerpendicular(xTejo,yTejo);

	Recta* recta1=triangulo->getRecta1();
	Recta* recta2=triangulo->getRecta2();
	Recta* recta3=triangulo->getRecta3();
	if(DEBUG==1){
		recta3->toString();
		recta2->toString();
		recta1->toString();
		rectaDireccionTejo->toString();
	}
	Recta* recta=recta3; //Recta con la que estoy mas cerca
	Recta* rectaColision=NULL;
	//Hallo las distancias de la posicion del tejo con respecto a las rectas del triangulo
	double d_r1 = hallarDistancia(recta1, tejo->getX(),tejo->getY());
	double d_r2 = hallarDistancia(recta2, tejo->getX(),tejo->getY());
	double d_r3 = hallarDistancia(recta3, tejo->getX(),tejo->getY());
	double dMenor;
	int numeroRecta=0;

	if (d_r1 < radioTejo && d_r2 < radioTejo && d_r1 < d_r3){
		colisionVertice = true;
		dMenor = d_r1;
		recta = recta1;

		int diferenciaVertice1 = (diferenciaEnXmodulo(triangulo->getVertice1()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice1()->getY(),yTejo));
		int diferenciaVertice2 = (diferenciaEnXmodulo(triangulo->getVertice2()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice2()->getY(),yTejo));
		int diferenciaVertice3 = (diferenciaEnXmodulo(triangulo->getVertice3()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice3()->getY(),yTejo));
        if(DEBUG2==1){
		std::cout<<"diferenciaVertice1: "<<diferenciaVertice1<<endl;
		std::cout<<"diferenciaVertice2: "<<diferenciaVertice2<<endl;
 }
		if(diferenciaVertice1<diferenciaVertice2 && diferenciaVertice1<diferenciaVertice3)
			verticeDeChoque = triangulo->getVertice1();
		else if(diferenciaVertice2<diferenciaVertice1 && diferenciaVertice2<diferenciaVertice3)
			verticeDeChoque = triangulo->getVertice2();
		else if(diferenciaVertice3<diferenciaVertice1 && diferenciaVertice3<diferenciaVertice2)
			verticeDeChoque = triangulo->getVertice3();

		numeroRecta=1;
	}
	else{
		if(d_r1 < radioTejo && d_r3 < radioTejo && d_r1 < d_r2){
			colisionVertice = true;
			dMenor = d_r1;
			recta = recta1;

				int diferenciaVertice1 = (diferenciaEnXmodulo(triangulo->getVertice1()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice1()->getY(),yTejo));
				int diferenciaVertice2 = (diferenciaEnXmodulo(triangulo->getVertice2()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice2()->getY(),yTejo));
				int diferenciaVertice3 = (diferenciaEnXmodulo(triangulo->getVertice3()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice3()->getY(),yTejo));
         if(DEBUG2==1){
		std::cout<<"diferenciaVertice1: "<<diferenciaVertice1<<endl;
		std::cout<<"diferenciaVertice2: "<<diferenciaVertice2<<endl;
       }
		if(diferenciaVertice1<diferenciaVertice2 && diferenciaVertice1<diferenciaVertice3)
			verticeDeChoque = triangulo->getVertice1();
		else if(diferenciaVertice2<diferenciaVertice1 && diferenciaVertice2<diferenciaVertice3)
			verticeDeChoque = triangulo->getVertice2();
		else if(diferenciaVertice3<diferenciaVertice1 && diferenciaVertice3<diferenciaVertice2)
			verticeDeChoque = triangulo->getVertice3();

			numeroRecta=1;
		}
		else{
			if (d_r2 < radioTejo && d_r3 < radioTejo && d_r2 < d_r1){
				colisionVertice = true;
				dMenor = d_r2;
				recta = recta2;
					int diferenciaVertice1 = (diferenciaEnXmodulo(triangulo->getVertice1()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice1()->getY(),yTejo));
					int diferenciaVertice2 = (diferenciaEnXmodulo(triangulo->getVertice2()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice2()->getY(),yTejo));
					int diferenciaVertice3 = (diferenciaEnXmodulo(triangulo->getVertice3()->getX(),xTejo)+diferenciaEnYmodulo(triangulo->getVertice3()->getY(),yTejo));
     if(DEBUG2==1){
		std::cout<<"diferenciaVertice1: "<<diferenciaVertice1<<endl;
		std::cout<<"diferenciaVertice2: "<<diferenciaVertice2<<endl;
           }
		if(diferenciaVertice1<diferenciaVertice2 && diferenciaVertice1<diferenciaVertice3)
			verticeDeChoque = triangulo->getVertice1();
		else if(diferenciaVertice2<diferenciaVertice1 && diferenciaVertice2<diferenciaVertice3)
			verticeDeChoque = triangulo->getVertice2();
		else if(diferenciaVertice3<diferenciaVertice1 && diferenciaVertice3<diferenciaVertice2)
			verticeDeChoque = triangulo->getVertice3();

				numeroRecta=2;
			}
			else{
				if (d_r1 < d_r2){
					if (d_r1 < d_r3){
						recta = recta1;
						dMenor = d_r1;
						numeroRecta=1;
					}
					else{
						recta = recta3;
						dMenor = d_r3;
						numeroRecta=3;
					}
				}
				else{
					if (d_r2 < d_r3){
						recta = recta2;
						dMenor = d_r2;
						numeroRecta=2;
					}
					else{
						recta = recta3;
						dMenor = d_r3;
						numeroRecta=3;
					}
				}
			}
		}
	}

	Posicion* posicion2 = rectaDireccionTejo->getInterseccion(recta);
	if(!isPuntoZonaDeInfluenciaTriangulo(posicion2,triangulo)&&posicion2!=NULL&&recta->getInfinito()!=-1&&recta->getPendiente()!=0){
		if(DEBUG2==1){
		std::cout<<"entra con esta recta :";
		recta->toString();
		std::cout<<"distancia con recta :"<<dMenor<<endl;
		}
		if(numeroRecta==1){
			if (d_r2 < d_r3){
				recta = recta2;
				dMenor = d_r2;
			}else{
				recta = recta3;
				dMenor = d_r3;
			}
		}else{
			if(numeroRecta==2){

				if (d_r1 < d_r3){
					recta = recta1;
					dMenor = d_r1;

				}
				else{
					recta = recta3;
					dMenor = d_r3;

				}

			}else{
				if(numeroRecta==3){
					if (d_r1 < d_r2){

						recta = recta1;
						dMenor = d_r1;

					}
					else{
						recta = recta3;
						dMenor = d_r3;

					}
				}

			}
		}
		if(DEBUG2==1){
		std::cout<<"sale con esta recta :";
				recta->toString();
				std::cout<<"distancia con recta :"<<dMenor<<endl;
				system("PAUSE");
		}
	}

	if(dMenor<=radioTejo){
		if(DEBUG2==1){
		std::cout<<"if(dMenor<=radioTejo){  :"<<endl;
					system("PAUSE");
		}
		//analisis colision con vertices, totalmente arbitrario el angulo de salida
		if (colisionVertice){
			bool puntoTriangulo=false;

						//Posicion* posicion3 = rectaDireccionTejo->getInterseccion(recta);
						Posicion* posicion4 = new Posicion(tejo->getX(),tejo->getY());

					/*	if(isPuntoZonaDeInfluenciaTriangulo(posicion3,triangulo)&&!isPuntoZonaDeInfluenciaTriangulo(posicion4,triangulo)){
							puntoTriangulo=true;
						}*/

						if(DEBUG2==1){
							std::cout<<"colisionVertice  :"<<puntoTriangulo<<endl;
							system("PAUSE");
						}


						if(triangulo->getTieneBonus()){
								tejo->setChocoFiguraConBonus(true);
						}
						//	if(puntoTriangulo){
					//	if(isPuntoZonaDeInfluenciaTejo(verticeDeChoque,tejo)){
								tejo->getDireccion()->setFi(CalculosMatematicos::getAnguloValido(obtenerAnguloTejo(verticeDeChoque,posicion4,rectaDireccionTejo,tejo,triangulo)));
								sacarDelAmbitoDelTriangulo(tejo,triangulo);
					//	}
						//	}


			         // delete posicion3;
			          delete posicion4;
		}
		else{
			if(DEBUG2==1){
						std::cout<<"recta de colision :";
						recta->toString();
						std::cout<<"distancia con recta :"<<dMenor<<endl;
						system("PAUSE");
					}
			//analisis con recta paralela al eje Y
			if (recta->getInfinito() == -1){
				if(triangulo->getTieneBonus()){
					tejo->setChocoFiguraConBonus(true);
				}

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
//				Posicion* posicion = hallarPuntoTriangulo(recta,tejo->getX(),tejo->getY());
//					if(getZonaDeInfluencia(rectaDireccionTejo,recta,triangulo,tejo)&&posicion!=NULL){
				if(isPuntoZonaDeInfluenciaTriangulo(posicion,triangulo)&&posicion!=NULL){
				if (recta->getPendiente() == 0){
					if(triangulo->getTieneBonus()){
						tejo->setChocoFiguraConBonus(true);
					}

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
							decidirDireccionCuartoCuadranteTriangulo(recta,tejo,triangulo);
						}else
							if (CalculosMatematicos::isTercerCuadrante(anguloDeltejo)){
								decidirDireccionTercerCuadranteTriangulo(recta,tejo,triangulo);
							}else
								if (CalculosMatematicos::isSegundoCuadrante(anguloDeltejo)){
									decidirDireccionSegundoCuadranteTriangulo(recta,tejo,triangulo);
								}else
									if (CalculosMatematicos::isPrimerCuadrante(anguloDeltejo)){
										decidirDireccionPrimerCuadranteTriangulo(recta,tejo,triangulo);
									}
						if(triangulo->getTieneBonus()){
							tejo->setChocoFiguraConBonus(true);
						}

					}
				}
				delete posicion;
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
	radioTejo=tejo->getRadio();
	double anguloDeltejo=tejo->getDireccion()->getFi();
	xAnteriorTejo=tejo->getXAnterior()-tejo->getRadio();
	yAnteriorTejo=tejo->getYAnterior()-tejo->getRadio();
	wFigura= cuadrado->getLado();
	hFigura=cuadrado->getLado();
	xFigura= cuadrado->getX();
	yFigura= cuadrado->getY();
	if( ((xTejo + wTejo) >= xFigura) && ((yTejo + hTejo) >= yFigura) && ((xFigura + wFigura) >= xTejo) && ((yFigura + hFigura) >= yTejo)){
		if(cuadrado->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);
		}
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
		if(rectangulo->getTieneBonus()){
			tejo->setChocoFiguraConBonus(true);

		}
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

		if(rectangulo->getTipo().compare(PAD_DERECHA)==0){
			tejo->setUltimaColisionPad(PAD_CLIENTE1);
			if(tejo->getPegajoso()){
				if(tejo->getPadPegajoso().compare(PAD_CLIENTE1) == 0){
					tejo->setMover(false);
				}
			}
		}
		else if(rectangulo->getTipo().compare(PAD_IZQUIERDA)==0){
			tejo->setUltimaColisionPad(PAD_CLIENTE2);
			if(tejo->getPegajoso()){
				if(tejo->getPadPegajoso().compare(PAD_CLIENTE2) == 0){
					tejo->setMover(false);
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
			escenario->setGolDe("PAD1");
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
			escenario->setGolDe("PAD2");
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

