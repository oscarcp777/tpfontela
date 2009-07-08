/*
 * Cliente.h
 *
 *  Created on: 29/05/2009
 *      Author: Programadores
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "cSender.h"
#include "cReceiver.h"
#include "Socket.h"
#include <string>
#include "Escenario.h"

class Cliente {
public:
        Cliente();
        // Se conecta al servidor y lanza los threads correspondientes
        void start(char*  host, int port);
        // Obtiene un mensaje del "servidor proxy" (lo desencola de los recibidos)
		std::string get();
        // Chequea el estado del servidor (conectado, no conectado, etc)
        int getStatus();
        // Setea el estado del servidor
        void setStatus(int status);
        void stop();
		void loading(Socket* s);
		~Cliente();

    private:
		int status;
		Socket sock;
		cSender sender;
		cReceiver receiver;
    	Cliente(const Cliente&);
    	Cliente& operator=(const Cliente&);
    	CONEXION conexion;
		bool finLoading;
};

#endif /* CLIENTE_H_ */
