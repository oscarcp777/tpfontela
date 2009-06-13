#ifndef cReceiverH
#define cReceiverH


//#include "cSafeQueue.h"
//#include "cMutex.h"
//#include "cLockableGuard.h"		// Para la guarda del mutex
#include "Thread.h"
#include "Utilidades.h"
#include "Socket.h"
#include "cSocketException.h"	// Para las excepciones de sockets
#include "Defines.h"				// Para las constantes CONNECTED etc
#include <string>				// Para el manejo de strings
#include <fstream>				// Para filemap y filetxt
#include <iostream>




class cReceiver : public Thread
{
    public:
        cReceiver();
        virtual ~cReceiver();
        virtual int process(void*);
        std::string dequeue();
        bool isEmpty();
        int getFileSize();
        int getDownloaded();
        void clearDownloaded();
        void stop();

    private:
		int status;
		//cMutex mFile, mDown;
    	//cSafeQueue received;
    	unsigned int filesize;
    	unsigned int downloaded;
    	static const unsigned int BUFFERSIZE;

    	cReceiver(const cReceiver&);
    	cReceiver& operator=(const cReceiver&);
		void loading(Socket * s);
};

#endif
