#include "Color.h"
#include "Define.h"
#include <iostream>


Color::~Color(){
	 if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Color"<<std::endl;
}
Color::Color(){
}

SDL_Color Color::getColor(){
	return this->color;
}
void Color::setColor(SDL_Color color){
	 this->color=color;
}
Color::Color(int colorFondo_R,int colorFondo_G,int colorFondo_B){
	this->color.r = colorFondo_R;
	this->color.g = colorFondo_G;
	this->color.b = colorFondo_B;
}
int  Color::getColorFondo_R(){
	return this->color.r;
}
int Color::getColorFondo_G(){
      return this->color.g;
}
int  Color::getColorFondo_B(){
	return this->color.b;
}

