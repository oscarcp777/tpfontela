#include "Hidratar.h"
#include "Escenario.h"
#include "StringUtils.h"
#include "Validador.h"
#include <vector>
#include <map>
#include <string>
static const std::string DELIMITADOR="\"";
static const std::string ID="id";
static const std::string PATH="path";
static const std::string TEXTURA="textura";

  void cargarListaClaves(list<string> listaClave,vector<string> tokens){
	  vector<string>::iterator the_iterator;
	  the_iterator = tokens.begin();
     string valor;
	      for (int var = 0; var < tokens.size(); ++var) {
	          if((var%2)==0){
	          	std::cout<<"par  "<<var<<endl;
				valor =StringUtils::trimPalabra(*the_iterator);
	          	int posicionCaracterIgual = valor.find_first_of("=");
	          	valor= valor.substr(0,posicionCaracterIgual);
	         	listaClave.push_back(valor);
	          }/*else{	std::cout<<"impar  "<<var<<endl;
	        	listaValor.push_back(*the_iterator);
	          }*/
	          the_iterator++;

	  }
  }


Cuadrado* Hidratar::hidratarCuadrado(std::string atributos){

	vector<string> vec;
	string valueId;
	int lado;
	Cuadrado *cuadrado = new Cuadrado();
	StringUtils::Tokenize(atributos,vec,"\"");
    valueId = StringUtils::getValorTag("id",vec);
	lado = atoi((StringUtils::getValorTag("lado",vec)).c_str());
	cuadrado->setIdTextura(valueId);
	cuadrado->setLado(lado);
	
	return cuadrado;
}

Circulo* Hidratar::hidratarCirculo(std::string atributos){
	vector<string> vec;
	string valueId;
	int radio;
	Circulo *circulo = new Circulo();

	StringUtils::Tokenize(atributos,vec,"\"");
	valueId = StringUtils::getValorTag("id",vec);
	radio = atoi((StringUtils::getValorTag("radio",vec)).c_str());
	circulo->setIdTextura(valueId);
	circulo->setRadio(radio);

	return circulo;
}

Rectangulo* Hidratar::hidratarRectangulo(std::string atributos){
	vector<string> vec;
	string valueId;
	int base, altura;
	Rectangulo *rectangulo = new Rectangulo();

	StringUtils::Tokenize(atributos,vec,"\"");
	valueId = StringUtils::getValorTag("id",vec);
	base = atoi((StringUtils::getValorTag("base",vec)).c_str());
	altura = atoi((StringUtils::getValorTag("altura",vec)).c_str());
	rectangulo->setIdTextura(valueId);
	rectangulo->setBase(base);
	rectangulo->setAltura(altura);

	return rectangulo;
}

Triangulo* Hidratar::hidratarTriangulo(std::string atributos){
	vector<string> vec;
	string valueId;
	
	Triangulo *triangulo = new Triangulo();

	StringUtils::Tokenize(atributos,vec,"\"");
	valueId = StringUtils::getValorTag("id",vec);

	triangulo->setIdTextura(valueId);
	

	return triangulo;
}


	int Hidratar::hidratarEscenario(std::string atributos){
		Escenario* escenario = Escenario::obtenerInstancia();
		//atributos
     return 0;
	}
	int Hidratar::hidratartextura(std::string atributos){
		Escenario* escenario=Escenario::obtenerInstancia();
	std::string id;
	std::string path;
	list<string> listaClave;
     vector<string> tokens;
	StringUtils::Tokenize(atributos, tokens,DELIMITADOR);
	cargarListaClaves(listaClave,tokens);
	Validador* validador=escenario->getValidador();
	if(validador->compararConListaAtributosValidos(TEXTURA,listaClave)==0){
	id=StringUtils::getValorTag(ID,tokens);
	path=StringUtils::getValorTag(PATH,tokens);
	Textura *textura = new Textura(id,path);
	escenario->addTextura(textura);
     	std::cout<<"exito AL CREAR LA TEXTURA  SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else{
		std::cout<<"ERROR AL CREAR LA TEXTURA NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		return -1;
	}
}

