#include "Cuadrado.h" 
#include "Circulo.h"
#include "Rectangulo.h"
#include "Triangulo.h"
#include "StringUtils.h"
#include <iostream>
#include "Textura.h"

class Hidratar{
	
	public: 
		
		static Cuadrado* hidratarCuadrado(std::string atributos);
		static Circulo* hidratarCirculo(std::string atributos);
		static Rectangulo* hidratarRectangulo(std::string atributos);
		static Triangulo* hidratarTriangulo(std::string atributos);
		static int hidratarEscenario(std::string atributos);
		static int hidratartextura(std::string atributos);
		
};