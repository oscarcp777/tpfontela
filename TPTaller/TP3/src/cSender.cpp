#include "cSender.h"
#include "Utilidades.h"
#include "Socket.h"			// Para connect(), send()
#include "cSocketException.h"	// Para las excepciones de sockets
//#include "cSafeQueue.h"			// Para el manejo de la cola thread safe
#include "Defines.h"				// Para las constantes CONNECTED, etc
#include <iostream>				// Para cerr y endl
#include <string>				// Para el manejo de strings
#include <windows.h>			// Para el Sleep()

using namespace std;

cSender::cSender():status(NOT_CONNECTED){}

int cSender::process(void* args)
{
	Socket* sock = (Socket*) args;

	try
	{
		string msg;

		status = CONNECTED;

		int seguirCiclando = 1;
	
		char msjIngresado[TAM_MSJ];
		char *pmsjIngresado = msjIngresado;
		char leyenda[TAM_MSJ];
		char * pLeyenda = leyenda;

		while (seguirCiclando == 1){
				pLeyenda = "INGRESE MENSAJE: (para salir QUIT)";
				ingresoMensaje(pmsjIngresado,pLeyenda);
				enviar(sock->getConexion(),pmsjIngresado);
		}
	
		//enviar(sock->getConexion());
//		while(status==CONNECTED || !toSend.isEmpty())
//		{
//			while(!toSend.isEmpty())
//			{
//				msg = toSend.pop();
//				sock->send(msg.c_str(), msg.size());
//			}
//			Sleep(100);
//		}
	}
	catch (cSocketException &e)
	{
		cerr << e.what() << endl;
		status = NO_HOST;
	}

	return 0;
}

void cSender::enqueue(string msg)
{
	//toSend.push(msg);
}

void cSender::stop()
{
	if(status==CONNECTED)
	{
		this->status = NOT_CONNECTED;
		this->join();
	}
}

cSender::~cSender(){}
