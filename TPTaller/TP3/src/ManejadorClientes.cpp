/*
 * ManejadorClientes.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "ManejadorClientes.h"
#include "archivoTexto.h"
#include "Define.h"
#include "CalculosMatematicos.h"

ManejadorClientes::ManejadorClientes(Socket* socketServer, int id, Socket* s, Juego* juego,
		std::list<Thread*>& clientes):
			socketServidor(socketServer), socketComunicacion(s), juegoNuevo(juego),
			todosLosClientes(clientes){
			this->estaListo = 0;
			this->recibioMapa = 0;
			seguirCiclando = 0;
			idCliente = id;
		}

		ManejadorClientes::~ManejadorClientes(){
			/*Cierra el socket que usaba para hablar con su cliente*/
			delete(socketComunicacion);
			/*Y si es el cliente 1 (el que inició el server) pide además cerrar el socket
	que el servidor usa para aceptar conexiones. Esto genera en el Servidor que
	se destrabe del accept, si estaba en ese lugar (o está allí, o está ciclando
	esperando que los clientes terminen de correr)*/
			if (this->idCliente == 1)
				delete(socketServidor);
			if(DEBUG_DESTRUCTOR==1)
					std::cout<<" entro al destructor de ManejadorClientes"<<endl;

		}


		int ManejadorClientes :: process(void* arg){
			Escenario* escenario=juegoNuevo->getEscenario();
			seguirCiclando = 1;
			std::string bufferStr = "";

			int bytesRecibidos;
			std::string buffer;
			char msjIngresado[TAM_MSJ];
			char *pmsjIngresado = msjIngresado;
			char leyenda[TAM_MSJ];
			char * pLeyenda = leyenda;
			char datosRecividos[30];
			char* pDatosRecividos = datosRecividos;
			std::string msj;

			int tipoBonus;


			while (seguirCiclando == 1){

				memset(pDatosRecividos,0,sizeof(char)*30);
				socketComunicacion->receive(pDatosRecividos,30);
				msj = pDatosRecividos;

				if(msj.find("QUIT")==0){
					quitarCliente(todosLosClientes);
					juegoNuevo->setJuegoCancelado(true);
					Sleep(1000);
					enviarAtodos(this->todosLosClientes,"FINJUEGO\n");
					seguirCiclando = 0;
					this->stopear();
				}
				else if(msj.find("PAD1 ABAJO") == 0){
						juegoNuevo->getEscenario()->getPadCliente1()->bajar_y();
					
					}
				else if(msj.find("PAD1 ARRIBA") == 0){	
						juegoNuevo->getEscenario()->getPadCliente1()->subir_y();
					}
					//string pPosicion = msj.substr(msj.find(" ")+1,msj.size());
					//juegoNuevo->getEscenario()->getPadCliente1()->setY(atoi(pPosicion.c_str()));				
				else if(msj.find("PAD2 ABAJO") == 0){
						juegoNuevo->getEscenario()->getPadCliente2()->bajar_y();
					
					}
				else if(msj.find("PAD2 ARRIBA") == 0){	
						juegoNuevo->getEscenario()->getPadCliente2()->subir_y();
					}
					//string pPosicion = msj.substr(msj.find(" ")+1,msj.size());
					//juegoNuevo->getEscenario()->getPadCliente2()->setY(atoi(pPosicion.c_str()));
								
				else if(msj.find("SOLTAR_TEJO")==0){
					juegoNuevo->getEscenario()->getTejo()->setMover(true);
				}



			}


			delete(this);
			return 0;


}

		//Envia los recursos necesarios a los clientes


		//Toma la lista de clientes y un string, itera la lista y envia el string
void ManejadorClientes::enviarAtodos(std::list<Thread*>& clientes,
				const std::string& mensaje)
{
			if (clientes.size()>0)
			for (std::list<Thread*>::iterator it = clientes.begin();
			it!= clientes.end(); ++it){
				if ((*it)->running() == true)
					((ManejadorClientes*)(*it))->enviarMensaje(mensaje);
			}
}



		/*Llama al send para enviar a traves del socket un string al cliente correspondiente
a ese socket*/
void ManejadorClientes::enviarMensaje(const std::string& mensaje)
		{
			socketComunicacion->send((char*)mensaje.data());

		}

int ManejadorClientes::enviarArchivo(const std::string& mensaje)
		{
			return socketComunicacion->sendFile((char*)mensaje.data());

		}

		/*Acumula en cantListos para saber cuantos clientes enviaron READY al Servidor.
Cuando cantListos == clientes.size() todos están listos y el juego comienza*/
/*int ManejadorClientes::obtenerListos(std::list<Thread*>& clientes)
		{
			int cantListos = 0;
			for (std::list<Thread*>::iterator it = clientes.begin();
			it != clientes.end(); ++it){
				if (((ManejadorClientes*)(*it))->estaListo == 1){
					cantListos++;}
			}
			return cantListos;
		}
*/
		/*Itera todos los clientes, indicandoles a cada uno que deben dejar de
ciclar*/
void ManejadorClientes::pararTodos(std::list<Thread*>& clientes)
		{
			for (std::list<Thread*>::iterator it = clientes.begin();
			it != clientes.end(); ++it){
				ManejadorClientes* clienteActual = (ManejadorClientes*)(*it);
				clienteActual->seguirCiclando = 0;
			}
			/*La lista de los clientes será limpiada por el servidor mas tarde*/
		}

		/*Busca a un cliente en la lista de clientes, y le indica que deje de
ciclar, además de quitarlo de la lista. Usado de esta manera para permitir
abrir un slot para que un nuevo jugador se una a la partida*/
void ManejadorClientes::quitarCliente(std::list<Thread*>& clientes)
		{
			int encontrado = 0;
			int fin = 0;
			std::list<Thread*>::iterator it = clientes.begin();
			while ((encontrado == 0)&&(fin == 0)){
				if (it != clientes.end()){
					ManejadorClientes* clienteActual =
						(ManejadorClientes*)(*it);
					if (clienteActual->idCliente == this->idCliente){
						encontrado = 1;
						clientes.erase(it);
						clienteActual->seguirCiclando = 0;
					}
					else ++it;
				}
				else fin = 1;
			}
		}


