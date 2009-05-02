#include <iostream>
#include <string>
#include "Circulo.h"
#include "Cuadrado.h"
#include "Rectangulo.h"
#include "Triangulo.h"
#include "Segmento.h"
#include "Escenario.h"
#include "archivoTexto.h"
#include "Textura.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include<math.h>
#include "Color.h"
#include "Hidratar.h"
using namespace std;



int main(int argc, char* argv[])
{


	Escenario* escenario = Escenario::obtenerInstancia();
	int exito = 0;
	std::string nombreArchivoXML;



	std::cout<<"INGRESE EL NOMBRE DEL ARCHIVO (ej: XML.xml)"<<endl;
	std::cin>>nombreArchivoXML;

		Posicion *posicion1 = new Posicion(50,50);
	Posicion *posicion2 = new Posicion(570,100);
	Posicion *posicion3 = new Posicion(580,470);
	Posicion *ver1 = new Posicion(100,400);
	Posicion *ver2 = new Posicion(200,400);
	Posicion *ver3 = new Posicion(250,500);
	Posicion *inicio = new Posicion(300,300);
	Posicion *fin = new Posicion(500,500);


	Rectangulo *rectangulo = new Rectangulo("rectangulo1",500,300,posicion1);
	rectangulo->setIdTextura("pocoyo4");


	Cuadrado *cuadrado = new Cuadrado("cuadrado",200,posicion2);
	cuadrado->setIdTextura("don");


	Circulo *circulo = new Circulo("circulo1",100,posicion3);
	circulo->setIdTextura("pocoyo");

	Triangulo *triangulo = new Triangulo("triangulo",ver1,ver2,ver3);
	triangulo->setIdTextura("river");
		

	//escenario->addFigura(cuadrado);
	//escenario->addFigura(rectangulo);
	//escenario->addFigura(circulo);
	//escenario->addFigura(triangulo);

	try{
		exito = escenario->cargarArchivo(nombreArchivoXML);
		if(exito == 0){
			//TODO aca se va a graficar todo en vez de imprimir los siguiente
			std::cout<<"*******************************"<<endl;
			std::cout<<"EL ARCHIVO XML NO TIENE ERRORES"<<endl;
			std::cout<<"*******************************"<<endl;

			std::cout<<"cantidad figuras en escenario: "<<escenario->sizeListaFiguras()<<endl;
			std::cout<<"cantidad texturas en escenario: "<<escenario->sizeListaTexturas()<<endl;
	
			escenario->graficar();
			SDL_FreeSurface(escenario->getScreen());
			SDL_Quit();

		}
		else{
			std::cout<<"**********************************************************************"<<endl;
			std::cout<<"SE ENCONTRARON ERRORES EN EL ARCHIVO XML, VER DETALLES ERRORES.ERR"<<endl;
			std::cout<<"**********************************************************************"<<endl;
		}
	}
	catch(std::ios_base::failure){
		std::cout<<"EL ARCHIVO NO EXISTE"<<endl;
	}

    	
	return 0;
}
