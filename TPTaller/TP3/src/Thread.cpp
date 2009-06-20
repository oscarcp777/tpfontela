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
    this->hilo = CreateThread(NULL,0,&(Thread::runProcess),this,0,&(this->id));
    this->engaged = true;
    return 0;
}

//To terminate a particular thread without terminating the entire process, use the API
//VOID ExitThread(DWORD ExitCode);
int Thread::join()
{
    this->engaged = false;
	//CloseHandle(this->hilo);
    ExitThread(0);
	return 0;
}

/*
runProcess() tiene que ser del tipo [void* func(void*)] para poder ponerlo como
parametro en el CreateThread(). Luego, este llamara a Process() que es un metodo
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
    if(this->engaged){
		this->engaged = false;
		TerminateThread(this->hilo,0);
	}
	
}

bool Thread::running()
{
	return engaged;
}

void Thread::sleep(unsigned long msecs){
	Sleep(msecs);
}
