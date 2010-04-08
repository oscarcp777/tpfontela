/*
 * Record.h
 *
 *  Created on: 07/04/2010
 *      Author: oscar
 */

#ifndef RECORD_H_
#define RECORD_H_
class Record {
private:
   int key;
   char* data;
public:
	Record(int key,char* data);
	Record();
	virtual ~Record();




    char *getData() const
    {
        return data;
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
