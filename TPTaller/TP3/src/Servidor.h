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

		std::list<Thread*> misClientes;
		unsigned int participantesMax;
		int puertoConexion;
		Juego* juegoNuevo;
		
};
