#include <iostream>
#include <iostream.h>
#include <string>
#include <list>
#include "Logfinal.h"
using namespace std;

class Validador{

	
private:
	

public:
	list<std::string> ListaTagsValidos;

	list<std::string> ListaTagsArchivo;

	Validador(std::string nombreArchivo);

	int validarSintaxis(std::string nombreArchivo);
	
	int validarArchivoXML(int i,string cadena);

	int validarAperturaYCierreTags();
	//compara la cadena pasada por parametro con los strings de ListaTagsValidos
	//devuelve 0 si la encuentra o numero distinto de 0 (cualquiera) si no perteneces a los tags validos
	int compararConTagsValidos(string cadena);

	int borrarDeTagsNoNecesariosDeListaTagsArchivo();
	
};

