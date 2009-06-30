#include "Servidor.h"
#include "Utilidades.h"
#include "CalculosMatematicos.h"
#include "archivoTexto.h"

Servidor :: Servidor(int puerto, int cantParticipantes):
			participantesMax(cantParticipantes),
			puertoConexion(puerto)
{
	/*Crea un juego vacio*/
	this->juegoNuevo = Juego::obtenerInstancia();
	puertoConexion = puerto;
}

Servidor :: ~Servidor(){
	delete(juegoNuevo);
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Servidor"<<endl;
}
/*
void antesDeCerrar(){
	//enviarAtodos(this->misClientes,"MURIO_SERVER \n");
}
*/
int Servidor :: process(void* arg){
    std::cout << "SERVER EN EJECUCION...\n";


    bool todoOK = true;//se usa para ver si no hay problemas
    Socket* socketServidor = new Socket();

    try {
    	socketServidor->listen(puertoConexion);
    }
    catch (cSocketException &e){
    	//O fallo el socket bind, o el listen
    	std::cout << "ERROR - EL PUERTO NO ESTA DISPONIBLE\n";
    	todoOK = false;
    }

    bool puedoCiclar = true;
    int cantConecEscuchadas = 0;
    /*Creo el archivo server.is.running para que el cliente sepa que el
    servidor esta escuchando*/
    std::ofstream archivo("server.is.running");

    /*El Servidor empieza a ciclar hasta que
    alguien le diga lo contrario*/
    while ((todoOK == true)&&(puedoCiclar == true)){
        /*Cuando los jugadores deciden arrancar el juego, el servidor
        deja de escuchar nuevas conexiones y sale del ciclo*/
        if ((juegoNuevo->arrancado() == true)||(juegoNuevo->cancelado() == true))
            puedoCiclar = false;
        /*Si el juego no arrancó, entonces llamamos al aceptar una
        nueva conexion*/
        else {
			std::string numJugador;
            Socket* s = socketServidor->accept();

            if (juegoNuevo->cancelado() == true){
                /*Si el juego fue cancelado, entonces se destrabó el accept a la
                fuerza, por lo que entra en este scope donde cerramos el socket
                forzado, y dejamos de ciclar el servidor*/
                delete(s);
                puedoCiclar = false;
            }
            else if ((misClientes.size() == participantesMax)||
                (juegoNuevo->arrancado() == true)){
                /*Pero si al aceptar (con juego no cancelado) tenemos la cantidad de
                clientes = al maximo, enviamos CANT_JOIN al cliente y cerramos ese socket*/
                std::string lineaError = "CANT_JOIN";
                lineaError += "\r\n";
                s->send((char*)lineaError.data());
                delete(s);
            }
            else{
                /*El juego acepta la conexion y como hay slots para mas clientes,
                entonces crea el ClientHandler que escuchará y enviará peticiones
                desde y hacia el cliente*/
                ++cantConecEscuchadas;

                ManejadorClientes* miCliente =	new ManejadorClientes(socketServidor, cantConecEscuchadas,s, juegoNuevo, misClientes);

                /*Manda el cliente a la lista de clientes (se usa para que el juego pueda
                enviarles mensajes)*/
                misClientes.push_back(miCliente);
	             miCliente->start(NULL);

                if (misClientes.size() == participantesMax){
                	puedoCiclar = false;
                }
            }
        }
    }

    //**************************************************************
    this->juegoNuevo->setEscenario(Escenario::obtenerInstancia());
    this->juegoNuevo->getEscenario()->cargarArchivo("nivel"+this->juegoNuevo->getNumeroNivelEnString()+".xml");
    //	this->juegoNuevo->setJuegoArrancado(true);


    //***********************************************************


    Escenario* escenario=juegoNuevo->getEscenario();
	Pad* pad1 = escenario->getPadCliente1();
	Pad* pad2 = escenario->getPadCliente2();
	Tejo* tejo = escenario->getTejo();
    char envioInt[1024];
    char* pEnvioInt = envioInt;
    int tipoBonus;
    std::string idFigura;
    char mensBonus[1024];
    char* pMensBonus = mensBonus;
    char puntajes[1024];
    char* pPuntajes = puntajes;
    char ganador[1024];
    char* pGanador = ganador;
    int puntosPad1, puntosPad2,posXPad1,posXPad2,posYPad1,posYPad2;
    char envioString[1024];
    char *pEnvioString = envioString;
	std::string posicionPad;
	std::string posicionTejo;
	/*
	void (*pfuncion)(void);
	pfuncion=antesDeCerrar;
	atexit(pfuncion);
    */

    //loading(misClientes,"loading1.txt");
    //loading(misClientes,"loading2.txt");

    juegoNuevo->setJuegoArrancado(true);
    sleep(6000);
    asignarNumeroClientes(this->misClientes);
    escenario->servidorInicializarListaBonus();
    enviarAtodos(this->misClientes,"INICIAR\n");

	Sleep(2000);

    /*Al salir del ciclo necesito verificar que efectivamente todos los ClientHandler
    hayan dejado de correr*/
	while (!juegoNuevo->cancelado() /*|| juegoNuevo->getEstado().compare("JUEGO_TERMINADO")!=0*/){

    	if(juegoNuevo->getEstado().compare("NIVEL_TERMINADO")!=0 ){
    		Sleep(10);
    		juegoNuevo->update();


    		if (juegoNuevo->getEstado().compare("CORRIENDO")== 0){ //envia las posiciones solo si esta corriendo (no hay goles ni nada)

    			//se forma la cadena "INT posX posY" con las posiciones del tejo
    			//this->posicionTejo(pEnvioInt);
				//enviarAtodos(this->misClientes,pEnvioInt);

				tejo->setXString(tejo->getX());
				tejo->setYString(tejo->getY());
				posicionTejo = "TEJO "+tejo->getXString()+" "+tejo->getYString()+"\n";
    			enviarAtodos(this->misClientes,(char*)posicionTejo.data());

    			if (escenario->getPadCliente1()->getCambioPosicion()){
    				pad1->setYString(pad1->getY());
					posicionPad = "PAD1 "+pad1->getYString()+"\n";
					enviarAtodos(this->misClientes,(char*)posicionPad.data());
    			}
				if (escenario->getPadCliente2()->getCambioPosicion()){
    				pad2->setYString(pad2->getY());
					posicionPad = "PAD2 "+pad2->getYString()+"\n";
					enviarAtodos(this->misClientes,(char*)posicionPad.data());
    			}
				if((CalculosMatematicos::ramdom(100)) <20 && escenario->getBonusActual()==NULL){
    				//Hago un random entre 0 y 100 si el numero es menor a 15 y no hay bonus actual aparece bonus
    				Bonus* bonus = juegoNuevo->getNuevoBonusRandom();

					if( escenario->shuffleListFiguras() == 0){
    					tipoBonus = bonus->getTipoBonus();
    					escenario->setBonusActual(bonus);
    					Figura* figura= *(escenario->iteratorListaFiguras());
    					figura->setTieneBonus(true);
    					idFigura = figura->getId();
    					escenario->setFiguraConBonus(figura);
    					//se forma la cadena "BONUS tipoBonus idFigura" tipoBonus es un int
    					this->bonus(pMensBonus,tipoBonus,idFigura);
    					enviarAtodos(this->misClientes,pMensBonus);
					}
    				//******************************************************
    			}
    		}

    		else if(juegoNuevo->getEstado().compare("GOL")== 0){
    			this->puntajes(pPuntajes);//se forma la cadena "STRING PUNTAJE puntosJug1 puntosJug2"
    			enviarAtodos(this->misClientes,pPuntajes);

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
    			Bonus::desAplicar();
				escenario->getBonusActual()->aplicar();
    			escenario->setBonusActual(NULL);
    			escenario->getFiguraConBonus()->setTieneBonus(false);
    			escenario->setFiguraConBonus(NULL);
    			escenario->getTejo()->setChocoFiguraConBonus(false);
    			enviarAtodos(this->misClientes,"APLICAR_BONUS "+escenario->getTejo()->obtenerUltimaColisionPad()+"\n");

    		}

    	}
    	else{//entra a este else si el juego esta en estado=JUEGO_TERMINADO o NIVEL_TERMINADO (es decir NO esta CORRIENDO)
    		/*if (juegoNuevo->cancelado()){
    			juegoNuevo->setEstado("JUGADOR_DESCONECTADO");
    			this->stopear();

    		}*/
    		//TODO Si se termino el juego (fin de todos los niveles) se envia el ganador a los jugadores y se finaliza la aplicacion
    		if(juegoNuevo->getEstado().compare("JUEGO_TERMINADO")==0){
    			this->ganador(pGanador);
    			//std::cout<<"JUEGO_TERMINADO envia: "<<pGanador<<endl;
    			enviarAtodos(this->misClientes,pGanador);
 				this->stopear();
 	   			//delete this->juegoNuevo;
				//exit(1);
				//return 0;
    		}
			/*if(juegoNuevo->getEstado().compare("JUGADOR_DESCONECTADO")==0){
				enviarAtodos(this->misClientes,"JUGADOR_DESCONECTADO\n");
				this->stopear();
				//delete this->juegoNuevo;
				//exit(1);
				//return 0;
			}*/
    		//si termino el nivel envio las imagenes y archivos a los clientes y vuelvo el estado del juego a CORRIENDO
    		else if(juegoNuevo->getEstado().compare("NIVEL_TERMINADO") == 0){
    			std::cout<<"ENTRO A NIVEL_TERMINADO"<<endl;
    			enviarAtodos(this->misClientes,"NIVEL_TERMINADO\n");
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
	/*Para cuando ya no hay mas clientes corriendo, todos los clientes se
	auto removieron de la lista misClientes.*/
	misClientes.clear();
	delete(this);
	exit(1);
	return 0;
}

/*Itera la lista de clientHandlers (que son hilos), y ve si estan en ejecucion
o no. A partir de esto el servidor sabe si todavía debe permanecer abierto o no*/
bool Servidor :: algunClienteCorre(std::list<Thread*>& clientes){

	bool unoCorre = false;
	for (std::list<Thread*>::iterator it = clientes.begin();
	(it != clientes.end())&&(unoCorre == false); ++it){
		Thread* clienteActual = *it;
		if (clienteActual->running() == true)
			unoCorre = true;
	}
	return unoCorre;
}

void Servidor::enviarAtodos(std::list<Thread*>& clientes,
				const std::string& mensaje)
{
			if (clientes.size()>0)
			for (std::list<Thread*>::iterator it = clientes.begin();
			it!= clientes.end(); ++it){
				if ((*it)->running() == true)
					((ManejadorClientes*)(*it))->enviarMensaje(mensaje);
			}
}

void Servidor ::posicionTejo(char* pEnvioInt){

		char auxX[20];
		char auxY[20];
		char* pauxX = auxX;
		char* pauxY = auxY;


		memset(pauxX,0,sizeof(char)*20);
		memset(pauxY,0,sizeof(char)*20);
		memset(pEnvioInt,0,sizeof(char)*1024);
		strcat(pEnvioInt,"TEJO ");
		itoa(juegoNuevo->getEscenario()->getTejo()->getX(),pauxX,10);
		itoa(juegoNuevo->getEscenario()->getTejo()->getY(),pauxY,10);
		strcat(pEnvioInt,pauxX);
		strcat(pEnvioInt," ");
		strcat(pEnvioInt,pauxY);
		strcat(pEnvioInt,"\n");


}

void Servidor::bonus(char* pMensBonus,int tipoBonus, std::string idFigura){

			char aux1[20];
			char* paux1 = aux1;
			char aux2[20];
			char* paux2 = aux2;

			memset(paux1,0,sizeof(char)*20);
			memset(paux2,0,sizeof(char)*20);
			memset(pMensBonus,0,sizeof(char)*1024);
			strcat(pMensBonus,"BONUS ");
			itoa(tipoBonus,paux1,10);

			strcat(pMensBonus,paux1);
			strcat(pMensBonus," ");
			strcat(pMensBonus,idFigura.c_str());
			strcat(pMensBonus,"\n");
}

void Servidor::puntajes(char* pPuntajes){

			char aux1[20];
			char aux2[20];
			char* paux1 = aux1;
			char* paux2 = aux2;


			memset(paux1,0,sizeof(char)*20);
			memset(paux2,0,sizeof(char)*20);
			memset(pPuntajes,0,sizeof(char)*1024);
			strcat(pPuntajes,"PUNTAJE ");
			itoa(juegoNuevo->getEscenario()->getPadCliente1()->getPuntaje()->getCantPuntosJugador(),paux1,10);
			itoa(juegoNuevo->getEscenario()->getPadCliente2()->getPuntaje()->getCantPuntosJugador(),paux2,10);
			strcat(pPuntajes,paux1);
			strcat(pPuntajes," ");
			strcat(pPuntajes,paux2);
			strcat(pPuntajes,"\n");


}

void Servidor::ganador(char* pGanador){

			char aux1[20];
			char* paux1 = aux1;

			memset(paux1,0,sizeof(char)*20);
			memset(pGanador,0,sizeof(char)*1024);
			strcat(pGanador,"GANADOR ");
			//si los goles el jugador 1 son mas que los del jugador 2 concatena STRING GANADOR 1
			if(juegoNuevo->getEscenario()->getPadCliente1()->getPuntaje()->getCantPuntosJugador() > juegoNuevo->getEscenario()->getPadCliente2()->getPuntaje()->getCantPuntosJugador())
				itoa(1,paux1,10);
			else if (juegoNuevo->getEscenario()->getPadCliente1()->getPuntaje()->getCantPuntosJugador() < juegoNuevo->getEscenario()->getPadCliente2()->getPuntaje()->getCantPuntosJugador())//sino concatena STRING GANADOR 2
				itoa(2,paux1,10);
			else
				itoa(0,paux1,10);

			strcat(pGanador,paux1);
			strcat(pGanador,"\n");
}

void Servidor::asignarNumeroClientes(std::list<Thread*>& clientes){
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

void Servidor::loading(std::list<Thread*>& clientes, std::string archivo){
			std::cout<<"ENTRO A LOADING SERVIDOR"<<endl;
			int nbytes;
			int i = 0;
			char aux1[20];
			char cantArchivos[20];
			char nombreArchivo[200];
			char *paux1= aux1;
			char *pCantArchivos= cantArchivos;
			char *pNombreArchivo = nombreArchivo;
			int tamanioArchivo = 0;
			string ok = "";
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
			std::cout<<"\n\nEnviando archivos de "<<archivo<<", total de: "<<listaArchivos.size()<<endl;
			strcat(pCantArchivos,paux1);
			for (std::list<Thread*>::iterator it = clientes.begin();
			it!= clientes.end(); ++it){
				if ((*it)->running() == true){
					((ManejadorClientes*)(*it))->enviarMensaje(pCantArchivos);
					while (listaArchivos.size()> i){
						sleep(500);//este sleep es entre envio de imagenes (sin este sleep pincha), puede ser mas chico (probar valores) PUEDE QUE EN RED NECESITE MAS TIEMPO
						memset(pNombreArchivo,0,sizeof(char)*200);
						cadena = (char*)(*iterArchivos).data();
						strcat(pNombreArchivo,cadena);
						((ManejadorClientes*)(*it))->enviarMensaje(pNombreArchivo);
						std::cout << "Nombre Archivo " << pNombreArchivo<< std::endl;
						nbytes =((ManejadorClientes*)(*it))->enviarArchivo(cadena);
						std::cout << "Bytes enviados: " << nbytes << std::endl;
						iterArchivos++;
						i++;
						ok =((ManejadorClientes*)(*it))->recibirMensaje();
						if (ok.find("OK")==0){
							std::cout << "Enviado correctamente\n" <<endl;
							ok = "";
						}
					}
					i = 0;
					iterArchivos = listaArchivos.begin();

				}
			}


}


