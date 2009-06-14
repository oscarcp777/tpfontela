/*
 * Cliente.cpp
 *
 *  Created on: 29/05/2009
 *      Author: Programadores
 */

#include "Cliente.h"
#include "Socket.h"			// Para connect(), send()
#include "cSender.h"			// Para el thread que envia al server
#include "cReceiver.h"			// Para el thread que recibe del server
//#include "cInstruction.h"		// Para parsear las instrucciones
#include "Defines.h"				// Para las constantes CONNECTED, etc
#include "cSocketException.h"	// Para las excepciones de sockets
#include "Escenario.h"
#include <iostream>				// Para cerr y endl
#include <string>

using namespace std;

Cliente::Cliente():status(NOT_CONNECTED){}

void Cliente::start(char* host, int port)
{


	char mensRecive[10000];
	char* pmensRecive;
	char posicion[100000];
	char* pPosicion;
	TDA_Parser parser;
	std::string msj;

	try
	{
		sock.connect(host, port);

		status = CONNECTED;

		Escenario* escenario = Escenario::obtenerInstancia();
		escenario->cargarArchivo("xml.xml");
		escenario->iniciarSDL();
	

		//sender.start((void*)&sock);
		receiver.start((void*)&sock);
		while (receiver.running() == true){
			//Sleep(100);

			while (receiver.isEmpty()){
				Sleep(20);
			}
			msj= this->get();
			if(msj.find(" "))
			{
				string pPosicion = msj.substr(0, msj.find(" "));
				escenario->getTejo()->setX(atoi(pPosicion.c_str()));
				pPosicion = msj.substr(msj.find(" ")+1,msj.size());
				escenario->getTejo()->setY(atoi(pPosicion.c_str()));
			}



			if(escenario->graficar()<0)
				this->stop();
			
		}


	}
	catch (cSocketException &e)
	{
		std::cerr << e.what() << endl;
		status = NO_HOST;
	}
}

void Cliente::send(string msg)
{
	sender.enqueue(msg+"\r\n");
}

int Cliente::getStatus()
{
	return status;
}

void Cliente::setStatus(int status)
{
	this->status = status;
}

bool Cliente::haveInstructions()
{
	return !receiver.isEmpty();
}

float Cliente::getDownloadedPercent()
{
	float percent = (float)receiver.getDownloaded()/(float)receiver.getFileSize();
	return percent;
}

void Cliente::clearDownloaded()
{
	receiver.clearDownloaded();
}



std::string Cliente::get()
{
	return receiver.dequeue();
}
//cInstruction Cliente::get()
//{
//	cInstruction instruction;
//
//	string msg = receiver.dequeue();
//
//	if(msg.find(" "))
//	{
//		string action = msg.substr(0, msg.find(" "));
//		instruction.setAction(action);
//		string parametros = msg.substr(msg.find(" ")+1);
//		unsigned int pos;
//		if(action!="CHAT")
//		{
//			while((pos=parametros.find(",")) != string::npos)
//			{
//				instruction.addParam(parametros.substr(0,pos));
//				parametros = parametros.substr(pos+1);
//			}
//			instruction.addParam(parametros);
//		}
//		else
//		{
//			pos = parametros.find(",");
//			instruction.addParam(parametros.substr(0, pos));
//			instruction.addParam(parametros.substr(pos+1));
//		}
//	}
//	else
//	{
//		instruction.setAction(msg);
//	}
//
//	return instruction;
//}

void Cliente::stop()
{
	SDL_FreeSurface(Escenario::obtenerInstancia()->getScreen());
	SDL_Quit();
	sender.stop();
	//receiver.stop();
	sock.shutdown();
	sock.close();
	status = NOT_CONNECTED;
}

Cliente::~Cliente()
{
	if(status==CONNECTED)
	{
		this->stop();
	}
	sock.cleanUp();
}

