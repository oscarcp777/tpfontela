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

using namespace std;


int SDL_main(int argc, char* argv[])
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
	Validador *validador = new  Validador("config Validador.txt","config Atributos.txt");
	std::cout<<"INGRESE EL NOMBRE DEL ARCHIVO (ej: XML.xml)"<<endl;
	std::cin>>nombreArchivoXML;
	

	try{
		exito = validador->validarSintaxis(nombreArchivoXML);
		
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

	Posicion *posicion1 = new Posicion(0,0);
	Textura *textura = new Textura("foto","C:\Users\Richy\Desktop\TP2\pocoyo.jpg");
	Cuadrado *cuadrado = new Cuadrado("cuadrado1",250,posicion1);
	
	Posicion *posicion2 = new Posicion(200,200);
	Rectangulo *rectangulo = new Rectangulo("rectangulo1",200,400,posicion2);
	

	Posicion *posicion3 = new Posicion(250,0);
	Circulo *circulo = new Circulo("circulo1",1000,posicion3);
	
	Posicion *ver1 = new Posicion(0,300);
	Posicion *ver2 = new Posicion(100,100);
	Posicion *ver3 = new Posicion(0,0);
	Triangulo *triangulo = new Triangulo("triangulo1",ver1,ver2,ver3);
	

	cuadrado->setIdTextura("foto");
	rectangulo->setIdTextura("foto");
	circulo->setIdTextura("foto");
	triangulo->setIdTextura("foto");
	Escenario::obtenerInstancia()->addFigura(cuadrado);
	Escenario::obtenerInstancia()->addFigura(rectangulo);
	Escenario::obtenerInstancia()->addFigura(circulo);
	Escenario::obtenerInstancia()->addFigura(triangulo);
	Escenario::obtenerInstancia()->addTextura(textura);
	Escenario::obtenerInstancia()->graficar();
	
	
   
	return 0;
}