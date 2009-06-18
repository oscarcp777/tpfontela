#include "cReceiver.h"
#include "Socket.h"			// Para connect(), send()
#include "cSocketException.h"	// Para las excepciones de sockets
//#include "cSafeQueue.h"			// Para el manejo de la cola thread safe
//#include "cMutex.h"				// Para el mutex de downloaded y filesize
//#include "cLockableGuard.h"		// Para la guarda del mutex
#include "Defines.h"				// Para las constantes CONNECTED etc
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

	char mensRecive[1000];
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

		status = CONNECTED;

		Escenario* escenario = Escenario::obtenerInstancia();
		
		//recibo numero de jugador
		memset(pNumJugador,0,sizeof(char)*400);
		sock->receive(pNumJugador);
		//recibir(sock->getConexion(), pNumJugador);
		
		std::cout<<"NUMERO DE JUGADOR "<<pNumJugador<<endl;		
		
		int jugador = atoi(pNumJugador);
		escenario->setPadJugador(jugador);
				
	
		while(status==CONNECTED){

			memset(pmensRecive,0,sizeof(char)*1000);

			/*if (recibir(sock->getConexion(), pmensRecive)<0)
				status = NOT_CONNECTED;*/
			try{
			sock->receive(pmensRecive);
			}catch (cSocketException &e)
			{
				std::cerr << e.what() << endl;
			}
			//std::cout<<"pmensRecive: "<<pmensRecive<<endl;
			msg = pmensRecive;
			received.push(msg);

		}
		//this->stop();
		delete(this);

		
		
//		int bytesReceived = 0;
//		char buffer[BUFFERSIZE];
//		memset(buffer, 0, BUFFERSIZE);
//		string bufferStr = "";
//		string instStr = "";
//		string action = "";
//		unsigned int i;
//		ofstream file;
//
//		while(status==CONNECTED)
//		{
//			bytesReceived = sock->receive(buffer, BUFFERSIZE);
//
//			bufferStr = buffer;
//
//			while((i=bufferStr.find("\r\n"))!=string::npos)
//			{
//				instStr = bufferStr.substr(0,i);
//				action = instStr.substr(0,instStr.find(" "));
//				bufferStr = bufferStr.substr(i+2);
//
//				if(action=="FILEMAP" || action=="FILETXT")
//				{
//					mFile.Lock();
//					filesize = atoi(instStr.substr(instStr.find(" ")+1).c_str());
//					mFile.Unlock();
//
//					if(action=="FILEMAP") file.open("map.jpg", ofstream::binary);
//					else if (action=="FILETXT") file.open("coords.txt", ofstream::binary);
//
//					// Si el tamanio del archivo es menor de lo que se recibio
//					// entonces TODO el archivo esta contenido en eso unico buffer
//					if(filesize <= bytesReceived-i-2)
//					{
//						file.write(buffer+i+2, filesize);
//						file.close();
//
//						mDown.Lock();
//						mFile.Lock();
//						downloaded = filesize;
//						mDown.Unlock();
//						mFile.Unlock();
//					}
//					else
//					{
//						// Sino, guardo el buffer e itero hasta llegar
//						// al tamanio del archivo especificado
//						file.write(buffer+i+2, bytesReceived-i-2);
//
//						cLockableGuard<cMutex,int,int> safeMuD(mDown,&cMutex::Lock,&cMutex::Unlock);
//						downloaded = bytesReceived-i-2;
//						safeMuD.Unlock();
//
//						while(downloaded < filesize)
//						{
//							bytesReceived = sock->receive(buffer, BUFFERSIZE);
//							if(downloaded+bytesReceived < filesize)
//							{
//								file.write(buffer, bytesReceived);
//								cLockableGuard<cMutex,int,int> safeMu(mDown,&cMutex::Lock,&cMutex::Unlock);
//								downloaded = downloaded + bytesReceived;
//							}
//							else
//							{
//								file.write(buffer, filesize-downloaded);
//								file.close();
//								cLockableGuard<cMutex,int,int> safeMu(mDown,&cMutex::Lock,&cMutex::Unlock);
//								cLockableGuard<cMutex,int,int> safeMu2(mFile,&cMutex::Lock,&cMutex::Unlock);
//								downloaded = filesize;
//							}
//						}
//					}
//					bufferStr.clear();
//				}
//				else
//				{
//					received.push(instStr);
//
//					#ifdef SOCK_TO_TXT
//					std::ofstream outfile("recv_queue.txt", std::ofstream::out | std::ofstream::app);
//					outfile.write(instStr.c_str(), instStr.size());
//					outfile.write("\n", 1);
//					outfile.close();
//					#endif
//				}
//			}
//			memset(buffer, 0, BUFFERSIZE);
//		}
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
	return this->filesize;
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
		//this->join();
		
	}
}

cReceiver::~cReceiver(){}
