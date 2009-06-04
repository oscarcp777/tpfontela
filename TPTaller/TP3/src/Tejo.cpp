/*
 * Tejo.cpp
 *
 *  Created on: 17/05/2009
 *      Author: oscar
 */

#include "Tejo.h"
#include "Circulo.h"
#include <math.h>
#include "Escenario.h"
#include "Define.h"
Tejo::Tejo() {
	// TODO Auto-generated constructor stub

}
Circulo* Tejo::getFigura(){
	return	this->circulo;
}

Tejo::Tejo(Circulo* circulo){
	this->circulo=circulo;
	std::cout<< "padv1: "  <<this->circulo->getIdTextura()<< endl;
	this->imagen=NULL;
	this->direccion = new Direccion();

}
void Tejo::cargarRadioDeInfluencia(){


	for(int i=0;i<8;i++){
		double angulo=i*PI/4;
		Posicion* posicion= new Posicion((int)getRadio()*cos(angulo)+getX(),(int)getRadio()*sin(angulo)+getY());
		this->puntosDeInfluencia.push_back(posicion);
		//	  	std::cout<<"puntos de influencia "<<"("<<posicion->getX()<<","<<posicion->getY()<<")"<<"iter"<<angulo<<endl;
		//		system("PAUSE");
	}
}
std::vector<Posicion*> Tejo::getPuntosDeInfluencia()
{
	return puntosDeInfluencia;
}

void Tejo::setPuntosDeInfluencia(std::vector<Posicion*> puntosDeInfluencia)
{
	this->puntosDeInfluencia = puntosDeInfluencia;
}
void Tejo::borrarTejo(){
	Escenario* escenario=Escenario::obtenerInstancia();
	SDL_Rect rectangulo;
	rectangulo.x=this->getXAnterior()-this->getRadio();
	rectangulo.y=this->getYAnterior()-this->getRadio();
	rectangulo.w=this->getFigura()->getRadio()*2;
	rectangulo.h=this->getFigura()->getRadio()*2;

	SDL_FillRect(escenario->getScreen(),&rectangulo,SDL_MapRGB(escenario->getScreen()->format,87,122,18));
	//	SDL_UpdateRect(escenario->getScreen(),this->getXAnterior()-this->getRadio(),this->getYAnterior()-this->getRadio(), this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);
}

int Tejo::getVelocidad()
{
	return velocidad;
}

void Tejo::setVelocidad(int velocidad)
{
	this->velocidad = velocidad;
}
void Tejo::dibujar(SDL_Surface *pantalla){
    SDL_Surface* image;
	//	 Cargamos la imagen
	if(this->imagen==NULL){
		std::string path = Escenario::obtenerInstancia()->obtenerPathTextura(this->circulo->getIdTextura());
		image = IMG_Load(path.begin());
		//			this->imagen = SDL_LoadBMP(path.begin());
		if(image == NULL) {
			std::cout<< "Error: " << SDL_GetError() << endl;
			exit(1);
		}
		//si la imagen no es null (es decir si la levanto bien) la escalo
		if(image != NULL){
			image = this->getFigura()->ScaleSurface(image, this->getFigura()->getRadio()*2,this->getFigura()->getRadio()*2);
		}
		//			// Calculamos el color transparente, en nuestro caso el verde
		SDL_SetColorKey(image,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(image->format,255 ,255, 255));
		this->imagen = SDL_DisplayFormat(image);
		  SDL_FreeSurface(image);
	}
	SDL_Rect rect;
	rect.x =this->getX()-this->getRadio();
	rect.y = this->getY()-this->getRadio();

	SDL_BlitSurface(this->imagen, NULL, pantalla, &rect);


}
Tejo::~Tejo() {
	// TODO Auto-generated destructor stub
}
int Tejo::getX(){
	return this->circulo->getPosicion()->getX();
}
int Tejo::getY(){
	return this->circulo->getPosicion()->getY();
}
void Tejo::setX(int x){
	this->circulo->getPosicion()->setX(x);
}
void Tejo::setY(int y){
	this->circulo->getPosicion()->setY(y);
}
// El movimiento de la imagen se establece

void Tejo::mover_x() {
	Escenario* escenario= Escenario::obtenerInstancia();
	//	borrarTejo();
	int x =this->getX();
	if(x>=escenario->getAncho()-this->getRadio()){
		x += PIXELES_SALTO*-1;
	}else{
		if(x<=this->getRadio()){
			x += PIXELES_SALTO;
		}else{
			this->setXAnterior(x);
			double res = cos(this->direccion->getFi());
			if(res>0.5){
				x += PIXELES_SALTO;
			}else{
				if(res<-0.5){
					x += PIXELES_SALTO*-1;
				}
			}
		}
	}
	this->setX(x);
//	std::cout<<"posicion X :"<<x<<endl;
}
/*void Tejo::retrasar_x() {
//	borrarTejo();
	int x =this->getX();
	x -= PIXELES_SALTO;
	this->setX(x);
}
void Tejo::bajar_y() {
//	borrarTejo();
	int y =this->getY();
	y += PIXELES_SALTO;
	this->setY(y);
}*/
void Tejo::mover_y() {
	//	borrarTejo();
	int y =this->getY();
	Escenario* escenario= Escenario::obtenerInstancia();
		//	borrarTejo();

		if(y>=escenario->getAlto()-this->getRadio()){
			y += PIXELES_SALTO*-1;
		}else{
			if(y<=this->getRadio()){
				y += PIXELES_SALTO;
			}else{
				this->setYAnterior(y);
				double res =sin(this->direccion->getFi());
				if(res>0.5){
					y -= PIXELES_SALTO;
				}else{
					if(res<-0.5){
						y -= PIXELES_SALTO*-1;
					}
				}
			}
		}
	this->setY(y);
//	std::cout<<"posicion Y :"<<y<<endl;
}
int Tejo::getRadio(){
	return this->circulo->getRadio();
}

Direccion* Tejo::getDireccion(){
	return this->direccion;
}

int Tejo::getXAnterior(){
	return this->XAnterior;
}
int Tejo::getYAnterior(){
	return this->YAnterior;
}
void Tejo::setXAnterior(int x){
	this->XAnterior = x;
}
void Tejo::setYAnterior(int y){
	this->YAnterior = y;
}


