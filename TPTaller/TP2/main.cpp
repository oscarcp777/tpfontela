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

	Escenario* escenario = Escenario::obtenerInstancia();
	Posicion *posicion1 = new Posicion(10,10);
	Rectangulo *rectangulo = new Rectangulo("rectangulo1",350,340,posicion1);
	Textura *textura1 = new Textura("don","don.png");
	rectangulo->setIdTextura("don");
/*
	Posicion *posicion2 = new Posicion(405,400);
	Rectangulo *rectangulo1 = new Rectangulo("rectangulo1",100,300,posicion2);
*/
	Posicion *posicion3 = new Posicion(500,200);
	Circulo *circulo = new Circulo("circulo1",150,posicion3);
	circulo->setIdTextura("pocoyo");
	Textura *textura2 = new Textura("pocoyo","pocoyo.jpg");
	
	escenario->addFigura(rectangulo);
	escenario->addFigura(circulo);
	escenario->addTextura(textura1);
	escenario->addTextura(textura2);

	escenario->graficar();	



	SDL_FreeSurface(escenario->getScreen());
	SDL_Quit();

	return 0;
}