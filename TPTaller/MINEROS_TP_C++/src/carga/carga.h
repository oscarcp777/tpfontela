/****************************************
    TDA: carga
    Archivos: carga.h, carga.cpp
****************************************/
//definicion de constante para evitar que incluya dos veces la libreria

#ifndef __CARGA__
#define __CARGA__

#include "cadena.h"
#include "indiceEquipos.h"
#include "dado.h"
#include "archivoTexto.h"
#include "archivoRegistros.h"
#include "indiceBots.h"

using namespace std;
typedef int tCantRondas;

struct regEquipos{
            int id;
            char nombre[50];
            char caracterPerforadora;
            char caracterSeccionCamino;
};
struct regBots{
            int  idBot;
            int  idEquipo;
            char arriba;
            char abajo;
            char izquierda;
            char derecha;
            char esperar;
            char procesarOro;
            char procesarPlata;
            char procesarCobre;
            char construirConducto;
            char destruirConducto;
            char destruirPerforadora;
};
/*Axiomas:
          - El numero de rondas debe ser mayor a 0;
*/
/*
 Nota:a ningun archivo hay qu eponerle la extension para el correcto
      funcionamiento
*/
struct Carga{
                tCantRondas cantRondas;
                string rutaTablero;
                string rutaBots;
                string rutaEquipos;
                string rutaResultado;
                indiceEquipos::Lista equipos;//sirve para controlar que el bot pertenezca a un equipo
                indiceBots::Lista bots;
};

/*  pre: -
    post: crea una instancia de carga con los siguientes valores por defecto:
            -cantidad de rondas = 10;
            -ruta del tablero = tablero.txt
            -ruta del archivo de los bots = bots.dat
            -del archivo equipos = equipos.dat
            -y del archivo resultado = resultado.txt
*/
void crear(Carga &carga);

/*  pre:  instancia creada
    post: genera el archivo de la partida y libera los recursos usados.
*/
void destruir(Carga &carga);

/*  pre:  instancia creada de carga. Una vez cargado bots, no se puede
          cambiar a una cantidad de columnas menor a los ingresados.
    post: genera un archivo con elementos al azar de las dimensiones es-
          pecificadas. Si el archivo ya existia lo destruye y lo crea
          nuevamente. Devuelve true si pudo crearlo satisfactoriamente.
*/
bool generarArchivoTablero(Carga &carga, int cantFilas, int cantColumnas);

/*  pre:  instancia creada de carga. Previamente deben estar cargado los
          equipos. Si el archivo ya existe, los agrega al final.
    post: pide los datos de los bots y los guarda en el archivo. Devuelve
          true si los pudo cargar satisfactoriamente.
*/
bool generarArchivoBots(Carga &carga);

/*  pre:  instancia de carga creada. Tablero de archivos cargado. Si ya
          hay equipos cargados los agrega.
    post: carga los equipos y actualiza el indice de los equipos. Devuelve
          true si los pudo agregar satisfactoriamente.
*/
bool generarArchivoEquipos(Carga &carga);

/*  pre:  instancia creada
    post: devuelve el numero de rondas.
*/
tCantRondas getCantRondas(Carga &carga);

/*  pre:  instancia creada. Cantidad mayor a 0.
    post: asigna la cantidad nueva, si es invalida, deja la anterior.
*/
void setCantRondas(Carga &carga, tCantRondas cantidad);

/*  pre:  instancia creada.
    post: devuelve la ruta del archivo tablero.
*/
string getRutaTablero(Carga &carga);

/*  pre:  instancia creada. Poniendo solo el nombre del archivo, toma
          la ruta donde se esta ejecuntado la carga.
    post: asigna la ruta del archivo tablero
*/
void setRutaTablero(Carga &carga, string cadena);

/*  pre:  instancia creada.
    post: devuelve la ruta del archivo equipos.
*/
string getRutaEquipos(Carga &carga);

/*  pre:  instancia creada. Poniendo solo el nombre del archivo, toma
          la ruta donde se esta ejecuntado la carga.
    post: asigna la ruta del archivo equipos
*/
void setRutaEquipos(Carga &carga, string cadena);

/*  pre:  instancia creada.
    post: devuelve la ruta del archivo resultados.
*/
string getRutaResultados(Carga &carga);

/*  pre:  instancia creada. Poniendo solo el nombre del archivo, toma
          la ruta donde se esta ejecuntado la carga.
    post: asigna la ruta del archivo resultados
*/
void setRutaResultados(Carga &carga, string cadena);

/*  pre:  instancia creada.
    post: devuelve la ruta del archivo de bots.
*/
string getRutaBots(Carga &carga);

/*  pre:  instancia creada. Poniendo solo el nombre del archivo, toma
          la ruta donde se esta ejecuntado la carga.
    post: asigna la ruta del archivo de bots
*/
void setRutaBots(Carga &carga, string cadena);
/*  pre:  instacia creada.
    post: devuelve una referencia al indice de los equipos
*/
indiceEquipos::Lista* getIndiceEquipos(Carga &carga);
/*  pre:  instacia creada.
    post: devuelve una referencia al indice de los bots
*/
indiceBots::Lista* getIndiceBots(Carga &carga);
#endif
