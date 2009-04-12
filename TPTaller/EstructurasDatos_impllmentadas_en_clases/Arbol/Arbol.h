/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Patricia Calvo                         *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/* Clase Arbol
 * Archivo : Arbol.h
 * Versi�n : 1.0
 */

#ifndef __ARBOL_H__
#define __ARBOL_H__

/* Headers */
/*----------------------------------------------------------------------------*/
#include "Dato.h"


/* Clase Nodo */
/*----------------------------------------------------------------------------*/
class Nodo {

  /* Atributos de clase */
  public:
    static Nodo* NULO;

  /* Atributos */
  private:
    Dato* dato;               // dato almancenado en el nodo
    Nodo* izq;                // puntero hacia el hijo izquierdo
    Nodo* der;                // puntero hacia el hijo derecho

  /* Constructor - Destructor */
  public:
    /*
      pre : ninguna.
      post: crea una nueva instancia con el dato pasado como par�metro.

      dato : puntero hacia el dato a almacenar en la instancia.
    */
    Nodo(Dato* dato) {
      this->dato = dato;
      this->izq = Nodo::NULO;
      this->der = Nodo::NULO;
    }

    /*
      pre : la instancia ha sido creada.
      post: destruye la instancia.
    */
    virtual ~Nodo() {
      this->izq = Nodo::NULO;
      this->der = Nodo::NULO;
    }

  /* M�todos */
  public:
    /*
      pre : la instancia ha sido creada.
      post: cambia el dato almanceado por el nodo.

      dato : puntero hacia el dato a almacenar en la instancia.
    */
    void setDato(Dato* dato) {
      this->dato = dato;
    }

    /*
      pre : la instancia ha sido creada.
      post: devuelve el dato alamacenado.

      return puntera al dato alamcenado.
    */
    Dato* getDato() {
      return this->dato;
    }

    /*
      pre : la instancia ha sido creada.
      post: cambia el hijo izquierdo.

      hijo : puntero hacia el nodo que ser� el hijo izquierdo.
    */
    void setHijoIzquierdo(Nodo* hijo) {
      this->izq = hijo;
    }

    /*
      pre : la instancia ha sido creada.
      post: devuelve el hijo izquierdo.

      return puntero hacia el hijo izquierdo.
    */
    Nodo* getHijoIzquierdo() {
      return this->izq;
    }

    /*
      pre : la instancia ha sido creada.
      post: cambia el hijo derecho.

      hijo : puntero hacia el nodo que ser� el hijo derecho.
    */
    void setHijoDerecho(Nodo* hijo) {
      this->der = hijo;
    }

    /*
      pre : la instancia ha sido creada.
      post: devuelve el hijo derecho.

      return puntero hacia el hijo derecho.
    */
    Nodo* getHijoDerecho() {
      return this->der;
    }
};


/* Clase Arbol */
/*----------------------------------------------------------------------------*/
class Arbol {

  /* Aributos */
  private:
    Nodo* raiz;          // nodo ra�z del que cuelgan todos los nodos del �rbol

  /* Constructor - Destructor */
  public:
    /*
      pre : ninguna.
      post: crea la instancia vacia.
    */
    Arbol();

    /*
      pre : la instancia ha sido creada.
      post: destruye la instancia y los datos contenidos.
    */
    virtual ~Arbol();

  /* M�todos */
  public:
    /*
      pre : la instancia ha sido creada y dato no es nulo.
      post: inserta el dato dentro del arbol; �ste es ordenado utilizando
            el m�todo compararCon().

      dato : puntero al dato a insertar en el �rbol.
    */
    void insertarDato(Dato* dato);

    /*
      pre : la instancia ha sido creada y nodo es un puntero a un Nodo,
            perteneciente a la instancia de �rbol invocada.
      post: retira el dato del �rbol y lo devuelve, destruyendo el nodo.

      nodo : puntero hacia un nodo del �rbol.
      return puntero hacia el dato contenido por el nodo.
    */
    Dato* retirarDato(Nodo* nodo);

    /*
      pre : la instancia ha sido creada y dato no es nulo.
      post: busca el dato dado dentro del �rbol, si lo encuentra, lo retira
            y lo elimina.

      dato : puntero al dato que se usa para localizar un dato en el �rbol.
    */
    void eliminarDato(Dato* dato);
    /*
      pre : la instancia ha sido creada y dato no es nulo.
      post: busca el dato dado dentro del �rbol, si lo encuentra, devuelve
            el nodo que lo contiene, en caso contrario devuelve Nodo::NULO.

      dato : puntero al dato que se usa para localizar un dato en el �rbol.
      return puntero hacia el nodo del �rbol que contiene el dato.
    */
    Nodo* buscarDato(Dato* dato);

    /*
      pre : la instancia ha sido creada.
      post: devuelve la raiz del �rbol, si est� vacio devuelve Nodo::NULO.

      return puntero al nodo que es la ra�z del �rbol.
    */
    Nodo* getRaiz() const;

    /*
      pre : la instancia ha sido creada.
      post: devuelve true si el �rbol est� vacio, false en caso contrario.
    */
    bool vacio() const;

  protected:

    /*
      pre : la instancia ha sido creada y nodo es un puntero a un Nodo,
            perteneciente a la instancia de �rbol invocada.
      post: destruye todo el subarbol que cuelga de nodo, incluyendo los datos
            que �ste contiene.

      nodo : puntero hacia un nodo del �rbol.
    */
    void eliminarSubarbol(Nodo* nodo);
};

#endif
