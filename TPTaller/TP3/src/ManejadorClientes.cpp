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
			/*Y si es el cliente 1 (el que inici� el server) pide adem�s cerrar el socket
	que el servidor usa para aceptar conexiones. Esto genera en el Servidor que
	se destrabe del accept, si estaba en ese lugar (o est� all�, o est� ciclando
	esperando que los clientes terminen de correr)*/
			if (this->idCliente == 1)
				delete(socketServidor);
		}

		void ManejadorClientes ::posicionTejo(char* pEnvioInt){

			char auxX[20];
			char auxY[20];
			char* pauxX = auxX;
			char* pauxY = auxY;


			memset(pauxX,0,sizeof(char)*20);
			memset(pauxY,0,sizeof(char)*20);
			memset(pEnvioInt,0,sizeof(char)*40);
			strcat(pEnvioInt,"TEJO ");
			itoa(juegoNuevo->getEscenario()->getTejo()->getX(),pauxX,10);
			itoa(juegoNuevo->getEscenario()->getTejo()->getY(),pauxY,10);
			strcat(pEnvioInt,pauxX);
			strcat(pEnvioInt," ");
			strcat(pEnvioInt,pauxY);
			strcat(pEnvioInt,"\n");


		}

		void ManejadorClientes::puntajes(char* pPuntajes){

			char aux1[20];
			char aux2[20];
			char* paux1 = aux1;
			char* paux2 = aux2;


			memset(paux1,0,sizeof(char)*20);
			memset(paux2,0,sizeof(char)*20);
			memset(pPuntajes,0,sizeof(char)*40);
			strcat(pPuntajes,"PUNTAJE ");
			itoa(juegoNuevo->getEscenario()->getPadCliente1()->getPuntaje()->getCantPuntosJugador(),paux1,10);
			itoa(juegoNuevo->getEscenario()->getPadCliente2()->getPuntaje()->getCantPuntosJugador(),paux2,10);
			strcat(pPuntajes,paux1);
			strcat(pPuntajes," ");
			strcat(pPuntajes,paux2);
			strcat(pPuntajes,"\n");


		}

		void ManejadorClientes::ganador(char* pGanador){

			char aux1[20];
			char* paux1 = aux1;

			memset(paux1,0,sizeof(char)*20);
			memset(pGanador,0,sizeof(char)*40);
			strcat(pGanador,"GANADOR ");
			//si los goles el jugador 1 son mas que los del jugador 2 concatena STRING GANADOR 1
			if(juegoNuevo->getEscenario()->getPadCliente1()->getCantGoles() > juegoNuevo->getEscenario()->getPadCliente2()->getCantGoles())
				itoa(1,paux1,10);
			else //sino concatena STRING GANADOR 2
				itoa(2,paux1,10);

			strcat(pGanador,paux1);
			strcat(pGanador,"\n");
		}

		void ManejadorClientes::bonus(char* pMensBonus,int tipoBonus, std::string idFigura){

			char aux1[20];
			char* paux1 = aux1;
			char aux2[20];
			char* paux2 = aux2;

			memset(paux1,0,sizeof(char)*20);
			memset(paux2,0,sizeof(char)*20);
			memset(pMensBonus,0,sizeof(char)*40);
			strcat(pMensBonus,"BONUS ");
			itoa(tipoBonus,paux1,10);
			
			strcat(pMensBonus,paux1);
			strcat(pMensBonus," ");
			strcat(pMensBonus,idFigura.c_str());
			strcat(pMensBonus,"\n");
		}

		int ManejadorClientes :: process(void* arg){
			Escenario* escenario=juegoNuevo->getEscenario();
			seguirCiclando = 1;
			std::string bufferStr = "";
			std::string idFigura;
			int bytesRecibidos;
			std::string buffer;
			char msjIngresado[TAM_MSJ];
			char *pmsjIngresado = msjIngresado;
			char leyenda[TAM_MSJ];
			char * pLeyenda = leyenda;
			char envioInt[40];
			char* pEnvioInt = envioInt;
			char puntajes[40];
			char* pPuntajes = puntajes;
			char ganador[40];
			char* pGanador = ganador;
			char datosRecividos[30];
			char mensBonus[40];
			char* pMensBonus = mensBonus;
			char* pDatosRecividos = datosRecividos;
			std::string msj;
			int puntosPad1, puntosPad2,posXPad1,posXPad2,posYPad1,posYPad2;
			int tipoBonus;
		
			if (this->socketComunicacion->getConexion()->usuario == 0){

				//loading(todosLosClientes,"loading1.txt");


				//loading(todosLosClientes,"loading2.txt");
				sleep(6000);
				asignarNumeroClientes(this->todosLosClientes);
				escenario->servidorInicializarListaBonus();
				enviarAtodos(this->todosLosClientes,"INICIADO\n");

			}
			while (seguirCiclando == 1){

				if (this->socketComunicacion->getConexion()->usuario == 0){

					if(!juegoNuevo->cancelado() && juegoNuevo->getEstado().compare("NIVEL_TERMINADO")!=0 && juegoNuevo->getEstado().compare("JUEGO_TERMINADO")!=0){
						Sleep(15);
						juegoNuevo->update();


						if (juegoNuevo->getEstado().compare("CORRIENDO")== 0){ //envia las posiciones solo si esta corriendo (no hay goles ni nada)

							//se forma la cadena "INT posX posY" con las posiciones del tejo
							this->posicionTejo(pEnvioInt);
							enviarAtodos(this->todosLosClientes,pEnvioInt);

							if((CalculosMatematicos::ramdom(100)) <10 && escenario->getBonusActual()==NULL){
							//Hago un random entre 0 y 100 si el numero es menor a 15 y no hay bonus actual aparece bonus
							 Bonus* bonus = juegoNuevo->getNuevoBonusRandom();
							 escenario->shuffleListFiguras();
							 tipoBonus = bonus->getTipoBonus();
							 escenario->setBonusActual(bonus);
							 Figura* figura= *(escenario->iteratorListaFiguras());
							 figura->setTieneBonus(true);
							 idFigura = figura->getId();
							 escenario->setFiguraConBonus(figura);
							 //se forma la cadena "BONUS tipoBonus idFigura" tipoBonus es un int
							 this->bonus(pMensBonus,tipoBonus,idFigura);
							 enviarAtodos(this->todosLosClientes,pMensBonus);
							//******************************************************
							}
						}

						else if(juegoNuevo->getEstado().compare("GOL")== 0){
							this->puntajes(pPuntajes);//se forma la cadena "STRING PUNTAJE puntosJug1 puntosJug2"
							enviarAtodos(this->todosLosClientes,pPuntajes);

							if(juegoNuevo->getTejosRestantes() == 0){
								//si no quedan tejos por jugar en el nivel, el nivel esta terminado y incrementa el nivel
								juegoNuevo->setEstado("NIVEL_TERMINADO");
								juegoNuevo->incrementarNivel();
								
								if(juegoNuevo->getNumeroNivel() == CANT_NIVELES+1){
									juegoNuevo->setEstado("JUEGO_TERMINADO");
								}

							}
							else {//si quedan tejos el estado del juego vuelve a ser "CORRIENDO"
								juegoNuevo->setEstado("CORRIENDO");
							}

						}

						if(escenario->getTejo()->getChocoFiguraConBonus() && juegoNuevo->getEstado().compare("CORRIENDO")== 0){
							std::cout<<"choco figura con bonus "<<escenario->getTejo()->getChocoFiguraConBonus()<<endl;
							escenario->getBonusActual()->aplicar();
							escenario->setBonusActual(NULL);
							escenario->getFiguraConBonus()->setTieneBonus(false);
							escenario->setFiguraConBonus(NULL);
							escenario->getTejo()->setChocoFiguraConBonus(false);
							enviarAtodos(this->todosLosClientes,"APLICAR_BONUS "+escenario->getTejo()->obtenerUltimaColisionPad()+"\n");
							
						}

					}
					else{//entra a este else si el juego esta en estado=JUEGO_TERMINADO o NIVEL_TERMINADO (es decir NO esta CORRIENDO)

						//TODO Si se termino el juego (fin de todos los niveles) se envia el ganador a los jugadores y se finaliza la aplicacion
						if(juegoNuevo->getEstado().compare("JUEGO_TERMINADO")==0){
							this->ganador(pGanador);
							std::cout<<"JUEGO_TERMINADO envia: "<<pGanador<<endl;
							enviarAtodos(this->todosLosClientes,pGanador);
							seguirCiclando = 0;
						}
						//si termino el nivel envio las imagenes y archivos a los clientes y vuelvo el estado del juego a CORRIENDO
						else if(juegoNuevo->getEstado().compare("NIVEL_TERMINADO") == 0){
							std::cout<<"ENTRO A NIVEL_TERMINADO"<<endl;
							enviarAtodos(this->todosLosClientes,"NIVEL_TERMINADO\n");
							std::cout<<"despues de nivel terminado"<<endl;
							juegoNuevo->setTejosRestantes(7);
							//guardo los puntos y las posiciones. los seteo luego de cargarArchivo, poruqe este metodo los borra
							puntosPad1 = escenario->getPadCliente1()->getPuntaje()->getCantPuntosJugador();
							puntosPad2 = escenario->getPadCliente2()->getPuntaje()->getCantPuntosJugador();
							posXPad1 = escenario->getPadCliente1()->getX();
							posYPad1 = escenario->getPadCliente1()->getY();
							posXPad2 = escenario->getPadCliente2()->getX();
							posYPad2 = escenario->getPadCliente2()->getY();
							
							
							
							escenario->setBonusActual(NULL);
							escenario->setFiguraConBonus(NULL);
							escenario->getTejo()->setChocoFiguraConBonus(false);
													
							escenario->borrarListaFiguras();
							escenario->borrarListaTexturas();						
							
							
							escenario->cargarArchivo("nivel"+juegoNuevo->getNumeroNivelEnString()+".xml");
							Sleep(4000);
							escenario->getPadCliente1()->getPuntaje()->setCantPuntosJugador(puntosPad1);
							escenario->getPadCliente2()->getPuntaje()->setCantPuntosJugador(puntosPad2);
							escenario->getPadCliente1()->setX(posXPad1);
							escenario->getPadCliente1()->setY(posYPad1);
							escenario->getPadCliente2()->setX(posXPad2);
							escenario->getPadCliente2()->setY(posYPad2);
							escenario->getTejo()->setY(escenario->getPadCliente2()->getY()+escenario->getPadCliente2()->getAltura()/2);
							escenario->getTejo()->setX(escenario->getPadCliente2()->getX()+escenario->getPadCliente2()->getBase()+escenario->getTejo()->getRadio());
							escenario->getTejo()->getDireccion()->setFi(PI/4);
							juegoNuevo->setEstado("CORRIENDO");
							
						}

					}
				}
				else{
					memset(pDatosRecividos,0,sizeof(char)*30);
					socketComunicacion->receive(pDatosRecividos,30);
					msj = pDatosRecividos;

					if(msj.find("QUIT")==0){
						quitarCliente(todosLosClientes);
						juegoNuevo->setJuegoCancelado(true);
						enviarAtodos(this->todosLosClientes,"FINJUEGO\n");
						seguirCiclando = 0;
					}
					else if(msj.find("PAD1")==0)
					{
						string pPosicion = msj.substr(msj.find(" ")+1,msj.size());
						juegoNuevo->getEscenario()->getPadCliente1()->setY(atoi(pPosicion.c_str()));
						enviarAtodos(this->todosLosClientes,msj+"\n");						
					}
					else if(msj.find("PAD2")==0)
					{
						string pPosicion = msj.substr(msj.find(" ")+1,msj.size());
						juegoNuevo->getEscenario()->getPadCliente2()->setY(atoi(pPosicion.c_str()));
						enviarAtodos(this->todosLosClientes,msj+"\n");						

					}


				}
			}



			/*Cuando el ManejadorClientes sale del ciclo de recepci�n es porque no
    recibir� mas mensajes (porque el juego termin� o alguien sali� de la partida),
    en ese caso, pide join() (para que el Servidor sepa que este cliente no corre mas),
    y luego el delete(this) que causa que el socket (y el de accept del Servidor si este cliente
    es el que inici� el servidor) se liberen*/
			delete(this);
			return 0;


}

		//Envia los recursos necesarios a los clientes
