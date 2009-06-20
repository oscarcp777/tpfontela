#ifndef __TRIANGULO_H__
#define __TRIANGULO_H__

#include "Figura.h"
#include "Posicion.h"
#include <iostream.h>
#include "Recta.h"
#include "define.h"

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
		Recta* getRecta1();
		Recta* getRecta2();
		Recta* getRecta3();

		int dibujar(SDL_Surface *screen);
		void calcularRadioDeInfluencia();
		Recta* obtenerRectaTriangulo(Posicion*posicion,Posicion*otraPosicion);
		std::string getBase();
		int getLado();
		void setLado(int lado);
		void setBase(std::string base);
		void asignarPuntosRectaBase(Recta*recta);
		int isBase(Recta*recta);
	
	private:
		Posicion *vertice1;
		Posicion *vertice2;
		Posicion *vertice3;
		Recta *recta1;
		Recta *recta2;
		Recta *recta3;
		int x1; //posiciones de la base del triangulo
		int y1;
		int x2;
		int y2;
		int lado;
		std::string base; //me dice donde esta la base del triangulo, abajo, arriba, derecha, izquierda
		void graficarPixel(SDL_Surface *screen, int i, int j, Posicion* ejeDeCoordenadas);
		void darNombreBaseTriangulo(Posicion*posicion1,Posicion*posicion2,Posicion*posicion3);



};

#endif
