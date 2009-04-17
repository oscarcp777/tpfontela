#include <iostream>
#include <string>
#include "Circulo.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Triangulo.h"
#include "Segmento.h"
#include "Escenario.h"
#include "archivoTexto.h"
#include "Validador.h"



using namespace std;


int main()
{

    
	int exito;

	Validador *validador = new  Validador("config Validador.txt");
	exito = validador->validarSintaxis("XML.xml");
	if(exito == 0){
		std::cout<<"*******************************"<<endl;
		std::cout<<"EL ARCHIVO XML NO TIENE ERRORES"<<endl;
		std::cout<<"*******************************"<<endl;
	}
	else{
		std::cout<<"****************************************"<<endl;
		std::cout<<"SE ENCONTRARON ERRORES EN EL ARCHIVO XML"<<endl;
		std::cout<<"****************************************"<<endl;
	}
	
	
	Posicion *posicion1 = new Posicion(20,500);
	/*std::cout<<"posicion x "<<posicion1->getX()<<endl;
	std::cout<<"posicion y "<<posicion1->getY()<<endl;
	*/

	
	Circulo *circulo = new Circulo(50,posicion1);	
	/*std::cout<<"radio circulo "<<circulo->getRadio()<<endl;
	std::cout<<"posicion x del circulo "<<circulo->getPosicion()->getX()<<endl;
	std::cout<<"posicion y del circulo "<<circulo->getPosicion()->getY()<<endl;
	*/
	
	
	Cuadrado *cuadrado = new Cuadrado(2,posicion1);
	/*std::cout<<"lado cuadrado "<<cuadrado->getLado()<<endl;
	std::cout<<"posicion x del cuadrado "<<cuadrado->getPosicion()->getX()<<endl;
	std::cout<<"posicion y del cuadrado "<<cuadrado->getPosicion()->getY()<<endl;
	*/

	
	Rectangulo *rectangulo = new Rectangulo(3,9,posicion1);
	/*std::cout<<"base rectangulo "<<rectangulo->getBase()<<endl;
	std::cout<<"altura rectangulo "<<rectangulo->getAltura()<<endl;
	std::cout<<"posicion x del cuadrado "<<rectangulo->getPosicion()->getX()<<endl;
	std::cout<<"posicion y del cuadrado "<<rectangulo->getPosicion()->getY()<<endl;
	*/
	
	
	Posicion *inicio = new Posicion(0,0);
	Posicion *fin = new Posicion(15,0);
	Segmento *segmento = new Segmento(inicio,fin);
	/*std::cout<<"inicioX segmento  "<<segmento->getInicio()->getX()<<endl;
	std::cout<<"inicioY segmento  "<<segmento->getInicio()->getY()<<endl;
	std::cout<<"finX segmento "<<segmento->getFin()->getX()<<endl;
	std::cout<<"finY segmento "<<segmento->getFin()->getY()<<endl;
	*/
	
	
	Posicion *ver1 = new Posicion(0,0);
	Posicion *ver2 = new Posicion(15,0);
	Posicion *ver3 = new Posicion(20,10);
	Triangulo *triangulo = new Triangulo(ver1,ver2,ver3);
	/*
	std::cout<<"ver1 X segmento  "<<triangulo->getVertice1()->getX()<<endl;
	std::cout<<"ver1 Y segmento  "<<triangulo->getVertice1()->getY()<<endl;
	std::cout<<"ver2 X segmento  "<<triangulo->getVertice2()->getX()<<endl;
	std::cout<<"ver2 Y segmento  "<<triangulo->getVertice2()->getY()<<endl;
	std::cout<<"ver3 X segmento  "<<triangulo->getVertice3()->getX()<<endl;
	std::cout<<"ver3 Y segmento  "<<triangulo->getVertice3()->getY()<<endl;
	*/

	Escenario *escenario = new Escenario();
	escenario->addFigura(circulo);
	escenario->addFigura(cuadrado);
	escenario->addFigura(rectangulo);
	escenario->addFigura(segmento);
	escenario->addFigura(triangulo);
	
	//grafico todo
	escenario->graficar();
	

	system("PAUSE");
   
	return 0;
}