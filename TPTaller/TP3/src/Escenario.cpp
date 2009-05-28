#include <stdio.h>
#include <list>
#include <windows.h>
#include "Escenario.h"
#include <utility>
#include "archivoTexto.h"
#include "Posicion.h"
#include "Teclado.h"
#include "Pad.h"
#include "Tejo.h"
#include "ControladorColisiones.h"

//pasar estas constantes a Constantes.h
const int RESOLUCION_640=640;
const int RESOLUCION_640_ALTO=480;
const int RESOLUCION_640_ANCHO=640;
const int RESOLUCION_800=800;
const int RESOLUCION_800_ALTO=600;
const int RESOLUCION_800_ANCHO=800;
const int RESOLUCION_1024=1024;
const int RESOLUCION_1024_ALTO=768;
const int RESOLUCION_1024_ANCHO=1024;
const int RESOLUCION_1280=1280;
const int RESOLUCION_1280_ALTO=768;
const int RESOLUCION_1280_ANCHO=1280;
const int RESOLUCION_BIT=32;
const string configDefaultEscenario = "config Default Escenario.txt";
Escenario::Escenario(){
	//los siguientes son valores por defecto (si existe <General> estos se modificaran)
	this->icono=NULL;
	this->fondoPantalla=NULL;
	this->setResolucion(RESOLUCION_800);
	this->texturaFig = "FigDefault";
	this->texturaEsc = "EscDefault";
	this->setColorFondoEscenario(new Color(0,0,0));
	this->setColorFondoFiguras(new Color(42,0,246));
	this->setColorLinea(new Color(255,0,0));
	inicializarLog(this->log, "errores.err");
	this->validador = new  Validador("config Validador.txt","config Atributos.txt");
	escribirTituloLog(*(this->getLog()),"DESCRIPCION DE ERRORES");
	this->validador->setLog(&(this->log));

	//levanto del archivo siguiente las texturas por default para el escenario
	ArchivoTexto miArchivoDefault(configDefaultEscenario);
	string linea;
	//la primer linea tiene el path de textura para el fondo del pad
	miArchivoDefault.leerLinea(linea);
	//	Textura * fondoPad = new Textura("fondoPad", linea);
	//	this->addTextura(fondoPad);
	//la segunda linea tiene el path de textura escenario por default
	miArchivoDefault.leerLinea(linea);
	Textura * texturaEscDefault = new Textura("EscDefault", linea);
	//
	this->addTextura(texturaEscDefault);
	miArchivoDefault.leerLinea(linea);
	Textura* icono = new Textura("icono", linea);
	//
	this->addTextura(icono);


}

Validador*  Escenario::getValidador(){
	return this->validador;
}
Escenario::~Escenario(){
	//los siguientes son valores por defecto (si existe <General> estos se modificaran)
	destruirLog(this->log);
	delete this->colorLinea;
	delete this->colorFondoEscenario;
	delete this->colorFondoFiguras;
	this->validador->~Validador();
	list<Textura*>::iterator iterTextura;
	Textura* textura;
	iterTextura=this->listaTexturas.begin();
	while(iterTextura !=this->listaTexturas.end()){
		textura=*iterTextura;
		delete textura;
		iterTextura++;
	}
	list<Figura*>::iterator iterFiguras;
	Figura* figura;
	iterFiguras=this->listaFiguras.begin();
	while(iterFiguras !=this->listaFiguras.end()){
		figura=*iterFiguras;
		delete figura;
		iterFiguras++;
	}

}

int Escenario::cargarArchivo(std::string nombreArchivo){
	return this->validador->validarSintaxis(nombreArchivo);

}

