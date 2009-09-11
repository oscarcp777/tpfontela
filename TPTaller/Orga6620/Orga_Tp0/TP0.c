#include "TP0.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINEA 255



//devuelve la letra del comando a ejecutar
//si el comando es incorrecto devuelve h
char validarComando(char* comando){

  char* punt = comando; 
  char c ='-';
  char palabra[MAX_LINEA]=""; //comando despues del 1er guion
  char *pPalabra = palabra; 
  int i,j;

  
  if (*punt != c){
	  printf("Error en el comando\n");
	  return 'h';
  }else{
	  strcpy(pPalabra,++punt);
	  printf ("El comando es: %s\n",pPalabra);
	  
	  //begin codigo feo
			i = strcmp(pPalabra, "V");
			j = strcmp(pPalabra, "-version");
			if ( j == 0 || i == 0)
				return 'V';
			i = strcmp(pPalabra, "h");
			j = strcmp(pPalabra, "-help");
			if ( j == 0 || i == 0)
				return 'h';
			i = strcmp(pPalabra, "d");
			j = strcmp(pPalabra, "-delimiter");
			if ( j == 0 || i == 0)
				return 'd';
			i = strcmp(pPalabra, "b");
			j = strcmp(pPalabra, "-bytes");
			if ( j == 0 || i == 0)
				return 'b';
			i = strcmp(pPalabra, "f");
			j = strcmp(pPalabra, "-field");
			if ( j == 0 || i == 0)
				return 'f';
			i = strcmp(pPalabra, "s");
			j = strcmp(pPalabra, "-ignore");
			if ( j == 0 || i == 0)
				return 's';
			else{
				printf("Error en el comando\n");
				return 'h';
			}
	  //end codigo feo
	  
  }
}


//PARA PROBARLO EJECUTALO POR CONSOLA, EL EXE EN VISUAL ESTA EN LA CARPETA
//DEBUG, YO YA LO PROBE Y HASTA ACA ANDA BIEN
int main(int argc, char* argv[]) {
  //int i;
  //printf("Se han pasado %3d argumentos:\n", argc);
  //for(i=0; i<argc; i++) printf("%5d- %s\n", i, argv[i]);
  char c;
  c = validarComando(argv[1]);
  printf("Comando devuelto: %c\n",c);

  return 0;
}
