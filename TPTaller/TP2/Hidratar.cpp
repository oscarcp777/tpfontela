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
