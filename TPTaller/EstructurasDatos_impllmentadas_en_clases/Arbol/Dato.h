/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* Clase Abstracta Dato
 * Archivo : Dato.h
 * Versión : 1.0
 */

#ifndef __DATO_H__
#define __DATO_H__

/* Headers */
/*----------------------------------------------------------------------------*/
#include <typeinfo>
#include <stdexcept>


/* Enumerado que representa el resultado de una comparación */
/*----------------------------------------------------------------------------*/
enum ResultadoComparacion {

                           menor = -1,
                           igual = 0,
                           mayor = 1
};

/* Clase ErrorComparacionIncorrecta */
/*----------------------------------------------------------------------------*/

/*
 * Descripción :
 *              Excepción provocada al intentar comparar dos instancias
 * descendientes de la clase Dato, pero que no pertenecen a la misma clase
 * hijo.
 *              Esta clase es descendiente de runtime_error, definida por
 * las librerías ANSI c++ como error en tiempo de ejecución.
 *
 */
class ErrorComparacionIncorrecta : public std::runtime_error {

  public:
    /*
      pre : ninguna.
      post: crea una nueva instancia de la excepción indicando como mensaje
            que la comparación es incorrecta.
    */
    ErrorComparacionIncorrecta() : std::runtime_error("No se pueden comparar") {
    }
};


/* Clase Dato */
/*----------------------------------------------------------------------------*/

/*
 * Descripción :
 *              La clase abstracta Dato es el ancestro común para todo objeto
 * que puede ser almacenado en una colección (contenedor) ordenada, por ejemplo
 * Arbol, Pila, Cola, Lista, etc.
 *              Define la interfaz mínima necesaria para que la colección
 * manipule correctamente una instancia.
 *
 */

class Dato {

  public:
    /*
      pre : la instancia ha sido creada y dato pertenece a la misma clase
            que la instancia invocada.
      post: devuelve menor, mayor o igual según resulte la comparación de
            la instancia invocada con dato.

      dato : instancia con la cual se realizará la comparación.
      return resultado de la comparación.

      exc : ErrorComparacionIncorrecta - dato no pertenece a la misma clase
            que la instancia invocada.
    */
    virtual ResultadoComparacion compararCon(const Dato& dato)
            throw (ErrorComparacionIncorrecta*) = 0;
};

#endif
