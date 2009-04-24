#ifndef _POSICION_H_
#define _POSICION_H_

class Posicion {

	public: 
		Posicion(int posX,int posY);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
	private:
		int x;
		int y;
		
		

};

#endif