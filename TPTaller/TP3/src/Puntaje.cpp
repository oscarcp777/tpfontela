// Puntaje.cpp: implementation of the Puntaje class.
//
//////////////////////////////////////////////////////////////////////

#include "Puntaje.h"
#include "Define.h"
#include "Escenario.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Puntaje::Puntaje()
{
	this->textImagen=NULL;
	this->cantPuntosJugador=0;
}

int Puntaje::getCantPuntosJugador(){
	return this->cantPuntosJugador;
}

void Puntaje::setCantPuntosJugador(int cantPuntos){
	this->cantPuntosJugador=cantPuntos;
}

int Puntaje::getPuntajeTotal(){
	return this->cantPuntosJugador + PUNTAJE_GANADOR_NIVEL;
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

	fuente = TTF_OpenFont("arial.ttf", 150);
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

int Puntaje::graficarPuntaje(int puntajeJugadorIzquierda, int puntajeJugadorDerecha,SDL_Surface*screen,TTF_Font* fuente,bool gol){
	Escenario* escenario= Escenario::obtenerInstancia();
	if(gol){

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

	fuente = TTF_OpenFont("arial.ttf",TAMANIO_LETRA);

	TTF_SetFontStyle(fuente, TTF_STYLE_BOLD);


	if(fuente == NULL){
	 printf("fallo la fuente");
	 return -1;
	}



	textImg=TTF_RenderText_Blended(fuente,puntaje.c_str(), color);
    if(textImg == NULL) {
     printf("Fallo al renderizar el texto");
       return -1;
	}
    this->textImagen = textImg;
    SDL_Rect rect={ (int)(escenario->getAncho()/2)-(int)(ANCHO_PUNTAJES/2), 0, ANCHO_PUNTAJES, ALTO_PUNTAJES };
	SDL_BlitSurface(this->textImagen,NULL,screen,&rect);

	}else{
		SDL_Rect rect1={ (int)(escenario->getAncho()/2)-(int)(ANCHO_PUNTAJES/2), 0, ANCHO_PUNTAJES, ALTO_PUNTAJES };
			SDL_BlitSurface(this->textImagen,NULL,screen,&rect1);
	}

	return 0;
}

Puntaje::~Puntaje()
{

}
