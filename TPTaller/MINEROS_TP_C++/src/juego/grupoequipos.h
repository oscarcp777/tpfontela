/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* GRUPO de equipos */

#ifndef __GRUPOEQUIPOS_H__
#define __GRUPOEQUIPOS_H__

#include "listadeequipos.h"
#include "definiciones.h"
#include "archivoRegistros.h"




/******************************************************************************/
/* Definiciones de Tipos de Datos */
/*--------------------------------*/
typedef Equipo* ptrEquipo;
/* Tipo de Dato */
struct GrupoEquipos{
    lequipos::Lista ListaEquipos;
};
/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : ninguna.
  post: el grupoequip queda creado y preparado para ser usado.

  grupoequip : estructura de datos a ser creada.
  Aequipos: es un archivo de registros que contiene los equipos
  Abots: es un archivo de registros que contiene los Bots


*/

void crearGrupoEquipos(GrupoEquipos &grupoequip,ArchivoRegistros &Aequipos,ArchivoRegistros &Abots);

/******************************************************************************/

/* pre:  el grupoequip existe y ha sido creado con crearGrupoEquipos
         ptrequip no pertenece al grupo de equipos
   post: ptrequip queda adicionado a la lista de equipos

*/

void agregarEquipo(GrupoEquipos &grupoequip,ptrEquipo ptrequip);
/******************************************************************************/

/* pre:  el grupoequip existe, ha sido creado con crearGrupoEquipos
         tiene equipos cargados y los equipos con bots tb cargados
         listabotsGrupo es una lista de bots vacia creada
   post: devuelve una lista de bots con todos los bots de todos los equipos
         que pertencen al grupo de equipos

*/


void obtenerlistaBotsGrupoEquipos(GrupoEquipos &grupoequip,ListaDeBots::Lista &listaBotsGrupo);
/******************************************************************************/

/* pre:  el grupoequip existe y ha sido creado con crearGrupoEquipos
         listaEquiposSalida es una lista de Equipos vacia
   post: devuelve una lista de equipos que pertencen al grupo de equipos

*/


void obtenerlistaEquipos(GrupoEquipos &grupoequip,lequipos::Lista &listaEquiposSalida);
/******************************************************************************/

/* pre:  el grupoequip existe y ha sido creado con crearGrupoEquipos
   post: se liberan los recursos asociados al TDA

*/


void destruirGrupoEquipos(GrupoEquipos &grupoequip);
/******************************************************************************/

/* pre: el grupoequip existe y ha sido creado con crearGrupoEquipos
        y tiene equipos cargados
   post: devuelve la cantidad de equipos del grupo de equipos

*/


int cantidadEquipos (GrupoEquipos &grupoequip);
/******************************************************************************/

/* pre: el grupoequip existe y ha sido creado con crearGrupoEquipos
        y tiene equipos cargados con Bots(y perforadoras) asignados
   post: debueve un puntero al equipo con mayor puntaje

*/


Equipo* EquipoMayorPuntaje(GrupoEquipos &grupoequip);
/******************************************************************************/

/* pre: el grupoequip existe y ha sido creado con crearGrupoEquipos
        y tiene equipos cargados con Bots
   post: devuelve la cantidad de bots q le pertencen al grupodeequipo

*/


int cantidadBotsTotales(GrupoEquipos &grupoequip);
/******************************************************************************/

/* pre: el grupoequip existe y ha sido creado con crearGrupoEquipos
        y tiene equipos cargados
   post: devuelve un puntero al equipo al cual le corresponde el id ingresado

   aclaracion: el ID ingresado debe ser de algun equipo

*/


Equipo* ObtenerEquipo(GrupoEquipos &grupoequip,tId_Equipo ID);

#endif
