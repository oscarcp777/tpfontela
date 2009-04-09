/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                               Definiciones                                 *
 ******************************************************************************/

 /* Este .h fue creado con el propósito de solucionar problemas de doble inclusión
 o erroes del compilador al detectar tipos de datos. Contiene tipos de datos
 de varios Tda conflictivos y algunas definiciones de tipos atómicos*/

#ifndef __DEFINICIONES__H__
#define __DEFINICIONES__H__

//defino el null
#ifndef NULL
#define NULL      0
#endif

#include <iostream>
using namespace std;
//registros de los archivos
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


//defino las actitudes posibles
enum EnumActitud{procesarOro, procesarPlata, procesarCobre, construirConducto, destruirConducto, destruirPerforadora};

//defino los movimientos posibles
enum EnumMovimiento{arriba, abajo, derecha, izquierda, nada};

//defino los contenidos de un casillero posibles.
enum EnumMinerales{roca, oro, plata, cobre};

typedef int tId_Bot; //Defino el tipo id de bot
typedef int tId_Equipo; //Defino el tipo id de equipo

//Defino los distintos recursos de la perforadora
typedef   int Energia;
typedef   int Hierro;
typedef   int Madera;

typedef   int BodegaPuntos; //Defino los puntos almacenados en las perforadoras
typedef   char TipoID; //Defino el tipo Id de la perforadora

typedef char Puntos; //Defino los puntos q puede contener un mineral
typedef int Tuberia; //Defino el tipo de dato tubería

//constantes con los valores que cuesta hacer cada accion
const int DESTRUIR_TUBERIA = 10;
const int DESTRUIR_BOT = 20;
const int ENERGIA_CONDUCTO = 1;
const int MADERA_CONDUCTO = 4;
const int HIERRO_CONDUCTO = 2;
const int DUREZAORO = 3;
const int DUREZAPLATA = 2;
const int DUREZACOBRE = 1;
const int RECOMPENSAORO = 5;
const int RECOMPENSAPLATA = 3;
const int RECOMPENSACOBRE = 1;

struct Vertice;
//Dato del vertice
struct DatoVertice{
                int Id;
                Tuberia tuberia;
                Vertice* dondeSeCargo;
                bool marcado;
};

//Dato de la arista
struct DatoArista {
                int Id;
};

//TIPO DE DATO DEL TDA MINERAL
struct Mineral{
                            EnumMinerales tipo;
                            Puntos puntos; //Puntos de dureza del mineral
};

/* Esta línea sirve para avisarle al compilador que posteriormente se ha declarado
la estructura Bot */
struct Bot;

//TIPO DE DATO DEL TDA CARGA PERFORADORA
struct  CargaPerforadora{
                 Energia energia;
                 Hierro hierro;
                 Madera madera;

};

//TIPO DE DATO DEL TDA CASILLERO
struct Casillero{
                            Bot* bot;
                            Mineral* mineral;
                            DatoVertice* datoVertice;
                            int IdCasillero;
};

//TIPO DE DATO DEL TDA ENTORNO
struct Entorno {
    Casillero* arriba;
    Casillero* abajo;
    Casillero* izquierda;
    Casillero* derecha;
};

//TIPO DE DATO DEL TDA PERFORADORA
struct Perforadora {
         TipoID ID;
         CargaPerforadora carga;
         Entorno entorno;
         BodegaPuntos bodegaPuntos;
         bool tieneSalida;
};

typedef int prioridadMovimiento; //Defino el tipo de prioridades de movimiento

//TIPO DE DATO DEL TDA MOVIMIENTOS
struct Movimientos{
                    prioridadMovimiento arriba;
                    prioridadMovimiento abajo;
                    prioridadMovimiento derecha;
                    prioridadMovimiento izquierda;
                    prioridadMovimiento nada;
};

typedef int prioridadActitud; //Defino el tipo de prioridades de actitud

//TIPO DE DATO DEL TDA ACTITUDES
struct Actitudes{
                    prioridadActitud procesarOro;
                    prioridadActitud procesarPlata;
                    prioridadActitud procesarCobre;
                    prioridadActitud construirConducto;
                    prioridadActitud destruirConducto;
                    prioridadActitud destruirPerforadora;
};

//TIPO DE DATO DEL TDA ESTRATEGIA
struct Estrategia{
                Movimientos movimientos;
                Actitudes actitudes;
};



#endif



