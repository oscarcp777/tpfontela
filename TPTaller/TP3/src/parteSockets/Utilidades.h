#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "transferencia.h"
#include "parser.h"

#define TAM_MSJ 10000                 //Tamaño maximo del mensaje a enviar
#define PRIMER_ENVIO 15
#define ARCH_CONF "config.txt"    //Nombre archivo configuración parser
#define ARCH_LOG  "log.txt"     //Nombre archivo de log del parser
#define TAM_NOMBRE_ARCH 30


#define RES_OK 0
#define RES_ERROR -1
#define RES_QUIT -2
#define RES_THREAD -3

/*****************************************************************/
/* recibir: Funcion que ejecuta en un hilo encargada de recibir    */
/*          los mensajes que le son enviados y mostrarlos          */
/*                                                                 */
/*        conexion:  apunta a la  conexion.                        */
/*        DWORD: devuelve el id del hilo que la esta ejecutando	   */
/*****************************************************************/
DWORD WINAPI recibir(LPVOID conexion);
/*****************************************************************/
/*****************************************************************/
/* recibir: Funcion que ejecuta en un hilo encargada de enviar     */
/*          los mensajes que le son enviados y mostrarlos          */
/*        conexion:  apunta a la  conexion.                        */
/*        DWORD: devuelve el id del hilo que la esta ejecutando	   */
/*****************************************************************/
DWORD WINAPI enviar(LPVOID conexion);
/*****************************************************************/
/* reconectarSockets: funcion que acepta cuando  un cliente se    */
/*                    conecta  cuando el cliente el que estaba    */
/*                    conectado se desconecto                     */
/*              devuelve RES_OK si alguien se conectó y pConexion */
/*              apunta a la nueva conexion.                       */
/*		  De lo contrario devuelve un codigo de error y           */
/*             pConexion permanece inalterado.		              */
/*****************************************************************/
int reconectarSockets(CONEXION *pConexion);
/*****************************************************************/
/* ingresoMensaje: Espera que se ingrese un mensaje para ser enviado*/
/*                 pmsj: mensaje ingresado
/*                 leyenda :mensaje para el que escribe   		    */
/*****************************************************************/
void ingresoMensaje(char *pmsj,char* leyenda);
/*****************************************************************/
/* deStringATipoDato: recibe un cadena de char y la devuelve      */
/*                   como un tipò de dato definido anteriomente		      */
/*****************************************************************/
enum tr_tipo_dato deStringATipoDato(char* cadena);
