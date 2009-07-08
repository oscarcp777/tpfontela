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
		std::string moverArriba, moverAbajo;
		std::string noMover = "NO MOVER\n";
		std::string soltarTejo = "SOLTAR_TEJO\n";
		char _moverArriba[40];
		char *_pmoverArriba = _moverArriba;
		char _noMover[40];
		char *_pnoMover = _noMover;
		char _moverAbajo[40];
		char *_pmoverAbajo = _moverAbajo;
		char _soltarTejo[40];
		char *_psoltarTejo = _soltarTejo;
		
		_pnoMover = (char*)noMover.c_str();
		_psoltarTejo = (char*)soltarTejo.c_str();

		while (escenario->getPadJugador()==NULL){
			sleep(3000);
		}
		//posPad_Y_actual = escenario->getPosicionYPad();
		Pad* pad = escenario->getPadJugador();
	
		if(escenario->getNumJugador() == 1){
			moverArriba = "PAD1 ARRIBA\n";
			_pmoverArriba = (char*)moverArriba.c_str();
			moverAbajo =  "PAD1 ABAJO\n";
			_pmoverAbajo = (char*)moverAbajo.c_str();
			
		}
		else if(escenario->getNumJugador() == 2){
			
			moverArriba =  "PAD2 ARRIBA\n";
			_pmoverArriba = (char*)moverArriba.c_str();
			moverAbajo = "PAD2 ABAJO\n";
			_pmoverAbajo = (char*)moverAbajo.c_str();
		}
				
		
		while(status==CONNECTED){
			Sleep(20);
		
			if(pad->getMoverArriba()){
				sock->send(_pmoverArriba);
				pad->setMoverArriba(false);
			}
			else if(pad->getMoverAbajo()){
				sock->send(_pmoverAbajo);
				pad->setMoverAbajo(false);
			}
			else if(pad->getSoltarTejo()){
				sock->send(_psoltarTejo);
				escenario->getPadJugador()->setSoltarTejo(false);
			
			}
			else if(!pad->getMoverArriba() && !pad->getMoverAbajo()){
				sock->send(_pnoMover);
				
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


void cSender::stop()
{
	if(status==CONNECTED)
	{
		this->status = NOT_CONNECTED;
		//this->join();
	}
}

cSender::~cSender(){}
