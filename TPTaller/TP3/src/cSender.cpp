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
/*
void cSender::posicionPad(char* pEnvioString){
	Escenario* escenario = Escenario::obtenerInstancia();
	char numJugador[20];
	char* pauxNumJugador = numJugador;
	memset(pEnvioString,0,sizeof(char)*40);
	strcat(pEnvioString,"PAD");
	itoa(escenario->getNumJugador(),pauxNumJugador,10);
	strcat(pEnvioString,pauxNumJugador);
	itoa(escenario->getPosicionYPad(),pauxY,10);
	strcat(pEnvioString," ");
	strcat(pEnvioString,pauxY);
	
}*/
void cSender::soltarTejo(char* pEnvioString){
	char aux[20];
	char* paux = aux;
	memset(paux,0,sizeof(char)*20);
	memset(pEnvioString,0,sizeof(char)*40);
	strcat(pEnvioString,"SOLTAR_TEJO");
		
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
		char soltarTejo[40];
		char *pSoltarTejo = soltarTejo;
		std::string moverArriba, moverAbajo;
		
		while (escenario->getPadJugador()==NULL){
			sleep(3000);
		}
		//posPad_Y_actual = escenario->getPosicionYPad();
		Pad* pad = escenario->getPadJugador();
	
		if(escenario->getNumJugador() == 1){
			moverArriba = "PAD1 ARRIBA";
			moverAbajo =  "PAD1 ABAJO";
		}
		else if(escenario->getNumJugador() == 2){
			
			moverArriba =  "PAD2 ARRIBA";
			moverAbajo = "PAD2 ABAJO";
		}
				
		
		while(status==CONNECTED){
			Sleep(30);
			/*
			if (posPad_Y_actual != escenario->getPosicionYPad()){ // si la pos del pad varia envio al servidor
				posPad_Y_actual = escenario->getPosicionYPad();
				this->posicionPad(pEnvioString);
				sock->send(pEnvioString);
				
			}*/
			if(pad->getMoverArriba()){
				sock->send((char*)moverArriba.data());
				pad->setMoverArriba(false);
			}
			if(pad->getMoverAbajo()){
				sock->send((char*)moverAbajo.data());
				pad->setMoverAbajo(false);
			}
			if(pad->getSoltarTejo()){
				this->soltarTejo(pSoltarTejo);
				sock->send(pSoltarTejo);
				escenario->getPadJugador()->setSoltarTejo(false);
			
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
