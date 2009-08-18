#include "balde.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void crearBalde(TDA_Balde* balde){
	balde->x=-1;
	balde->y=-1;
	balde->vol=-1;
	balde->ancho=-1;
	balde->cantidadGotas= 0;
	balde->id = (char*)malloc(sizeof(char)*50);
	
}


void cargarCamposBaldes(TDA_Balde* balde, char* linea){
	
	char s=' ';
	
	memcpy(balde->id, strtok(linea,&s),sizeof(char)*50);
	balde->x= atof(strtok(NULL,&s));
	balde->y= atof(strtok(NULL,&s));
	balde->vol= atoi(strtok(NULL,&s));
	balde->ancho= atof(strtok(NULL,&s));

}

void destruirBalde(TDA_Balde* balde){
	balde->x=-1;
	balde->y=-1;
	balde->vol=-1;
	balde->ancho=-1;
	free(balde->id);

}