/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA archivoTexto
 * Implementación con fstream.
 * Archivo : archivoTexto.cpp
 * Versión : 1.0
 */

/******************************************************************************/
/* Headers */
/*---------*/

#include "archivoTexto.h"

using namespace std;

/******************************************************************************/
/* Implementación de Primitivas */
/*------------------------------*/

void crear( ArchivoTexto &archivoTexto , std::string nombre ) {

    /* abre el archivo en modo lectura - escritura*/
    archivoTexto.archivo.open(nombre.c_str(),std::fstream::in |std::fstream::out);

    /* determina si tuvo éxito la apertura del archivo */
    if (! archivoTexto.archivo.is_open()) {

        /* limpia los flags de control de estado del archivo */
        archivoTexto.archivo.clear();

        /* crea el archivo */
        archivoTexto.archivo.open(nombre.c_str(),std::fstream::out);
        archivoTexto.archivo.close();

        /* reabre el archivo para lectura - escritura binario */
        archivoTexto.archivo.open(nombre.c_str(),std::fstream::in|std::fstream::out);

        /* verifica que haya podido crear el archivo */
        if (! archivoTexto.archivo.is_open())

            /* arroja una excepción */
            throw string("El archivo no pudo ser abierto");
    }
}

/*----------------------------------------------------------------------------*/
void destruir( ArchivoTexto &archivoTexto ) {

    /* cierra el archivo */
    archivoTexto.archivo.close();
}

/*----------------------------------------------------------------------------*/
void escribirCaracter(ArchivoTexto &archivoTexto, char Caracter) {

    /* verifica que el archivo esté abierto */
    if (archivoTexto.archivo.is_open()) {

        /* escribe el caracter en el archivo */
        archivoTexto.archivo.put(Caracter);

        /* chequea si se ha producido un error */
        if (archivoTexto.archivo.fail())
            /* arroja una excepción ante la imposibilidad de escribir el caracter */
            throw string("No se pudo escribir correctamente el registro");
    }
    else {
        /* arroja una excepción porque el archivo no está abierto */
        throw string("El archivo no está abierto");
    }
}

/*----------------------------------------------------------------------------*/
void escribirCadena(ArchivoTexto &archivoTexto, std::string Cadena) {

    /* verifica que el archivo esté abierto */
    if (archivoTexto.archivo.is_open()) {

        /* escribe la cadena en el archivo */
        archivoTexto.archivo<<Cadena;

        /* chequea si se ha producido un error */
        if (archivoTexto.archivo.fail())
            /* arroja una excepción ante la imposibilidad de escribir la cad */
            throw string("No se pudo escribir correctamente el registro");
    }
    else {
        /* arroja una excepción porque el archivo no está abierto */
        throw string("El archivo no está abierto");
    }
}

/*----------------------------------------------------------------------------*/
void bajarDeLinea( ArchivoTexto &archivoTexto ) {

    /* verifica que el archivo esté abierto */
    if (archivoTexto.archivo.is_open()) {

        /* escribe en el archivo */
        archivoTexto.archivo<<endl;

        /* chequea si se ha producido un error */
        if (archivoTexto.archivo.fail())
            /* arroja una excepción ante la imposibilidad de escribir */
            throw string("No se pudo escribir correctamente el registro");
    }
    else {
        /* arroja una excepción porque el archivo no está abierto */
        throw string("El archivo no está abierto");
    }
}

/*----------------------------------------------------------------------------*/
void tabular( ArchivoTexto &archivoTexto ) {

    /* verifica que el archivo esté abierto */
    if (archivoTexto.archivo.is_open()) {

        /* escribe en el archivo */
        archivoTexto.archivo.put('\t');

        /* chequea si se ha producido un error */
        if (archivoTexto.archivo.fail())
            /* arroja una excepción ante la imposibilidad de escribir */
            throw string("No se pudo escribir correctamente el registro");
    }
    else {
        /* arroja una excepción porque el archivo no está abierto */
        throw string("El archivo no está abierto");
    }
}

/*----------------------------------------------------------------------------*/
bool leerLinea( ArchivoTexto &archivoTexto, std::string &Cadena ) {

    /* verifica que el archivo esté abierto */
    if (archivoTexto.archivo.is_open()) {

        char     Linea[512];
        int      Valor = 256;

        /* lee del archivo la cadena */
        archivoTexto.archivo.getline( (char*)&Linea , Valor , '\n' );
        Cadena=Linea;

        /* chequea si se ha producido un error */
        if ( archivoTexto.archivo.fail() ) {
            archivoTexto.archivo.clear();
            return false;
        }
        else
            return true;

    }
    else {
        /* arroja una excepción porque el archivo no está abierto */
        return false;
    }
}

/*----------------------------------------------------------------------------*/
void irAlComienzo( ArchivoTexto &archivoTexto ) {

    archivoTexto.archivo.tellg();
    archivoTexto.archivo.clear();
    archivoTexto.archivo.seekg(0);
    archivoTexto.archivo.seekp(0);
    archivoTexto.archivo.tellg();
}

/*----------------------------------------------------------------------------*/
void irAlFinal( ArchivoTexto &archivoTexto ) {

    archivoTexto.archivo.tellg();
    archivoTexto.archivo.clear();
    archivoTexto.archivo.seekg(0,ios::end);
    archivoTexto.archivo.seekp(0,ios::end);
    archivoTexto.archivo.tellg();
}

/*----------------------------------------------------------------------------*/
