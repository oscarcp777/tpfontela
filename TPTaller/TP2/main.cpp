#include <iostream>
#include <string>
#include "archivoTexto.h"
#include <list>
#include "Validador.h"

using namespace std;

int validarSintaxis(list<std::string> L){
 int exito;
	





return exito;
}




int main()
{

    
	int exito;
	Validador *validador = new  Validador("config Validador.txt");
    
	
	list<string>::iterator i;
    
//	IMPRIME todos los elementos de la listaTagsValidos
/*	for(i=validador->ListaTagsValidos.begin(); i != validador->ListaTagsValidos.end(); ++i) {
	   std::cout << *i<< " "<<endl;
	}*/
   

	exito = validador->validarSintaxis("XML.xml");

	if(exito == 0){
		std::cout <<"LA SINTAXIS DEL ARCHIVO ES CORRECTA"<< " "<<endl;
	}
	else {
		std::cout <<"LA SINTAXIS ES INCORRECTA"<< " "<<endl;
	}
	system("PAUSE");
   





}