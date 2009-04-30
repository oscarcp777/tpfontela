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
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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


	try{
		exito = escenario->cargarArchivo(nombreArchivoXML);
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
	Segmento *segmento = new Segmento("segmento1",inicio,fin);

	Textura *textura1 = new Textura("pocoyo4","pocoyo4.jpg");
	Textura *textura2 = new Textura("pocoyo","pocoyo.jpg");
	Textura *textura3 = new Textura("don","don.png");
	Textura *textura4 = new Textura("estrellas","boca.jpg");
	Textura *textura5 = new Textura("river","boca.jpg");
	escenario->setIdTextura("estrellas");


	escenario->addFigura(cuadrado);
	escenario->addFigura(rectangulo);
	escenario->addFigura(circulo);
	escenario->addFigura(triangulo);
	escenario->addFigura(segmento);
	escenario->addTextura(textura1);
	escenario->addTextura(textura2);
	escenario->addTextura(textura3);
	escenario->addTextura(textura4);
	escenario->addTextura(textura5);

	escenario->graficar();



	SDL_FreeSurface(escenario->getScreen());
	SDL_Quit();



 // test de hidratacion de el escenario
string str=	"General resolucion=\"640\" colorFondoFig=\"255215000\" texturaFig=\"textura1\" colorLinea=\"000255000\" colorFondoEsc=\"255255255\" texturaEsc=\"textura4\">";
int posicionCaracter = str.find_first_of(" ");
	str= str.substr(posicionCaracter,str.size());
	std::cout<<str<<endl;
Hidratar::hidratarEscenario(str);

 escenario = Escenario::obtenerInstancia();

	std::cout<<"ALTO : "<<escenario->getAlto()<<endl;
	std::cout<<"ANCHO : "<<escenario->getAncho()<<endl;
	std::cout<<"RESOLUCION : "<<escenario->getResolucion()<<endl;
	std::cout<<"TEXTURA ESCENARIO : "<<escenario->getTexturaEsc()<<endl;
	std::cout<<"TEXTURA FIGURA : "<<escenario->getTexturaFig()<<endl;
	SDL_Color sdlColor=escenario->getColorFondoEscenario();
    std::cout<<"COLOR ESCENARIO R  :"<<sdlColor.r<<endl;
	std::cout<<"COLOR ESCENARIO G :"<<sdlColor.g<<endl;
	std::cout<<"COLOR ESCENARIO B :"<<sdlColor.b<<endl;
	 sdlColor=escenario->getColorFondoFiguras();
	    std::cout<<"COLOR FIGURA R  :"<<sdlColor.r<<endl;
		std::cout<<"COLOR FIGURA G  :"<<sdlColor.g<<endl;
		std::cout<<"COLOR FIGURA B  :"<<sdlColor.b<<endl;
		 sdlColor=escenario->getColorLinea();
		    std::cout<<"COLOR LINEA R  :"<<sdlColor.r<<endl;
			std::cout<<"COLOR LINEA G  :"<<sdlColor.g<<endl;
			std::cout<<"COLOR LINEA B  :"<<sdlColor.b<<endl;




    	system("PAUSE");
	return 0;
}
