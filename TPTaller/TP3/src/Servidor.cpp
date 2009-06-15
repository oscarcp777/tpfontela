#include "Servidor.h"
#include "Utilidades.h"

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
}

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
                s->send((char*)lineaError.data(), lineaError.length());
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
                	juegoNuevo->setJuegoArrancado(true);

                }
            }
        }
    }
    this->sleep(5000);
		
		//**************************************************************
		    this->juegoNuevo->setEscenario(Escenario::obtenerInstancia());
			this->juegoNuevo->getEscenario()->cargarArchivo("xml.xml");
			this->juegoNuevo->setJuegoArrancado(true);

		
		//***********************************************************
		
		ManejadorClientes* servidorSender =new ManejadorClientes(socketServidor, cantConecEscuchadas,
    			socketServidor, juegoNuevo, misClientes);
    	servidorSender->start(NULL);

    /*Al salir del ciclo necesito verificar que efectivamente todos los ClientHandler
    hayan dejado de correr*/
    while (algunClienteCorre(misClientes) == true){

    	this->sleep(100);

    }

	/*Para cuando ya no hay mas clientes corriendo, todos los clientes se
	auto removieron de la lista misClientes.*/
	misClientes.clear();
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
