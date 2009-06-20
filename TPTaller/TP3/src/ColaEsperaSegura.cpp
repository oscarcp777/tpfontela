#include "ColaEsperaSegura.h"
//#include "cMutex.h"
//#include "cLockableGuard.h"
#include <string>

using namespace std;

ColaEsperaSegura::ColaEsperaSegura(){}

void ColaEsperaSegura::push(string padron)
{
	//cLockableGuard<cMutex,int,int> safeMutex(this->mutex, &cMutex::Lock, &cMutex::Unlock);
	this->cola.push(padron);
}

string ColaEsperaSegura::pop()
{
	//cLockableGuard<cMutex,int,int> safeMutex(this->mutex, &cMutex::Lock, &cMutex::Unlock);
	string ret = cola.front();
	this->cola.pop();
	return ret;
}

int ColaEsperaSegura::size()
{
	//cLockableGuard<cMutex,int,int> safeMutex(this->mutex, &cMutex::Lock, &cMutex::Unlock);
	return cola.size();
}

bool ColaEsperaSegura::isEmpty()
{
	//cLockableGuard<cMutex,int,int> safeMutex(this->mutex, &cMutex::Lock, &cMutex::Unlock);
	return cola.empty();
}
