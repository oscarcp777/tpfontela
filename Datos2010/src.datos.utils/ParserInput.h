/*
 * ParserInput.h
 *
 *  Created on: 15/04/2010
 *      Author: nelson ramos
 */

#ifndef PARSERINPUT_H_
#define PARSERINPUT_H_

#include <iostream>

class ParserInput {

private:
	int key;
	std::string data;

public:
	ParserInput();
	void parser(std::string line);
	int getKey();
	std::string getData();
	~ParserInput();
};

#endif /* PARSERINPUT_H_ */
