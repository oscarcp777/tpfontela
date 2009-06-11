/*
 * Socket.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "Socket.h"
#include "cSocketException.h"
#include <iostream> 
#include <fstream> 

#define BLOCK 1024

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

void Socket::connect(char  *host, unsigned int port)
{
	if (trConectar(host,port,&this->conexion)==-1){
				std::cout<<"ERROR EN CONNECT...\n"<<endl;
	}
	this->sockDesc = this->conexion.locsock;
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

void Socket::listen(unsigned int port)
{
	int error;
	error = trEscuchar(port,&(this->conexion));
	if (error < RES_OK){
		throw cSocketException("aaa");
	}
	this->sockDesc = this->conexion.locsock;

	initialized = true;

}

int Socket::receiveFile(const char *path)
{
	
	#define BLOCK 1024 
	int size, ofs, nbytes = 0, block = BLOCK; 
	char pbuf[BLOCK]; 

    std::ofstream os(path, std::ios::binary); 

    recv(sockDesc, reinterpret_cast<char*>(&size), sizeof size, 0); 

    for(ofs = 0; block == BLOCK; ofs += BLOCK) 
    { 

        if(size - ofs < BLOCK) block = size - ofs; 

        nbytes += recv(sockDesc, pbuf, block, 0); 

        os.write(pbuf, block); 
    } 

    os.close(); 

	return nbytes; 
 

}

int Socket::sendFile(const char *path)
{
 
	std::ifstream is; 
	char pbuf[BLOCK]; 
	int size, ofs, nbytes = 0, block = BLOCK; 


    is.open (path, std::ios::binary ); 

    is.seekg (0, std::ios::end); 
    size = is.tellg(); 
    is.seekg (0, std::ios::beg); 

    ::send(sockDesc, reinterpret_cast<char*>(&size), sizeof size , 0); 

    for(ofs = 0; block == BLOCK; ofs += BLOCK) 
    { 

        if(size - ofs < BLOCK) block = size - ofs; 

            is.read(pbuf, block); 

			nbytes += ::send(sockDesc, pbuf, block, 0); 

    } 

    is.close(); 

	return nbytes; 
} 

	//    if (::send(sockDesc, (raw_type*)stream, size, 0)==-1)
//    {
//        throw cSocketException("Error en send()");
//    }
//}

void Socket::send(char* stream, unsigned int size)
{

	enviar(&(this->conexion),stream);		
//    if (::send(sockDesc, (raw_type*)stream, size, 0)==-1)
//    {
//        throw cSocketException("Error en send()");
//    }
}

int Socket::receive(char* stream, unsigned int size)
{
    int ret;
    if (recibir(&(this->conexion), NULL)<0)
		throw cSocketException("Error en recv()");
    initialized = false;

//    if ((ret = recv(sockDesc, (raw_type*)stream, size, 0))==-1)
//    {
//        throw cSocketException("Error en recv()");
//    }
    return ret;
}

Socket* Socket::accept()
{
	//Si clienteDescriptor es mayor que 0 devuelve la direccion del cliente aceptado

    int newSockDesc;
    newSockDesc = trAceptar(&(this->conexion));

    Socket* aux = new Socket(newSockDesc);
    aux->conexion.locsock = newSockDesc;
	aux->conexion.usuario = 1;
    return aux;
}

void Socket::shutdown()
{
	::shutdown(sockDesc, '0x02');

}

void Socket::close()
{
	if(sockDesc!=-1)
	{
		::closesocket(sockDesc);
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
