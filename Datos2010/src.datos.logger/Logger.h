/*
 *  Logger.h
 *
 *  Created on: 26/03/2010
 *      Author: nelson
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>

using namespace std;

class Logger{

private:

	static Logger* logger;
	fstream file;
	char* date;
	int sizeFile;
	int coutFiles;

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
	string getTimeSystem();
	/*
	 * Crea un archivo nuevo.
	 */
	void split(string cadena);
	/*
	 * Funcion auxiliar que convierte un numero entero al mismo
	 * numero en una cadena de caracteres.
	 */
	string convertIntToString(int numero);
	/*
	 * Constructor privado, para que solo se instancie
	 * mediante el metodo getInstacia.
	 */
	Logger(int sizeFile = 512);

public:
	/*
	 * Se obtiene un puntero a la unica instancia del
	 * logger.
	 */
	static Logger* getUnicaInstancia();
	/*
	 * Setea el tamaño maximo del archivo, se recomienda inicializarlo
	 * luego de pedir una instancia de logger y no modificarlo.
	 */
	void setSizeFile(int fileSize);
	/*
	 * Escribe en el archivo de salida, la informacion del
	 * programa que se desea almacenar.
	 */
	void info(string cadena);
	/*
	 * Muestra en un archivo, todo el logger
	 */
	void print();
	/*
	 * Libera los recursos solicitados por el logger.
	 */
	~Logger();
};

#endif /* LOGGER_H_ */
