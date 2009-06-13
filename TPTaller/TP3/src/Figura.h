#ifndef _FIGURA_H_
#define _FIGURA_H_

//#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include "Color.h"
#include "Posicion.h"
#include "RectanguloInfluencia.h"
#include <list>

class Figura{

	public:
		 virtual int dibujar(SDL_Surface *screen)=0; //metodo virtual puro
		 Figura();
		 virtual ~Figura();
		 std::string getId();
		 std::string getIdTextura();
		 void setId(std::string id);
		 void setIdTextura(std::string idTextura);
		 static SDL_Surface* ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);
		 static void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
		 static Uint32 ReadPixel(SDL_Surface *surface, int x, int y);
         Color* getColorLinea();
         void setColorLinea(Color *colorLinea);
         Color* Figura::getColorFigura();
          void Figura::setColorFigura(Color *colorFigura);
          Posicion* getPosicion();
          void setPosicion(Posicion * posicion);
          std::list<RectanguloInfluencia*>::iterator iteratorRectangulosDeInfluencia();
          void addRectanguloInfluencia(RectanguloInfluencia *rectanguloInfluencia);
          int sizeListaRectangulos();
		  virtual void calcularRadioDeInfluencia()=0;
		  int getX();
	 	  int getY();
		  int getXInfluencia();

		     void setXInfluencia(int xInfluencia);

		     int getYInfluencia();

		     void setYInfluencia(int yInfluencia);

		     int getAnchoInfluencia();

              void analizarChoque();
		     void setAnchoInfluencia(int anchoInfluencia);

		     int getAltoInfluencia();


		     void setAltoInfluencia(int altoInfluencia);
             std::string getTipo();
             void setTipo(std::string tipo);

protected:
	    int xInfluencia;
	    int yInfluencia;
	    int anchoInfluencia;
	    int altoInfluencia;
		std::string id;
		std::string idTextura;
		std::string tipo;
		SDL_Color color;
		Color* colorFigura;
		Color* colorLinea;
		SDL_Surface *imagen; //donde se guarda la imagen en caso de tenerla
		Posicion *pos;
		std::list<RectanguloInfluencia*> rectangulosDeInfluencia;

		void putpixel(SDL_Surface *screen, int x, int y, SDL_Color color);
		SDL_Color getpixel(SDL_Surface *imagen, int x, int y);
		void dibujarLinea(SDL_Color color,SDL_Surface *screen ,int x1, int y1, int x2, int y2);
		void plot( SDL_Surface* surface, int x, int y, SDL_Color color);

};
#endif
