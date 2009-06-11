#include <iostream>
#include <fstream>
#include "Servidor.h"
#include "Utilidades.h"

using namespace std;



int main(int argc, char* argv[]){
	int error = 0;

	char leyenda[30];
	char* pLeyenda = leyenda;
	char puerto[50];
	pLeyenda = "PUERTO DE CONEXION (EJ: 2121)";

	ingresoMensaje(puerto,pLeyenda);

	Servidor* s = new Servidor(atoi(puerto), 2);
	s->start(NULL);
	s->join();
	delete(s);
	
	return 0;
}
