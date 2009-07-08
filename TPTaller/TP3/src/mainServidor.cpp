#include <iostream>
#include <fstream>
#include "Servidor.h"
#include "Utilidades.h"

using namespace std;



int main(int argc, char* argv[]){
	int error = 0;



	Servidor* s = new Servidor(1050, 2);
	s->start(NULL);
	s->join();
	delete(s);
	
	
	return 0;
}
