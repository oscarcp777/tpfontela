#include "ManejadorClientes.h"
#include "cSocketException.h"
#include "Juego.h"
#include "Thread.h"
#include "Socket.h"
#include <iostream>
#include <fstream>

class Servidor : public Thread
{
	public:
		Servidor(int puerto, int cantParticipantes);
		virtual ~Servidor();
	protected:
		virtual int process(void*);
	private:
		bool algunClienteCorre(std::list<Thread*>& clientes);
		void posicionTejo(char* pEnvioInt);
		void enviarAtodos(std::list<Thread*>& clientes,
							const std::string& mensaje);
		void bonus(char* pMensBonus,int tipoBonus,std::string idFigura);
		void puntajes(char* pPuntajes);
		void ganador(char* pPuntajes);
		void asignarNumeroClientes(std::list<Thread*>& clientes);
		void loading(std::list<Thread*>& clientes,std::string archivo);
		std::list<Thread*> misClientes;
		unsigned int participantesMax;
		int puertoConexion;
		Juego* juegoNuevo;
		void posicionPad(char* pEnvioString, int numJugador);

};
