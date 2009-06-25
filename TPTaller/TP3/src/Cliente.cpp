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

#include "cSocketException.h"	// Para las excepciones de sockets
#include "Escenario.h"
#include <iostream>				// Para cerr y endl
#include <string>
#include "GraficadorPuntajes.h"
#include "Define.h"
#include <time.h>

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
	this->finLoading=false;
	SDL_Surface *screen;



	try
	{
		this->sock.connect(host, port);

		status = CONNECTED;

		loading(&sock);
		Escenario* escenario = Escenario::obtenerInstancia();
		escenario->iniciarSDL();
		GraficadorPuntajes::obtenerInstancia()->graficarString(escenario->getScreen(),"LOADING...",escenario->getAncho()/4,2*escenario->getAlto()/5);
		SDL_Flip(escenario->getScreen());

		loading(&sock);
		escenario->cargarArchivo("nivel"+escenario->getNumeroNivelEnString()+".xml");
		escenario->clienteInicializarListaBonus();
		escenario->setCorriendo(true);

		receiver.start((void*)&sock);
		sender.start((void*)&sock);

		while (receiver.isEmpty()){
				Sleep(2);
			}


		msj= this->get();

		if(msj.find("INICIAR")==0){
			GraficadorPuntajes::obtenerInstancia()->graficarString(escenario->getScreen(),"NIVEL "+escenario->getNumeroNivelEnString(),escenario->getAncho()/3,escenario->getAlto()/3);
			SDL_Flip(escenario->getScreen());
			Sleep(3000);
		}

		while (receiver.running() == true){

			while (receiver.isEmpty()){
				Sleep(1);
			}
			//std::cout<<"size pila: "<<receiver.getFileSize()<<endl;
			msj= this->get();

			if(msj.find("TEJO")==0){
				string pPosicion = msj.substr(msj.find(" ")+1,msj.find_last_of(" "));
				escenario->getTejo()->setX(atoi(pPosicion.c_str()));
				pPosicion = msj.substr(msj.find_last_of(" ")+1,msj.size());
				escenario->getTejo()->setY(atoi(pPosicion.c_str()));
				}

			else if(msj.find("PAD1")==0){
				string pPosicion = msj.substr(msj.find(" ")+1,msj.size());
				escenario->getPadCliente1()->setY(atoi(pPosicion.c_str()));

			}
			else if(msj.find("PAD2")==0){
				string pPosicion = msj.substr(msj.find(" ")+1,msj.size());
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
				escenario->setPrimerPintada(false);


			}

			else if(msj.find("BONUS")==0){
				std::cout<<"msj "<<msj<<endl;
				string tipoBonus,idFigura;
				tipoBonus = msj.substr(msj.find(" ")+1,msj.find_last_of(" "));
				idFigura = msj.substr(msj.find_last_of(" ")+1,msj.size());
				Figura* figura= escenario->getFiguraPorId(idFigura);
				Bonus* bonus = escenario->obtenerBonusPorTipo(atoi(tipoBonus.c_str()));
				figura->setImagenBonus(bonus->getImagen());
				escenario->setBonusActual(bonus);
				escenario->setFiguraConBonus(figura);
				escenario->setPrimerPintada(false);

			}
			else if(msj.find("APLICAR_BONUS")==0){
				std::cout<<"msj "<<msj<<endl;
				string ultimoPad = msj.substr(msj.find(" ")+1,msj.size());
				Bonus::desAplicar();
				escenario->getTejo()->setUltimaColisionPad(ultimoPad);
				escenario->getFiguraConBonus()->setImagenBonus(NULL);
				escenario->getFiguraConBonus()->setEscalada(false);
				escenario->setFiguraConBonus(NULL);
				escenario->setPrimerPintada(false);
				//TODO desaplicar bonus anterior etc, "pensar eso"
				escenario->getBonusActual()->aplicar();


			}
			else if(msj.find("NIVEL_TERMINADO")==0){
				escenario->setCorriendo(false);
				escenario->setTejosRestantes(7);
				escenario->incrementarNivel();
				GraficadorPuntajes::obtenerInstancia()->graficarString(escenario->getScreen(),"NIVEL "+escenario->getNumeroNivelEnString(),escenario->getAncho()/3,escenario->getAlto()/3);
				SDL_Flip(escenario->getScreen());
				Sleep(3000);
				escenario->borrarListaFiguras();
				escenario->borrarListaTexturas();
				escenario->setearImagenesEnNull();
				escenario->setFiguraConBonus(NULL);
				Bonus::desAplicar();
				escenario->cargarArchivo("nivel"+escenario->getNumeroNivelEnString()+".xml");
				escenario->setPrimerPintada(false);
				escenario->setCorriendo(true);

			}
			else if(msj.find("GANADOR")==0){
				std::cout<<"msj "<<msj<<endl;
				string cadena = "";

				if(msj.find("GANADOR 1")==0){
					if(escenario->getNumJugador() == 1)
						cadena = "GANASTE!!!!!!";
					else
						cadena = "PERDISTE!!!!!";

				}
				else if(msj.find("GANADOR 2")==0){
					if(escenario->getNumJugador() == 1)
						cadena = "PERDISTE!!!!!!";
					else
						cadena = "GANASTE!!!!!";

				}

				GraficadorPuntajes::obtenerInstancia()->graficarString(escenario->getScreen(),cadena, 200,escenario->getAlto()/3);
				SDL_Flip(escenario->getScreen());
				Sleep(3000);
				//seteo msj en finJuego asi no grafica mas CAMBIAR ESTO
				msj = "FINJUEGO";
			}
			else if(msj.find("JUGADOR_DESCONECTADO")==0){
				std::string cadena = "SE DESCONECTO EL OPONENTE";
				GraficadorPuntajes::obtenerInstancia()->graficarString(escenario->getScreen(),cadena, 10,escenario->getAlto()/3);
				SDL_Flip(escenario->getScreen());
				Sleep(3000);
				//seteo msj en finJuego asi no grafica mas CAMBIAR ESTO
				msj = "FINJUEGO";
			
			
			}
			if(msj.find("FINJUEGO")==0){
				this->sock.send("QUIT");
				this->stop();
			}
			else{
				if(escenario->graficar()<0){
				this->sock.send("QUIT");
				receiver.stop();
				}
			}

		}
		this->stop();
		std::cerr << "SALIOOO.." << endl;
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


void Cliente::stop()
{
	sender.stop();
	Sleep(1000);
	sock.shutdown();
	sock.close();
	status = NOT_CONNECTED;
	SDL_FreeSurface(Escenario::obtenerInstancia()->getScreen());
	SDL_Quit();
	delete(Escenario::obtenerInstancia());
	exit(1);

}

void Cliente::loading(Socket* s){
	std::cout<<"ENTRO A LOADING CLIENTE"<<endl;
	int i=0;
	int nbytes;
	char numArch[5];
	char* auxNumArch = numArch;
	string numArchivos;
	char nombreArchivo[200];
	char* pNombreArchivo = nombreArchivo;

	memset(auxNumArch,0,sizeof(char)*5);
	s->receive(auxNumArch,5);
	std::cout<<"auxNumArch "<<auxNumArch<<endl;

	while(i<atoi(auxNumArch)){
		memset(pNombreArchivo,0,sizeof(char)*200);
		s->receive(pNombreArchivo,200);
		std::cout << "NombreArchivo: "<< pNombreArchivo << std::endl;
		nbytes = s->receiveFile(pNombreArchivo);
		std::cout << "nbytes "<< nbytes<< std::endl;
		i++;

	}
	this->finLoading=true;

}


Cliente::~Cliente()
{
	if(status==CONNECTED)
	{
		this->stop();
	}
	sock.cleanUp();
}

