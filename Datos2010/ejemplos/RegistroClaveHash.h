/*
 * RegistroClaveHash.h
 *
 *  Created on: 07/11/2009
 *      Author: santiago
 */

#ifndef REGISTROCLAVEHASH_H_
#define REGISTROCLAVEHASH_H_

using namespace std;

#include<string>

class RegistroClaveHash {
private:
     string clave;
	 int offset;
public:
	RegistroClaveHash();
	string getClave();
	void setClave(string clave);
	int getOffset();
	void setOffset(int offset);
	virtual ~RegistroClaveHash();
};

#endif /* REGISTROCLAVEHASH_H_ */
