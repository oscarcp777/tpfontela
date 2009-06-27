#include "cSocketException.h"
#include <string>
#include <sstream>

#ifdef WIN32
#include <winsock.h>
#else
#include <errno.h>
#endif

using namespace std;

cSocketException::cSocketException(const string &error) throw():error(error)
{
    this->error.append(": ");
    #ifdef WIN32
    std::ostringstream tmp;
	tmp << WSAGetLastError();;
	this->error.append(tmp.str());
	#else
	this->error.append(strerror(errno));
	#endif
}

const char *cSocketException::what() const throw()
{
    return this->error.c_str();
}

cSocketException::~cSocketException() throw() {}
