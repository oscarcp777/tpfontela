/*
 * ManejadorClientes.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "ManejadorClientes.h"

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
}

int ManejadorClientes :: process(void* arg){
	seguirCiclando = 1;
	std::string bufferStr = "";
	int bytesRecibidos;
	std::string buffer;
	char msjIngresado[TAM_MSJ];
	char *pmsjIngresado = msjIngresado;
	char leyenda[TAM_MSJ];
	char * pLeyenda = leyenda;


	if (this->socketComunicacion == this->socketServidor){
		pLeyenda = "INGRESE MENSAJE: (para salir QUIT)";
		ingresoMensaje(pmsjIngresado,pLeyenda);
		enviarAtodos(this->todosLosClientes,pmsjIngresado);
	}
//	bytesRecibidos = socketComunicacion->receive((char*)buffer.data(), 258);
//	while (seguirCiclando == 1){
//	   /*Crea el buffer para receive una linea del cliente*/
//	   std::string lineaRecibida;
//	   std::string lineaAEnviar;
//	   std::string buffer;
//	   buffer.resize(258);
//	   std::string numeroCliente;
//	   numeroCliente = itoa(this->idCliente);
//	   int bytesRecibidos;
//
//	   bytesRecibidos = socketComunicacion->receive((char*)buffer.data(), 258);
//	   if (bytesRecibidos == 0){
//	   	/*Si no recibo bytes eso significa que al socket que usamos para
//		comunicarnos con este cliente le pasó algo, por lo que se considera como
//		que hubiera salido del juego (como si hubiera mandado un mensaje de QUIT)*/
//
//		/*Primero vemos en que etapa está el juego. Si está arrancado
//		o no*/
//		if (juegoNuevo->arrancado() == true){
//			/*Si el juego está arrancado, cualquiera que pida un
//			QUIT genera que el juego deba suspenderse*/
//			juegoNuevo->cancelar();
//			lineaAEnviar += "QUIT ";
//			lineaAEnviar += numeroCliente.str();
//			lineaAEnviar += "\r\n";
//			enviarAtodos(todosLosClientes, lineaAEnviar);
//			pararTodos(todosLosClientes);
//		}
//		else {
//			/*Si el juego no está arrancado (está en la fase previa
//			donde los jugadores se van uniendo), el juego solo se
//			suspende en el caso que el que pide QUIT es el jugador
//			que inició el server*/
//			if (this->idCliente == 1){
//				/*Suspendemos...*/
//				juegoNuevo->cancelar();
//				lineaAEnviar += "QUIT ";
//				lineaAEnviar += numeroCliente.str();
//				lineaAEnviar += "\r\n";
//				enviarAtodos(todosLosClientes, lineaAEnviar);
//				pararTodos(todosLosClientes);
//			}
//			else {
//				/*En este caso no se suspende el juego, sino
//				que solo se quita al jugador en cuestión*/
//				lineaAEnviar += "QUIT ";
//				lineaAEnviar += numeroCliente.str();
//				lineaAEnviar += "\r\n";
//				enviarAtodos(todosLosClientes, lineaAEnviar);
//				juegoNuevo->quitarJugador(this->idCliente);
//				quitarCliente(todosLosClientes);
//			}
//		}
//	   }
//	   else {
//        //Pudimos recibir algunos bytes del cliente
//		bufferStr += buffer;
//		unsigned int i;
//		/*Se cicla y se va armando el comando que el cliente nos envía. Busca el
//		\r\n que determina separación entre comandos (ya que el cliente podría estar
//		enviando varios comandos y el receive formaría el string con los comandos
//		pegados)*/
//		while ((i = bufferStr.find("\r\n")) != std::string::npos){
//			lineaRecibida = bufferStr.substr(0,i);
//			bufferStr = bufferStr.substr(i+2);
//
//			int offset = lineaRecibida.find(" ",0);
//			int offset2 = lineaRecibida.find('\0',0);
//
//			/*Mensaje 1--INFO map_image,map_info*/
//			if (lineaRecibida.find("INFO",0) != std::string::npos){
//				int offset3 = lineaRecibida.find(",",offset+1);
//				/*Obtiene el nombre de la imagen y del archivo de datos*/
//				map_image = lineaRecibida.substr(offset+1,offset3-(offset+1));
//				map_info = lineaRecibida.substr(offset3+1,offset2-(offset3+1));
//				/*Y luego se los pasa al juego, que se encargará de verificar que
//				esté todo en orden*/
//				juegoNuevo->setear(this->idCliente, map_info,
//								map_image);
//			}
//
//			/*Mensaje 2--JOIN nick*/
//			else if (lineaRecibida.find("JOIN",0) != std::string::npos){
//				std::string color = colorAleatorio();
//				/*Pide al juego agregar al jugador (con mismo id al del cliente),
//				luego analizamos si el resultado fue exitoso o no*/
//				int result = juegoNuevo->agregarJugador(this->idCliente,
//				lineaRecibida.substr(offset+1,offset2-(offset+1)),
//				color);
//				if (result == 0){//JOIN exitoso
//					lineaAEnviar += "JOIN ";
//					lineaAEnviar += lineaRecibida.substr(offset+1,
//							offset2-(offset+1));
//					lineaAEnviar += ",";
//					lineaAEnviar += color;
//					lineaAEnviar += ",";
//					lineaAEnviar += numeroCliente.str();
//					lineaAEnviar += "\r\n";
//					/*Emviamos a todos los clientes que se unió un jugador*/
//					enviarAtodos(todosLosClientes, lineaAEnviar);
//				}
//				else if (result == 3){//El jugador ya existe
//					enviarMensaje("NICK_IN_USE\r\n");
//					quitarCliente(todosLosClientes);
//				}
//			}
//
//			/*Mensaje 3--QUIT*/
//			else if (lineaRecibida.find("QUIT",0) != std::string::npos){
//				/*Suponemos que si se llama a QUIT el jugador hizo JOIN antes*/
//
//				/*Primero vemos en que etapa está el juego. Si está arrancado
//				o no*/
//				if (juegoNuevo->arrancado() == true){
//					/*Si el juego está arrancado, cualquiera que pida un
//					QUIT genera que el juego deba suspenderse*/
//					juegoNuevo->cancelar();
//					lineaAEnviar += "QUIT ";
//					lineaAEnviar += numeroCliente.str();
//					lineaAEnviar += "\r\n";
//					enviarAtodos(todosLosClientes, lineaAEnviar);
//					pararTodos(todosLosClientes);
//				}
//				else {
//					/*Si el juego no está arrancado (está en la fase previa
//					donde los jugadores se van uniendo), el juego solo se
//					suspende en el caso que el que pide QUIT es el jugador
//					que inició el server*/
//					if (this->idCliente == 1){
//						/*Suspendemos...*/
//						juegoNuevo->cancelar();
//						lineaAEnviar += "QUIT ";
//						lineaAEnviar += numeroCliente.str();
//						lineaAEnviar += "\r\n";
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//						pararTodos(todosLosClientes);
//					}
//					else {
//						/*En este caso no se suspende el juego, sino
//						que solo se quita al jugador en cuestión*/
//						lineaAEnviar += "QUIT ";
//						lineaAEnviar += numeroCliente.str();
//						lineaAEnviar += "\r\n";
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//						juegoNuevo->quitarJugador(this->idCliente);
//						quitarCliente(todosLosClientes);
//					}
//				}
//			}
//
//			/*Mensaje 4--CHAT text*/
//			else if (lineaRecibida.find("CHAT",0) != std::string::npos){
//				lineaAEnviar += "CHAT ";
//				lineaAEnviar += numeroCliente.str();
//				lineaAEnviar += ",";
//				lineaAEnviar += lineaRecibida.substr(offset+1,
//							offset2-(offset+1));
//				lineaAEnviar += "\r\n";
//				/*Envia a todos los clientes el mismo string que recibió el
//				ClientHandler (es decir, el servidor)*/
//				enviarAtodos(todosLosClientes, lineaAEnviar);
//			}
//
//			/*Mensaje 5--INIT*/
//			else if (lineaRecibida.find("INIT",0) != std::string::npos){
//				int result = juegoNuevo->arrancar(this->idCliente);
//				if (result == 0){//INIT exitoso
//					/*Envia el INIT a todos los clientes para que pasen a modo
//					de ejecucion*/
//					enviarAtodos(todosLosClientes, "INIT\r\n");
//					sleep(1000);
//					/*Tiene que enviar a todos los clientes los tamaños de los
//					dos archivos, junto con el contenido*/
//
//					std::stringstream tamanioArchImagen;
//					tamanioArchImagen << juegoNuevo->getImageSize();
//					char* archImagen = juegoNuevo->getImage();//Obtiene el contenido del binario
//					int lengthImagen = juegoNuevo->getImageSize();
//					std::string stringImagen;
//					stringImagen.assign(archImagen,lengthImagen);//Pasa ese contenido a un string
//					lineaAEnviar += "FILEMAP ";
//					lineaAEnviar += tamanioArchImagen.str();
//					lineaAEnviar += "\r\n";
//					lineaAEnviar += stringImagen;
//					lineaAEnviar += "\r\n";
//					/*Y luego envia a todos los clientes el string*/
//					enviarAtodos(todosLosClientes, lineaAEnviar);
//
//				}
//				else if (result == 1){//Jugador no habilitado para iniciar
//					enviarMensaje("ERROR No habilitado para arranque\r\n");
//				}
//				else if (result == 2){//Juego no seteado
//					enviarMensaje("ERROR Juego no seteado\r\n");
//				}
//				else if (result == 3){//No hay 2 o mas jugadores
//					enviarMensaje("ERROR Deben haber 2 o mas jugadores conectados\r\n");
//				}
//				else if (result == 4){//Juego ya arrancado
//					enviarMensaje("ERROR Juego ya arrancado\r\n");
//				}
//			}
//
//			/*Mensaje 5-1--FILE_OK*/
//			/*Una vez que un cliente recibe todo el archivo de imagen, envía un FILE_OK,
//			que usamos para empezar a enviar el archivo de datos*/
//			else if (lineaRecibida.find("FILE_OK",0) != std::string::npos){
//				/*Confiamos en que los clientes no manden FILE_OK si no recibieron
//				efectivamente el archivo de imagen*/
//				if (juegoNuevo->arrancado() == false)
//					enviarMensaje("ERROR Juego no arrancado\r\n");
//				else if (this->recibioMapa == 0){
//					this->recibioMapa = 1;
//
//					/*Genera el string con el contenido del archivo que es
//					enviado al cliente*/
//					std::stringstream tamanioArchDatos;
//					tamanioArchDatos << juegoNuevo->getDataSize();
//					char* archDatos = juegoNuevo->getData();//Obtiene el contenido del binario
//					int lengthDatos = juegoNuevo->getDataSize();
//					std::string stringDatos;
//					stringDatos.assign(archDatos,lengthDatos);//Pasa ese contenido a un string
//					lineaAEnviar += "FILETXT ";
//					lineaAEnviar += tamanioArchDatos.str();
//					lineaAEnviar += "\r\n";
//					lineaAEnviar += stringDatos;
//					lineaAEnviar += "\r\n";
//					/*Y luego envia a todos los clientes el string*/
//					enviarMensaje(lineaAEnviar);
//				}
//			}
//
//			/*Mensaje 6--READY*/
//			/*Cada cliente envia READY cuando recibió el archivo de datos*/
//			else if (lineaRecibida.find("READY",0) != std::string::npos){
//				/*Confiamos en que los clientes no manden READY si no estan
//				efectivamente listos para empezar a jugar*/
//				if (juegoNuevo->arrancado() == false)
//					enviarMensaje("ERROR Juego no arrancado\r\n");
//				else if (this->recibioMapa == 0)
//					enviarMensaje("ERROR Primero enviar FILE_OK\r\n");
//				else if (this->estaListo == 0){
//					this->estaListo = 1;//Se setea como que esta listo
//					/*Primero este ClientHandler ve cuantos clientes están listos*/
//					unsigned int clientesListos = obtenerListos(todosLosClientes);
//					if (clientesListos == todosLosClientes.size()){
//					/*Entonces todos los clientes estan listos y el juego
//					está arrancado. El juego inicia informando a todos los
//					clientes de quien es el turno*/
//						std::stringstream jugadorTurno;
//						jugadorTurno << juegoNuevo->obtenerJugadorSiguiente();
//						lineaAEnviar += "TURN ";
//						lineaAEnviar += jugadorTurno.str();
//						lineaAEnviar += ",SETUP";
//						lineaAEnviar += "\r\n";
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//					}
//				}
//			}
//
//			/*Mensaje 7--PUT id_pais*/
//			else if (lineaRecibida.find("PUT",0) != std::string::npos){
//				std::string id_pais = lineaRecibida.substr(offset+1,offset2-(offset+1));
//				bool faseCambia = false;
//				/*Si le queda solo una tropa para poner, se que la fase va a cambiar*/
//				if (juegoNuevo->getTropas() == 1)
//					faseCambia = true;
//                /*Pide al juego que ubique, y veremos que resultado nos da*/
//				int result = juegoNuevo->ubicar(this->idCliente, atoi(id_pais.c_str()), 1);
//				if (result == 0){
//				    /*Pudo ubicar*/
//					std::stringstream jugadorTurno;
//					/*Ve de quien será el turno luego de ubicar (puede que sea del
//					mismo jugador aún)*/
//					jugadorTurno << juegoNuevo->obtenerJugadorSiguiente();
//					lineaAEnviar += "PUT ";
//					lineaAEnviar += id_pais;
//					lineaAEnviar += "\r\n";
//					/*Se envia a todos que se ubicó una unidad*/
//					enviarAtodos(todosLosClientes, lineaAEnviar);
//					lineaAEnviar.clear();
//					/*Y ahora analizo en que fase estoy luego de ese ubicar*/
//					if ((faseCambia == true)&&
//						(juegoNuevo->getFaseActual() == 100)){
//                        /*Todavia estoy en la fase de ubicacion en paises desocupados.*/
//						lineaAEnviar += "TURN ";
//						lineaAEnviar += jugadorTurno.str();
//						lineaAEnviar += ",SETUP";
//						lineaAEnviar += "\r\n";
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//					}
//					if ((faseCambia == true)&&
//						(juegoNuevo->getFaseActual() == 101)){
//                        /*Ahora cambié a la primera ronda de refuerzos*/
//						std::stringstream jugadorTropas;
//						jugadorTropas << juegoNuevo->getTropas();
//						lineaAEnviar += "TURN ";
//						lineaAEnviar += jugadorTurno.str();
//						lineaAEnviar += ",REINFORCE,";
//						lineaAEnviar += jugadorTropas.str();
//						lineaAEnviar += "\r\n";
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//					}
//					if ((faseCambia == true)&&
//						(juegoNuevo->getFaseActual() == 1)){
//                        /*Ahora cambié a la ronda regular de refuerzos*/
//						std::stringstream jugadorTropas;
//						jugadorTropas << juegoNuevo->getTropas();
//						lineaAEnviar += "TURN ";
//						lineaAEnviar += jugadorTurno.str();
//						lineaAEnviar += ",REINFORCE,";
//						lineaAEnviar += jugadorTropas.str();
//						lineaAEnviar += "\r\n";
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//					}
//					if ((faseCambia == true)&&
//						(juegoNuevo->getFaseActual() == 2)){
//                        /*Ahora sigo con el mismo jugador, en la ronda de ataque*/
//						lineaAEnviar += "TURN ";
//						lineaAEnviar += jugadorTurno.str();
//						lineaAEnviar += ",ATTACK";
//						lineaAEnviar += "\r\n";
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//					}
//				}
//				else if (result == 1){
//					enviarMensaje("ERROR Jugador no existe\r\n");
//				}
//				else if (result == 2){
//					enviarMensaje("ERROR No es tu turno\r\n");
//				}
//				else if (result == 3){
//					enviarMensaje("ERROR No esta en fase de ubicar\r\n");
//				}
//				else if (result == 4){
//					enviarMensaje("ERROR Cantidad erronea\r\n");
//				}
//				else if (result == 5){
//					enviarMensaje("ERROR No se puede ubicar\r\n");
//				}
//			}
//
//			/*Mensaje 8--ATTACK id_pais_origen,id_pais_destino,cantidad*/
//			else if (lineaRecibida.find("ATTACK",0) != std::string::npos){
//			    /*Parseamos origen, destino, cantidad*/
//				int offset3 = lineaRecibida.find(",",offset+1);
//				int offset4 = lineaRecibida.find(",",offset3+1);
//				std::string id_paisOrigen;
//				std::string id_paisDestino;
//				std::string cantidad;
//				id_paisOrigen = lineaRecibida.substr(offset+1,offset3-(offset+1));
//				id_paisDestino = lineaRecibida.substr(offset3+1,offset4-(offset3+1));
//				cantidad = lineaRecibida.substr(offset4+1,offset2-(offset4+1));
//				/*Primero se pide al juego que valide si el ataque puede hacerse*/
//				int result = juegoNuevo->validarAtaque(this->idCliente,
//								atoi(id_paisOrigen.c_str()),
//								atoi(id_paisDestino.c_str()),
//								atoi(cantidad.c_str()));
//				if (result == 0){
//				    /*Si puede hacerse, entonces se pide a juego que produzca el ataque*/
//					std::string resultadoAtaque = juegoNuevo->atacar(this->idCliente,
//                                                            atoi(id_paisOrigen.c_str()),
//                                                            atoi(id_paisDestino.c_str()),
//                                                            atoi(cantidad.c_str()));
//                    resultadoAtaque += "\r\n";
//                    /*El resultado del ataque será el especificado en el protocolo, con
//                    los ids de los paises involucrados, las tropas que fueron perdidas
//                    por los jugadores, el id del jugador que quedó en el pais atacado,
//                    y con los resultados de la tirada de dados*/
//					enviarAtodos(todosLosClientes, resultadoAtaque);
//					/*Luego de producir el ataque se verifica si se cumple
//					algun objetivo de algun jugador, el valor de retorno es el
//					id de un objetivo para ese jugador, mientras que en
//					idJugador vuelve el id del jugador que cumple dicho
//					objetivo*/
//					int idJugador = 0;
//					int idObjetivo = juegoNuevo->verificarObjetivos(idJugador);
//					if (idObjetivo != 0){
//						std::stringstream jugadorID;
//						jugadorID << idJugador;
//						std::stringstream objetivoID;
//						objetivoID << idObjetivo;
//						lineaAEnviar += "GOAL ";
//						lineaAEnviar += jugadorID.str();
//						lineaAEnviar += ",";
//						lineaAEnviar += objetivoID.str();
//						lineaAEnviar += "\r\n";
//						sleep(1000);
//						enviarAtodos(todosLosClientes, lineaAEnviar);
//						/*Ademas, si alguien cumple un objetivo, eso
//						significa que el juego termina, asi que les
//						ordenamos a todos los ClientHandler a que dejen de
//						correr*/
//						pararTodos(todosLosClientes);
//					}
//				}
//				else if (result == 1){
//					enviarMensaje("ERROR Jugador no existe\r\n");
//				}
//				else if (result == 2){
//					enviarMensaje("ERROR No es tu turno\r\n");
//				}
//				else if (result == 3){
//					enviarMensaje("ERROR No esta en fase de atacar\r\n");
//				}
//				else if (result == 4){
//					enviarMensaje("ERROR Todavia falta ubicar tropas\r\n");
//				}
//				else if (result > 4){
//					enviarMensaje("ERROR No se puede atacar\r\n");
//				}
//			}
//
//			/*Mensaje 9--MOVE id_pais_origen,id_pais_destino,cantidad*/
//			else if (lineaRecibida.find("MOVE",0) != std::string::npos){
//			    /*Parsea el origen, destino y cantidad*/
//				int offset3 = lineaRecibida.find(",",offset+1);
//				int offset4 = lineaRecibida.find(",",offset3+1);
//				std::string id_paisOrigen;
//				std::string id_paisDestino;
//				std::string cantidad;
//				id_paisOrigen = lineaRecibida.substr(offset+1,offset3-(offset+1));
//				id_paisDestino = lineaRecibida.substr(offset3+1,offset4-(offset3+1));
//				cantidad = lineaRecibida.substr(offset4+1,offset2-(offset4+1));
//				/*Luego pide al juego que valide si el movimiento puede hacerse*/
//				int result = juegoNuevo->validarMover(this->idCliente,
//								atoi(id_paisOrigen.c_str()),
//								atoi(id_paisDestino.c_str()),
//								atoi(cantidad.c_str()));
//				if (result == 0){
//				    /*Si el movimiento puede hacerse, entonces primero se le avisa
//				    al juego que termine el ataque (si aún estaba en fase de ataque),
//				    y luego pide que produzca el movimiento*/
//                    juegoNuevo->terminarAtaque(this->idCliente);
//					std::string resultadoMovimiento = juegoNuevo->mover(this->idCliente,
//                                                                atoi(id_paisOrigen.c_str()),
//                                                                atoi(id_paisDestino.c_str()),
//                                                                atoi(cantidad.c_str()));
//                    /*El resultado es un string que informa los paises involucrados y las
//                    cantidades de tropas que quedan en cada pais*/
//					resultadoMovimiento += "\r\n";
//					enviarAtodos(todosLosClientes, resultadoMovimiento);
//				}
//				else if (result == 1){
//					enviarMensaje("ERROR Jugador no existe\r\n");
//				}
//				else if (result == 2){
//					enviarMensaje("ERROR No es tu turno\r\n");
//				}
//				else if (result == 3){
//					enviarMensaje("ERROR No esta en fase de mover\r\n");
//				}
//				else if (result == 4){
//					enviarMensaje("ERROR Ya hizo una fortificacion\r\n");
//				}
//				else if (result > 4){
//					enviarMensaje("ERROR No se puede mover\r\n");
//				}
//			}
//
//			/*Mensaje 10--ENDTURN*/
//			/*Cuando se pide, se le avisa al juego que cambie de turno y fase*/
//			else if (lineaRecibida.find("ENDTURN",0) != std::string::npos){
//				int result = juegoNuevo->terminarTurno(this->idCliente);
//				if (result == 0){//FIN de turno exitoso
//					std::stringstream jugadorTurno;
//					/*Ve de quien sera el turno luego del cambio*/
//					jugadorTurno << juegoNuevo->obtenerJugadorSiguiente();
//					std::stringstream jugadorTropas;
//					jugadorTropas << juegoNuevo->getTropas();
//					lineaAEnviar += "TURN ";
//					lineaAEnviar += jugadorTurno.str();
//					lineaAEnviar += ",REINFORCE,";
//					lineaAEnviar += jugadorTropas.str();
//					lineaAEnviar += "\r\n";
//					enviarAtodos(todosLosClientes, lineaAEnviar);
//				}
//				else if (result == 1){//Jugador que pide ENDTURN no existe
//					enviarMensaje("ERROR El jugador no existe\r\n");
//				}
//				else if (result == 2){//No es su turno
//					enviarMensaje("ERROR No es tu turno\r\n");
//				}
//			}
//
//			/*Mensaje 11--PLAYERLIST*/
//			else if (lineaRecibida.find("PLAYERLIST",0) != std::string::npos){
//			    /*Obtiene un string con todos los jugadores que estan conectados hasta el momento*/
//				std::string jugadoresConectados = juegoNuevo->obtenerListaJugadores(this->idCliente);
//				if (jugadoresConectados != "")
//                    enviarMensaje(jugadoresConectados);//Siempre y cuando hayan jugadores conectados
//			}
//		}//Fin del while bufferStr.find
//	   }//Fin del else (cuando el receive no devuelve -1)
//	}//Fin del while seguirCiclando == 1

    /*Cuando el ManejadorClientes sale del ciclo de recepción es porque no
    recibirá mas mensajes (porque el juego terminó o alguien salió de la partida),
    en ese caso, pide join() (para que el Servidor sepa que este cliente no corre mas),
    y luego el delete(this) que causa que el socket (y el de accept del Servidor si este cliente
    es el que inició el servidor) se liberen*/
	this->join();
	delete(this);
	return 0;
}

/*Toma la lista de clientes y un string, itera la lista y envia el string*/
void ManejadorClientes::enviarAtodos(std::list<Thread*>& clientes,
					const std::string& mensaje)
{
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
	//socketComunicacion->send((char*)mensaje.data(), mensaje.length());
	enviar(socketComunicacion->getConexion(),(char*)mensaje.data());
}

/*Acumula en cantListos para saber cuantos clientes enviaron READY al Servidor.
Cuando cantListos == clientes.size() todos están listos y el juego comienza*/
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

/*Función que devuelve un color aleatorio en un string de formato "FF005F"*/
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
