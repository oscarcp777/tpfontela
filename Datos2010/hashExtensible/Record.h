/*
 * Record.h
 *
 *  Created on: 07/04/2010
 *      Author: oscar
 */

#ifndef RECORD_H_
#define RECORD_H_
#include <string>


class Record {
private:
   int key;
   std::string data;
public:
	Record(int key,char* data);
	Record();
	virtual ~Record();
	/**
	 * este metodo retorna el tamanio del registro entero en bytes , el tamanio que va a
	 * ocupar en el archivo junato su metadata
	 * @oscar
	 * @return tamanio que va a ocupar en disco
	 *
	 */
    int getSizeRecord();
    int getSizeDataRecord();
    void clear();

    char* getData() const
    {
        return (char*)data.c_str();
    }

    int getKey() const
    {
        return key;
    }

    void setData(char *data)
    {
        this->data = data;
    }

    void setKey(int key)
    {
        this->key = key;
    }

};

#endif /* RECORD_H_ */
