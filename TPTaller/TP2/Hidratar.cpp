#include "Hidratar.h"
#include "Escenario.h"
#include "StringUtils.h"
#include "Validador.h"
#include <vector>
#include <map>
#include <string>
static const std::string DELIMITADOR="\"";
static const std::string ID="id";
static const std::string RADIO="radio";
static const std::string LADO="lado";
static const std::string BASE="base";
static const std::string ALTURA="ALTURA";
static const std::string PATH="path";
static const std::string TEXTURA="textura";
static const std::string CUADRADO="cuadrado";
static const std::string RECTANGULO="rectangulo";
static const std::string TRIANGULO="triangulo";
static const std::string CIRCULO="circulo";

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


int Hidratar::hidratarCuadrado(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	list<string> listaClave;
	vector<string> vec;
	string valueId;
	int lado;
	Cuadrado *cuadrado;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConListaAtributosValidos(CUADRADO,listaClave)==0){
	cuadrado = new Cuadrado();
	valueId = StringUtils::getValorTag(ID,vec);
	lado = atoi((StringUtils::getValorTag(LADO,vec)).c_str());
	cuadrado->setIdTextura(valueId);
	cuadrado->setLado(lado);
	escenario->addFigura(cuadrado);
     	std::cout<<"exito AL CREAR EL CUADRADO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL CUADRADO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		
	return -1;
	
	

}

int Hidratar::hidratarCirculo(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	list<string> listaClave;
	vector<string> vec;
	string valueId;
	int radio;
	Circulo *circulo;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConListaAtributosValidos(CIRCULO,listaClave)==0){
	circulo = new Circulo();
	valueId = StringUtils::getValorTag(ID,vec);
	radio = atoi((StringUtils::getValorTag(RADIO,vec)).c_str());
	circulo->setIdTextura(valueId);
	circulo->setRadio(radio);
	escenario->addFigura(circulo);
     	std::cout<<"exito AL CREAR EL CIRCULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL CIRCULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		
	return -1;
}

int Hidratar::hidratarRectangulo(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	list<string> listaClave;
	vector<string> vec;
	string valueId;
	int base,altura;
	Rectangulo *rectangulo;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConListaAtributosValidos(RECTANGULO,listaClave)==0){
	rectangulo = new Rectangulo();
	valueId = StringUtils::getValorTag(ID,vec);
	base = atoi((StringUtils::getValorTag(BASE,vec)).c_str());
	altura = atoi((StringUtils::getValorTag(ALTURA,vec)).c_str());
	rectangulo->setIdTextura(valueId);
	rectangulo->setBase(base);
	rectangulo->setAltura(altura);
	escenario->addFigura(rectangulo);
     	std::cout<<"exito AL CREAR EL RECTANGULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL RECTANGULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		
	return -1;
}

int Hidratar::hidratarTriangulo(std::string atributos){
		Escenario* escenario=Escenario::obtenerInstancia();
	list<string> listaClave;
	vector<string> vec;
	string valueId;
	Triangulo *triangulo;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConListaAtributosValidos(TRIANGULO,listaClave)==0){
	triangulo = new Triangulo();
	valueId = StringUtils::getValorTag(ID,vec);
	triangulo->setIdTextura(valueId);
	escenario->addFigura(triangulo);
     	std::cout<<"exito AL CREAR EL TRIANGULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL TRIANGULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		
	return -1;
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