Escenario* Escenario::unicaInstanciaEscenario = NULL;
void Escenario::setTexturaFig(std::string texturaFig){
	this->texturaFig=texturaFig;
}
std::string Escenario::getTexturaFig(){
	return this->texturaFig;
}
std::string Escenario::getTexturaEsc(){
	return this->texturaEsc;
}
void Escenario::setTexturaEsc(std::string texturaEsc){
	this->texturaEsc=texturaEsc;
}
Escenario* Escenario::obtenerInstancia(){

	if(!Escenario::unicaInstanciaEscenario){
		Escenario::unicaInstanciaEscenario = new Escenario();
	}

	return Escenario::unicaInstanciaEscenario;
}
void  Escenario::setColorFondoEscenario(Color* colorFondoEscenario){
	this->colorFondoEscenario=colorFondoEscenario;
}
void  Escenario::setColorFondoFiguras(Color* colorFondoFiguras){
	this->colorFondoFiguras=colorFondoFiguras;
}
void  Escenario::setColorLinea(Color* colorLinea){
	this->colorLinea=colorLinea;
}
SDL_Color Escenario::getColorFondoEscenario(){
	return	this->colorFondoEscenario->getColor();
}
Color* Escenario::getColorFondoFiguras(){
	return	this->colorFondoFiguras;
}
Color* Escenario::getColorLinea(){
	return this->colorLinea;
}
void  Escenario::setAncho(int ancho){
	this->ancho=ancho;
}
int   Escenario::getAncho(){
	return	this->ancho;
}
void  Escenario::setAlto(int alto){
	this->alto=alto;
}
int   Escenario::getAlto(){
	return this->alto;
}
int Escenario::getResolucion(){
	return this->resolucion;
}
void  Escenario::setResolucion(int resolucion){
	this->resolucion=resolucion;
	if(resolucion==RESOLUCION_640){
		this->alto=RESOLUCION_640_ALTO;
		this->ancho=RESOLUCION_640_ANCHO;
	}
	if(resolucion==RESOLUCION_800){
		this->alto=RESOLUCION_800_ALTO;
		this->ancho=RESOLUCION_800_ANCHO;
	}
	if(resolucion==RESOLUCION_1024){
		this->alto=RESOLUCION_1024_ALTO;
		this->ancho=RESOLUCION_1024_ANCHO;
	}
	if(resolucion==RESOLUCION_1280){
		this->alto=RESOLUCION_1280_ALTO;
		this->ancho=RESOLUCION_1280_ANCHO;
	}
}
void Escenario::addFigura(Figura *figura){
	//si existe el id de figura tiro error y no lo agrego
	if(this->existeIdFigura(figura->getId())){
		escribirMensajeLog(this->log,"error: idFigura duplicado, ya existia una figura con el id: " + figura->getId() );
	}
	//sino la agrego
	else{
		this->listaFiguras.push_back(figura);
	}
}

void Escenario::addTextura(Textura *textura){
	this->listaTexturas.push_back(textura);

}

int Escenario::sizeListaFiguras(){
	return this->listaFiguras.size();
}


int Escenario::sizeListaTexturas(){
	return this->listaTexturas.size();
}

std::list<Figura*>::iterator Escenario::iteratorListaFiguras(){
	return this->listaFiguras.begin();
}


std::list<Textura*>::iterator Escenario::iteratorListaTexturas(){
	return this->listaTexturas.begin();
}

void Escenario::setIdTextura(std::string idTextura){
	this->texturaEsc = idTextura;
}

Log* Escenario::getLog(){
	return &(this->log);
}


void Escenario::pintarPantalla(){


	std::list<Figura*>::iterator iter;
	iter = this->iteratorListaFiguras();
	int res = this->texturaEsc.compare("NULL");

	if( res!=0){

		if(this->fondoPantalla==NULL){
			//si no tiene NULL en texturaEsc
			std::string path = this->obtenerPathTextura(this->texturaEsc);

			if(path.compare("NULL") != 0){
				//si se encontro el path de la textura
				this->fondoPantalla = IMG_Load (path.begin());
				if(this->fondoPantalla == NULL) {
					escribirMensajeLog(this->log,"error al intentar cargar la imagen: "+path);
											SDL_Rect dest;
											dest.x = 0;
											dest.y = 0;
											dest.w = this->screen->w;
											dest.h = this->screen->h;
											SDL_Color color = this->getColorFondoEscenario();
											SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format, color.r,color.g,color.b));
				}
				if(this->fondoPantalla != NULL){
					this->fondoPantalla = Figura::ScaleSurface(this->fondoPantalla, this->getAncho(), this->getAlto());
				}
			}
			else{
					//si NO se encontro el path de la textura, es porque el id no existe en la lista
					escribirMensajeLog(this->log,"no se encontro el path correspondiente a texturaEsc: "+this->texturaEsc);
					SDL_Rect dest;
					dest.x = 0;
					dest.y = 0;
					dest.w = this->screen->w;
					dest.h = this->screen->h;
					SDL_Color color = this->getColorFondoEscenario();
					SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format, color.r,color.g,color.b));
				}
		}
		if(this->fondoPantalla != NULL){
		SDL_Rect rect;
		rect.x =0;
		rect.y =0;
		rect.w = this->getAncho();
		rect.h = this->getAlto();
		SDL_BlitSurface(this->fondoPantalla, NULL,this->screen, &rect);
		int i = 1;
		Figura *figura;
					while(i<=this->sizeListaFiguras()){
						figura = *iter;
						figura->dibujar(this->screen);
						iter++;
						i++;
					}

		}
	}





}

