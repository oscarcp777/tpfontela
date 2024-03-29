#ifndef cReceiverH
#define cReceiverH

//#include "cMutex.h"
#include "Thread.h"
#include "ColaEsperaSegura.h"
#include "Socket.h"
#include <string>

class cReceiver : public Thread
{
    public:
        cReceiver();
        virtual ~cReceiver();
        virtual int process(void*);
        std::string dequeue();
        bool isEmpty();
        int getFileSize();
        void stop();

    private:
		int status;
		//cMutex mFile, mDown;
    	ColaEsperaSegura received;
    	unsigned int filesize;
    	unsigned int downloaded;
    	static const unsigned int BUFFERSIZE;

    	cReceiver(const cReceiver&);
    	cReceiver& operator=(const cReceiver&);
		void loading(Socket * s);
};

#endif
