#include <iostream>
#include <list>
#include <string>
#include "Validador.h"
#include "archivoTexto.h" 
#include "StringUtils.h" 
using namespace std;


Validador::Validador(std::string nombreArchivo){
	 ArchivoTexto miArchivo(nombreArchivo);
  string linea;
  miArchivo.irAlPrincipio();
  while (miArchivo.leerLinea(linea)) {
        std::cout << linea << std::endl;
	    //leo la linea y la guardo en la Lista
	   Validador::ListaTagsValidos.push_back(linea);

    }
}


Validador::validarSintaxis(std::string nombreArchivo){
    StringUtils *stringUtils= new StringUtils();
	string cadena,linea;
    ArchivoTexto miArchivo(nombreArchivo);
    miArchivo.irAlPrincipio();
  
  while (miArchivo.leerLinea(linea)) {
    std::cout << linea << std::endl;
	   cadena += linea;
			 
    }
    cadena=stringUtils->trim(cadena);
    std::cout<<cadena<<endl;
    ArchivoTexto miArchivo1("XMLSinEspacios.txt");
    miArchivo1.irAlPrincipio();
    miArchivo1.escribir(cadena);
	return 0;
}




