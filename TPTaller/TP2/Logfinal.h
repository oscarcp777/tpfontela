#ifndef __logfinal_h__
#define __logfinal_h__

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

/* Definiciones de Tipos de Datos */
/*----------------------------------------------------------------------------*/


using namespace std;

typedef struct Log {
    ofstream arch;
    int contador;
};

    
/* Definiciones de constantes */
/*----------------------------------------------------------------------------*/

const string ASTERISCOS="****************************************";
const string LINEA="----------------------------------------";
const string TOTMENSAJES=" Total de mensajes : ";

/* Definición de Primitivas */
/*----------------------------------------------------------------------------*/
/*
pre : ninguna.
post: el log queda listo para ser usado.
log : estructura a ser inicializada.
nombreArchivo : nombre del archivo donde se escribirán los mensajes.
*/

void inicializar (Log& log, string nombreArchivo);

/*----------------------------------------------------------------------------*/

/*
pre : log ha sido inicializado con la primitiva inicializar().
post: el log queda eliminado.
log : instancia sobre la cual se aplica la primitiva.
*/
void destruir (Log& log);

/*----------------------------------------------------------------------------*/

/*
pre : log ha sido inicializado.
post: agrega el mensaje al log con el siguiente formato
[fecha-hora] Mensaje
log : instancia sobre la cual se aplica la primitiva.
mensaje : texto a escribir.
*/
void escribirMensaje (Log& log, string mensaje);

/*----------------------------------------------------------------------------*/

/*
pre : log ha sido inicializado.
post: agrega el titulo al log, con el formato:
        *********************************************
        titulo
        *********************************************
log : instancia sobre la cual se aplica la primitiva.
titulo : titulo a escribir.
*/
void escribirTitulo (Log& log, string titulo);

/*----------------------------------------------------------------------------*/

/*
pre : log ha sido inicializado.
post: agrega un mensaje con la cantidad de mensajes escritos hasta ese
momento con el formato:
----------------------------------------------
[fecha-hora] Total de Mensajes : XX
log : instancia sobre la cual se aplica la primitiva.
*/
void escribirTotalMensajes (Log& log);

/*----------------------------------------------------------------------------*/


#endif

