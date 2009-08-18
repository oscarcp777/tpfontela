#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gota.h"
#include "balde.h"


#define NOMBRE_ARCHIVO 50
#define MAX_LINEA 50
#define MAX_GOTAS 50
#define MAX_BALDES 50
#define MAX_CAIDA 100


int obtenerGotas(TDA_Gota* gotas[MAX_GOTAS], char* nomArch){

	FILE* aGotas = fopen(nomArch,"r");
	char linea[MAX_LINEA];
	int cantidadGotas=0;
	
	if (!aGotas){
		printf("Error al abrir el archivo de Gotas\n");
		return -1;
	}


	while (!feof(aGotas)){
		
		fgets(linea,MAX_LINEA,aGotas);
		gotas[cantidadGotas]= (TDA_Gota*)malloc(sizeof(TDA_Gota));
		crearGota(gotas[cantidadGotas]);
		cargarCamposGotas(gotas[cantidadGotas],linea);
		cantidadGotas++;
	}

	fclose(aGotas);
	return cantidadGotas;
}


int obtenerBaldes(TDA_Balde* baldes[MAX_BALDES], char* nomArch){
	
	FILE* aBaldes = fopen(nomArch,"r");
	char linea[MAX_LINEA];
	int cantidadBaldes=0;
	
	if (!aBaldes){
		printf("Error al abrir el archivo de Baldes\n");
		return -1;
	}


	while (!feof(aBaldes)){
		
		fgets(linea,MAX_LINEA,aBaldes);
		baldes[cantidadBaldes]= (TDA_Balde*)malloc(sizeof(TDA_Balde));
		crearBalde(baldes[cantidadBaldes]);
		cargarCamposBaldes(baldes[cantidadBaldes],linea);
		cantidadBaldes++;
	}

	fclose(aBaldes);
	return cantidadBaldes;


}

void analizarCaida(TDA_Gota* gota, TDA_Balde* baldes[MAX_BALDES], int nBaldes){

	int i;
	for (i=0; i<nBaldes; i++){
		if (gota->y == (baldes[i])->y){
			if (gota->x >= (baldes[i])->x && gota->x <= ((baldes[i])->x +(baldes[i])->ancho)){
				if ((baldes[i])->cantidadGotas < (baldes[i])->vol ){
					gota->enBalde = 1;
					(baldes[i])->cantidadGotas+=1;
				}else
					gota->x = (baldes[i])->x;
			}
		}
	}
}

int compare(const void* a, const void* b){
	
	TDA_Balde* b1;
	TDA_Balde* b2;

	b1 = *(TDA_Balde**)a;
	b2 = *(TDA_Balde**)b;

	if (b1->cantidadGotas>b2->cantidadGotas)
		return 1;
	else if (b1->cantidadGotas<b2->cantidadGotas)
			return -1;
		 else
			 return 0;

}

int main(){

	TDA_Gota* gotas[MAX_GOTAS];
	TDA_Balde* baldes[MAX_BALDES];
	char nomArchGotas[NOMBRE_ARCHIVO]="gotas.txt";
	char nomArchBaldes[NOMBRE_ARCHIVO]="baldes.txt";
	int cantidadGotas;
	int cantidadBaldes;
	int i;
	int k=0;
	int cayendo=1;

	cantidadGotas = obtenerGotas(gotas, nomArchGotas);
	cantidadBaldes = obtenerBaldes(baldes, nomArchBaldes);

	printf("Numero de gotas: %d\n", cantidadGotas);
	printf("Numero de baldes: %d\n\n", cantidadBaldes);
	

	

	
	while (k<MAX_CAIDA && cayendo==1){
			cayendo=0;
			for (i=0; i<cantidadGotas; i++){
				if (gotas[i]->enBalde == 0){
					analizarCaida(gotas[i],baldes, cantidadBaldes);
					gotas[i]->y--;
					cayendo=1;
				}
			}
			k++;

	}
	
	qsort(baldes,cantidadBaldes, sizeof(baldes[0]), &compare);
	
	for (i=0; i<cantidadGotas; i++){
		destruirGota(gotas[i]);
		free(gotas[i]);
	
	}
	for (i=0; i<cantidadBaldes; i++){
		printf("IDbalde: %s  Cantidad Gotas: %d\n", baldes[i]->id, baldes[i]->cantidadGotas);
		destruirBalde(baldes[i]);
		free(baldes[i]);
	
	}

}