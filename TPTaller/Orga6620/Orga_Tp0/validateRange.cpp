#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>




int rango[10] = {-5,-5,-5,-5,-5,-5,-5,-5,-5,-5};
int* validateRange(char* datos);
int numDigitos( int numero );				
int main(int argc, char** argv){
     int k =0 ;
     char datos[20] = "10,15,19,165";     
  
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

int numDigitos( int numero ){
    int cuentaDigitos = 0;
    while ( numero ) {
          ++cuentaDigitos;
          numero /= 10;
    }
    return cuentaDigitos;
}


int* validateRange(char* datos){
      
      char* pDatos;
      int i = 0;
      int aux1;
      int aux2;
      int iInicial;   
      int diferencia;
      int digitos;
      
    if(strpbrk(datos,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.:;!¡¿?_+*[]{}´¨°¬#$%&^/=`~") != NULL){
		 printf("tiene caracteres incorrectos \n"); 
        return NULL;	
	}
	else{
         pDatos = datos;
         
         while(*pDatos != '\0'){
               
               if(i==0){
               //si es el primer caracter leido
                     if(*pDatos == '-'){
                                
                                //si es un guion, ej -5 pongo en el vector 5,-2
                                rango[i+1]= -2; 
                                pDatos++;
                                rango[i]= atoi(pDatos);  
                                digitos = numDigitos(rango[i]);
                                while(digitos){
                                  pDatos++;
                                 digitos--;
                                }
                                i++;
                     }
                     else if(*pDatos == ','){
                          
                          //no puede empezar con una "," ERROR
                          return NULL;     
                     }                     
                     else{
                          //si es un numero                          
                          rango[i] = atoi(pDatos);
                          digitos = numDigitos(rango[i]);
                          while(digitos){
                              pDatos++;
                              digitos--;
                          } 
                          i++;          
                                                 
                     }
               }
               else{
                    //si no es el primer caracter
                    if(*pDatos == '-'){
                               pDatos++;
                                
                                if(*pDatos == '\0'){
                                   //si es un guion y le sigue un \0, ej 5- pongo 5,-1 
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
                                        digitos = numDigitos(aux1);
                                        while(digitos){
                                              pDatos++;
                                              digitos--;                                                                                                                 
                                        }
                                     }        
                                     
                                }
                     }
                     else if(*pDatos == ','){                          
                           pDatos++;
                           if( (*pDatos == ',') || (*pDatos == ' ') || (*pDatos == '-') )
                               return NULL; 
                           else{
                                //si es un numero
                                rango[i] = atoi(pDatos);
                                digitos = numDigitos(rango[i]);
                                while(digitos){
                                     pDatos++;
                                     digitos--;
                                } 
                                i++;  
                           }
                             
                     }                     
                     else{
                          //si es un numero
                          rango[i] = atoi(pDatos);
                          digitos = numDigitos(rango[i]);
                          while(digitos){
                               pDatos++;
                               digitos--;
                          } 
                          i++; 
                                                   
                     }
                    
                    
                    }               
                     
                      
          }
		
		 return rango;
		}
      
}	