void ManejadorClientes::loading(std::list<Thread*>& clientes, std::string archivo){
			std::cout<<"ENTRO A LOADING SERVIDOR"<<endl;
			int nbytes;
			int i = 0;
			char aux1[20];
			char cantArchivos[20];
			char nombreArchivo[200];
			char *paux1= aux1;
			char *pCantArchivos= cantArchivos;
			char *pNombreArchivo = nombreArchivo;
			memset(paux1,0,sizeof(char)*20);
			memset(pCantArchivos,0,sizeof(char)*20);


			std::list<std::string> listaArchivos;  //todas las imagenes a cargar
			string linea = " ";


			ArchivoTexto archivoNivel(archivo);
			archivoNivel.leerLinea(linea);

			while(linea.compare("FIN") != 0){
				std::cout<<linea<<endl;
				listaArchivos.push_back(linea);
				archivoNivel.leerLinea(linea);
			}

			std::list<std::string>::iterator iterArchivos = listaArchivos.begin();

			char* cadena;
			itoa(listaArchivos.size(),paux1,10);
			std::cout<<"listaArchivos.size() "<<listaArchivos.size()<<endl;
			strcat(pCantArchivos,paux1);
			for (std::list<Thread*>::iterator it = this->todosLosClientes.begin();
			it!= this->todosLosClientes.end(); ++it){
				if ((*it)->running() == true){
					((ManejadorClientes*)(*it))->enviarMensaje(pCantArchivos);
					while (listaArchivos.size()> i){
						sleep(500);//este sleep es entre envio de imagenes (sin este sleep pincha), puede ser mas chico (probar valores) PUEDE QUE EN RED NECESITE MAS TIEMPO
						memset(pNombreArchivo,0,sizeof(char)*200);
						cadena = (char*)(*iterArchivos).data();
						std::cout << "cadena: " << cadena<< std::endl;
						strcat(pNombreArchivo,cadena);
						((ManejadorClientes*)(*it))->enviarMensaje(pNombreArchivo);
						std::cout << "Nombre Archivo " << pNombreArchivo<< std::endl;
						nbytes =((ManejadorClientes*)(*it))->socketComunicacion->sendFile(cadena);
						std::cout << "Bytes enviados: " << nbytes << std::endl;
						iterArchivos++;
						i++;

					}
					i = 0;
					iterArchivos = listaArchivos.begin();

				}
			}


		}

		//Toma la lista de clientes y un string, itera la lista y envia el string
