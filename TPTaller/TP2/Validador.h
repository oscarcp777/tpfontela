#ifndef _VALIDADOR_H_
#define _VALIDADOR_H_


#include <iostream>
#include <iostream.h>
#include <string>
#include <vector>
#include "Logfinal.h"
#include "Tag.h"
using namespace std;

class Validador{


private:
	list<Tag*> ListaTagsValidos;
	//list<std::string> ListaTagsValidos;

	list<std::string> ListaTagsArchivo;

	Log* log;

public:

	Validador(std::string nombreArchivoTags,std::string nombreArchivoAtributos);

	void setLog(Log* log);

	int validarValues(std::string tipo,std::string values);

	int validarSintaxis(std::string nombreArchivo);

	int validarArchivoXML(int i,string cadena);

	int validarAperturaYCierreTags();
	//compara la cadena pasada por parametro con los strings de ListaTagsValidos
	//devuelve 0 si la encuentra o numero distinto de 0 (cualquiera) si no perteneces a los tags validos
	int compararConTagsValidos(string cadena);
    int compararConAtributosValidos(string cadenaTag,string cadenaAtributo);
    int compararConVectorAtributosValidos(string cadenaTag,std::vector<string> listaAtributos);

	int borrarDeTagsNoNecesariosDeListaTagsArchivo();
	int hidratar(std::string tipo, std::string values);

};
#endif
