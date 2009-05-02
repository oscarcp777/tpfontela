#include <iostream>
#include "Hidratar.h"
#include "Escenario.h"
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
/*############################################################################################################################*/

/*             ESTA CLASE LA USO PARA PONER LAS COSAS QUE SE PRUEBA ASI SABEMOS COMO FUNCIONA CORRIENDO ESA PARTE   */
/*############################################################################################################################*/


//PARA SEGMENTO
int main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
/*	string segmento= "id=\"segmento1\"  x=\"5\" y=\"4\"  x=\"45\" y=\"455\" colorLinea=\"255255255\" colorFigura=\"123123123\" idTextura=\"textura2\"";

	 Hidratar::hidratarSegmento(segmento);
 /**/
	string rectangulo= " id=\"rectangulo1\" base=\"200\" altura=\"100 x=\"250\" y=\"400\" ";

    Hidratar::hidratarRectangulo(rectangulo);
//PARA GENERAL

/*
	string general= "\"resolucion=\"640\" colorFondoFig=\"255215000\" texturaFig=\"textura1\" colorLinea=\"000255000\" colorFondoEsc=\"255255255\" texturaEsc=\"textura4\" ";
	 Hidratar::hidratarEscenario(general);
	 // test de hidratacion de el escenario
string str=	"General resolucion=\"640\" colorFondoFig=\"255215000\" texturaFig=\"textura1\" colorLinea=\"000255000\" colorFondoEsc=\"255255255\" texturaEsc=\"textura4\">";
int posicionCaracter = str.find_first_of(" ");
	str= str.substr(posicionCaracter,str.size());
	std::cout<<str<<endl;
Hidratar::hidratarEscenario(str);

Escenario* escenario = Escenario::obtenerInstancia();

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
*/
	 system("PAUSE");
return 0;
 }
