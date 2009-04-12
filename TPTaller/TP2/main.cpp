#include <iostream>
#include <iostream.h>
#include "cadena.h"
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
	ArchivoTexto archivo;
    
	int exito;
	Validador *validador = new  Validador("config Validador.txt");
    
	
	list<std::string>::iterator iteradorLista;
    
//	IMPRIME todos los elementos de la listaTagsValidos
	for(iteradorLista=validador->ListaTagsValidos.begin(); iteradorLista != validador->ListaTagsValidos.end(); ++iteradorLista) {
	   std::cout << *iteradorLista << " "<<endl;
	}

	exito = validador->validarSintaxis("XML.txt");

	if(exito == 0){
		std::cout <<"LA SINTAXIS DEL ARCHIVO ES CORRECTA"<< " "<<endl;
	}
	else {
		std::cout <<"LA SINTAXIS ES INCORRECTA"<< " "<<endl;
	}
	system("PAUSE");
    destruir(archivo);
   





}