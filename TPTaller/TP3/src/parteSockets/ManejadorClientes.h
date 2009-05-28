/*
 * ManejadorClientes.h
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#ifndef MANEJADORCLIENTES_H_
#define MANEJADORCLIENTES_H_

#include <iostream>
#include <list>
#include <string>
#include "Thread.h"
#include "Socket.h"
#include "Juego.h"


class ManejadorClientes : public Thread{

public:
		ManejadorClientes(Socket* socketServer, int id, Socket* s, Juego* juego,
				std::list<Thread*>& clientes);
		~ManejadorClientes();

		int seguirCiclando;
	protected:
		virtual int process(void*);
	private:
        void enviarMensaje(const std::string& mensaje);
		void enviarAtodos(std::list<Thread*>& clientes,
					const std::string& mensaje);
		int obtenerListos(std::list<Thread*>& clientes);
		void pararTodos(std::list<Thread*>& clientes);
		void quitarCliente(std::list<Thread*>& clientes);

        Socket* socketServidor;
		Socket* socketComunicacion;
		int idCliente;
		Juego* juegoNuevo;
		std::list<Thread*>& todosLosClientes;
		std::string map_image;
		std::string map_info;
		int estaListo;
		int recibioMapa;

		std::string colorAleatorio();
};

#endif /* MANEJADORCLIENTES_H_ */
