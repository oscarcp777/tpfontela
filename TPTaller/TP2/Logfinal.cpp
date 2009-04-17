#include "logfinal.h"

/* Funciones adicionales 
//void insertarFechayHora(log& log)
/* ----------------------------------------------------------------------------*/
/*
   Pre: log creado con inicializar
   Post: inserta en el log la fecha y la hora con el formato:
         [fecha-hora]

   gmtime: primitiva de la librería time.h
           devuelve la hora respecto al meridiano de Greenwich
           (en Argentina, 3 horas menos)
   *gmt contiene los campos:
   tm_mday (día del mes: 1 - 31)
   tm_mon  (mes: 0 - 11)
   tm_year (año desde 1900)
   tm_hour (hora desde medianoche: 0 - 23)
   tm_min  (minutos: 0 - 59)
   tm_sec  (segundos: 0 - 59)
*/
/*----------------------------------------------------------------------------*/
void insertarFechaHora(Log& log)
{
int hora, minutos, segundos, dia, mes, anio;

    time_t t;
    struct tm *gmt;
    t=time(NULL);
    gmt=gmtime(&t);
       
    if (gmt->tm_hour>=3 && gmt->tm_hour<=23)
      hora = gmt->tm_hour - 3;
    else
      hora = gmt->tm_hour + 21;
   
    minutos = gmt->tm_min;
    segundos = gmt->tm_sec;
    dia = gmt->tm_mday;
    mes = gmt->tm_mon + 1;
    anio = gmt->tm_year-100;

    log.arch<<"["<<dia<<"/"<<mes<<"/"<<anio<<"-"<<hora<<":"<<minutos<<
    ":"<<segundos<<"]"<<" ";
}
/*----------------------------------------------------------------------------*/


/* Implementación de Primitivas */
/*----------------------------------------------------------------------------*/
/*Primitiva inicializar , inicializa una estructura en que se inicializa
 un archivo txt en el que despues se va a escribir y un contador que indica la
 cantidad de mensajes que se estan escribiendo.
*/
void inicializar (Log& log, string nombreArchivo)
{
    log.arch.open(nombreArchivo.c_str(),ios::out | ios::app);
    log.contador = 0;
}
/*----------------------------------------------------------------------------*/
/*Primitiva Destruir , cierra el archivo de nuestra estructura log
y coloca el contador en cero.Borrando los rastros de nuestra pasada por log.
*/
void destruir (Log& log)
{
    log.arch.close();
    log.contador=0;
}
/*----------------------------------------------------------------------------*/
/*Primitiva escribirMensaje , se utiliza la funcion adicional para insertar la 
fecha y hora en nuestra estructura, se incrementa el contador cada vez que se 
llama a esta primitiva,y por ultimo graba el mensaje en el archivo de texto
*/
void escribirMensaje (Log& log, string mensaje)
{
    insertarFechaHora (log);
    log.contador+=1;
    log.arch << mensaje << endl;
}
/*----------------------------------------------------------------------------*/
/*Primitiva EscribirTitulo ,Crea un Titulo en el archivo con un lindo rotulo  
*/
void escribirTitulo (Log& log, string titulo)
{
    log.arch << ASTERISCOS << endl << titulo << endl << 
                ASTERISCOS << endl;
}
/*----------------------------------------------------------------------------*/
/*Primitiva escribirTotalMensajes ,Inserta en nuestro archivo el total del 
contador de mensajes. 
*/
void escribirTotalMensajes (Log& log)
{
    log.arch << LINEA << endl;
    insertarFechaHora(log);
    log.arch << TOTMENSAJES << log.contador << endl;
    log.arch << LINEA << endl;
}
