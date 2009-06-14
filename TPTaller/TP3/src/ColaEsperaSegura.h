#ifndef cSafeQueueH
#define cSafeQueueH

//#include "cMutex.h"
#include <string>
#include <queue>

class ColaEsperaSegura
{
	private:
		//cMutex mutex;
		std::queue<std::string> cola;
		ColaEsperaSegura(const ColaEsperaSegura&);
        ColaEsperaSegura &operator=(const ColaEsperaSegura&);

	public:
        ColaEsperaSegura();
		void push(std::string);
		std::string pop();
		int size();
		bool isEmpty();
};

#endif
