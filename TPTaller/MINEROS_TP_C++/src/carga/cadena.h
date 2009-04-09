/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************
 * TDA Cadena
 * Archivo : Cadena.h , Cadena.cpp
 ******************************************/
#ifndef __CADENA__H__
#define __CADENA__H__

#include <sstream>
/*  axiomas:
            -una cadena vacia es ""
*/
struct Cadena{
                std::string valor;
};
/*  pre:
    post: deja una cadena creada con el valor por defecto ""
*/
void crear(Cadena& cadena);

/*  pre:  cadena creada
    post: libera recursos
*/
void destruir(Cadena &cadena);

/*  pre: cadena creada
    post: asigna el valor pasado por parametro a la cadena
*/
void setValor(Cadena &cadena, std::string valor);

/*  pre:  cadena creada
    post: devuelve el valor que tiene la cadena
*/
std::string getValor(const Cadena &cadena);

/*  pre:  cadena creada. El caracter de inicio y de fin debe existir
    post: devuelve la subcadena entre los dos demarcadores, por ejemplo:
          "partida.ronda=100", entre '.' e '=" devuelve ronda
*/
std::string buscarParametro(Cadena &cadena, char charInicio, char charFin);
/*  pre:  cadena creada y el caracter inicial existente
    post: devuelve la subcadena despues del caracter, por ejemplo:
          partida.rondas=100, devuelve 100 si el caracter incial es '='
*/
std::string obtenerValor(Cadena &cadena, char charInicial);

/*  pre: cadena creada y con algun valor numerico en forma de string, ej= "12"
    post: devuelve su valor en entero
*/
int convertirStringAInt(const Cadena &cadena);

/*  pre:  cadena creada, numero entero valido
    post: cambia el valor de la cadena con la representacion del numero pasado
*/
void convertirIntAString(Cadena &cadena, int numero);

/*  pre:  cadena creada
    post: devuelve la cantidad de caracteres de la cadena
*/
int cantidadCaracteres(Cadena &cadena);
#endif
