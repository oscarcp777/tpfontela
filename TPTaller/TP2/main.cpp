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
#include "Dibujar.h"
#define WALLCOLOR 0x9f1f1f 
#define AMARRILLO 0xF7FE2E 
#define AZUL 0x4A09E2
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

SDL_Event event;
SDL_Surface *screen;
SDL_Surface *imagen;
SDL_Rect rect;
SDL_Color color;
int done = 0;
Escenario *escenario = Escenario::obtenerInstancia();
std::cout<<"\nAlto \n"<<escenario->getAlto()<<endl;
std::cout<<"\n Anchoo \n"<<escenario->getAncho()<<endl;
screen = SDL_SetVideoMode(escenario->getAncho(),escenario->getAlto(),32, SDL_SWSURFACE | SDL_DOUBLEBUF );
if(!screen){
std::cout<<"No se pudo iniciar la pantalla: %s\n"<< SDL_GetError()<<endl;
SDL_Quit();
exit(-1);
}

//dibujo un rectangulo
	Posicion *posicion1 = new Posicion(10,10);
	Rectangulo *rectangulo = new Rectangulo("rectangulo1",200,150,posicion1);

	//dibujo otro un rectangulo
	Posicion *posicion2 = new Posicion(405,400);
	Rectangulo *rectangulo1 = new Rectangulo("rectangulo1",100,300,posicion2);
//dibujo  un circulo
	Posicion *posicion3 = new Posicion(300,300);
	Circulo *circulo = new Circulo("circulo1",150,posicion3);
	
Dibujar *dibujar =Dibujar::obtenerInstancia();
//aca le seteo al dibujar la pantalla donde dibujar

dibujar->pantalla=screen;
std::cout<<"veo que trae"<<dibujar->pantalla<<endl;
//pruebo que las funciones dibujan bien
//dibujar->dibujarCirculo(400,400,50,AMARRILLO);
//dibujar->dibujarRectangulo(100,200,200,200,AZUL);
std::cout<<"\nAlto \n"<<escenario->getAlto()<<endl;
std::cout<<"\n Anchoo \n"<<escenario->getAncho()<<endl;

//llamo al dibujar del rectangulo par que se dibuje
rectangulo->dibujar(screen);
circulo->dibujar(screen);
rectangulo1->dibujar(screen);

//PONE DENTRO DEL CIRCULO LA TEXTURA
imagen = IMG_Load ("pocoyo.jpg");
	float ang;
	float radio;
	float PI =3.14f;
	//(Xinicial,Yinicial) es la posicion de imagen desde donde copiara el circulo
	int XiniColor = imagen->w/2;
	int YiniColor = imagen->h/2;
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	float x= circulo->getPosicion()->getX();
	float y= circulo->getPosicion()->getY();

	

	for(ang = 0;ang<=360;ang+=0.2){
         
  		for(radio = 1;radio<circulo->getRadio();radio+=0.477){
			color = getpixel(imagen,XiniColor,YiniColor);
			putpixel(screen,x,y,color);
			
			XiniColor=imagen->w/2+radio*cos(PI*ang/180);
			YiniColor=imagen->h/2+radio*sin(PI*ang/180);
            
			x=circulo->getPosicion()->getX()+radio*cos(PI*ang/180);
			y=circulo->getPosicion()->getY()+radio*sin(PI*ang/180);		
			
		}			
		
	}
//FIN PONE DENTRO DEL CIRCULO LA TEXTURA 
/*
//piso con imagenes las figuras
  imagen = IMG_Load ("lente.png");

rect.x = 540;
rect.y = 270;
rect.w = 200;
rect.h = 150;
//rect.w = imagen->w;
//rect.h = imagen->h;
SDL_BlitSurface(imagen, NULL, screen, &rect);
imagen = IMG_Load ("circulo.png");

rect.x = 400;
rect.y = 400;
rect.w = imagen->w;
rect.h = imagen->h;
SDL_BlitSurface(imagen, NULL, screen, &rect);

imagen = IMG_Load ("triangulo.bmp");

rect.x = 110;
rect.y = 220;
rect.w = 200;
rect.h = 150;
SDL_BlitSurface(imagen, NULL, screen, &rect);
*/
		
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
//*************************************************************************
/*	SDL_Event event;
	SDL_Surface *screen;
	SDL_Surface *imagen;
	SDL_Color color;
	int done = 0;
	Escenario *escenario = Escenario::obtenerInstancia();
	std::cout<<"\nAlto \n"<<escenario->getAlto()<<endl;
	std::cout<<"\n Anchoo \n"<<escenario->getAncho()<<endl;
	screen = SDL_SetVideoMode(escenario->getAncho(),escenario->getAlto(),32, SDL_SWSURFACE | SDL_DOUBLEBUF );
	if(!screen){
		std::cout<<"No se pudo iniciar la pantalla: %s\n"<< SDL_GetError()<<endl;
		SDL_Quit();
		exit(-1);
	}
	imagen = IMG_Load ("pocoyo3.jpg");
	float ang=0;
	float radio = 90;
	float PI =3.14f;
	float x= 200;
	float y= 400;
	//Xinicial Yinicial son las posiciones de imagen que determinan el centro del circulo
	const int Xinicial = 200;
	const int Yinicial = 150;
	//posicionXPantalla posicionYPantalla son las posiciones donde grafica el circulo
	const int posicionXPantalla = 100;
	const int posicionYPantalla = 95;


	for(ang = 0;ang<=360;ang+=0.2){
         
  		for(radio = 1;radio<100;radio+=0.477){
			color = getpixel(imagen,x,y);
			putpixel(screen,x+posicionXPantalla,y+posicionYPantalla,color);
            x=Xinicial+radio*cos(PI*ang/180);
			y=Yinicial+radio*sin(PI*ang/180);		
			
		}			
		
	}



//*********************************************************************
*/
	
	while (done == 0) {
		SDL_Flip (screen);
		// Comprobando teclas para opciones
		while (SDL_PollEvent(&event)) {
			// Cerrar la ventana
			if (event.type == SDL_QUIT) { done = 1; }
			// Pulsando una tecla
			if (event.type == SDL_KEYDOWN) {
			done = 1;
			}
		}
	}
SDL_FreeSurface(imagen);
SDL_FreeSurface(screen);
SDL_Quit();
std::cout<<"\nTodo ha salido bien.\n"<<endl;
	
	return 0;
}