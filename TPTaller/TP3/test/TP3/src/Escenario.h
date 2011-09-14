#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_

#include <iostream>
#include "Figura.h"
#include "Textura.h"
#include <list>
#include <map>
#include "SDL.h"
#include "Color.h"
#include "Pad.h"
#include "Tejo.h"
#include "Validador.h"



// ESCENARIO ES UN SINGLETON
class Escenario {

	public:
			~Escenario();
			static Escenario* obtenerInstancia();
			void addFigura(Figura *figura);
			void setTejo(Tejo *tejo);
			void setPadCliente1(Pad *padCliente1);
			Pad* getPadCliente1();
			Pad* getPadCliente2();
			Tejo* getTejo();
			void setPadCliente2(Pad *padCliente2);
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
		    Color* getColorFondoFiguras();
			Color* getColorLinea();
		    void  setColorFondoEscenario(Color* colorFondoEscenario);
		    void  setColorFondoFiguras(Color* colorFondoFiguras);
		    void  setColorLinea(Color* colorLinea);
			void setIdTextura(std::string idTextura);
			Log* getLog();
			void pintarPantalla();
			SDL_Surface* getScreen();
			int cargarArchivo(std::string nombreArchivo);
			Validador* getValidador();
		    void setTexturaFig(std::string texturaFig);
			std::string getTexturaFig();
			std::string getTexturaEsc();
			void setTexturaEsc(std::string texturaEsc);
			bool existeIdFigura(std::string idFigura);


	protected:
		Escenario();

	private:
		SDL_Surface *fondoPantalla;
		int ancho;
		int alto;
		int resolucion;
		std::string texturaFig;
		std::string texturaEsc;
		static Escenario *unicaInstanciaEscenario;
		SDL_Surface *screen;
		std::list<Figura*> listaFiguras;
		std::list<Textura*> listaTexturas;
		Tejo* tejo;
		Pad* padCliente1;
		Pad* padCliente2;
		Color* colorFondoEscenario;
		Color* colorFondoFiguras;
		Color* colorLinea;
		Log log;
		Validador* validador;
};

#endif
