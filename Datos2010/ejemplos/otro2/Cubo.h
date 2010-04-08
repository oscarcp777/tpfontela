/*
 * Cubo.h
 *
 *  Created on: 25/10/2009
 *      Author: Francisco
 */

#ifndef CUBO_H_
#define CUBO_H_

#include <vector>
//#include "../../classes.inc.h"
//#include "../Indice.inc.h"

using namespace std;

class Cubo{
private:
	
	unsigned int numero;
	unsigned int td;
	std::vector<unsigned long int>* claves;
	
public:
	/**
	 * Constructor Cubo
	 *
	 * Crea un Cubo nuevo con el numero del cubo,
	 * el tamanio de dispersion y un vector de claves vacio
	 *
	 * @author Francisco
	 *
	 * @param numero es el numero del cubo en el archivo
	 * @param td es el tamanio de dispersion del cubo
	 * 
	 */
	Cubo(unsigned int numero, unsigned int td);
	/**
	 * Destructor Cubo
	 *
	 * Destruye el vector de las claves
	 *
	 * @author Francisco
	 *
	 */
	~Cubo();
	/**
	 * InsertarClave
	 *
	 * Inserta la clave en el cubo 
	 *
	 * @author Francisco
	 * 
	 * @param long int clave a insertar
	 *
	 */
	void InsertarClave(unsigned long int claveAInsertar);
	/**
	 * EliminarClave
	 * 
	 * Elimina la clave del cubo si se encuentra la clave en el cubo
	 * 
	 * @author Francisco
	 * 
	 * @param long int clave a eliminar del cubo
	 * 
	 */
	void EliminarClave(unsigned long int claveAEliminar);
	/**
	 * estaVacio
	 * 
	 * Si el cubo se encuentra vacio o no
	 * 
	 * @author Francisco
	 * 
	 * @return bool Devuelve si esta vacio o no
	 * 
	 */
	bool estaVacio();
	/**
	 * setTd
	 * 
	 * Modifica el tamanio de dispersion del cubo
	 * 
	 * @author Francisco
	 * 
	 * @param unsigned int tamanio de dispersion nuevo
	 * 
	 */
	void setTd(unsigned int tamanio);
	/**
	 * getTd
	 * 
	 * Devuelve el tamanio de dispersion del cubo
	 * 
	 * @author Francisco
	 * 
	 * @return unsigned int El tamanio de dispersion del cubo
	 * 
	 */
	unsigned int getTd();
	/**
	 * getClaves
	 * 
	 * Devuelve el vector de claves del cubo
	 * 
	 * @author Francisco
	 * 
	 * @return std::vector Vector de claves del cubo
	 * 
	 */
	std::vector<unsigned long int>* getClaves();
	
	
};

#endif /*CUBO_H_*/
