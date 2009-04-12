/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Patricia Calvo                         *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/* Clase Abstracta Dato
 * Archivo : Dato.h
 * Versi�n : 1.0
 */

#ifndef __DATO_H__
#define __DATO_H__

/* Headers */
/*----------------------------------------------------------------------------*/
#include <typeinfo>
#include <stdexcept>


/* Enumerado que representa el resultado de una comparaci�n */
/*----------------------------------------------------------------------------*/
enum ResultadoComparacion {

                           menor = -1,
                           igual = 0,
                           mayor = 1
};

/* Clase ErrorComparacionIncorrecta */
/*----------------------------------------------------------------------------*/

/*
 * Descripci�n :
 *              Excepci�n provocada al intentar comparar dos instancias
 * descendientes de la clase Dato, pero que no pertenecen a la misma clase
 * hijo.
 *              Esta clase es descendiente de runtime_error, definida por
 * las librer�as ANSI c++ como error en tiempo de ejecuci�n.
 *
 */
class ErrorComparacionIncorrecta : public std::runtime_error {

  public:
    /*
      pre : ninguna.
      post: crea una nueva instancia de la excepci�n indicando como mensaje
            que la comparaci�n es incorrecta.
    */
    ErrorComparacionIncorrecta() : std::runtime_error("No se pueden comparar") {
    }
};


/* Clase Dato */
/*----------------------------------------------------------------------------*/

/*
 * Descripci�n :
 *              La clase abstracta Dato es el ancestro com�n para todo objeto
 * que puede ser almacenado en una colecci�n (contenedor) ordenada, por ejemplo
 * Arbol, Pila, Cola, Lista, etc.
 *              Define la interfaz m�nima necesaria para que la colecci�n
 * manipule correctamente una instancia.
 *
 */

class Dato {

  public:
    /*
      pre : la instancia ha sido creada y dato pertenece a la misma clase
            que la instancia invocada.
      post: devuelve menor, mayor o igual seg�n resulte la comparaci�n de
            la instancia invocada con dato.

      dato : instancia con la cual se realizar� la comparaci�n.
      return resultado de la comparaci�n.

      exc : ErrorComparacionIncorrecta - dato no pertenece a la misma clase
            que la instancia invocada.
    */
    virtual ResultadoComparacion compararCon(const Dato& dato)
            throw (ErrorComparacionIncorrecta*) = 0;
};

#endif
