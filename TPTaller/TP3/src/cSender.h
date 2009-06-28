#ifndef cSenderH
#define cSenderH

#include "Thread.h"
//#include "cSafeQueue.h"
#include "Socket.h"
#include <string>

class cSender : public Thread
{
    public:
        cSender();
        virtual ~cSender();
        virtual int process(void*);
        void enqueue(std::string msg);
        void stop();
		void posicionPad(char* pEnvioString);
		// soltarTejo(char* pEnvioString);
    private:
    	int status;
    	//cSafeQueue toSend;

    	cSender(const cSender&);
    	cSender& operator=(const cSender&);
};

#endif