void ManejadorClientes::enviarAtodos(std::list<Thread*>& clientes,
				const std::string& mensaje)
		{
			for (std::list<Thread*>::iterator it = clientes.begin();
			it!= clientes.end(); ++it){
				if ((*it)->running() == true)
					((ManejadorClientes*)(*it))->enviarMensaje(mensaje);
			}
		}

void ManejadorClientes::asignarNumeroClientes(std::list<Thread*>& clientes){
			std::string numeroCliente1 = "1";
			std::string numeroCliente2 = "2";
			int i=1;
			for (std::list<Thread*>::iterator it = clientes.begin();
			it!= clientes.end(); ++it){
				if(i == 1){
					if ((*it)->running() == true)
						((ManejadorClientes*)(*it))->enviarMensaje(numeroCliente1);
					i++;
				}
				else{
					if ((*it)->running() == true)
						((ManejadorClientes*)(*it))->enviarMensaje(numeroCliente2);
				}
			}
		}

		/*Llama al send para enviar a traves del socket un string al cliente correspondiente
a ese socket*/
void ManejadorClientes::enviarMensaje(const std::string& mensaje)
		{
			socketComunicacion->send((char*)mensaje.data());

		}

		/*Acumula en cantListos para saber cuantos clientes enviaron READY al Servidor.
Cuando cantListos == clientes.size() todos est�n listos y el juego comienza*/
int ManejadorClientes::obtenerListos(std::list<Thread*>& clientes)
		{
			int cantListos = 0;
			for (std::list<Thread*>::iterator it = clientes.begin();
			it != clientes.end(); ++it){
				if (((ManejadorClientes*)(*it))->estaListo == 1){
					cantListos++;}
			}
			return cantListos;
		}

		/*Itera todos los clientes, indicandoles a cada uno que deben dejar de
ciclar*/
void ManejadorClientes::pararTodos(std::list<Thread*>& clientes)
		{
			for (std::list<Thread*>::iterator it = clientes.begin();
			it != clientes.end(); ++it){
				ManejadorClientes* clienteActual = (ManejadorClientes*)(*it);
				clienteActual->seguirCiclando = 0;
			}
			/*La lista de los clientes ser� limpiada por el servidor mas tarde*/
		}

		/*Busca a un cliente en la lista de clientes, y le indica que deje de
ciclar, adem�s de quitarlo de la lista. Usado de esta manera para permitir
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

		/*Funci�n que devuelve un color aleatorio en un string de formato "FF005F"*/
		//std::string ManejadorClientes::colorAleatorio(){
		//	srand(time(NULL));
		//	std::stringstream color;
		//	int valorAleatorio;
		//	for (int i = 0; i < 3; ++i){
		//		valorAleatorio = rand()%255;
		//		if (valorAleatorio > 15)
		//			color << std::uppercase << std::hex << valorAleatorio;
		//		else color << "0" << std::uppercase << std::hex << valorAleatorio;
		//	}
		//	return color.str();
		//}
