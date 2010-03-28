/*
 * Logger.h
 *
 *  Created on: 26/03/2010
 *      Author: nelson
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
using namespace std;

class Logger {

private:

	static Logger* logger;
	fstream fileInfo;
	fstream fileDebug;
	fstream fileError;
	/*
	 * Constructor privado, para que solo se instancie
	 * mediante el metodo getInstacia.
	 */
	Logger();
	/*
	 * Apertura de archivos, si el archivo esta creado, lo abre.
	 * Si no esta creado, lo crea y lo deja activo para su
	 * utilizacion.
	 */
	void open(fstream file, string fileName);

	/*
	 * Escritura de los archivos, si el archivo no existe el logger
	 * lo crea y lo deja y escribe. Si existe, simplemente escribe
	 * sobre este.
	 */
	void write(fstream file,string cadena);
	/*
	 * Retorna la fecha y hora del sistema.
	 */
	std::string getTimeSystem();

public:
	/*
	 * Se obtiene un puntero a la unica instancia del
	 * logger.
	 */
	static Logger* getUnicaInstance();
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
