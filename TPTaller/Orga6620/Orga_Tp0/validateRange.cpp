#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>




int rango[10] = {-5,-5,-5,-5,-5,-5,-5,-5,-5,-5};
int* validateRange(char* datos);
				
int main(int argc, char** argv){
     int k =0 ;
     char datos[15] = "2-5";        
     if(validateRange(datos) == NULL){
                   printf("ERROR EN LOS DATOS \n");          
                   system("PAUSE");
     }
     else{
          for(k; k<10; k++){
             printf("rango en i= %d   valor=%d\n",k,rango[k]);     
          
          
          }
            system("PAUSE");        
          }
 
	return EXIT_SUCCESS;
}


int* validateRange(char* datos){
      
      char* pDatos;
      int i = 0;
      int aux1;
      int aux2;
      int iInicial;   
      int diferencia;
      
    if(strpbrk(datos,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.:;!¡¿?_+*[]{}´¨°¬#$%&^/=`~") != NULL){
		 printf("tiene caracteres incorrectos \n"); 
        return NULL;	
	}
	else{
         pDatos = datos;
         //********ESTA COMENTADO EL pDatos != NULL porque no corta el while con esa condicion ANDA PERFECTO si cortas con el i, probe todos los casos del tp
         //buscar cual es el caracter de corte del char* para que salga correctamente del while, otra cosa, cuando pongas 2- no va a andar porque el caracter de fin no lo conozco
         //si le pones 2-? y comparas contra ? anda perfecto ENCARGATE DE VER CUAL ES EL FIN DE UN char* y esta parte ya esta joya CUALQUIER COSA LLAMAME AL CEL
         while(/*pDatos != NULL*/i<3 ){
               //printf("pDatos %c\n",*pDatos);
               if(i==0){
               //si es el primer caracter leido
                     if(*pDatos == '-'){
                                printf("entro a - con i=0 \n"); 
                                //si es un guion, ej -5 pongo en el vector 5,-2
                                rango[i+1]= -2; 
                                pDatos++;
                                rango[i]= atoi(pDatos);  
                                i++;
                     }
                     else if(*pDatos == ','){
                          printf("entro a , con i=0 \n");
                          //no puede empezar con una "," ERROR
                          return NULL;     
                     }                     
                     else{
                          //si es un numero
                          printf("entro numero , con i=0 \n");
                          rango[i] = atoi(pDatos);
                          i++;                         
                     }
               }
               else{
                    //si no es el primer caracter
                    if(*pDatos == '-'){
                               pDatos++;
                                printf("entro - con i>0 \n");
                                if(*pDatos == '?'){
                                   //si es un guion y le sigue un espacio, ej 5- pongo 5,-1 
                                   rango[i]= -1;    
                                   i++;
                                }
                                else if(*pDatos == ','){
                                     //no puede empezar con una "," ERROR
                                     return NULL;     
                                }
                                else{
                                   //si es un guion y le sigue un numero, ej 2-5 pongo 2,3,4,5 pero si el primero es mayor al segundo es un ERROR  (ej 5-2) 
                                     aux1 = rango[i-1];// ultimo numero guardado
                                     aux2 = atoi(pDatos);//obtengo el siguiente despues del "-"
                                     
                                     if(aux2<=aux1)//es un error(ej 5-2)
                                           return NULL;  
                                     else{
                                        iInicial = i;
                                        diferencia = aux2-aux1;
                                        for(i;i<iInicial+diferencia;i++){
                                            aux1++; 
                                            rango[i]= aux1;//guardo el siguiente en el ejemplo de 2-5 seria el 3
                                                              
                                                                         
                                        }
                                     }        
                                     
                                }
                     }
                     else if(*pDatos == ','){
                          printf("entro , con i>0 \n");
                           pDatos++;
                           if( (*pDatos == ',') || (*pDatos == ' ') || (*pDatos == '-') )
                               return NULL; 
                           else{
                                //si es un numero
                                rango[i] = atoi(pDatos);
                                i++;   
                           }
                             
                     }                     
                     else{
                          //si es un numero
                          printf("entro numero con i>0 \n");
                          rango[i] = atoi(pDatos);
                          i++;                         
                     }
                    
                    
                    }          
            
               pDatos++;       
                      
          }
		
		 return rango;
		}
      
}	
