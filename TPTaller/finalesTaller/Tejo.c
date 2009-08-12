#include <stdio.h>
#include <stdlib.h>
#include "Tejo.h"


int tejoCrear(TDA_Tejo* tda){
    tda->x = -1;
    tda->y = -1;
    tda->radio = -1;
    tda->linea = NULL;  
    tda->distRecorrida = 0;
    tda->id = (char*)malloc(sizeof(char)*MAX_ID); 
    tda->idDispChoque = (char*)malloc(sizeof(char)*MAX_ID);
    tda->choco = 0;
}

void parsearLineaTejo(TDA_Tejo* tda){
    char s2[20] = " ";
    char *ptr;
       
    tda->id = strtok( tda->linea, s2 ); 
    //printf( "idTejo= %s\n ", tda->id);    
    
    ptr = strtok( NULL, s2 ); 
    tda->x = atof(ptr);
    //printf( "X= %f\n ", tda->x);
    
    ptr = strtok( NULL, s2 ); 
    tda->y = atof(ptr);
    //printf( "Y= %f\n ",tda->y);
    
    ptr = strtok( NULL, s2 ); 
    tda->radio = atof(ptr);
    //printf( "radio= %f\n ", tda->radio );
        
}

void cargarLineaTejo(TDA_Tejo* tda, char* linea){
     tda->linea = (char*) malloc(sizeof(char)*TAM_LINEA);
     memcpy(tda->linea,linea,sizeof(char)*TAM_LINEA);
}

void mostrarLineaTejo(TDA_Tejo* tda){
     printf("Linea cargada %s \n", tda->linea);
     
}
void setearIdDispChoque(TDA_Tejo* tda, char* idDisp){
     tda->idDispChoque = idDisp;     
}
int tejoDestruir(TDA_Tejo* tda){
    free(tda->id);
    free(tda->linea);
    free(tda->idDispChoque);
    tda->linea = NULL; 
    tda->x = -1;
    tda->y = -1;
    tda->radio = -1;
    tda->distRecorrida = -1;
     

}
