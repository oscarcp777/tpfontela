#include "logfinal.h"

/* Implementación de Primitivas */
/*----------------------------------------------------------------------------*/
/*Primitiva inicializar , inicializa una estructura en que se inicializa
 un archivo txt en el que despues se va a escribir y un contador que indica la
 cantidad de mensajes que se estan escribiendo.
*/
void inicializarLog (Log& log, string nombreArchivo)
{
    log.arch.open(nombreArchivo.c_str(),ios::out | ios::trunc);
    log.contador = 0;
}
/*----------------------------------------------------------------------------*/
/*Primitiva Destruir , cierra el archivo de nuestra estructura log
y coloca el contador en cero.Borrando los rastros de nuestra pasada por log.
*/
void destruirLog (Log& log)
{
    log.arch.close();
    log.contador=0;
}
/*----------------------------------------------------------------------------*/
/*Primitiva escribirMensaje , se utiliza la funcion adicional para insertar la 
fecha y hora en nuestra estructura, se incrementa el contador cada vez que se 
llama a esta primitiva,y por ultimo graba el mensaje en el archivo de texto
*/
void escribirMensajeLog (Log& log, string mensaje)
{
    log.contador+=1;
    log.arch << mensaje << endl;
}
/*----------------------------------------------------------------------------*/
/*Primitiva EscribirTitulo ,Crea un Titulo en el archivo con un lindo rotulo  
*/
void escribirTituloLog (Log& log, string titulo)
{
    log.arch << ASTERISCOS << endl << titulo << endl << 
                ASTERISCOS << endl;
}
/*----------------------------------------------------------------------------*/
/*Primitiva escribirTotalMensajes ,Inserta en nuestro archivo el total del 
contador de mensajes. 
*/
void escribirTotalMensajesLog (Log& log)
{
    log.arch << LINEA << endl;
    log.arch << TOTMENSAJES << log.contador << endl;
    log.arch << LINEA << endl;
}
