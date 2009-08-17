#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gota.h"
#include "balde.h"

#define MAX_BALDES 50
#define MAX_GOTAS 50
#define TAM_LINEA 40
#define NombreArchBaldes "baldes.txt"
#define NombreArchGotas "gotas.txt"

void cargarDatosBalde(TDA_Balde* balde,char* linea){
	char s = ' ';
	 
	memcpy(balde->id,strtok(linea,&s),sizeof(char)*20);
	 

	balde->x = atof(strtok(NULL,&s));
	//printf("balde X %f\n",balde->x);
	
	balde->y= atof(strtok(NULL,&s));
	//printf("balde Y %f\n",balde->y);
	
	balde->vol = atof(strtok(NULL,&s));
	balde->ancho = atof(strtok(NULL,&s));
	

}


int cargarVecBaldes(TDA_Balde* vecBaldes[MAX_BALDES]){
	int cantBaldes = 0;
	char linea[TAM_LINEA];
	FILE* archBaldes = fopen(NombreArchBaldes,"r");
	
	if(!archBaldes){
		printf("ERROR AL ABRIR ARCHIVO BALDES \n");
		return -1;
	
	}
	else{

		while(!feof(archBaldes)){
			vecBaldes[cantBaldes] = (TDA_Balde*)malloc(sizeof(TDA_Balde));
			crearBalde(vecBaldes[cantBaldes]);
			fgets(linea,TAM_LINEA,archBaldes);
			//printf("linea %s \n",linea);
			cargarDatosBalde(vecBaldes[cantBaldes],linea);
			memset(linea,0,sizeof(char)*TAM_LINEA);			
			cantBaldes++;
		}
		fclose(archBaldes);

		
	
	
	}
	return cantBaldes;

}

void cargarDatosGota(TDA_Gota* gota, char linea[TAM_LINEA]){
	char s = ' ';
	
	gota->x = atof(strtok(linea,&s));
	gota->y = atof(strtok(NULL,&s));


}


int cargarVecGotas(TDA_Gota* vecGotas[MAX_GOTAS]){
	int cantGotas= 0;
	char linea[TAM_LINEA];

	FILE* archGotas = fopen(NombreArchGotas,"r");
	
	if(!archGotas){
		printf("error al abrir archivo gotas");
		return -1;		
	
	}
	else{
		while(!feof(archGotas)){
			vecGotas[cantGotas] = (TDA_Gota*)malloc(sizeof(TDA_Gota));
			crearGota(vecGotas[cantGotas]);
			fgets(linea,TAM_LINEA,archGotas);
			//printf("linea %s\n",linea);
			cargarDatosGota(vecGotas[cantGotas],linea);
			memset(linea,0,sizeof(char)*TAM_LINEA);
			cantGotas++;
		
		}
		fclose(archGotas);
	
	}

	return cantGotas;
}

int compare(const void* _a,const void* _b){
	TDA_Balde** a;
	TDA_Balde** b;
	a = (TDA_Balde**) _a;
	b = (TDA_Balde**) _b;

		if((*a)->y > (*b)->y){
			return -1;
		}
		else if ((*a)->y < (*b)->y){
			return 1;
		}
		else{
			return 0;
		}	




}
int main(){
	
	int cantGotas;
	int cantBaldes;
	TDA_Balde* vecBaldes[MAX_BALDES];
	TDA_Gota* vecGotas[MAX_GOTAS];
	int i = 0;
	int k=0;
	
	
	cantBaldes = cargarVecBaldes(vecBaldes);
	printf("cant baldes =  %d\n",cantBaldes);
	
	cantGotas = cargarVecGotas(vecGotas);
	printf("cant gotas =  %d\n",cantGotas);

	if((cantBaldes != -1) && (cantGotas != -1)){
		qsort(vecBaldes,cantBaldes, sizeof(vecBaldes[0]), &compare);
		
		
		for(i=0;i<cantGotas;i++){

			for(k=0;k<cantBaldes;k++){
				if(vecGotas[i]->choco == 0){
					
					 if(vecGotas[i]->y >= vecBaldes[k]->y){
										
						if(vecGotas[i]->x >= vecBaldes[k]->x && vecGotas[i]->x <= vecBaldes[k]->x + vecBaldes[k]->ancho){
							if(vecBaldes[k]->vol > vecBaldes[k]->cantGotas){
								//si en el balde entra otra gota
								vecBaldes[k]->cantGotas++;
								vecGotas[i]->choco = 1;
							}else{
								//si no entra otra gota, tiene que rebalsar el balde y seguir bajando
								vecGotas[i]->x = vecBaldes[k]->x;
								vecGotas[i]->y = vecBaldes[k]->y;							
							}
						}
					 }

				}				
			
			}
		
		}		
		
		
		for(i=0; i<cantBaldes ; i++){
			printf("id balde=  %s",(vecBaldes[i])->id);
			printf("     cant gotas= %d\n",(vecBaldes[i])->cantGotas);
		}
		for(i=0; i<cantBaldes ; i++){
			free(vecBaldes[i]);
		}
	
	
	}
	else{
		printf("ERROR");
		system("PAUSE");
		
	}
	
	return 0;
}