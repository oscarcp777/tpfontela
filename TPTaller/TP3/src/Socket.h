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
    void connect(char *host, unsigned int port);
    void listen(unsigned int port);
    Socket* accept();
    void send(char *stream);
	int sendFile(const char *path);
	int receiveFile(const char *path);
    int receive(void* dato,int size);
    void shutdown();
    void close();
    virtual ~Socket();
    void cleanUp();
    CONEXION* getConexion();
    void setConexion(CONEXION conexion);
    bool getInitialized();


protected:
    int sockDesc;
private:
    Socket(int sockDesc);
    CONEXION conexion;
    bool initialized;
};

#endif /* SOCKET_H_ */
