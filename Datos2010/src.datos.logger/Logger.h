/*
 * Logger.h
 *
 *  Created on: 26/03/2010
 *      Author: nelson
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Object.h"
#include "TextFile.h"

class Logger {

private:

	static Logger* logger;
	TextFile* fileInfo;
	TextFile* fileDebug;
	TextFile* fileError;
	/*
	 * Constructor privado, para que solo se instancie
	 * mediante el metodo getInstacia.
	 */
	Logger();

public:
	/*
	 * Se obtiene un puntero a la unica instancia del
	 * logger.
	 */
	static Logger* getInstacia();
	/*
	 * Escribe en el archivo de salida de informacion
	 * la info seteada.
	 */
	void setInfo(std::string cadena);
	/*
	 * Escribe en el archivo de salida de debug la informacion
	 * seteada.
	 */
	void setDebug(std::string object, std::string cadena);
	/*
	 * Escribe en el archivo de salida de error la informacion
	 * de error seteada.
	 */
	void setError(std::string object, std::string cadena);
	/*
	 * Libera los recursos solicitados por el logger.
	 */
	~Logger();
};

#endif /* LOGGER_H_ */
