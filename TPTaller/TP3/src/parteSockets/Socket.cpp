/*
 * Socket.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "Socket.h"

typedef char raw_type;
//bool Socket::initialized = false;

using namespace std;

sockaddr_in Socket::getAddressStruct(const string& address, unsigned int port)
{
    sockaddr_in strctAddr;
    memset(&strctAddr, 0, sizeof(address));

    hostent* he;
//    if((he=gethostbyname(address.c_str())) == NULL)
//    {
//        throw cSocketException("Error en gethostbyname()");
//    }

    strctAddr.sin_family = AF_INET;
    strctAddr.sin_addr = *((struct in_addr *)he->h_addr);
    strctAddr.sin_port = htons(port);

    return strctAddr;
}

Socket::Socket()
{
}

Socket::Socket(int sockDesc)
{
    this->sockDesc = sockDesc;
    this->initialized = false;
}

void Socket::connect(const char& host, unsigned int port)
{
	if (trConectar(&host,port,&this->conexion)==-1){
				std::cout<<"ERROR EN CONNECT...\n"<<endl;
	}
	initialized = true;
//	try
//	{
//		sockaddr_in destAddr = getAddressStruct(host, port);
//
//		if (::connect(sockDesc, (sockaddr*) &destAddr, sizeof(destAddr))==-1)
//		{
//			throw cSocketException("Error en connect()");
//		}
//	}
//	catch(cSocketException &e)
//    {
//    	throw e;
//    }
}

Socket* Socket::listen(unsigned int port)
{
	int clienteDescriptor;
	clienteDescriptor = trEscuchar(port,&(this->conexion));
	this->sockDesc = this->conexion.locsock;
	//Si clienteDescriptor es mayor que 0 devuelve la direccion del cliente aceptado
	if ( clienteDescriptor < 0){
	     Sleep(500); // Esperamos 500 Milisegundos y…
	     Socket::listen(port); // Repetimos proceso
	}
	initialized = true;
	Socket* aux = new Socket(clienteDescriptor);
	aux->conexion.locsock = clienteDescriptor;
	return aux;
}

void Socket::send(const char* stream, unsigned int size)
{
//    if (::send(sockDesc, (raw_type*)stream, size, 0)==-1)
//    {
//        throw cSocketException("Error en send()");
//    }
}

int Socket::receive(char* stream, unsigned int size)
{
    int ret;
    recibir(&(this->conexion));
    initialized = false;

//    if ((ret = recv(sockDesc, (raw_type*)stream, size, 0))==-1)
//    {
//        throw cSocketException("Error en recv()");
//    }
    return ret;
}

//Socket* Socket::accept()
//{
//    int newSockDesc;
////    if ((newSockDesc = ::accept(sockDesc, NULL, 0))==-10)
////    {
////        throw cSocketException("Error en accept()");
////    }
//
//    return new Socket(newSockDesc);
//}

void Socket::shutdown()
{
	#ifdef WIN32
	::shutdown(sockDesc, '0x02');
	#else
	::shutdown(sockDesc, SHUT_RDWR);
	#endif
}

void Socket::close()
{
	if(sockDesc!=-1)
	{
		#ifdef WIN32
		::closesocket(sockDesc);
		#else
		::close(sockDesc);
		#endif
		sockDesc = -1;
	}
}

Socket::~Socket()
{
	this->shutdown();
	this->close();
}

void Socket::cleanUp()
{

//	if (WSACleanup()!=0)
//	{
//		throw cSocketException("Error en WSACleanup()");
//	}
	initialized = false;

}

CONEXION* Socket::getConexion()
{
	return &(conexion);
}

void Socket::setConexion(CONEXION c)
{
	memcpy(&conexion,&c,sizeof(CONEXION));
}

bool Socket::getInitialized()
{
	return initialized;
}
