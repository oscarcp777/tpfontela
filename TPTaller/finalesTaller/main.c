#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dispersor.h"
#include "tejo.h"



#define CANT_TEJOS 50
#define CANT_DISP 50
#define AVANCE_MAXIMO 1000

void analizarColision(TDA_Tejo* tejo,TDA_Dispersor* vecDisp[CANT_DISP], int cantidadDisp){
       
		//si hay colision seteo choco = 1 en tejo y le asigno el idDispersor con el que choco con la 
       //funcion setearIdDispChoque(TDA_Tejo* tda, char* idDisp)
       int i = 0;
       int estaAbajo = 0;
       int estaArriba = 0;
       
       
       while(i<cantidadDisp && tejo->choco == 0 ){
           estaAbajo = 0;
           estaArriba = 0;
           if ((tejo->x + tejo->radio)>= (vecDisp[i])->x){
                        
                        if (tejo->y <= ((vecDisp[i])->y + (vecDisp[i])->alto) && 
                            tejo->y >= (vecDisp[i])->y ){
                                     tejo->choco = 1;
                                     tejo->idDispChoque = (vecDisp[i])->id;
                        }
                        else if (tejo->y - tejo->radio <= ((vecDisp[i])->y + (vecDisp[i])->alto) && 
                             tejo->y - tejo->radio >= (vecDisp[i])->y ){
                                     estaAbajo = 1;
                                     if (sqrt(pow(tejo->x - (vecDisp[i])->x, 2)+ 
                                        pow(tejo->y - ((vecDisp[i])->y + (vecDisp[i])->alto),2))<=tejo->radio){
                                              tejo->choco = 1;
                                              tejo->idDispChoque = (vecDisp[i])->id;      
                                        }
                                                         
                        }
                        else if (tejo->y + tejo->radio <= ((vecDisp[i])->y + (vecDisp[i])->alto) && 
                            tejo->y + tejo->radio >= (vecDisp[i])->y ){
                                    estaArriba = 1;
                                    if (sqrt(pow(tejo->x - (vecDisp[i])->x, 2)+ 
                                        pow(tejo->y - (vecDisp[i])->y ,2))<=tejo->radio){
                                              tejo->choco = 1;
                                              tejo->idDispChoque = (vecDisp[i])->id;      
                                        }
                        }
                            
           }
                              
                            
           i++;                     
       }
       
                                                                                   
}


int cargarDispersores(TDA_Dispersor* vecDisp[CANT_DISP],char *archDisp){
       
      int cantDisp = 0;
      int i = 0;
      FILE *aDisp;
      char linea[TAM_LINEA];
      char *pLinea = linea;
      aDisp = fopen(archDisp,"r");  

      if(!aDisp){
                 printf("ERROR AL ABRIR ARCHIVO\n");
                 system("PAUSE");                 
      } 
      else{      
      while (!feof(aDisp)){

                vecDisp[i]=(TDA_Dispersor*)malloc(sizeof(TDA_Dispersor));                
                fgets(linea,TAM_LINEA,aDisp);
                dispersorCrear(vecDisp[i]);
                cargarLineaDispersor(vecDisp[i],linea);
                //mostrarLineaDisp(vecDisp[i]);
                parsearLineaDispersor(vecDisp[i]);
                pLinea = NULL;  
                i++;
               
            
      }   
      fclose(aDisp);
      }
     cantDisp = i;
     return cantDisp;
}

int cargarTejos(TDA_Tejo* vecTejo[CANT_TEJOS],char *archTejos){
     int cantTejos = 0;
      int i = 0;
      FILE *aTejo;
      char linea[TAM_LINEA];
      char *pLinea = linea;
      aTejo = fopen(archTejos,"r");  

      if(!aTejo){
                 printf("ERROR AL ABRIR ARCHIVO\n");
                 system("PAUSE");                 
      } 
      else{      
      while (!feof(aTejo)){

                vecTejo[i]=(TDA_Tejo*)malloc(sizeof(TDA_Tejo));  
                
                fgets(linea,TAM_LINEA,aTejo);
                tejoCrear(vecTejo[i]);
                cargarLineaTejo(vecTejo[i],linea);
                //mostrarLineaTejo(vecTejo[i]);
                parsearLineaTejo(vecTejo[i]);
                pLinea = NULL;  
                i++;
               
            
      }   
      fclose(aTejo);
      }
      cantTejos = i;
      return cantTejos;
}

int compare(const void* _a, const void* _b) {         
    TDA_Tejo** a;
    TDA_Tejo** b;
    a = (TDA_Tejo**) _a;
    b = (TDA_Tejo**) _b;
    
        
    if((*a)->distRecorrida > (*b)->distRecorrida)
     return 1;
     
     else if ((*a)->distRecorrida < (*b)->distRecorrida)
        return -1;
        
        else 
             return 0;         
}

int main(){
    
    TDA_Dispersor* vecDisp[CANT_DISP];
    
    TDA_Tejo* vecTejo[CANT_TEJOS];
   
    char archDisp[50]= "dispersores2.txt";
    char archTejos[50]= "tejos2.txt";
    int cantidadTejos = 0;
    int cantidadDisp = 0;
    
    int i = 0;
    int k = 0;
   
    cantidadDisp = cargarDispersores(vecDisp,archDisp);
    cantidadTejos = cargarTejos(vecTejo,archTejos);
    
    printf("CANT TEJOS %d\n", cantidadTejos);
    printf("CANT DISPERSORES %d\n", cantidadDisp);
    
    
    while(k<AVANCE_MAXIMO){
        for(i=0; i< cantidadTejos; i++){
                             
                //si el tejo tiene choco = 0, analizo sino NO
                if((vecTejo[i])->choco == 0){ 
                //ANALIZO LA POSIBLE COLISION CON TODOS LOS DISPERSORES DEL VECTOR
                    (vecTejo[i])->distRecorrida++;
                    (vecTejo[i])->x++;
                    analizarColision(vecTejo[i],vecDisp,cantidadDisp);
                                                                   
                }
                
        }         
        k++;            
                           
   }
   
  
  // el vector de tejos lo tengo que ordenar por distancia recorrida
  //y despues imprimir 
    
    qsort(vecTejo, cantidadTejos, sizeof(vecTejo[0]), &compare);
    for(i=0; i< cantidadTejos; i++){
                //si el tejo tiene choco = 1, imprimo sino NO
                if((vecTejo[i])->choco == 1){ 
                    printf("Tejo= %s", (vecTejo[i])->id);
                    printf(" choco con Dispersor= %s", (vecTejo[i])->idDispChoque);
                    printf(" y recorrio una distancia de= %.2f \n", (vecTejo[i])->distRecorrida);                                                                                       
                } 
              
        }  
        
    for(i=0; i< cantidadTejos; i++){    
              tejoDestruir(vecTejo[i]);
		      free (vecTejo[i]);
    }    
            
	for(i=0; i< cantidadDisp; i++){    
              dispersorDestruir(vecDisp[i]);
              free(vecDisp[i]);
    }
    
     system("PAUSE"); 
    
}
