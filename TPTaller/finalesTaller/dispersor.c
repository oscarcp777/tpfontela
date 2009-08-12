#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dispersor.h"



int dispersorCrear(TDA_Dispersor* tda){
    
    tda->linea = NULL;
    tda->x = -1;
    tda->y = -1;
    tda->ancho = -1;
    tda->alto = -1;
    tda->id = (char*)malloc(sizeof(char)*MAX_ID);
    
}
void parsearLineaDispersor(TDA_Dispersor* tda){
    char s2[20] = " ";
    char *ptr;
       
    tda->id = strtok( tda->linea, s2 ); 
    //printf( "idDisperor= %s\n ", tda->id);    
    
    ptr = strtok( NULL, s2 ); 
    tda->x = atof(ptr);
    //printf( "X= %f\n ", tda->x);
    
    ptr = strtok( NULL, s2 ); 
    tda->y = atof(ptr);
    //printf( "Y= %f\n ",tda->y);
    
    ptr = strtok( NULL, s2 ); 
    tda->alto = atof(ptr);
    //printf( "alto= %f\n ", tda->alto );
    
    ptr = strtok( NULL, s2 ); 
    tda->ancho = atof(ptr);
    //printf( "ancho= %f\n ", tda->ancho );
    
}

void cargarLineaDispersor(TDA_Dispersor* tda, char* linea){
     
     tda->linea = (char*)malloc(sizeof(char)*TAM_LINEA);
     memcpy(tda->linea, linea, sizeof(char)*TAM_LINEA);     
}


void mostrarLineaDisp(TDA_Dispersor* tda){
                   
     printf("Linea Cargada: %s \n", tda->linea);              
                   
}

int dispersorDestruir(TDA_Dispersor* tda){
    free(tda->id);
    free(tda->linea);
    tda->linea = NULL;
    tda->x = -1;
    tda->y = -1;
    tda->ancho = -1;
    tda->alto = -1;
    
    
}
