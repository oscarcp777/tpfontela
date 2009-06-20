/*
 * RectanguloInfluencia.cpp
 *
 *  Created on: 31/05/2009
 *      Author: oscar
 */
#include "RectanguloInfluencia.h"

RectanguloInfluencia::RectanguloInfluencia(int x,int y, int w,int h,std::string posicion) {
    this->posicionRectangulo=posicion;
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
}

RectanguloInfluencia::~RectanguloInfluencia() {
	// TODO Auto-generated destructor stub
}
std::string RectanguloInfluencia::getPosicionRectangulo()
    {
        return this->posicionRectangulo;
    }
void RectanguloInfluencia::setPosicionRectangulo(std::string posicionRectangulo)
{
    this->posicionRectangulo = posicionRectangulo;
}

int RectanguloInfluencia::getX()
{
    return x;
}

void RectanguloInfluencia::setX(int x)
{
    this->x = x;
}

int RectanguloInfluencia::getY()
{
    return y;
}

void RectanguloInfluencia::setY(int y)
{
    this->y = y;
}

int RectanguloInfluencia::getW()
{
    return w;
}

void RectanguloInfluencia::setW(int w)
{
    this->w = w;
}

int RectanguloInfluencia::getH()
{
    return h;
}

void RectanguloInfluencia::setH(int h)
{
    this->h = h;
}
