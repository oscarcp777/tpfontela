#ifndef _POSICION_H_
#define _POSICION_H_

class Posicion {

	public:
		~Posicion();
		Posicion(int posX,int posY);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
		int compare(Posicion*otraPosicion);

	private:
		int x;
		int y;



};

#endif
