/*
 * Thread.cpp
 *
 *  Created on: 28/05/2009
 *      Author: Programadores
 */

#include "Thread.h"

Thread::Thread():engaged(false){}

int Thread::start(void* args)
{
    this->args = args;
    this->hilo = CreateThread(NULL,0,Thread::runProcess,NULL,0,&(this->id));
    this->engaged = true;
    return 0;
}

int Thread::join()
{
    this->engaged = false;
    ExitThread(this->id);
    return 0;
}

/*
runProcess() tiene que ser del tipo [void* func(void*)] para poder ponerlo como
parametro en el pthread_create(). Luego, este llamara a Process() que es un metodo
virtual que definiran las clases que hereden Thread.
*/
DWORD WINAPI Thread::runProcess(LPVOID thread)
{
    Thread* thisThread = (Thread*) thread;
    if(thisThread)
    {
        thisThread->process(thisThread->args);
    }
    return 0;
}

Thread::~Thread()
{
    if(this->engaged) Thread::join();
}

bool Thread::running()
{
	return engaged;
}

void Thread::sleep(unsigned long msecs){
	Sleep(msecs);
}
