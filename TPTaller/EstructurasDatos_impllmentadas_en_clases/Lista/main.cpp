/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Patricia Calvo                         *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
 * Prueba sobre la clase Lista  
 * 
 * Version: 1.0
 * Autor: Mariano Simone (marianosimone+7541@gmail.com)
 *        Mariano Tugnarelli
 **/

#include <iostream>
#include "Lista.h"

/**
 * Clase abstracta, que define la interfaz de todos las Pruebas.
 * 
 */
class Prueba {
    
    public:
        /**
         * pre : ninguna.
         * post: ejecuta la Prueba.
         */
        virtual void ejecutar() {
            
            std::cout << "-----------------------------------------------------"
                      << std::endl
                      << "Comenzando Prueba: "
                      << this->getNombre() 
                      << std::endl
                      << "---------------" << std::endl; 
            
            this->comenzar();
            
            std::cout << "Prueba Finalizada" << std::endl;
        }
        
    protected:
        
        /**
         * Método abstracto que será implementado por los descendientes con
         * el conjunto de pasos de la Prueba.
         * 
         */
        virtual void comenzar() = 0;

        /**
         * pre : ninguna.
         * post: devuelve el nombre de la Prueba.
         */
        virtual std::string getNombre() = 0;

};

/**
 * Prueba la Lista con Enteros (int)
 */
class PruebaListaEnteros: public Prueba {
    
    protected:
        
        virtual void comenzar() {

            Lista<int> listaEnteros;

            std::cout << "La lista de enteros ahora tiene: "
                      << listaEnteros.tamanio()
                      << " elemendos"
                      << std::endl;
            
            listaEnteros.agregar(1);
            listaEnteros.agregar(2);
            listaEnteros.agregar(3);
            
            std::cout << "Agrega elementos, y la lista de enteros ahora tiene: "
                      << listaEnteros.tamanio()
                      << " elemendos"
                      << std::endl;

            std::cout << "Crea dos iteradores" 
                      << std::endl;
            
            IteradorLista<int> iterador = listaEnteros.iterador();
            IteradorLista<int> iterador2 = listaEnteros.iterador();

            if (iterador.tieneSiguiente()) {
                std::cout << "Obtiene un elemento con el primer iterador:"
                          << iterador.siguiente() 
                          << std::endl;
            }

            while (iterador2.tieneSiguiente()) {
                std::cout << "Obtiene un elemento con el segundo iterador: "
                          << iterador2.siguiente() 
                          << std::endl;
            }

            while (iterador.tieneSiguiente()) {
                std::cout << "Obtiene un elemento con el primer iterador: "
                          << iterador.siguiente() 
                          << std::endl;
            }

        }

        virtual std::string getNombre() {
            
            return "Lista de Enteros";
        }
        
};

/**
 * Prueba la Lista con strings
 */
class PruebaListaStrings: public Prueba {
    
    protected:
        virtual void comenzar() {
            
            Lista<std::string> listaStrings;
            
            std::cout << "La lista de strings ahora tiene: "
                      << listaStrings.tamanio()
                      << std::endl;
            
            listaStrings.agregar("Primer elemento");
            listaStrings.agregar("Segundo elemento");
            listaStrings.agregar("Tercer elemento");
            listaStrings.agregar("Cuarto elemento");
            listaStrings.agregar("Quinto elemento");
            std::cout << "Elementos agregados, y la lista tiene: "
                      << listaStrings.tamanio()
                      << " elemendos"
                      << std::endl;
            
            IteradorLista<std::string> iterador = listaStrings.iterador();
            while (iterador.tieneSiguiente()) {
                std::cout << "Obtiene un elemento : "
                          << iterador.siguiente()
                          << std::endl;
            }
        
        }

        virtual std::string getNombre() {
            
            return "Lista de Strings";
        }
        
};

/**
 * Prueba la Lista con punteros a enteros (int*);
 */
class PruebaListaPunterosEnteros: public Prueba {
    
