#include "cSender.h"
#include "Utilidades.h"
#include "Socket.h"			// Para connect(), send()
#include "cSocketException.h"	// Para las excepciones de sockets
//#include "cSafeQueue.h"			// Para el manejo de la cola thread safe
#include "Defines.h"				// Para las constantes CONNECTED, etc
#include <iostream>				// Para cerr y endl
#include <string>				// Para el manejo de strings
#include <windows.h>			// Para el Sleep()
#include "Escenario.h"

using namespace std;

cSender::cSender():status(NOT_CONNECTED){}

void cSender::posicionPad(char* pEnvioString){
	Escenario* escenario = Escenario::obtenerInstancia();
	char auxX[20];
	char auxY[20];
	char* pauxX = auxX;
	char* pauxY = auxY;
	memset(pauxX,0,sizeof(char)*20);
	memset(pauxY,0,sizeof(char)*20);
	memset(pEnvioString,0,sizeof(char)*40);
	strcat(pEnvioString,"STRING ");
	itoa(escenario->getPadJugador()->getX(),pauxX,10);
	itoa(escenario->getPadJugador()->getY(),pauxY,10);
	strcat(pEnvioString,pauxX);
	strcat(pEnvioString," ");
	strcat(pEnvioString,pauxY);
}

int cSender::process(void* args)
{
	Socket* sock = (Socket*) args;
	Escenario* escenario = Escenario::obtenerInstancia();
	try
	{
		string msg;

		status = CONNECTED;

		int seguirCiclando = 1;		
		char envioString[40];
		char *pEnvioString = envioString;
		int posPad_Y_actual;
		
		while (escenario->getPadJugador()==NULL){
			sleep(10);
		}
		posPad_Y_actual = escenario->getPadJugador()->getY();

		while (seguirCiclando == 1){
			if (posPad_Y_actual != escenario->getPadJugador()->getY()){ // si la pos del pad varia envio al servidor
				posPad_Y_actual = escenario->getPadJugador()->getY();
				this->posicionPad(pEnvioString);
				std::cout<<pEnvioString<<endl;
				enviar(sock->getConexion(),pEnvioString);
			}
			
			
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
		std::cerr << e.what() << endl;
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
