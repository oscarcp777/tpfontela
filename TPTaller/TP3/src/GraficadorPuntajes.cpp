/*
 * GraficadorPuntajes.cpp
 *
 *  Created on: 10/06/2009
 *      Author: oscar
 */

#include "GraficadorPuntajes.h"
#include "Escenario.h"
#include "Define.h"
GraficadorPuntajes* GraficadorPuntajes::unicaInstancia = NULL;


GraficadorPuntajes::GraficadorPuntajes() {
	this->imagenTejo=NULL;
	this->textImagen=NULL;	
	
}
GraficadorPuntajes* GraficadorPuntajes::obtenerInstancia(){

	if(!GraficadorPuntajes::unicaInstancia){
		GraficadorPuntajes::unicaInstancia = new GraficadorPuntajes();
		unicaInstancia->inicializarFuente(0,0);
	}

	return GraficadorPuntajes::unicaInstancia;
}

GraficadorPuntajes::~GraficadorPuntajes() {
	// TODO Auto-generated destructor stub
}


void GraficadorPuntajes::graficarCantidadDeTejos(SDL_Surface*screen){
	Escenario* escenario = Escenario::obtenerInstancia();
	int ladoTejoPuntajes=(int)(escenario->getAncho()*PORCENTAJE_TEJO_PUNTAJES);
   
	
SDL_Surface* image;
	//	 Cargamos la imagen
	if(this->imagenTejo==NULL){
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(escenario->getTejo()->getFigura()->getIdTextura());

		image = IMG_Load(path.begin());
		//			this->imagen = SDL_LoadBMP(path.begin());
		if(image == NULL) {
			std::cout<< "Error: " << SDL_GetError() << endl;
			exit(1);
		}
		//si la imagen no es null (es decir si la levanto bien) la escalo
		if(image != NULL){
			image = Figura::ScaleSurface(image, ladoTejoPuntajes,ladoTejoPuntajes);
		}
		//			// Calculamos el color transparente, en nuestro caso el verde
		SDL_SetColorKey(image,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(image->format,255 ,255, 255));
		this->imagenTejo = SDL_DisplayFormat(image);
		  SDL_FreeSurface(image);
	}
	for(int i=1;i<=escenario->getTejosRestantes()-1;i++){
	SDL_Rect rect;
	rect.x =i*ladoTejoPuntajes;
	rect.y =8;
	SDL_BlitSurface(this->imagenTejo, NULL, screen, &rect);
	}
}


void IntToString(int i, string & s)
{
    s = "";
    if (i == 0)
    {
        s = "0";
        return;
    }
    if (i < 0)
    {
        s += '-';
        i = -i;
    }
    int count = (int)log10(i);
    while (count >= 0)
    {
        s += ('0' + i/pow(10.0, count));
        i -= static_cast<int>(i/pow(10.0,count)) * static_cast<int>(pow(10.0,count));
        count--;
    }
}

int openFont(TTF_Font* fuente){

	if (TTF_Init() == -1) {
		printf("Fallo al inicializar SDL_TTF");
		return -1;
	}

	fuente = TTF_OpenFont("arial.ttf", 100);
	if(fuente == NULL) {
	printf("Fallo al abrir la fuente");
	    return -1;
	}

	TTF_SetFontStyle(fuente, TTF_STYLE_BOLD);

	return 0;

}

void closeFont(TTF_Font* fuente){
 TTF_CloseFont(fuente);
 TTF_Quit();
}

//puntajeJugadorIzquierda=this->getPadCliente1()->getPuntaje()->getCantPuntosJugador(),
//puntajeJugadorDerecha=this->getPadCliente2()->getPuntaje()->getCantPuntosJugador(),

int GraficadorPuntajes::inicializarFuente(int puntajeJugadorIzquierda, int puntajeJugadorDerecha){
	
	//Fuente que se va a utilizar
	SDL_Surface* textImg;
	SDL_Color color= {0, 0, 0, 255};

		std::string puntaje,puntajeJugador;
		IntToString(puntajeJugadorIzquierda,puntajeJugador);
		puntaje+=puntajeJugador;
		IntToString(puntajeJugadorDerecha,puntajeJugador);
		puntaje+='-';
		puntaje+=puntajeJugador;

	

	if (TTF_Init() == -1) {
		printf("Fallo al inicializar SDL_TTF");
		return -1;
	}

	this->fuente = TTF_OpenFont("arial.ttf",TAMANIO_LETRA);

	TTF_SetFontStyle(this->fuente, TTF_STYLE_BOLD);


	if(this->fuente == NULL){
	 printf("fallo la fuente");
	 return -1;
	}



	textImg=TTF_RenderText_Blended(this->fuente,puntaje.c_str(), color);
    if(textImg == NULL) {
     printf("Fallo al renderizar el texto");
       return -1;
	}
    this->textImagen = textImg;


}

int GraficadorPuntajes::graficarPuntaje(SDL_Surface*screen){
		
		
		Escenario* escenario = Escenario::obtenerInstancia();
		SDL_Color color= {0, 0, 0, 255};//TODO poner el color como atributo de graficador puntaje y llamarlo como this->color hacer lo mismo con textImg
		
		std::string puntaje,puntajeJugador;
		IntToString(escenario->getPadCliente2()->getPuntaje()->getCantPuntosJugador(),puntajeJugador);
		puntaje+=puntajeJugador;
		IntToString(escenario->getPadCliente1()->getPuntaje()->getCantPuntosJugador(),puntajeJugador);
		puntaje+='-';
		puntaje+=puntajeJugador;
		
		this->textImagen=TTF_RenderText_Blended(this->fuente,puntaje.c_str(), color);
		
		if(this->textImagen == NULL) {
			printf("Fallo al renderizar el texto");
			return -1;
		}
		
		SDL_Rect rect1={ (int)(escenario->getAncho()/2)-(int)(ANCHO_PUNTAJES/2), 0, ANCHO_PUNTAJES, ALTO_PUNTAJES };
		SDL_BlitSurface(this->textImagen,NULL,screen,&rect1);
	

	return 0;
}

int GraficadorPuntajes::graficarString(SDL_Surface*screen, std::string mensaje, int posX, int posY){
		
		Escenario* escenario = Escenario::obtenerInstancia();
		SDL_Color colorTexto= {0, 100, 155, 255};//TODO poner el color como atributo de graficador puntaje y llamarlo como this->color hacer lo mismo con textImg
		SDL_Color colorFondo= {0, 0, 0, 255};
	
		this->textImg = TTF_RenderText_Blended(this->fuente,mensaje.c_str(), colorTexto);
		
		if(this->textImg == NULL) {
			printf("Fallo al renderizar el texto");
			return -1;
		}
		
		SDL_Rect dest;
		dest.x = 0;
		dest.y = 0;
		dest.w = screen->w;
		dest.h = screen->h;
		SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format, colorFondo.r,colorFondo.g,colorFondo.b));
		
		SDL_Rect rect;
		rect.h= escenario->getAlto();
		rect.w= escenario->getAncho();
		rect.x = posX;
		rect.y = posY;
		SDL_BlitSurface(this->textImg,NULL,screen,&rect);
	

	return 0;
}

void GraficadorPuntajes::setImagen(SDL_Surface *imagen){

	this->imagenTejo = imagen;
}