    protected:
        virtual void comenzar() {
            
            Lista<int*> lista;
            int* a = new int();
            *a = 3;
            int* b = new int();
            *b = 2;
            int* c = new int();
            *c = 1;

            std::cout << "La lista ahora tiene: "
                      << lista.tamanio() 
                      << " elementos"
                      << std::endl;
            
            lista.agregar(a);
            lista.agregar(b);
            lista.agregar(c);
            std::cout << "Agrega elementos, y la lista tiene: "
                      << lista.tamanio()
                      << " elementos"
                      << std::endl;

            IteradorLista<int*> iterador = lista.iterador();
            while (iterador.tieneSiguiente()) {
                
                int* elemento = iterador.siguiente(); 
                std::cout << "Obtiene un elemento : "
                          << (*elemento)
                          << std::endl;
            }

            delete a;
            delete b;
            delete c;
        }
        
        virtual std::string getNombre() {
            
            return "Lista de Punteros a Entero";
        }
};

/**
 * Prueba la Lista con iteraciones más complejas;
 */
class PruebaListaIteraciones: public Prueba {
    
    protected:
        
        void mostrar(Lista<char>& lista) {
            
            IteradorLista<char> iterador = lista.iterador();
            while (iterador.tieneSiguiente()) {
                std::cout << iterador.siguiente() << " ";
            }
            std::cout << std::endl;
        }
        
        virtual void comenzar() {
            
            Lista<char> lista;
            
            for (char caracter = 'A'; caracter <= 'Z'; caracter++) {
                
                lista.agregar(caracter);
            }
            
            IteradorLista<char> iterador = lista.iterador();
            while (iterador.tieneSiguiente()) {
                std::cout << iterador.siguiente() << " ";
            }
            std::cout << std::endl;
            while (iterador.tieneAnterior()) {
                std::cout << iterador.anterior() << " ";
            }
            std::cout << std::endl;
            
            iterador.primero();
            for (int i = 0; i < 5; i++) {
                std::cout << iterador.siguiente() << " ";
            }
            for (int i = 0; i < 5; i++) {
                std::cout << iterador.anterior() << " ";
            }
            std::cout << std::endl;
            
            iterador.ultimo();
            for (int i = 0; i < 5; i++) {
                std::cout << iterador.anterior() << " ";
            }

            for (int i = 0; i < 5; i++) {
                std::cout << iterador.siguiente() << " ";
            }
            std::cout << std::endl;

            this->mostrar(lista);
            
            iterador.primero();
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            std::cout << "cambiar->" << iterador.get();
            iterador.set('1');
            std::cout << " por->" << iterador.get() << std::endl;
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            std::cout << "cambiar->" << iterador.get();
            iterador.set('2');
            std::cout << " por->" << iterador.get() << std::endl;
            std::cout << "cambiar->" << iterador.siguiente() << std::endl;
            std::cout << "cambiar->" << iterador.get();
            iterador.set('3');
            std::cout << " por->" << iterador.get() << std::endl;
            std::cout << "anterior->" << iterador.anterior() << std::endl;
            std::cout << "anterior->" << iterador.anterior() << std::endl;
            std::cout << "remover->" << iterador.remover() << std::endl;
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            std::cout << "siguiente->" << iterador.siguiente() << std::endl;
            
            iterador.insertar('@');
            std::cout << "insertar->" << iterador.get() << std::endl;
            
            this->mostrar(lista);
            
        }
        
        virtual std::string getNombre() {
            
            return "Iteraciones complejas sobre la lista";
        }
};

/**
 * Prueba de diferentes comparadores para ordenar y buscar elementos en la
 * Lista. 
 */
class PruebaComparadores: public Prueba {
    
    protected:
        void mostrar(Lista<int>& lista) {
            
            IteradorLista<int> iterador = lista.iterador();
            while (iterador.tieneSiguiente()) {
                std::cout << iterador.siguiente() << " ";
            }
            std::cout << std::endl;
        }