std::string Escenario::obtenerPathTextura(std::string id){
	std::list<Textura*>::iterator iter;
	Textura *textura;
	iter = this->iteratorListaTexturas();
	int i=1;
	std::string idAux = "NULL";

	while(i<=this->sizeListaTexturas()){
		textura = *iter;

		if(textura->getId().compare(id)==0){
			return textura->getPath();
		}

		else{
			i++;
			iter++;
		}

	}
	return idAux;

}

bool Escenario::existeIdFigura(std::string idFigura){
	bool existe = false;
	std::list<Figura*>::iterator iter;
	Figura *figura;
	iter = this->iteratorListaFiguras();
	int i=1;
	while(i<=this->sizeListaFiguras()){
		figura = *iter;
		if(figura->getId().compare(idFigura) == 0){
			return true;
		}
		else{
			i++;
			iter++;
		}
	}
	return existe;
}

SDL_Surface* Escenario::getScreen(){
	return this->screen;

}

int Escenario::graficar(){

	int done = 0;
	SDL_Event event;


	// Iniciar SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
		std::string aux = SDL_GetError();
		escribirMensajeLog(this->log,"No se pudo iniciar SDL: " + aux );
		return -1;
	}
	atexit(SDL_Quit);

	// Comprobamos que sea compatible el modo de video

	if(SDL_VideoModeOK(this->getAncho(), this->getAlto(), 32, SDL_SWSURFACE|SDL_DOUBLEBUF) == 0) {

		std::cout<< "Modo no soportado: " << SDL_GetError() << endl;
		exit(1);

	}
	if(this->icono==NULL){
		std::string pathIcono =this->obtenerPathTextura("icono");
		std::cout<< "path  " << pathIcono << endl;
		this->icono = IMG_Load(pathIcono.begin());
		if(this->icono == NULL) {
			std::cout<< "Error: " << SDL_GetError() << endl;
			exit(1);
		}
		if(this->icono != NULL){
			this->icono = Figura::ScaleSurface(this->icono,40,40);
		}
	}
	//seteamos el titulo a la barra
	SDL_WM_SetCaption("    Taller de Programacion Grupo Nro:3   GRAFICADOR  "," Taller de Programacion Grupo Nro:3   GRAFICADOR ");
	SDL_WM_SetIcon(icono, NULL); // Compatible con MS Windows

	this->screen = SDL_SetVideoMode(this->getAncho(),this->getAlto(),32, SDL_SWSURFACE | SDL_DOUBLEBUF );

	if(!screen){
		std::cout<<"No se pudo iniciar la pantalla: %s"<<SDL_GetError();
		std::string aux = SDL_GetError();
		escribirMensajeLog(this->log,"No se pudo iniciar la pantalla: " + aux );
		return -1;
	}
	std::cout<< "alto de la pantalla" <<this->screen->h << endl;


	std::list<Figura*>::iterator iter;
	iter = this->iteratorListaFiguras();

	int i = 1;
	Figura *figura;
	Posicion *posicion=  new Posicion(150,150);
	while(i<=this->sizeListaFiguras()){
		figura = *iter;
		//	figura->dibujar(this->screen);
		iter++;
		i++;
	}

	// Teclado para controlar al personaje
	Teclado teclado;

	// Lo mostramos por pantalla
	Pad* padCliente1=this->getPadCliente1();
	Pad* padCliente2=this->getPadCliente2();
	Tejo* tejo=this->getTejo();
	// Variables auxiliares
	SDL_Event evento;
	bool terminar = false;
	int x0, y0,x1,y1,x2,y2;
	this->pintarPantalla();
	tejo->dibujar(this->screen);
	padCliente1->dibujar(this->screen);
	padCliente2->dibujar(this->screen);
	SDL_Flip(this->getScreen());
	// Controlará la dirección con
	// respecto al eje x o y
	int direccion_x = true;
	int direccion_y = false;
	// Game loop

	while(terminar == false) {

		
		// Variables de control para saber si
		// tenemos que refrescar la pantalla o no
//		x2 = tejo->getX();
//		y2 = tejo->getY();
//		if(direccion_x == true && tejo->getX() >= this->getAncho()-tejo->getRadio())
//			direccion_x = false;
//		if(direccion_y == true && tejo->getY() >= this->getAlto()-tejo->getRadio())
//			direccion_y= false;
//		if(direccion_x == false && tejo->getX() <= 0+tejo->getRadio())
//			direccion_x = true;
//		if(direccion_y == false && tejo->getY() <= 0+tejo->getRadio())
//			direccion_y = true;
//
//		if(direccion_x == true)
			ControladorColisiones::calcularDireccion();
			tejo->mover_x();
			tejo->mover_y();
//		else
//			tejo->retrasar_x();
//		if(direccion_y == true)
//			tejo->bajar_y();
//		else
//			tejo->subir_y();

		// Actualizamos el estado del teclado

		teclado.actualizar();

		// Variables de control para saber si
		// tenemos que refrescar la pantalla o no


		y0 = padCliente1->getY();
		y1 = padCliente2->getY();

		// Actualización lógica de la posición
		if(teclado.pulso(Teclado::TECLA_SUBIR_PAD1)) {
			if(padCliente1->getY()>=0)
				padCliente1->subir_y();
		}

		if(teclado.pulso(Teclado::TECLA_BAJAR_PAD1)) {
			if(padCliente1->getY()<450)
				padCliente1->bajar_y();
		}
		if(teclado.pulso(Teclado::TECLA_SUBIR_PAD2)) {
			if( padCliente2->getY()>=0)
				padCliente2->subir_y();
		}

		if(teclado.pulso(Teclado::TECLA_BAJAR_PAD2)) {
			if(padCliente2->getY()<450)
				padCliente2->bajar_y();
		}


		if(x2 != tejo->getX() || y2 != tejo->getY()) {

					 Uint32 negro = SDL_MapRGB(this->screen->format, 87,122,18);

					 SDL_FillRect(this->screen, NULL, negro);
//	     this->pintarPantalla();
			padCliente1->dibujar(this->screen);
			SDL_UpdateRect(this->screen,padCliente1->getX(),padCliente1->getY(), padCliente1->getFigura()->getBase(), padCliente1->getFigura()->getAltura());
			padCliente2->dibujar(this->screen);
			SDL_UpdateRect(this->screen,padCliente2->getX(),padCliente2->getY(), padCliente2->getFigura()->getBase(), padCliente2->getFigura()->getAltura());
			
			
			tejo->borrarTejo();
			tejo->dibujar(this->screen);

			ControladorColisiones::posibilidadDeColisionDispersores();
//		SDL_Flip(this->getScreen());
             Sleep(1000/tejo->getVelocidad());
			 
			SDL_UpdateRect(this->screen,tejo->getX()-tejo->getRadio(),tejo->getY()-tejo->getRadio(), tejo->getFigura()->getRadio()*2,tejo->getFigura()->getRadio()*2);
			
		}


		// Control de Eventos

		while (SDL_PollEvent(&evento)) {
			if(evento.type == SDL_KEYDOWN) {
				if(evento.key.keysym.sym == SDLK_ESCAPE)
					terminar = true;
			}
			if(evento.type == SDL_QUIT){
				terminar = true;
			}
		}

	}

	return 0;
}

void Escenario::setPadCliente1(Pad *padCliente1){
	this->padCliente1 = padCliente1;
}

void Escenario::setPadCliente2(Pad *padCliente2){
	this->padCliente2 = padCliente2;
}

void Escenario::setTejo(Tejo *tejo){
	this->tejo = tejo;
}

Pad* Escenario::getPadCliente1(){
	return this->padCliente1;
}

Pad* Escenario::getPadCliente2(){
	return this->padCliente2;
}

Tejo* Escenario::getTejo(){
	return this->tejo;
}
