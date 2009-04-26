#include "Figura.h"


std::string Figura::getId(){
		return this->id;
}

void Figura::setIdTextura(std::string idTextura){
	this->idTextura = idTextura;
}
std::string Figura::getIdTextura(){
		return this->idTextura;
}


void Figura::putpixel(SDL_Surface *screen, int x, int y, SDL_Color color)
{
	// Convertimos color
	Uint32 col=SDL_MapRGB(screen->format, color.r, color.g, color.b);
	// Determinamos posici�n de inicio
	char *buffer=(char*) screen->pixels;
	// Calculamos offset para y
	buffer+=screen->pitch*y;
	// Calculamos offset para x
	buffer+=screen->format->BytesPerPixel*x;
	// Copiamos el pixel
	memcpy(buffer, &col, screen->format->BytesPerPixel);
}

SDL_Color Figura::getpixel(SDL_Surface *imagen, int x, int y)
{
	SDL_Color color;
	Uint32 col;
	// Determinamos posici�n de inicio
	char *buffer=(char *) imagen->pixels;
	// Calculamos offset para y
	buffer+=imagen->pitch*y;
	// Calculamos offset para x
	buffer+=imagen->format->BytesPerPixel*x;
	// Obtenemos el pixel
	memcpy(&col, buffer, imagen->format->BytesPerPixel);
	// Descomponemos el color
	SDL_GetRGB(col, imagen->format, &color.r, &color.g, &color.b);
	// Devolvemos el color
	return color;
}
