#include <iostream>
#include "Figura.h"
#include "Textura.h"
#include <list>
#include <map>


// ESCENARIO ES UN SINGLETON 
class Escenario {
	
	public:
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
			
	
	protected:
		Escenario();
	
	private:
		int ancho;
		int alto;
		int resolucion;
		std::string colorFondoFig;
		std::string texturaFig;
		std::string colorLinea;
		std::string colorFondoEsc;
		std::string texturaEsc;
		static Escenario *unicaInstanciaEscenario;

		std::list<Figura*> listaFiguras;	
		std::list<Textura*> listaTexturas;	
		
};
