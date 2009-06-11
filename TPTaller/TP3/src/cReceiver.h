#ifndef cReceiverH
#define cReceiverH

//#include "cMutex.h"
#include "Thread.h"
#include "Utilidades.h"
//#include "cSafeQueue.h"
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
