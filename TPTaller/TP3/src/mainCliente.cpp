/*
 * mainCliente.cpp
 *
 *  Created on: 29/05/2009
 *      Author: Programadores
 */

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>                 // Referencia a la librería
#include <windows.h>
#include "transferencia.h"
#include "Escenario.h"
#include "parser.h"
#include "Utilidades.h"
#include "Cliente.h"

void iniciarCliente(Cliente *cliente){ // Procedimiento que iniciara el socket secuencialmente.

	//por default

	char leyenda[25];
	char ip[100];
	char puerto[100];

	char* pLeyenda = leyenda;
	char* pIp = ip;
	char* pPuerto = puerto;

	pLeyenda = "CONECTAR CON LA IP (EJ: localhost)";

	//ingresoMensaje(pIp,pLeyenda);

	pLeyenda="CONECTAR CON EL PUERTO (EJ: 2121)";

	//ingresoMensaje(pPuerto,pLeyenda);

	//cliente->start(pIp, atoi(pPuerto));
	cliente->start("169.254.55.132", 1050);
	

}



/************************************************************/
/*                                                          */
/*                  MAIN DEL CLIENTE                        */
/* se conecta el cliente y se levantan los hilos            */
/*                                                          */
/***********************************************************/


int main(int argc, char *argv[])
{
	/*Escenario* escenario = Escenario::obtenerInstancia();
	escenario->cargarArchivo("xml.xml");
	escenario->iniciarSDL();
    */
	Cliente cliente;
    iniciarCliente(&cliente); // Iniciamos el Socket
/*
	SDL_FreeSurface(escenario->getScreen());
	SDL_Quit();
	std::cout<<"SALIO BIEN"<<endl;
	system("PAUSE");
*/
	return 0;
}
