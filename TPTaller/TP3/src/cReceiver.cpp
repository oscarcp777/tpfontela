#include "cReceiver.h"
#include "Socket.h"			// Para connect(), send()
#include "cSocketException.h"	// Para las excepciones de sockets
//#include "cSafeQueue.h"			// Para el manejo de la cola thread safe
//#include "cMutex.h"				// Para el mutex de downloaded y filesize
//#include "cLockableGuard.h"		// Para la guarda del mutex
#include "Define.h"				// Para las constantes CONNECTED etc
#include <iostream>				// Para cerr y endl
#include <string>				// Para el manejo de strings
#include <fstream>				// Para filemap y filetxt
#include <iostream>
#include <fstream>
#include "Escenario.h"

using namespace std;

const unsigned int cReceiver::BUFFERSIZE = 1024;

cReceiver::cReceiver():status(NOT_CONNECTED),filesize(1),downloaded(0)
{
	#ifdef SOCK_TO_TXT
	std::ofstream outfile;
	outfile.open("recv_queue.txt", std::ofstream::out | std::ofstream::trunc);
	outfile.close();
	#endif
}


int cReceiver::process(void* args){

	char mensRecive[1024];
	char* pmensRecive;
	char posicion[100000];
	char* pPosicion;
	char numJugador[400];
	char* pNumJugador = numJugador;
	TDA_Parser parserPrueba;
	int jugador;

	Socket* sock = (Socket*) args;
	pmensRecive = mensRecive;
	pPosicion = posicion;

	try
	{
		string msg;
		string bufferStr = "";
		status = CONNECTED;
		int i;

		Escenario* escenario = Escenario::obtenerInstancia();

		//recibo numero de jugador
		memset(pNumJugador,0,sizeof(char)*400);
		sock->receive(pNumJugador,400);
		//recibir(sock->getConexion(), pNumJugador);

		std::cout<<"NUMERO DE JUGADOR "<<pNumJugador<<endl;

		int jugador = atoi(pNumJugador);
		escenario->setPadJugador(jugador);


		while(status==CONNECTED){



			/*if (recibir(sock->getConexion(), pmensRecive)<0)
				status = NOT_CONNECTED;*/
			try{
				if(escenario->getCorriendo()==true){

					memset(pmensRecive,0,sizeof(char)*1024);
					sock->receive(pmensRecive,1024);
					msg="";
					msg = pmensRecive;
					bufferStr += msg;
					//std::cout<<msg;
					while((i=bufferStr.find("\n")) != -1){
						msg = bufferStr.substr(0,i);
						received.push(msg);
						bufferStr = bufferStr.substr(i+1);

					}

				}
			}catch (cSocketException &e){
			//	std::cerr << e.what() << endl;
			}


		}
		//this->stop();
		delete(this);




	}
	catch (cSocketException &e)
	{
		std::cerr << e.what() << endl;
		status = NO_HOST;
	}

	return 0;
}

bool cReceiver::isEmpty()
{
	return received.isEmpty();
}

string cReceiver::dequeue()
{
	return received.pop();
}

int cReceiver::getFileSize()
{
	//cLockableGuard<cMutex,int,int> safeMu(mFile,&cMutex::Lock,&cMutex::Unlock);
	return received.size();
}

int cReceiver::getDownloaded()
{
	//cLockableGuard<cMutex,int,int> safeMu(mDown,&cMutex::Lock,&cMutex::Unlock);
	return this->downloaded;
}

void cReceiver::clearDownloaded()
{
	//cLockableGuard<cMutex,int,int> safeMu(mDown,&cMutex::Lock,&cMutex::Unlock);
	this->downloaded = 0;
}


void cReceiver::stop()
{
	if(status==CONNECTED)
	{
		this->status = NOT_CONNECTED;
		this->stopear();

	}
}

cReceiver::~cReceiver(){}
