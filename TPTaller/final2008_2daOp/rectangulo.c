#include "rectangulo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void crearRBase(TDA_RBase* rect){

	rect->x= -1;
	rect->y= -1;
	rect->alto= -1;
	rect->ancho= -1;
	rect->id= (char*)malloc(sizeof(char)*50);

}

void cargarRBase(TDA_RBase* rect, char* linea){

	char s=' ';
	float xInfI,yInfI,xSupD,ySupD;
	
	memcpy(rect->id, strtok(linea,&s),sizeof(char)*50);
	xInfI = atof( strtok(NULL,&s));
	yInfI = atof( strtok(NULL,&s));
	xSupD = atof( strtok(NULL,&s));
	ySupD = atof( strtok(NULL,&s));

	rect->x= xInfI;
	rect->y= ySupD;
	rect->alto= ySupD - yInfI;
	rect->ancho= xSupD - xInfI;

}


void destruirRBase(TDA_RBase* rect){

	rect->x= -1;
	rect->y= -1;
	rect->alto= -1;
	rect->ancho= -1;
	free(rect->id);
}