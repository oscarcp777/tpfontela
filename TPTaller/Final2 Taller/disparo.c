#include "disparo.h"



void crearDisparo(TDA_Disparo* tda){
	
	tda->idAtaja=0;
	tda->idPatea=0;
	tda->xF=tda->xI=tda->yF=tda->yI=0;
	tda->yArquero=0;
	tda->alturaArquero=0;
	
}

void destruirDisparo(TDA_Disparo* tda){

	tda->idAtaja=-1;
	tda->idPatea=-1;
	tda->xF=tda->xI=tda->yF=tda->yI=-1;
	tda->yArquero=-1;
	tda->alturaArquero=-1;

}