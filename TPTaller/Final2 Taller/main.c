#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "equipo.h"
#include "disparo.h"

#define CANT_EQUIPOS 4
#define CANT_DISPAROS 50
#define TAM_LINEA 50
#define POS_ARCO 75
#define PALO_INF 15
#define PALO_SUP 35
#define ZONA1 25
#define ZONA2 50
#define ZONA3 75
#define PUNTOS_ZONA1 30 
#define PUNTOS_ZONA2 20
#define PUNTOS_ZONA3 10




void parsearLineaArchivo(TDA_Disparo * disparo,char *linea){


	char s = ' ';
	char lineaAux[TAM_LINEA];
	

	disparo->idPatea = atoi(strtok(linea,&s));

	disparo->idAtaja = atoi(strtok(NULL,&s));

	disparo->xI = atoi(strtok(NULL,&s));

	disparo->yI = atoi(strtok(NULL,&s));

	disparo->xF = atoi(strtok(NULL,&s));

	disparo->yF = atoi(strtok(NULL,&s));

	disparo->yArquero = atoi(strtok(NULL,&s));

	disparo->alturaArquero = atoi(strtok(NULL,&s));
	
	

}


int cargarArchivoDisparos(TDA_Disparo *vecDisparos[CANT_DISPAROS], char *nomArch){



	char linea[TAM_LINEA];
	FILE *arch = fopen(nomArch,"r");
	int cantDisparos = 0;



	if (!arch){
		printf("Error al cargar archivo \n");
		return -1;
	}
	else{
		while (!feof(arch)){
			vecDisparos[cantDisparos] = (TDA_Disparo*)malloc(sizeof(TDA_Disparo));
			crearDisparo(vecDisparos[cantDisparos]);
			fgets(linea,TAM_LINEA,arch);
			printf("Linea= %s \n", linea);
			parsearLineaArchivo(vecDisparos[cantDisparos],linea);
			cantDisparos++;
			memset(linea,0,sizeof(char)*TAM_LINEA);
			
		}
		fclose(arch);
		return cantDisparos;
	}

}



void analizarDisparo(TDA_Equipo *vecEquipos[CANT_EQUIPOS], TDA_Disparo * disparo){

	int xDir, yDir;
	float m; //pendiente
	float b; //ordenada
	float yDestino;

	xDir = disparo->xF - disparo->xI;
	yDir = disparo->yF - disparo->yI;
	m = yDir/xDir; //OJOOOOOOOOOOOOOOOOOOO
	b = disparo->yF - disparo->xF*m;

	yDestino = POS_ARCO*m + b;
	
	

	if( yDestino<= disparo->yArquero + disparo->alturaArquero &&  disparo->yArquero <= yDestino ){ 
		vecEquipos[disparo->idAtaja-1]->atajadas++;
		
	}
	else if( yDestino > PALO_INF && yDestino < PALO_SUP){
		vecEquipos[disparo->idPatea-1]->goles++;
		 
		if(disparo->xI >= 0 && disparo->xI<= ZONA1){
			vecEquipos[disparo->idPatea-1]->puntos+= PUNTOS_ZONA1;
		
		} 
		
		else if(disparo->xI >ZONA1 && disparo->xI<= ZONA2){
			vecEquipos[disparo->idPatea-1]->puntos+= PUNTOS_ZONA2;
		
		}
		else if(disparo->xI >ZONA2 && disparo->xI<= ZONA3){
			vecEquipos[disparo->idPatea-1]->puntos+= PUNTOS_ZONA3;
		
		} 
			
	
	}

	


}

void imprimirResultado(TDA_Equipo *vecEquipos[CANT_EQUIPOS]){
	int equipoMaxGoles = 1;
	int equipoMaxPuntaje = 1;
	int equipoMaxAtajadas = 1;
	
	int maxGoles = vecEquipos[0]->goles;
	int maxPuntaje = vecEquipos[0]->puntos;
	int maxAtajadas = vecEquipos[0]->atajadas;
	

	int i =1;
	for( i ; i<CANT_EQUIPOS; i++){
			
		if(maxGoles < vecEquipos[i]->goles){
			maxGoles = vecEquipos[i]->goles;
			equipoMaxGoles = i+1;
		}
		if(maxPuntaje < vecEquipos[i]->puntos){
			maxPuntaje = vecEquipos[i]->puntos;
			equipoMaxPuntaje = i+1;
		}
		if(maxAtajadas < vecEquipos[i]->atajadas){
			maxAtajadas = vecEquipos[i]->atajadas;
			equipoMaxAtajadas = i+1;
		}
			
	
	}

	printf("Equipo con mas goles, equipo %d\n", equipoMaxGoles);
	printf("Equipo con mas atajadas, equipo %d\n", equipoMaxAtajadas);
	printf("Equipo con mas puntos, equipo %d\n", equipoMaxPuntaje);
	
	
}

int main(){

	TDA_Equipo *vecEquipos[CANT_EQUIPOS];
	TDA_Disparo *vecDisparos[CANT_DISPAROS];
	char nomArch[50]="abc.txt";
	int cantDisparos = 0;
	int i,k;
	
	for(k=0 ; k<CANT_EQUIPOS;k++){
		vecEquipos[k] = (TDA_Equipo *)malloc(sizeof(TDA_Equipo));
		crearEquipo(vecEquipos[k]);
	
	}

	cantDisparos = cargarArchivoDisparos(vecDisparos,nomArch);
	
	for (i=0; i<cantDisparos;i++){

		analizarDisparo(vecEquipos,vecDisparos[i]);
	}
	
	imprimirResultado(vecEquipos);

	for (i=0; i<cantDisparos;i++){

		free(vecDisparos[i]);
	}

	return 0;


}
