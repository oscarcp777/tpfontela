#include <iostream>
#include <iostream.h>
#include <string>
#include <list>
#include "Logfinal.h"
#include "Tag.h"
using namespace std;

class Validador{

	
private:
	list<Tag*> ListaTagsValidos;
	//list<std::string> ListaTagsValidos;

	list<std::string> ListaTagsArchivo;

public:
	
	Validador(std::string nombreArchivoTags,std::string nombreArchivoAtributos);

	
	int validarValues(std::string tipo,std::string values);

	int validarSintaxis(std::string nombreArchivo);
	
	int validarArchivoXML(int i,string cadena);

	int validarAperturaYCierreTags();
	//compara la cadena pasada por parametro con los strings de ListaTagsValidos
	//devuelve 0 si la encuentra o numero distinto de 0 (cualquiera) si no perteneces a los tags validos
	int compararConTagsValidos(string cadena);
	int compararConAtributosValidos(string cadenaTag,string cadenaAtributo);

	int borrarDeTagsNoNecesariosDeListaTagsArchivo();
	
	int hidratar(std::string tipo, std::string values);
	
};
