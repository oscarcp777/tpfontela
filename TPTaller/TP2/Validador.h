#include <iostream>
#include <iostream.h>

#include <list>

using namespace std;

class Validador{

	
private:
	

public:
	list<std::string> ListaTagsValidos;

	Validador(std::string nombreArchivo);

	int validarSintaxis(std::string nombreArchivo);

	
};

