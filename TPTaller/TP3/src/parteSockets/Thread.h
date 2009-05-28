/*
 * Thread.h
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <windows.h>

class Thread {
public:
public:
        Thread();
        int start(void* args);
        int join();
	bool running();
        virtual ~Thread();
	static void sleep(unsigned long msecs);
    protected:
        static DWORD WINAPI runProcess(void*);
        virtual int process(void*) = 0;

    private:
    	bool engaged;
        DWORD id;
        HANDLE hilo;
        void* args;
};

#endif /* THREAD_H_ */
