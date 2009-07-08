/*
 * Socket.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "Socket.h"
#include "Define.h"
#include "cSocketException.h"
#include <iostream>
#include <fstream>

#define BLOCK 1024

typedef char raw_type;
//bool Socket::initialized = false;

using namespace std;



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

void Socket::send(char* stream)
{
	::send(this->sockDesc,stream,sizeof(char)*strlen((char*)stream),0);
	/*if (enviar(&(this->conexion),stream)<0)
	{
		 throw cSocketException("Error en send()");
	}*/
}

int Socket::receive(void* dato, int size)
{
    int ret;
    ret = ::recv(this->sockDesc,(char*)dato,sizeof(char)*size,0);
    if (ret < 0)
		throw cSocketException("Error en recv()");
    initialized = false;


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
		trCerrarConexion(&(this->conexion));
		sockDesc = -1;
	}
}

Socket::~Socket()
{
	this->shutdown();
	this->close();
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Socket"<<std::endl;

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
