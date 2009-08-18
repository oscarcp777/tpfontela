#include "gota.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void crearGota(TDA_Gota* gota){
	gota->x= -1;
	gota->y= -1;
	gota->enBalde= 0;
}


void cargarCamposGotas(TDA_Gota* gota, char* linea){
	char s=' ';

	gota->x= atof(strtok(linea,&s));
	gota->y= atof(strtok(NULL,&s));
}

void destruirGota(TDA_Gota* gota){
	gota->x= -1;
	gota->y= -1;
}