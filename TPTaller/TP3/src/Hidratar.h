#include "Cuadrado.h"
#include "Circulo.h"
#include "Rectangulo.h"
#include "Triangulo.h"
#include "StringUtils.h"
#include <iostream>
#include "Textura.h"
#include "Pad.h"
#include "Tejo.h"
#include "Puntaje.h"

class Hidratar{

	public:

		static int hidratarCuadrado(std::string atributos);
		static int hidratarCirculo(std::string atributos);
		static int hidratarRectangulo(std::string atributos);
		static int hidratarTriangulo(std::string atributos);
		static int hidratarEscenario(std::string atributos);
		static int hidratartextura(std::string atributos);
		static int hidratarSegmento(std::string atributos);
	//	static int hidratarTejo(std::string atributos);
	//	static int hidratarPads(std::string atributos);

};
