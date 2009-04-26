#include "Dibujar.h"
#include "Escenario.h"
#include <math.h>
#include <SDL_main.h>
#define WALLCOLOR 0x9f1f1f
Dibujar::Dibujar(){
}/*
Dibujar* Dibujar::unicaInstanciaDibujar = NULL;
Dibujar* Dibujar::obtenerInstancia(){
	
	if(!Dibujar::unicaInstanciaDibujar){
		Dibujar::unicaInstanciaDibujar = new Dibujar();
	}
	
	return Dibujar::unicaInstanciaDibujar;
}
*/
void Dibujar::dibujarTriangulo(SDL_Surface *screen,int izqX, int izqY,int derX, int derY,int supX, int supY){
	

     Dibujar::dibujarLinea(screen ,izqX,  izqY, derX, derY);
	 Dibujar::dibujarLinea(screen ,derX, derY, supX,supY); 
	 Dibujar::dibujarLinea(screen ,izqX,  izqY, supX,supY);



}
 void Dibujar::dibujarLinea(SDL_Surface *screen ,int x1, int y1, int x2, int y2){
	Escenario *escenario = Escenario::obtenerInstancia();
int color=	SDL_MapRGB(screen->format,escenario->getColorLinea()->getColorFondo_R(),
			 escenario->getColorLinea()->getColorFondo_G(),escenario->getColorLinea()->getColorFondo_B());
	bool steep = abs(y2-y1) > abs(x2-x1);
	if( steep )
	{
		int t = x1;
		x1 = y1;
		y1 = t;
		t = x2;
		x2 = y2;
		y2 = t;
	}
	if( x1 > x2 )
	{
		int t = x1;
		x1 = x2;
		x2 = t;
		t = y1;
		y1 = y2;
		y2 = t;
	}
	int dx = x2 - x1;
	int dy = abs(y2-y1);
	int error = 0;
	int ystep = 0;
	int y = y1;
	if( y1 < y2 ) ystep = 1; else ystep = -1;
	for(int x = x1; x < x2; x++ )
	{
		if( steep )
		{
			plot(screen, y, x, color );
		}
		else
		{
			plot( screen, x, y, color );
		}
		error = error + dy;
		if( 2*error >= dx )
		{
			y = y + ystep;
			error = error - dx;
		}
	}
}

void Dibujar::plot( SDL_Surface* surface, int x, int y, int color )
{
	if( x >= 0 && x < surface->w && y >= 0 && y < surface->h )
	{
		unsigned int* p = (unsigned int*) surface->pixels;
		p[(y*(surface->pitch/4))+x] = color;
	}
}

void Dibujar::pintarPantalla(SDL_Surface *screen){
		Escenario *escenario = Escenario::obtenerInstancia();
	SDL_Rect dest;
dest.x = 0;
dest.y = 0;
dest.w = screen->w;
dest.h = screen->h;
SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format,escenario->getColorFondoEscenario()->getColorFondo_R(),
			 escenario->getColorFondoEscenario()->getColorFondo_G(),escenario->getColorFondoEscenario()->getColorFondo_B()));
}

 void Dibujar::dibujarRectangulo(SDL_Surface *screen,int posX, int posY, int ancho, int alto){
	Escenario *escenario = Escenario::obtenerInstancia();
	SDL_Rect dest;
dest.x = posX;
dest.y = posY;
dest.w = ancho;
dest.h = alto;
SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format,escenario->getColorFondoFiguras()->getColorFondo_R(),
			 escenario->getColorFondoFiguras()->getColorFondo_G(),escenario->getColorFondoFiguras()->getColorFondo_B()));	


}
 void Dibujar::dibujarCirculo(SDL_Surface *screen,int posX, int posY, int radio){
	Escenario *escenario = Escenario::obtenerInstancia();
int color=	SDL_MapRGB(screen->format,escenario->getColorFondoFiguras()->getColorFondo_R(),
			 escenario->getColorFondoFiguras()->getColorFondo_G(),escenario->getColorFondoFiguras()->getColorFondo_B());
  int i, j;
  int PITCH =(screen)->pitch / 4;
  for (i = 0; i < 2 * radio; i++)
  {
    // vertical clipping: (top and bottom)
	  if ((posY - radio + i) >= 0 && (posY - radio + i) < escenario->getAlto())
    {
		  int len = (int)sqrt((float)(radio * radio - (radio - i) * (radio - i))) * 2;
      int xofs = posX - len / 2;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= escenario->getAncho())
      {
        len -= (xofs + len) - escenario->getAncho();
      }
      int ofs = (posY - radio + i) * PITCH + xofs;
      
      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; j++)
        ((unsigned int*)(screen)->pixels)[ofs + j] = color;
    }
  }
}