/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Patricia Calvo                         *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/* Clase DatoEntero
 * Archivo : DatoEntero.h
 * Versi�n : 1.0
 * Descripci�n :
 *              Ejemplo de extensi�n de la clase Dato.
 */

#ifndef __DATO_ENTERO_H__
#define __DATO_ENTERO_H__

/* Headers */
/*----------------------------------------------------------------------------*/
#include "Dato.h"

/* Clase DatoEntero */
/*----------------------------------------------------------------------------*/
class DatoEntero : public Dato {

  private:
    int valor;


  public:
    DatoEntero(const int& valor) {
      this->valor = valor;
    }
    virtual ~DatoEntero() {
    }

    int getValor() const{
      return this->valor;
    }

    void setValor(const int& valor) {
      this->valor = valor;
    }

    /*
      pre : la instancia ha sido creada y dato a la clase DatoEntero
      post: devuelve menor, mayor o igual seg�n resulte la comparaci�n de
            la instancia invocada con dato.

      dato : instancia con la cual se realizar� la comparaci�n.
      return resultado de la comparaci�n.

      exc : ErrorComparacionIncorrecta - dato no pertenece a la clase DatoEntero
    */
    virtual ResultadoComparacion compararCon(const Dato& dato)
            throw (ErrorComparacionIncorrecta*) {

      /* valida si dato pertenece a la clase DatoEntero */
      if (typeid(dato) != typeid(DatoEntero))

        /* arroja la excepci�n indicando el error */
        throw new ErrorComparacionIncorrecta;

      /* castea la referencia hacia el dato din�micamentente */
      const DatoEntero& datoEntero = dynamic_cast<const DatoEntero&>(dato);

      /* opera ahora con la referencia a DatoEntero */
      ResultadoComparacion resultado;
      if (this->getValor() > datoEntero.getValor())
        resultado = mayor;
      else
        if (this->getValor() < datoEntero.getValor())
          resultado = menor;
        else
          resultado = igual;

      return resultado;
    }
};

#endif
