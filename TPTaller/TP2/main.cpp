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


//PARA EXPANDIR Y CONTRAER IMAGENES

Uint32 ReadPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    //Aqui p es la direccion del pixel que nosotros queremos recuperar
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* por descarte devuelvo 0 */
    }
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
     //Aqui la direccion del pixel que nosotros queremos setear
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

//Esta es la funcion que usamos para expandir y contraer una imagen
//Esta funcion invoca a readPixel y drawPixel

SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height)
{
    if (!Surface || !Width || !Height)
        return 0;

    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
                        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

    double  _stretch_factor_x = (static_cast<double>(Width)  / static_cast<double>(Surface->w)),
                                _stretch_factor_y = (static_cast<double>(Height) / static_cast<double>(Surface->h));

    for (Sint32 y = 0; y < Surface->h; y++)
        for (Sint32 x = 0; x < Surface->w; x++)
            for (Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for (Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    DrawPixel(_ret, static_cast<Sint32>(_stretch_factor_x * x) + o_x,
                              static_cast<Sint32>(_stretch_factor_y * y) + o_y, ReadPixel(Surface, x, y));

    return _ret;
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


	Posicion *posicion1 = new Posicion(10,10);
	Rectangulo *rectangulo = new Rectangulo("rectangulo1",350,340,posicion1);
	Textura *textura1 = new Textura("don","don.png");


	Posicion *posicion2 = new Posicion(405,400);
	Rectangulo *rectangulo1 = new Rectangulo("rectangulo1",100,300,posicion2);

	Posicion *posicion3 = new Posicion(500,200);
	Circulo *circulo = new Circulo("circulo1",150,posicion3);
	Textura *textura2 = new Textura("don","don.png");
	
	std::cout<<"miCadena = "<<textura1->getPath().begin()<<endl;


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
imagen = IMG_Load (textura2->getPath().begin());
	float ang;
	float radio;
	float PI =3.14f;
	//(Xinicial,Yinicial) es la posicion de imagen desde donde copiara el circulo
	int XiniColor = imagen->w/2;
	int YiniColor = imagen->h/2;
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	float xCirculo= circulo->getPosicion()->getX();
	float yCirculo= circulo->getPosicion()->getY();

	

	for(ang = 0;ang<=360;ang+=0.2){
         
  		for(radio = 1;radio<circulo->getRadio();radio+=0.477){
			color = getpixel(imagen,XiniColor,YiniColor);
			putpixel(screen,xCirculo,yCirculo,color);
			
			XiniColor=imagen->w/2+radio*cos(PI*ang/180);
			YiniColor=imagen->h/2+radio*sin(PI*ang/180);
            
			xCirculo=circulo->getPosicion()->getX()+radio*cos(PI*ang/180);
			yCirculo=circulo->getPosicion()->getY()+radio*sin(PI*ang/180);		
			
		}			
		
	}
//FIN PONE DENTRO DEL CIRCULO LA TEXTURA 



//PONE DENTRO DEL RECTANGULO LA TEXTURA
	imagen = ScaleSurface(IMG_Load (textura1->getPath().begin()), rectangulo->getBase(), rectangulo->getAltura());
	
	rect.x=rectangulo->getPosicion()->getX();
	rect.y=rectangulo->getPosicion()->getY();
	rect.h=imagen->h;
	rect.w=imagen->w;

	std::cout<<"base "<<rectangulo->getBase()<<endl;
	std::cout<<"altura "<<rectangulo->getAltura()<<endl;
	//x e y van guardando las posiciones mientras se recorre la circunferencia y se grafica el cirulo
	SDL_BlitSurface(imagen, NULL, screen, &rect);
/*	int x= rectangulo->getPosicion()->getX();
	int y= rectangulo->getPosicion()->getY();

	while(x<=(rectangulo->getBase()+rectangulo->getPosicion()->getX())){
		//std::cout<<"x "<<x<<endl;
		y=rectangulo->getPosicion()->getY();
		while(y<=(rectangulo->getAltura()+rectangulo->getPosicion()->getY())){
		//	std::cout<<"y "<<y<<endl;
		color = getpixel(imagen,x,y);
		putpixel(screen,x,y,color);
		y++;
		}
		x++;
	
	}*/

//FIN PONE DENTRO DEL RECTANGULO LA TEXTURA  



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