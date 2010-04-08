/*
 * IndiceHashExtensible.h
 *
 *  Created on: 29/10/2009
 *      Author: Francisco
 */
#ifndef INDICEHASHEXTENSIBLE_H_
#define INDICEHASHEXTENSIBLE_H_

#include "Cubo.h"
#include "HashChange.h"
#include "EstrategiaIndice.h"
#include <stdlib.h>
#include <string.h>
#include "../Buffer.h"
#include <vector>
#include <cmath>

using namespace std;

class IndiceHashExtensible : public EstrategiaIndice{
private:
	vector<unsigned int>* tabla;
	vector<unsigned int>* bloquesLibres;
	vector<Cubo*>* Cubos;
	vector<HashChange>* Modificaciones;
	
	/**
	 * desbordeEnBloque
	 * 
	 * Cuando hay desborde en un bloque, se realiza los cambios necesarios, 
	 * duplicar tabla, reemplazar referencias, etc...
	 * 
	 * @author Francisco
	 * 
	 * @param unsigned int bloqueAInsertar El bloque que se desborda
	 * @param unsigned long int claveEntero La clave a insertar al bloque
	 * 
	 */
	void desbordeEnBloque (unsigned int bloqueAInsertar, unsigned long int claveEntero);
	
	/**
	 * seDesborda
	 * 
	 * Se fija si el dato entra en el bloque, si no entra al bloque, 
	 * se devuelve true, caso contrario false
	 * 
	 * @author Francisco
	 * 
	 * @param unsigned int bloqueAInsertar El bloque a insertar el dato
	 * @param unsigned int tamDato El tamanio del dato a insertar
	 * 
	 * @return bool Devuelve el resultado
	 * 
	 */
	bool seDesborda(unsigned int bloqueAInsertar, unsigned int tamDato);
	
	/**
	 * redispersarBloque
	 * 
	 * Se redispersan todas las claves de ese bloque
	 * 
	 * @author Francisco
	 * 
	 * @param unsigned int bloque El bloque que se va a dispersar las claves
	 * 
	 */
	void redispersarBloque (unsigned int bloque);
	/**
	 * posicionTabla
	 * 
	 * La funcion para acceder a la tabla con la clave
	 * 
	 * @author Francisco
	 * 
	 * @param unsigned long int clave La clave que se le aplica la funcion
	 * 
	 * @return unsigned int pos La posicion que se encuentra de la tabla
	 * 
	 */
	unsigned int posicionTabla (unsigned long int clave);
	/**
	 * Hash
	 * 
	 * La funcion de Hashing
	 * 
	 * @author Francisco
	 * 
	 * @param unsigned long int clave La clave que se le aplica la funcion de hash
	 * 
	 * @return unsigned int bloque El numero de bloque que se encuentra la clave
	 * 
	 */
	unsigned int Hash (unsigned long int clave);
	/**
	 * compactarTabla
	 * 
	 * Se fija si la tabla esta duplicada, si esta duplicada se trunca la mitad
	 * 
	 * @author Francisco
	 * 
	 */
	void compactarTabla();
	
public:
	/**
	* Constructor IndiceHashExtensible
	*
	* Crea un indiceHashExtensible nuevo con la clave primaria
	*
	* @author Francisco
	*
	* @param primaryKey es la clave primaria
	* 
	*/
	IndiceHashExtensible(PrimaryKey* primaryKey) throw(IndexException);
	/**
	* Destructor IndiceHashExtensible
	*
	* Libera los recursos asociados
	*
	* @author Francisco
	*
	*/
	~IndiceHashExtensible();
	/**
	* Cargar
	*
	* Carga el dato en el indice
	*
	* En caso de inidce primario si el identificador esta repetido
	* tira IndexException
	*
	* @author Francisco
	*
	* @param void* dato serializado a agregar en el indice
	*
	* @param int id en que esta guardado el dato
	*
	*/
	void Cargar(char* datoSerializadoACargar, unsigned int id) throw(IndexException);
	/**
	* Buscar
	*
	* Busca el dato indexado con la clave dada
	*
	* @author Francisco
	*
	* @param std::string clave que se busca en el indice
	*
	* @return std::vector<unsigned int> vector con el numero del bloque que se encuentra el dato
	*
	*/
	vector<unsigned int> Buscar(std::string claveABuscar);
	/**
	* Modificar
	*
	* cambia los datos en el indice
	*
	* @author Francisco
	*
	* @param DatoSerializadoSinModificar datos serializados sin modificar
	*
	* @param DatosSerializadoModificado datos serializados modificados
	*
	* @param idModificado id de los datos modificados
	*
	*/
	void Modificar(char* DatoSerializadoSinModificar, char* DatoSerializadoModificado, unsigned int idModificado);
	
	void Modificar(char* DatoSerializadoSinModificar, char* DatoSerializadoModificado, 
					unsigned int tamDatoSinModificar, unsigned int tamDatoModificado);

	/**
	* Eliminar
	*
	* Elimina el dato del indice
	*
	* @author Francisco
	*
	* @param DatoSeralizadoAEliminar
	*
	*/
	void Eliminar(char* DatoSerializadoAEliminar);

	/**
	 * getModificaciones
	 * 
	 * Devuelve las modificaciones de la redispersion de claves de algun bloque
	 * 
	 * @author Francisco
	 * 
	 * @return vector<HashChange>* El vector de las modificaciones luego de la redispersion
	 * 
	 */
	vector<HashChange>* getModificaciones();
	
};

#endif /* ESTRATEGIAINDICE_H_ */
