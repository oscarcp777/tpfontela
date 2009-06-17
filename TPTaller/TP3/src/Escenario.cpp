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
#include "Define.h"
#include "GraficadorPuntajes.h"


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
	this->padJugador = NULL;

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
Rectangulo* Escenario::getArcoDerecha()
{
	return arcoDerecha;
}

void Escenario::setArcoDerecha(Rectangulo *arcoDerecha)
{
	this->arcoDerecha = arcoDerecha;
}

Rectangulo* Escenario::getArcoIzquierda()
{
	return arcoIzquierda;
}

void Escenario::setArcoIzquierda(Rectangulo *arcoIzquierda)
{
	this->arcoIzquierda = arcoIzquierda;
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

	SDL_Surface *imagen;
	std::list<Figura*>::iterator iter;
	iter = this->iteratorListaFiguras();
	int res = this->texturaEsc.compare("NULL");

	if( res!=0){

		if(this->fondoPantalla==NULL){
			//si no tiene NULL en texturaEsc
			std::string path = this->obtenerPathTextura(this->texturaEsc);

			if(path.compare("NULL") != 0){
				//si se encontro el path de la textura
				imagen = IMG_Load (path.begin());
				if(imagen == NULL) {
					escribirMensajeLog(this->log,"error al intentar cargar la imagen: "+path);
					SDL_Rect dest;
					dest.x = 0;
					dest.y = 0;
					dest.w = this->screen->w;
					dest.h = this->screen->h;
					SDL_Color color = this->getColorFondoEscenario();
					SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format, color.r,color.g,color.b));
				}
				if(imagen != NULL){
					imagen = Figura::ScaleSurface(imagen, this->getAncho(), this->getAlto());
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
			this->fondoPantalla=SDL_DisplayFormat(imagen);
			 SDL_FreeSurface(imagen);
		}
		if(this->fondoPantalla != NULL){
			SDL_Rect rect;
			rect.x =0;
			rect.y =0;
			rect.w = this->getAncho();
			rect.h = this->getAlto();
			SDL_BlitSurface(this->fondoPantalla, NULL,this->screen, &rect);

			// dibujo los arcos
			this->arcoDerecha->dibujar(this->screen);
			this->arcoIzquierda->dibujar(this->screen);
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
Posicion* Escenario::getPosicionInicialTejo()
{
	return posicionInicialTejo;
}

void Escenario::setPosicionInicialTejo(Posicion *posicionInicialTejo)
{
	this->posicionInicialTejo = posicionInicialTejo;
}
int Escenario::iniciarSDL(){

	// Iniciar SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
		std::string aux = SDL_GetError();
		escribirMensajeLog(this->log,"No se pudo iniciar SDL: " + aux );
		exit(1);
	}
	atexit(SDL_Quit);

	// Comprobamos que sea compatible el modo de video

	if(SDL_VideoModeOK(this->getAncho(), this->getAlto(), 24, SDL_SWSURFACE|SDL_DOUBLEBUF) == 0) {

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

	this->screen = SDL_SetVideoMode(this->getAncho(),this->getAlto(),24, SDL_SWSURFACE | SDL_DOUBLEBUF );

	if(!this->screen){
		std::cout<<"No se pudo iniciar la pantalla: %s"<<SDL_GetError();
		std::string aux = SDL_GetError();
		escribirMensajeLog(this->log,"No se pudo iniciar la pantalla: " + aux );
		exit(1);
	}
	return 0;

}



int Escenario::graficar(){
	
		SDL_Event evento;
		Teclado teclado;
		Pad* pad;

		teclado.actualizar();
		// Actualización lógica de la posición
		pad = this->getPadJugador();	


		if(teclado.pulso(Teclado::TECLA_SUBIR)) {
			if(pad->getY()>0)
				pad->subir_y();
		}

		if(teclado.pulso(Teclado::TECLA_BAJAR)) {
			if(pad->getY()<this->getAlto() - pad->getAltura())
				pad->bajar_y();
		}

		this->pintarPantalla();
		
		this->getPadCliente1()->dibujar(this->screen);
		this->getPadCliente2()->dibujar(this->screen);	    
		
		GraficadorPuntajes* graficadorPuntajes=GraficadorPuntajes::obtenerInstancia();
		graficadorPuntajes->graficarPuntaje(this->getScreen());
		graficadorPuntajes->graficarCantidadDeTejos(this->getScreen());
		
		this->getTejo()->dibujar(this->screen);

		SDL_Flip(this->getScreen());


		while (SDL_PollEvent(&evento)) {
			if(evento.type == SDL_QUIT)
				return -1;
			
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
/*void Escenario::setNumJugador(int num){
	this->numJugador = num;
}
*/
int Escenario::getNumJugador(){
	return this->numJugador;
}

Pad* Escenario::getPadJugador(){
		return this->padJugador;
}

void Escenario::setPadJugador(int jugador){

	if (jugador == 1){
			this->padJugador = this->getPadCliente1();
			this->numJugador=1;
	}
	else{
			this->padJugador = this->getPadCliente2();
			this->numJugador=2;

	}
}