/*
 * Socket.h
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#ifndef SOCKET_H_
#define SOCKET_H_
#include <string>
#include <winsock.h>
#include <iostream>

#include "Utilidades.h"
#include "Transferencia.h"


class Socket {
public:
public:
	 	Socket();
    void connect(const char & host, unsigned int port);
    Socket *listen(unsigned int port);
    void send(const char *stream, unsigned int size);
    int receive(char *stream, unsigned int size);
    void shutdown();
    void close();
    virtual ~Socket();
    static void cleanUp();
    CONEXION* getConexion();
    void setConexion(CONEXION conexion);

protected:
    int sockDesc;
private:
    Socket(int sockDesc);
    CONEXION conexion;
    sockaddr_in getAddressStruct(const std::string & address, unsigned int port);
    static bool initialized;
};

#endif /* SOCKET_H_ */
