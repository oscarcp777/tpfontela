#include "cSender.h"
#include "Socket.h"		
#include "cSocketException.h"	
#include "Define.h"			
#include <iostream>				
#include <string>				
#include <windows.h>			
#include "Escenario.h"

using namespace std;

cSender::cSender():status(NOT_CONNECTED){}

void cSender::posicionPad(char* pEnvioString){
	Escenario* escenario = Escenario::obtenerInstancia();
	char auxX[20];
	char auxY[20];
	char numJugador[20];
	char* pauxX = auxX;
	char* pauxY = auxY;
	char* pauxNumJugador = numJugador;
	memset(pauxX,0,sizeof(char)*20);
	memset(pauxY,0,sizeof(char)*20);
	memset(pEnvioString,0,sizeof(char)*40);
	strcat(pEnvioString,"PAD");
	itoa(escenario->getNumJugador(),pauxNumJugador,10);
	strcat(pEnvioString,pauxNumJugador);
	itoa(escenario->getPadJugador()->getX(),pauxX,10);
	itoa(escenario->getPosicionYPad(),pauxY,10);
	strcat(pEnvioString," ");
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

		char envioString[40];
		char *pEnvioString = envioString;
		int posPad_Y_actual;
		
		while (escenario->getPadJugador()==NULL){
			sleep(3000);
		}
		posPad_Y_actual = escenario->getPosicionYPad();

		while(status==CONNECTED){
			
			if (posPad_Y_actual != escenario->getPosicionYPad()){ // si la pos del pad varia envio al servidor
				posPad_Y_actual = escenario->getPosicionYPad();
				this->posicionPad(pEnvioString);
				//std::cout<<pEnvioString<<endl;
				sock->send(pEnvioString);
				
			}
			
			
		}
		
		
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
		//this->join();
	}
}

cSender::~cSender(){}
