/*
 * Logger.cpp
 *
 *  Created on: 26/03/2010
 *      Author: nelson
 */

#include "Logger.h"

	Logger* Logger::logger = 0;

	static Logger* Logger::getInstacia(){

		if(logger==0){
		/*
		 * Aca instancio abro los archivos.
		 */
		}

		return this->logger;
	}
	/*
	 * En los metodos que se encuentran a continuacion
	 * tengo que escribir los archivos.
	 */
	void Logger::setInfo(std::string cadena);
	void Logger::setDebug(std::string object, std::string cadena);
	void Logger::setError(std::string object, std::string cadena);
	/*
	 * El logger se instancia al comienzo de la aplicacion
	 * por lo tanto cuando esta se termine llamara al destructor
	 * del logger automaticamente y es ahi donde se cierran los archivos
	 * y liberan los recursos.
	 */
	Logger::~Logger();
