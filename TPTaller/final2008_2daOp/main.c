#include "rectangulo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECTS 30
#define MAX_LINEA 100



int cargarRBases (TDA_RBase* rBase[MAX_RECTS], char* nomArch){

	char linea[MAX_LINEA];
	FILE* arch = fopen(nomArch, "r");
	int cantidadR = 0;

	if (!arch){
		printf("Error al abrir archivo\n");
		return -1;
	}
	while (!feof(arch)){
		
		fgets(linea,MAX_LINEA,arch);
		rBase[cantidadR] = (TDA_RBase*)malloc(sizeof(TDA_RBase));
		crearRBase(rBase[cantidadR]);
		cargarRBase(rBase[cantidadR], linea);
		cantidadR++;
	}

	fclose(arch);
	return cantidadR;
}


void buscarRRes(TDA_RBase* rBase[MAX_RECTS],TDA_RBase* rActual , int numRect,
				int nInterseccion,int nTotalRect, int nTotalRes,TDA_RRes*  rRes[MAX_RECTS]){
	int i;
	TDA_RBase aux; //guarda el rectangulo q se genera en la interseccion
	if (numRect + 2 <= nTotalRect){
		for(i=numRect+1;i<nTotalRect; i++){
			if (rBase[i]->x <= (rActual->x + rActual->ancho) &&
				rBase[i]->y >= 	(rActual->y - rActual->alto) &&
				(rBase[i]->x + rBase[i]->ancho) >= rActual->x  &&
				(rBase[i]->y - rBase[i]->alto) <= 	rActual->y){
					printf("entro\n");
					nInterseccion++;
					if (rBase[i]->x >= rActual->x)
						aux.x = rBase[i]->x;
					else
						aux.x = rActual->x;
					if (rBase[i]->y <= 	rActual->y)
						aux.y = rBase[i]->y;
					else
						aux.y = rActual->y;
					if ((rBase[i]->x + rBase[i]->ancho)<=(rActual->x + rActual->ancho))
						aux.ancho = (rBase[i]->x + rBase[i]->ancho) - aux.x;
					else
						aux.ancho = (rActual->x + rActual->ancho) - aux.x;
					if ((rBase[i]->y - rBase[i]->alto)>=(rActual->y - rActual->alto))
						aux.alto = aux.y - (rBase[i]->y - rBase[i]->alto);
					else
						aux.alto = aux.y - (rActual->y - rActual->alto);

					if (nInterseccion == 2){
						printf("El rectangulo hallado es: \nX:%f\nY:%f\nAncho:%f\nAlto:%f\n",
							aux.x,aux.y,aux.ancho,aux.alto);

						rRes[nTotalRes]= (TDA_RRes*)malloc(sizeof(TDA_RRes));
						memcpy(rRes[nTotalRes], &aux,sizeof(TDA_RRes));
						nTotalRes++;
						nInterseccion = 0;
						//buscarRRes(rBase,rBase[numRect+1],numRect+1,nInterseccion,nTotalRect,
						//	nTotalRes,rRes);
					}
					else
						buscarRRes(rBase,&aux,numRect+1,nInterseccion,nTotalRect,
							nTotalRes,rRes);




			}
			numRect++;
			nInterseccion = 0;
		}
	}


}


int main(){

	TDA_RBase* rBase[MAX_RECTS];
	TDA_RRes*  rRes[MAX_RECTS];
	char nomArch[20]="rectangulos.txt";
	int cantidadRBases = 0;
	int i;

	cantidadRBases = cargarRBases(rBase, nomArch);
	
	printf("Numero rectangulos cargados: %d\n", cantidadRBases);

	if (cantidadRBases > 2){
		buscarRRes(rBase, rBase[0], 0, 0, cantidadRBases, 0, rRes);
	}

	for (i=0; i<cantidadRBases; i++){
		printf("ID: %s\n", rBase[i]->id);
		free (rBase[i]);
	}

}





