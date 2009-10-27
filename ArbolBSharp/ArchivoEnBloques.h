/*
 * ArchivoEnBloques.h
 *
 *  Created on: Oct 24, 2009
 *      Author: dan
 */
#include <fstream>
#include <sstream>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include "BloqueUtils.h"
#include "StringUtils.h"


#ifndef ARCHIVOENBLOQUES_H__
#define ARCHIVOENBLOQUES_H__

typedef char byte;
using namespace std;

class ArchivoEnBloques{

	public:
			ArchivoEnBloques(int n, string path);
			void cerrar();
			int getTamanioBloque();
			int getCantidadBloques();
			int agregarBloque(byte b[],int tamanioB);
			void modificarBloque(byte b[], int tamanioB, int n);
			byte* leerBloque(byte b[], int tamanioB, int n);

	private:
			fstream archivo;
			struct stat datosDeArchivo;
			int tamBloque;
};

#endif
