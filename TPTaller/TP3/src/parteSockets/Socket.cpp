/*
 * Socket.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "Socket.h"

#include <winsock2.h>
typedef char raw_type;
bool Socket::initialized = false;

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
}

void Socket::connect(const string& host, unsigned int port)
{
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

void Socket::listen(unsigned int port)
{
	int a;
	a = trEscuchar(port,&(this->conexion));

	if ( a == -1){
	     Sleep(500); // Esperamos 500 Milisegundos y…
	     Socket::listen(port); // Repetimos proceso
	}
	initialized = true;

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


//    if ((ret = recv(sockDesc, (raw_type*)stream, size, 0))==-1)
//    {
//        throw cSocketException("Error en recv()");
//    }
    return ret;
}

Socket* Socket::accept()
{
    int newSockDesc;
//    if ((newSockDesc = ::accept(sockDesc, NULL, 0))==-10)
//    {
//        throw cSocketException("Error en accept()");
//    }

    return new Socket(newSockDesc);
}

void Socket::shutdown()
{
	#ifdef WIN32
	::shutdown(sockDesc, SD_BOTH);
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
	#ifdef WIN32
//	if (WSACleanup()!=0)
//	{
//		throw cSocketException("Error en WSACleanup()");
//	}
	initialized = false;
	#endif
}
