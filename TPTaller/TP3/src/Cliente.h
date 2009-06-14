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

class Cliente {
public:
        Cliente();
        // Se conecta al servidor y lanza los threads correspondientes
        void start(char*  host, int port);
        // Envia el mensaje al "servidor proxy" (lo encola para enviar)
        void send(std::string msg);
        // Obtiene un mensaje del "servidor proxy" (lo desencola de los recibidos)
		std::string get();
        // Chequea si hay instrucciones encoladas
        bool haveInstructions();
        // Chequea el estado del servidor (conectado, no conectado, etc)
        int getStatus();
        // Setea el estado del servidor
        void setStatus(int status);
        // Obtiene el porcentaje descargado del fichero (en caso que se este bajando uno)
        float getDownloadedPercent();
        // Resetea el porcentaje descargado
        void clearDownloaded();
        // Detiene la ejecucion del "server proxy" (cierra el socket y joinea los threads)
        void stop();
        ~Cliente();

    private:
		int status;
		Socket sock;
		cSender sender;
		cReceiver receiver;
    	Cliente(const Cliente&);
    	Cliente& operator=(const Cliente&);
    	CONEXION conexion;
};

#endif /* CLIENTE_H_ */
