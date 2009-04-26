#include "Color.h"


Color::Color(){
}
Color::~Color(){
	delete this;
}

Color::Color(int colorFondo_R,int colorFondo_G,int colorFondo_B){
	this->colorFondo_R=colorFondo_R;
    this->colorFondo_G=colorFondo_G;
    this->colorFondo_B=colorFondo_B;
}
int  Color::getColorFondo_R(){
	return this->colorFondo_R;
}
int Color::getColorFondo_G(){
      return this->colorFondo_G;
}
int  Color::getColorFondo_B(){
	return this->colorFondo_B;
}