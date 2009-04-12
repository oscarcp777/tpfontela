/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Patricia Calvo                         *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/**
 * 
 * Version: 1.0
 * Autor: Mariano Tugnarelli
 **/

#ifndef __ELEMENTO_INEXISTENTE_EXCEPTION_H__
#define __ELEMENTO_INEXISTENTE_EXCEPTION_H__

#include <string>

/**
 * Excepci�n provocada cuando se intenta acceder a un elemento que no existe
 * en la lista.
 * 
 */ 
class ElementoInexistenteException {
    
    private:
        std::string mensaje;
    
    public:
        ElementoInexistenteException(std::string mensaje) {
            
            this->setMensaje(mensaje);
        }
        
        virtual ~ElementoInexistenteException() {
            
        }

        std::string getMensaje() {
            
            return this->mensaje;
        }
        
    protected:
        
        void setMensaje(std::string mensaje) {
            
            this->mensaje = mensaje;
        }
};

#endif
