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

#include "Utilidades.h"
#include "Transferencia.h"


class Socket {
public:
public:
	 	Socket();
	 	/* Client: Connectarse a un server */
	 	void connect(const char& host, unsigned int port);
	 	/* Server: Escuchar clientes */
	 	Socket* listen(unsigned int port);
	 	/* Client/Server: Enviar datos */
	 	void send(const char* stream, unsigned int size);
	 	/* Client/Server: Recibir datos */
	 	int receive(char* stream, unsigned int size);
	 	/* Server: Aceptar coneccion */
	 	//Socket* accept();
	 	/* Client/Server: Deshabilita el send/recv */
	 	void shutdown();
	 	/* Client/Server: Cierra el socket */
	 	void close();
	 	/* Client/Server: Cierra el socket, libera recursos de la dll */
	 	virtual ~Socket();
	 	/* Client/Server: Libera recursos de la dll (solo windows) */
	 	static void cleanUp();

	 protected:
	 	int sockDesc;

	 private:
	 	/* Server: Crea un socket con un SD dado */
	 	Socket(int sockDesc);

	 	CONEXION conexion;
	 	/* Pasando una direccion y puerto me devuelve la struct necesaria para el connect() */
	 	sockaddr_in getAddressStruct(const std::string& address, unsigned int port);
	 	/* Flag que indica si ya fue hecha la etapa de init de sockets en WIN32 */
	 	static bool initialized;
};

#endif /* SOCKET_H_ */
