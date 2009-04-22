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
#include <c:\program files\microsoft visual studio\vc98\sdl-1.2.13\include\SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>
//#include <SDL_main.h>
#include<math.h>

using namespace std;

void putpixel(SDL_Surface *screen, int x, int y, SDL_Color color)
{
	// Convertimos color
	Uint32 col=SDL_MapRGB(screen->format, color.r, color.g, color.b);
	// Determinamos posición de inicio
	char *buffer=(char*) screen->pixels;
	// Calculamos offset para y
	buffer+=screen->pitch*y;
	// Calculamos offset para x
	buffer+=screen->format->BytesPerPixel*x;
	// Copiamos el pixel
	memcpy(buffer, &col, screen->format->BytesPerPixel);
}

SDL_Color getpixel(SDL_Surface *screen, int x, int y)
{
	SDL_Color color;
	Uint32 col;
	// Determinamos posición de inicio
	char *buffer=(char *) screen->pixels;
	// Calculamos offset para y
	buffer+=screen->pitch*y;
	// Calculamos offset para x
	buffer+=screen->format->BytesPerPixel*x;
	// Obtenemos el pixel
	memcpy(&col, buffer, screen->format->BytesPerPixel);
	// Descomponemos el color
	SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
	// Devolvemos el color
	return color;
}

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
	*/
	SDL_Surface *screen;
	SDL_Surface *imagen;
	SDL_Color color;


	screen = SDL_SetVideoMode(640,480,32, SDL_SWSURFACE | SDL_DOUBLEBUF );
	if(!screen){
		printf("No se pudo iniciar la pantalla: %s\n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	
	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);
	
		
	/*//COPIA UNA IMAGEN PIXEL A PIXEL Y LA CARGA EN PANTALLA
	imagen = IMG_Load ("pocoyo.jpg");
	int x,y;
	x=0;
	y=0;
	while(x<imagen->w){
		y=0;
		while(y<imagen->h){
		color = getpixel(imagen,x,y);
		putpixel(screen,x,y,color);
		y++;
		}
		x++;
	}

	//FIN COPIA UNA IMAGEN PIXEL A PIXEL Y LA CARGA EN PANTALLA */

	imagen = IMG_Load ("pocoyo.jpg");
	float ang=0;
	float radio = 1;
	float PI =3.14;
	float x= 0;
	float y= 0;
	
	for(ang = 0;ang<=90;ang+=0.2){
         
  		for(radio = 1;radio<200;radio+=0.477){
			color = getpixel(imagen,x,y);
			putpixel(screen,x,y,color);
            y=radio*sin(PI*ang/180);		
			x=radio*cos(PI*ang/180);
		}			
		
	}
	
	
	if(SDL_MUSTLOCK(screen))
	SDL_UnlockSurface(screen);
	SDL_Flip(screen);
   	system("PAUSE");
	
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}