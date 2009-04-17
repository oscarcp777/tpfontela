#include <iostream>
#include "Figura.h"
#include "Textura.h"
#include <list>
#include <map>

class Escenario {
	
	public:
			Escenario();
			void addFigura(Figura *figura);
			void addTextura(Textura *textura);
			int sizeListaFiguras();
			std::list<Figura*>::iterator iteratorListaFiguras();
			//TODO hacer geters y setters atributos
			int graficar();
			
	private:
		
		int resolucion;
		std::string colorFondoFig;
		std::string texturaFig;
		std::string colorLinea;
		std::string colorFondoEsc;
		std::string texturaEsc;
		std::list<Figura*> listaFiguras;	
		
		std::map<std::string,std::string>  mapaTexturas;  //es un mapa clave valor (string idTextura, string path)
	
};
