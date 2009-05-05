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

	try{
		exito = escenario->cargarArchivo(nombreArchivoXML);
		if(exito == 0){
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
