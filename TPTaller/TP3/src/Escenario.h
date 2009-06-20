#ifndef __ESCENARIO_H__
#define __ESCENARIO_H__

#include <iostream>
#include "Figura.h"
#include "Textura.h"
#include <list>
#include <map>
#include "SDL.h"
#include <SDL_IMAGE.h>
#include "Color.h"
#include "Pad.h"
#include "Tejo.h"
#include "Validador.h"
/*#include "DecLongPad.h"
#include "DecLongPadVs.h"
#include "DecRadioTejo.h"
#include "IncLongPad.h"
#include "IncLongPadVs.h"
#include "IncRadioTejo.h"
#include "IncVelocidadTejo.h"
#include "PegamentoTejo.h"
#include "FrenoTejo.h"
#include "Bonus.h"*/
		
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
    void setAncho(int ancho);
    int getAncho();
    void setAlto(int alto);
    int getAlto();
    void setResolucion(int resolucion);
    int getResolucion();
    int graficar();
    SDL_Color getColorFondoEscenario();
    Color *getColorFondoFiguras();
    Color *getColorLinea();
    void setColorFondoEscenario(Color *colorFondoEscenario);
    void setColorFondoFiguras(Color *colorFondoFiguras);
    void setColorLinea(Color *colorLinea);
    void setIdTextura(std::string idTextura);
    Log *getLog();
    void pintarPantalla();
    SDL_Surface *getScreen();
    int cargarArchivo(std::string nombreArchivo);
    Validador *getValidador();
    void setTexturaFig(std::string texturaFig);
    std::string getTexturaFig();
    std::string getTexturaEsc();
    void setTexturaEsc(std::string texturaEsc);
    bool existeIdFigura(std::string idFigura);
    Rectangulo *getArcoDerecha();
    void setArcoDerecha(Rectangulo *arcoDerecha);
    Rectangulo *getArcoIzquierda();
    void setArcoIzquierda(Rectangulo *arcoIzquierda);
    Posicion *getPosicionInicialTejo();
    void setPosicionInicialTejo(Posicion *posicionInicialTejo);
	//void inicializarListaBonus();
	//void shuffleListBonus();
    int iniciarSDL();
	//void setNumJugador(int num);
	int getNumJugador();
	Pad* getPadJugador();
	void setPadJugador(int jugador);
	int getTejosRestantes();
	void setTejosRestantes(int cantTejos);
	void decrementarTejosRestantes();
	bool getCorriendo();
	void setCorriendo(bool corriendo);
	int getNumeroNivel();
	void incrementarNivel();
	std::string getNumeroNivelEnString();

protected:
		Escenario();

	private:

		SDL_Surface* icono;
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
		//std::list<Bonus*> listaBonus;
		Tejo* tejo;
		Pad* padCliente1;
		Pad* padCliente2;
		Color* colorFondoEscenario;
		Color* colorFondoFiguras;
		Color* colorLinea;
		Log log;
		Validador* validador;
		Rectangulo* arcoDerecha;
		Rectangulo* arcoIzquierda;
		Posicion* posicionInicialTejo;
		int numJugador;
		Pad* padJugador;
		int tejosRestantes;
		bool corriendo;
		int numeroNivel;
};

#endif
