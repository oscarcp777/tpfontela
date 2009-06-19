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
#include "cSocketException.h"	// Para las excepciones de sockets
#include "Escenario.h"
#include <iostream>				// Para cerr y endl
#include <string>
#include "GraficadorPuntajes.h"
#include "Define.h"

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
		this->sock.connect(host, port);

		status = CONNECTED;

		Escenario* escenario = Escenario::obtenerInstancia();
		escenario->iniciarSDL();
		GraficadorPuntajes::obtenerInstancia()->graficarString(escenario->getScreen(),"LOADING...",250,250);
		SDL_Flip(escenario->getScreen());

		//loading(&sock);


		escenario->cargarArchivo("nivel1.xml");


		receiver.start((void*)&sock);
		sender.start((void*)&sock);



		while (receiver.running() == true){


			while (receiver.isEmpty()){
				Sleep(20);
			}
			//std::cout<<"size pila: "<<receiver.getFileSize()<<endl;
			msj= this->get();

			if(msj.find("PAD1")==0)
			{
				string pPosicion = msj.substr(msj.find(" ")+1,msj.find_last_of(" "));
				escenario->getPadCliente1()->setX(atoi(pPosicion.c_str()));
				pPosicion = msj.substr(msj.find_last_of(" ")+1,msj.size());
				escenario->getPadCliente1()->setY(atoi(pPosicion.c_str()));

			}
			else if(msj.find("PAD2")==0)
			{
				string pPosicion = msj.substr(msj.find(" ")+1,msj.find_last_of(" "));
				escenario->getPadCliente2()->setX(atoi(pPosicion.c_str()));
				pPosicion = msj.substr(msj.find_last_of(" ")+1,msj.size());
				escenario->getPadCliente2()->setY(atoi(pPosicion.c_str()));


			}
			else if(msj.find("PUNTAJE")==0)
			{
				//el cliente no se entera quien hizo el gol, cuando recibe puntajes es porque hubo un gol
				//se setean los puntajes nuevos y se decrementa la cantidad de tejos restantes (esto es solo para graficar los "tejitos" en pantalla
				string cadena,puntaje;
				cadena = msj.substr(msj.find(" ")+1,msj.find_last_of(" "));
				puntaje = cadena.substr(0,cadena.find_last_of(" "));
				escenario->getPadCliente1()->getPuntaje()->setCantPuntosJugador(atoi(puntaje.c_str()));
				puntaje = msj.substr(msj.find_last_of(" ")+1,msj.size());
				escenario->getPadCliente2()->getPuntaje()->setCantPuntosJugador(atoi(puntaje.c_str()));
				escenario->decrementarTejosRestantes();


			}
			else if(msj.find("GANADOR")==0)
			{
				string cadena;
				if(msj.find("1")==0)
					cadena = "GANO EL JUGADOR 1";
				else
					cadena = "GANO EL JUGADOR 2";
				GraficadorPuntajes::obtenerInstancia()->graficarString(escenario->getScreen(),cadena,50,escenario->getAlto()/3);
				SDL_Flip(escenario->getScreen());
				Sleep(3000);
				//seteo msj en finJuego asi no grafica mas CAMBIAR ESTO
				msj = "FINJUEGO";
			}


			else{
					string pPosicion = msj.substr(0, msj.find(" "));
					escenario->getTejo()->setX(atoi(pPosicion.c_str()));
					pPosicion = msj.substr(msj.find(" ")+1,msj.size());
					escenario->getTejo()->setY(atoi(pPosicion.c_str()));
				}



			if(escenario->graficar()<0 || msj.find("FINJUEGO")==0){
				this->sock.send("QUIT");
				this->stop();
			}
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
	sender.stop();
	receiver.stop();
	Sleep(1000);
	sock.shutdown();
	sock.close();
	status = NOT_CONNECTED;
	SDL_FreeSurface(Escenario::obtenerInstancia()->getScreen());
	SDL_Quit();

}

void Cliente::loading(Socket* s){
	int i=0;
	int nbytes;
	char numArch[5];
	char* auxNumArch = numArch;
	string numArchivos;
	char nombreArchivo[200];
	char* pNombreArchivo = nombreArchivo;

	memset(auxNumArch,0,sizeof(char)*5);
	s->receive(auxNumArch,5);

	while(i<atoi(auxNumArch)){
		memset(pNombreArchivo,0,sizeof(char)*200);
		s->receive(pNombreArchivo,200);
		std::cout << "NombreArchivo: "<< pNombreArchivo << std::endl;
		nbytes = s->receiveFile(pNombreArchivo);
		std::cout << "nbytes "<< nbytes<< std::endl;
		i++;

	}

}

Cliente::~Cliente()
{
	if(status==CONNECTED)
	{
		this->stop();
	}
	sock.cleanUp();
}

