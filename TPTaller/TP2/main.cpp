#include <iostream>
#include <string>
#include "archivoTexto.h"
#include <list>
#include "Validador.h"

using namespace std;


int main()
{

    
	int exito;

	Validador *validador = new  Validador("config Validador.txt");
	exito = validador->validarSintaxis("XML.xml");
	if(exito == 0){
		std::cout<<"*******************************"<<endl;
		std::cout<<"EL ARCHIVO XML NO TIENE ERRORES"<<endl;
		std::cout<<"*******************************"<<endl;
	}
	else{
		std::cout<<"****************************************"<<endl;
		std::cout<<"SE ENCONTRARON ERRORES EN EL ARCHIVO XML"<<endl;
		std::cout<<"****************************************"<<endl;
	}
	/*
	list<string>::iterator i;
    i= validador->ListaTagsArchivo.begin();	
	while(i != validador->ListaTagsArchivo.end()){
	std::cout << *i<< " "<<endl;
	i++;
	}*/

	system("PAUSE");
   





}