#ifndef MiscH
#define MiscH

#define SETUP 0
#define REINFORCE 1
#define ATTACK 2
#define FORTIFY 3

#define NOT_CONNECTED 0
#define CONNECTED 1
#define NO_HOST 2

#include <sstream>
#include <string>

template<typename T> std::string toStr(T var)
{
	std::ostringstream tmp;
	tmp << var;
	return tmp.str();
}

#endif
