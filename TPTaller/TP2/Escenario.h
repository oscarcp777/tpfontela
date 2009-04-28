#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_

#include <iostream>
#include "Figura.h"
#include "Textura.h"
#include <list>
#include <map>
#include "SDL.h"
#include "Color.h"
//#include "Logfinal.h"
#include "Validador.h"



// ESCENARIO ES UN SINGLETON
class Escenario {

	public:
			Escenario::~Escenario();
			static Escenario* obtenerInstancia();
			void addFigura(Figura *figura);
			void addTextura(Textura *textura);
			int sizeListaFiguras();
			int sizeListaTexturas();
			std::list<Figura*>::iterator iteratorListaFiguras();
			std::list<Textura*>::iterator iteratorListaTexturas();
			std::string Escenario::obtenerPathTextura(std::string id);
			//TODO hacer geters y setters atributos
			void setAncho(int ancho);
			int getAncho();
			void setAlto(int alto);
			int getAlto();
			void setResolucion(int resolucion);
			int getResolucion();
			int graficar();
			SDL_Color getColorFondoEscenario();
		    SDL_Color getColorFondoFiguras();
			SDL_Color getColorLinea();
		    void  setColorFondoEscenario(Color* colorFondoEscenario);
		    void  setColorFondoFiguras(Color* colorFondoFiguras);
		    void  setColorLinea(Color* colorLinea);
			void setIdTextura(std::string idTextura);
			Log* getLog();
			void pintarPantalla();
			SDL_Surface* getScreen();
			int cargarArchivo(std::string nombreArchivo);
			Validador* getValidador();



	protected:
		Escenario();

	private:
		int ancho;
		int alto;
		int resolucion;
		Color* colorFondoFig;
		std::string texturaFig;
		std::string colorLineaString;
		std::string colorFondoEsc;
		std::string texturaEsc;
		static Escenario *unicaInstanciaEscenario;
		SDL_Surface *screen;
		std::list<Figura*> listaFiguras;
		std::list<Textura*> listaTexturas;
		Color* colorFondoEscenario;
		Color* colorFondoFiguras;
		Color* colorLinea;
		Log log;
		Validador* validador;
};

#endif
