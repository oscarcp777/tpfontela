/*
 * HashChange.h
 *
 *  Created on: 30/10/2009
 *      Author: Francisco
 */

#ifndef HASHCHANGE_H_
#define HASHCHANGE_H_

#include <iostream>

using namespace std;

class HashChange{
private:
	// clave: La clave de registro que se tuvo que redispersar
	unsigned long int clave;
	// bloqueAnterior: El bloque que se encontraba antes de la redispersion
	unsigned int bloqueAnterior;
	// bloqueActual: El bloque que se encuentra despues de la redispersion
	unsigned int bloqueActual;
public:
	/**
	 * Constructor HashChange
	 * 
	 * Crea un HashChange con la clave de registro, el bloque que se encontraba
	 * y el bloque que se encuentra despues de la redispersion
	 * 
	 * @author Francisco
	 * 
	 * @param clave La clave de registro que se tuvo que redispersar
	 * @param bloqAnterior El bloque que se encontraba antes de la redispersion
	 * @param bloqActual El bloque que se encuentra despues de la redispersion
	 * 
	 */
	HashChange(unsigned long int clave, unsigned int bloqAnterior, unsigned int bloqActual);
	/**
	 * Destructor HashChange
	 * 
	 * @author Francisco
	 * 
	 */
	~HashChange();
	/**
	 * getClave
	 * 
	 * Devuelve la clave de registro
	 * 
	 * @author Francisco
	 * 
	 * @return unsigned int La clave de registro
	 * 
	 */
	unsigned long int getClave();
	/**
	 * getBloqueAnterior
	 * 
	 * Devuelve el bloque que se encontraba el registro antes de la redispersion
	 * 
	 * @author Francisco
	 * 
	 * @return unsigned int El bloque anterior de la redispersion
	 * 
	 */
	unsigned int getBloqueAnterior();
	/**
	 * getBloqueActual
	 * 
	 * Devuelve el bloque que se encuentra el registro despues de la redispersion
	 * 
	 * @author Francisco
	 * 
	 * @return unsigned int El bloque actual de la redispersion
	 * 
	 */
	unsigned int getBloqueActual();
	void imprimir();
};

#endif /*HASHCHANGE_H_*/