        virtual void comenzar() {
            
            Lista<int> lista;
            lista.agregar(2);
            lista.agregar(1);
            lista.agregar(4);
            lista.agregar(6);
            lista.agregar(5);
            lista.agregar(10);
            lista.agregar(1);
            lista.agregar(9);
            lista.agregar(9);            
            lista.agregar(8);
            lista.agregar(7);
            lista.agregar(3);
            lista.agregar(1);
            
            this->mostrar(lista);
            
            Lista<int> listaAscendente(new ComparadorSimpleAscendente<int>());
            IteradorLista<int> iterador = lista.iterador();
            while (iterador.tieneSiguiente()) {
                
                listaAscendente.agregar(iterador.siguiente());
            }
            
            this->mostrar(listaAscendente);
            
            Lista<int> listaDescendente(new ComparadorSimpleDescendente<int>());
            iterador.primero();
            while (iterador.tieneSiguiente()) {
                
                listaDescendente.agregar(iterador.siguiente());
            }
            
            this->mostrar(listaDescendente);
            
            std::cout << listaAscendente.buscar(2).get() << std::endl;
            
        }            
        virtual std::string getNombre() {
            
            return "Comparadores";
        }

};


/**
 * Prueba generar errores al operar con la lista
 */
class PruebaErrores: public Prueba {
    
    protected:

        virtual void comenzar() {

            try {
                
                Comparador<std::string>* 
                    comparador = new ComparadorSimpleDescendente<std::string>();
                
                Lista<std::string> lista(comparador);
                
                lista.agregar("Algoritmos");
                lista.agregar("Objetos");
                lista.agregar("Templates");
                lista.agregar("Excepciones");
                
                IteradorLista<std::string> iterador = lista.iterador();
                while (iterador.tieneSiguiente()) {
                    
                    std::cout << iterador.siguiente() << " ";
                }
                
                std::cout << std::endl;
                
                std::string buscado = "Objetos";
                
                std::cout << "Buscando " << buscado << " encontró: " 
                          << lista.buscar(buscado).get() 
                          << std::endl;
                
                
                buscado = "Error";
                
                IteradorLista<std::string> 
                    iteradorBusqueda = lista.buscar(buscado);
                    
                if (iteradorBusqueda.tieneSiguiente()) {
                    
                    std::cout << "Buscando " << buscado << " encontró: " 
                              << iteradorBusqueda.get()
                              << std::endl;
                } else {
                    
                    std::cout << "Buscando " << buscado << " no se encontró" 
                              << std::endl;
                }
                    
                
                /* esta línea debería provocar un error */
                std::cout << "Encontró: " 
                          << lista.buscar(buscado).get() 
                          << std::endl;
                
            
            } catch (ElementoInexistenteException error) {
                
                
                std::cout << "Se provocó un error: " 
                          << error.getMensaje() 
                          << std::endl; 
            }
            
        }
        
        virtual std::string getNombre() {
            
            return "Errores";
        }        
};

int main(int argc, char **argv) {
    
    Prueba** pruebas = new Prueba*[2];
    
    pruebas[0] = new PruebaListaEnteros();
    pruebas[1] = new PruebaListaStrings();
    
    
    for (int i = 0; i < 2; i++) {
        
        pruebas[i]->ejecutar();
        
        delete pruebas[i];
    }
    
    delete [] pruebas;
    
    
    /* Lista de punteros a Prueba (Prueba*) */
    Lista<Prueba*> listaPruebas;
    
    listaPruebas.agregar(new PruebaListaEnteros());
    listaPruebas.agregar(new PruebaListaStrings());
    listaPruebas.agregar(new PruebaListaPunterosEnteros());
    listaPruebas.agregar(new PruebaListaIteraciones());
    listaPruebas.agregar(new PruebaComparadores());
    listaPruebas.agregar(new PruebaErrores());

    IteradorLista<Prueba*> iterador = listaPruebas.iterador();
    while (iterador.tieneSiguiente()) {
        
        iterador.siguiente()->ejecutar();
    }
    
    /* recorre la lista retirando y destruyendo los elementos */
    iterador.primero();
    while (iterador.tieneSiguiente()) {

        Prueba* prueba = iterador.remover();
        delete prueba;
    }
}
