/*
 * TextIndex.h
 *
 *  Created on: 02/04/2010
 *      Author: richy
 */

#ifndef TEXTINDEX_H_
#define TEXTINDEX_H_

class TextIndex {
public:
	TextIndex(int maxKeys =100, int unique = 1);
	virtual ~TextIndex();
	int insert(const char* key, int recAddr);
	int remove(const char* key);
	int search(const char* key)const;
	void print();
protected:
	int find(const char* key)const;
	int init(int maxkeys, int unique);
	int maxKeys;
	int numKeys;
	char** keys;
	int* recAddrs;
	int unique; //si es true, cada key tiene que ser unica

	friend class TextIndexBuffer;

};

#endif /* TEXTINDEX_H_ */
