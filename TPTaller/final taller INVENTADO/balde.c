#include "balde.h"




void crearBalde(TDA_Balde* balde){
	balde->x= -1;
	balde->y= -1;
	balde->ancho = -1;
	balde->vol = -1;
	balde->id = (char*)malloc(sizeof(char)*20);
	balde->cantGotas = 0;

}
