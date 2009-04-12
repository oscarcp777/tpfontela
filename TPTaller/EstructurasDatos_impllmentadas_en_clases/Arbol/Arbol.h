/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* Clase Arbol
 * Archivo : Arbol.h
 * Versión : 1.0
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
      post: crea una nueva instancia con el dato pasado como parámetro.

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

  /* Métodos */
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

      hijo : puntero hacia el nodo que será el hijo izquierdo.
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

      hijo : puntero hacia el nodo que será el hijo derecho.
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
    Nodo* raiz;          // nodo raíz del que cuelgan todos los nodos del árbol

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

  /* Métodos */
  public:
    /*
      pre : la instancia ha sido creada y dato no es nulo.
      post: inserta el dato dentro del arbol; éste es ordenado utilizando
            el método compararCon().

      dato : puntero al dato a insertar en el árbol.
    */
    void insertarDato(Dato* dato);

    /*
      pre : la instancia ha sido creada y nodo es un puntero a un Nodo,
            perteneciente a la instancia de árbol invocada.
      post: retira el dato del árbol y lo devuelve, destruyendo el nodo.

      nodo : puntero hacia un nodo del árbol.
      return puntero hacia el dato contenido por el nodo.
    */
    Dato* retirarDato(Nodo* nodo);

    /*
      pre : la instancia ha sido creada y dato no es nulo.
      post: busca el dato dado dentro del árbol, si lo encuentra, lo retira
            y lo elimina.

      dato : puntero al dato que se usa para localizar un dato en el árbol.
    */
    void eliminarDato(Dato* dato);
    /*
      pre : la instancia ha sido creada y dato no es nulo.
      post: busca el dato dado dentro del árbol, si lo encuentra, devuelve
            el nodo que lo contiene, en caso contrario devuelve Nodo::NULO.

      dato : puntero al dato que se usa para localizar un dato en el árbol.
      return puntero hacia el nodo del árbol que contiene el dato.
    */
    Nodo* buscarDato(Dato* dato);

    /*
      pre : la instancia ha sido creada.
      post: devuelve la raiz del árbol, si está vacio devuelve Nodo::NULO.

      return puntero al nodo que es la raíz del árbol.
    */
    Nodo* getRaiz() const;

    /*
      pre : la instancia ha sido creada.
      post: devuelve true si el árbol está vacio, false en caso contrario.
    */
    bool vacio() const;

  protected:

    /*
      pre : la instancia ha sido creada y nodo es un puntero a un Nodo,
            perteneciente a la instancia de árbol invocada.
      post: destruye todo el subarbol que cuelga de nodo, incluyendo los datos
            que éste contiene.

      nodo : puntero hacia un nodo del árbol.
    */
    void eliminarSubarbol(Nodo* nodo);
};

#endif
