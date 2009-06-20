#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#define maxlinea 10000

             
int limpiaescape (char* a)

{
    
  char* punt;
  char c ='/';
  punt=NULL;
  
  while ((punt=strchr(a,c))!=NULL)
  {
   *punt=' ';
   *(++punt)=' '; 
  }
}

int limpiacoment (char* s)
{
   char aux[maxlinea]="";
   char aux2[maxlinea]="";
   char* p;
   char* punt;
   char* punt2;
   char c = '*';
   int encontro=0;
   
   p=aux;
   memcpy(aux,s,maxlinea);
      
   punt=aux;
   punt2=aux;
   punt2=strchr(punt2,c);
   if (punt2!=NULL)
   strcpy(s,strncpy(aux2, aux,(punt2-punt)));
   
   
}




int parserCrear(TDA_Parser* tda,char* arch_conf,char* arch_log)
{
    char linea[50];    //para guardar la linea tomada de archivo
    char* punt;  // para moverse dentro de la linea
    char* encontro;   //para definir escape, coment y sep
    
     
	  tda->config[0]=' ';
      tda->config[1]='@';
      tda->config[2]='*';
	  tda->linea=NULL;
       
      return 1;
      
       
} 
       
      
int parserDestruir(TDA_Parser* tda)
{
          int i;
           for(i=0;i<3;++i) 
             tda->config[i]=0;
           if (tda->linea!=NULL)
           free(tda->linea);
           tda->linea=NULL;
          
           
           tda->log=NULL;
           return 1;
}

int parserCargarLinea(TDA_Parser* tda,char* linea)
{
      if (tda->linea!=NULL)
      free(tda->linea);
      
      tda->linea=(char*)malloc(sizeof(char)*maxlinea);
      
      memcpy(tda->linea,linea,sizeof(char)*maxlinea);
      
}         
         
int parserCantCampos(TDA_Parser*tda)
{
      char lineaaux[maxlinea];
      char* llimpia;
      //char c=' ';
      char cant=0;
      
      
      llimpia=lineaaux;
      memcpy(lineaaux,tda->linea,sizeof(char)*maxlinea);
      limpiaescape(llimpia);
      limpiacoment(llimpia);
      llimpia=lineaaux;
  if ((llimpia++) == "" )
  return 0;
  else
  {     
     while (llimpia!=NULL) 
      {
       
       if ((llimpia=strchr(++llimpia,tda->config[0]))!= NULL) 
       cant++; 
       
      }
     cant ++;
     tda->ncampos=cant;
    
   
   return(cant);  
 }      
}


int parserCampo(TDA_Parser* tda, int n, char* valor)
{
    char c ='/';  
//variables para extraer campo de cadena limpia
    char cadenaaux[maxlinea]="";
    char *pcinicio , *pcfinal;   //marcan las posisiones de inicio y fin del campo
    char* p;  //situado siempre en la 1er posicion
    int i,cant,pos1,pos2,largo;

//variables para limpiar campo de cadena original    
    char *pcin , *pcfin;   //marcan las posisiones de inicio y fin del campo
    char *valor2;
    
//inicio funcion    
    
    valor2=valor;
       
   
    memcpy(cadenaaux,tda->linea,sizeof(char)*maxlinea);
    p=cadenaaux;
    cant=0;
    limpiaescape(p);
    limpiacoment(p);
    strcpy((tda->linea+strlen(p))," "); //saca el comentario de la linea original
    
        
    pcinicio=p;
    pcfinal=p;
    pcin=tda->linea;
    pcfin=tda->linea;
    
    for(i=0;i<n;++i)
    {
      pcinicio=pcfinal;
      pcfinal=strchr(pcfinal,tda->config[0]); 
      if (pcfinal!=NULL) ++pcfinal;
    }
    if (n==tda->ncampos)
   {
    pos1=(pcinicio-p);
    pcin=(pcin+pos1);
    strcpy(valor,pcin);
   }
   else
   {
    pos1=(pcinicio-p);
    pos2=(pcfinal-p);
    pcin=(pcin+pos1);
    pcfin=(pcfin+pos2);
    cant= ((--pcfin)-pcin);
    strncpy(valor,pcin,cant);
    
    
   }
  
  valor=valor2;  
   
  
  
  while ((valor=strchr(valor,c))!=NULL)
     {
     *valor=' ';
     valor=valor+2;
     }
     
     
    
   
}   
 
