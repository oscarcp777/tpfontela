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

class Object;

class Logger{

private:

	static Logger* logger;
	fstream fileInfo;
	fstream fileDebug;
	fstream fileError;
	char* temp;

	/*
	 * Apertura de archivos, si el archivo esta creado, lo abre.
	 * Si no esta creado, lo crea y lo deja activo para su
	 * utilizacion.
	 */
	void open(fstream* file, string fileName);

	/*
	 * Escritura de los archivos, si el archivo no existe el logger
	 * lo crea y lo deja y escribe. Si existe, simplemente escribe
	 * sobre este.
	 */
	void write(fstream* file,string cadena);
	/*
	 * Retorna la fecha y hora del sistema.
	 */
	std::string getTimeSystem();
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
	static Logger* getUnicaInstancia();
	/*
	 * Escribe en el archivo de salida de informacion
	 * la info seteada.
	 */
	void info(Object* object, std::string cadena);
	/*
	 * Escribe en el archivo de salida de debug la informacion
	 * seteada.
	 */
	void debug(Object* object, std::string cadena);
	/*
	 * Escribe en el archivo de salida de error la informacion
	 * de error seteada.
	 */
	void error(Object* object, std::string cadena);
	/*
	 * Libera los recursos solicitados por el logger.
	 */
	~Logger();
};

#endif /* LOGGER_H_ */
