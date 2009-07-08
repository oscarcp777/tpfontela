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
        void stop();
		void posicionPad(char* pEnvioString);
		
    private:
    	int status;

    	cSender(const cSender&);
    	cSender& operator=(const cSender&);
};

#endif
