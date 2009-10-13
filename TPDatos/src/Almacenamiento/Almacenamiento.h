/*
 * Almacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ALMACENAMIENTO_H_
#define ALMACENAMIENTO_H_



#include "../Composite/Compuesto.h"
#include "../Composite/Componente.h"
#include "../Object/Object.h"
#include <fstream>
class Almacenamiento:public Object{
protected:
	std::fstream  archivo;
private:
    Compuesto *compuesto;
    std::string nombreArchivo;
    std::string ruta;
    int tamanio;
    std::string tipoArchivo;
public:

    Almacenamiento();
    virtual ~Almacenamiento();
    Compuesto *getCompuesto();
    std::string toString();

    void agregarComponente(Componente *componente);
    std::string getNombreArchivo();
    std::string getRuta();
    std::string getPath();
    void setNombreArchivo(std::string nombreArchivo);
    void setRuta(std::string ruta);
    int getTamanio();
    void setTamanio(int tamanio);

    virtual void guardar(std::string registro) = 0;
    virtual void guardar(const char* registro,int tamanioRegistro) = 0;
   // virtual std::string leer () = 0;
    virtual void leer(void* datosestrategiaAlmac, int tamanio) = 0;
    virtual void abrirArchivo();
    std::string getTipoArchivo();

    void setTipoArchivo(std::string tipoArchivo);

};

#endif /* ALMACENAMIENTO_H_ */
