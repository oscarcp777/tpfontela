#ifndef __TRIANGULO_H__
#define __TRIANGULO_H__

#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>

class Triangulo: public Figura {


	public:
		Triangulo();
		~Triangulo();
		Triangulo(std::string id,Posicion *ver1,Posicion *ver2, Posicion *ver3);
		void setVertice1(Posicion * posicion);
		void setVertice2(Posicion * posicion);
		void setVertice3(Posicion * posicion);
		Posicion* getVertice1();
		Posicion* getVertice2();
		Posicion* getVertice3();
		int dibujar(SDL_Surface *screen);
		void calcularRadioDeInfluencia();
    int getLado();

    void setLado(int lado);
private:
		Posicion *vertice1;
		Posicion *vertice2;
		Posicion *vertice3;
		int lado;
		void graficarPixel(SDL_Surface *screen, int i, int j, Posicion* ejeDeCoordenadas);



};

#endif
