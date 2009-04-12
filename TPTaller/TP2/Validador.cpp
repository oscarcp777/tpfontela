#include <iostream>
#include <list>
#include <string>
#include "Validador.h"
#include "archivoTexto.h" 

using namespace std;


Validador::Validador(std::string nombreArchivo){
	ArchivoTexto archivoConfig;
	std::string linea;
	//abre el archivo si existe
	crear(archivoConfig, nombreArchivo);
  
	while (!fin(archivoConfig))
    {
       leerLinea(archivoConfig,linea);
	    //leo la linea y la guardo en la Lista
	   Validador::ListaTagsValidos.push_back(linea);

    }
}


Validador::validarSintaxis(std::string nombreArchivo){
	ArchivoTexto archivoXML;
	std::string linea;
	string cadena;
	
	//abre el archivo si existe
	crear(archivoXML, nombreArchivo);
	
	while (!fin(archivoXML))
    {
	   leerLinea(archivoXML,linea);
	   cadena += linea;
			   

    }
	Validador::validarCadena(cadena);
	std::cout<<cadena.begin()<<endl;
	
	return 0;
}
Validador::validarCadena( string cadena){
string tagApertura="<";
cadena
<circulo id="hola">




}






