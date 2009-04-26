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
#include "Textura.h"
#include "logfinal.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_main.h>
#include<math.h>
using namespace std;




int main(int argc, char* argv[])
{

		
/*	
	int exito = 0;
	std::string nombreArchivoXML;
	//en las siguientes tres lineas, se crean el log lo inicializa y ecribe un titulo en el archivo "errores.err"
	Log log;
	inicializarLog(log, "errores.err");
	escribirTituloLog(log,"DESCRIPCION DE ERRORES");
	destruirLog(log);
	
	//el archivo config Validador.txt tiene las palabras de los tags validos ej CIRCULO ESCENARIO etc
	//Validador *validador = new  Validador("config Validador.txt","config Atributos.txt");
	std::cout<<"INGRESE EL NOMBRE DEL ARCHIVO (ej: XML.xml)"<<endl;
	std::cin>>nombreArchivoXML;
	

	try{
	//	exito = validador->validarSintaxis(nombreArchivoXML);
		
		if(exito == 0){
			//TODO aca se va a graficar todo en vez de imprimir los siguiente
			std::cout<<"*******************************"<<endl;
			std::cout<<"EL ARCHIVO XML NO TIENE ERRORES"<<endl;
			std::cout<<"*******************************"<<endl;
		}
		else{
			std::cout<<"****************************************"<<endl;
			std::cout<<"SE ENCONTRARON ERRORES EN EL ARCHIVO XML"<<endl;
			std::cout<<"****************************************"<<endl;
		}
	}
	catch(std::ios_base::failure){
		std::cout<<"EL ARCHIVO NO EXISTE"<<endl;
	}
*/	

	Escenario* escenario = Escenario::obtenerInstancia();

	
	Posicion *posicion1 = new Posicion(10,10);
	Posicion *posicion2 = new Posicion(400,0);
	Posicion *posicion3 = new Posicion(400,400);
	
	
	Rectangulo *rectangulo = new Rectangulo("rectangulo1",350,340,posicion1);
	rectangulo->setIdTextura("pocoyo3");

	
	Cuadrado *cuadrado = new Cuadrado("cuadrado",250,posicion2);
	cuadrado->setIdTextura("river");

	
	Circulo *circulo = new Circulo("circulo1",100,posicion3);
	circulo->setIdTextura("pocoyo");
	
	Textura *textura1 = new Textura("pocoyo3","pocoyo3.jpg");
	Textura *textura2 = new Textura("pocoyo","pocoyo.jpg");
	Textura *textura3 = new Textura("river","river.jpg");

	escenario->addFigura(rectangulo);
	escenario->addFigura(circulo);
	escenario->addFigura(cuadrado);
	escenario->addTextura(textura1);
	escenario->addTextura(textura2);
	escenario->addTextura(textura3);

	escenario->graficar();	



	SDL_FreeSurface(escenario->getScreen());
	SDL_Quit();

	return 0;
}