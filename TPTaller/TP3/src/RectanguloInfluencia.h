/*
 * RectanguloInfluencia.h
 *
 *  Created on: 31/05/2009
 *      Author: oscar
 */

#ifndef __RECTANGULOINFLUENCIA_H__
#define __RECTANGULOINFLUENCIA_H__
#include <iostream>
class RectanguloInfluencia {
public:
	RectanguloInfluencia(int x,int y, int w,int h,std::string posicion);
	 ~RectanguloInfluencia();
    std::string getPosicionRectangulo();
    void setPosicionRectangulo(std::string posicionRectangulo);

    int getX();

    void setX(int x);
    int getY();
    void setY(int y);
    int getW();
    void setW(int w);
    int getH();

    void setH(int h);
private:
	  std::string posicionRectangulo;
	  int x;
	  int y;
	  int w;
	  int h;

};

#endif /* RECTANGULOINFLUENCIA_H_ */
