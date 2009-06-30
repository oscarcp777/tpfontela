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
	this->bonusActual = NULL;

	//levanto del archivo siguiente las texturas por default para el escenario
	ArchivoTexto miArchivoDefault(configDefaultEscenario);
	string linea;
	//la primera linea tiene el path de textura escenario por default
	miArchivoDefault.leerLinea(linea);
	Textura * texturaEscDefault = new Textura("EscDefault", linea);
	//
	this->addTextura(texturaEscDefault);
	this->tejosRestantes = 7;
	this->numeroNivel = 1;
	this->primerPintada = false;


}

void Escenario::servidorInicializarListaBonus(){


	DecLongPad* decLongPad = new DecLongPad();
	decLongPad->setTipoBonus(DEC_LONG_PAD);
	this->listaBonus.push_back(decLongPad);

	DecLongPadVs* decLongPadVs = new DecLongPadVs();
	decLongPadVs->setTipoBonus(DEC_LONG_PAD_VS);
	this->listaBonus.push_back(decLongPadVs);

	DecRadioTejo* decRadioTejo = new DecRadioTejo();
	decRadioTejo->setTipoBonus(DEC_RADIO_TEJO);
	this->listaBonus.push_back(decRadioTejo);

	IncLongPad* incLongPad = new IncLongPad();
	incLongPad->setTipoBonus(INC_LONG_PAD);
	this->listaBonus.push_back(incLongPad);

	IncLongPadVs* incLongPadVs = new IncLongPadVs();
	incLongPadVs->setTipoBonus(INC_LONG_PAD_VS);
	this->listaBonus.push_back(incLongPadVs);

	IncRadioTejo* incRadioTejo = new IncRadioTejo();
	incRadioTejo->setTipoBonus(INC_RADIO_TEJO);
	this->listaBonus.push_back(incRadioTejo);


	IncVelocidadTejo* incVelocidadTejo = new IncVelocidadTejo();
	incVelocidadTejo->setTipoBonus(INC_VELOCIDAD_TEJO);
	this->listaBonus.push_back(incVelocidadTejo);

	PegamentoTejo* pegamentoTejo = new PegamentoTejo();
	pegamentoTejo->setTipoBonus(PEGAMENTO_TEJO);
	this->listaBonus.push_back(pegamentoTejo);

	FrenoTejo* frenoTejo = new FrenoTejo();
	frenoTejo->setTipoBonus(FRENO_TEJO);
	this->listaBonus.push_back(frenoTejo);


}


void Escenario::clienteInicializarListaBonus(){

	DecLongPad* decLongPad = new DecLongPad();
	decLongPad->setTipoBonus(DEC_LONG_PAD);
	decLongPad->cargarImagen("decLongPad");
	this->listaBonus.push_back(decLongPad);
	
	DecLongPadVs* decLongPadVs = new DecLongPadVs();
	decLongPadVs->setTipoBonus(DEC_LONG_PAD_VS);
	decLongPadVs->cargarImagen("decLongPadVs");
	this->listaBonus.push_back(decLongPadVs);
	

	DecRadioTejo* decRadioTejo = new DecRadioTejo();
	decRadioTejo->setTipoBonus(DEC_RADIO_TEJO);
	decRadioTejo->cargarImagen("decRadioTejo");
	this->listaBonus.push_back(decRadioTejo);
	
	IncLongPad* incLongPad = new IncLongPad();
	incLongPad->setTipoBonus(INC_LONG_PAD);
	incLongPad->cargarImagen("incLongPad");
	this->listaBonus.push_back(incLongPad);
	
	IncLongPadVs* incLongPadVs = new IncLongPadVs();
	incLongPadVs->setTipoBonus(INC_LONG_PAD_VS);
	incLongPadVs->cargarImagen("incLongPadVs");
	this->listaBonus.push_back(incLongPadVs);

	IncRadioTejo* incRadioTejo = new IncRadioTejo();
	incRadioTejo->setTipoBonus(INC_RADIO_TEJO);
	incRadioTejo->cargarImagen("incRadioTejo");
	this->listaBonus.push_back(incRadioTejo);

	IncVelocidadTejo* incVelocidadTejo = new IncVelocidadTejo();
	incVelocidadTejo->setTipoBonus(INC_VELOCIDAD_TEJO);
	incVelocidadTejo->cargarImagen("incVelocidadTejo");
	this->listaBonus.push_back(incVelocidadTejo);


	PegamentoTejo* pegamentoTejo = new PegamentoTejo();
	pegamentoTejo->setTipoBonus(PEGAMENTO_TEJO);
	pegamentoTejo->cargarImagen("pegamentoTejo");
	this->listaBonus.push_back(pegamentoTejo);


	FrenoTejo* frenoTejo = new FrenoTejo();
	frenoTejo->setTipoBonus(FRENO_TEJO);
	frenoTejo->cargarImagen("frenoTejo");
	this->listaBonus.push_back(frenoTejo);
}

void Escenario::shuffleListBonus(){

		list<Bonus*>::iterator begin = this->listaBonus.begin();
		list<Bonus*>::iterator end = this->listaBonus.end();
		list<Bonus*>::iterator p = begin;

		for (int i = this->listaBonus.size(); i > 0; --i) {
			for (int r = rand(); r > 0; --r) {
				if (++p == end)
					p = begin;
				}
			swap<Bonus*>(*begin, *p);
		}
	
}

int Escenario::shuffleListFiguras(){
	int res = -1;
	if(this->sizeListaFiguras()>0){
		res = 0;
		list<Figura*>::iterator begin = this->listaFiguras.begin();
		list<Figura*>::iterator end = this->listaFiguras.end();
		list<Figura*>::iterator p = begin;

		for (int i = this->listaFiguras.size(); i > 0; --i) {
			for (int r = rand(); r > 0; --r) {
				if (++p == end)
				p = begin;
			}
			swap<Figura*>(*begin, *p);
		}
	}
	return res;
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
	SDL_FreeSurface(this->icono);
	SDL_FreeSurface(this->fondoPantalla);
	SDL_FreeSurface(this->buffer);

	delete this->tejo;
	delete this->padCliente1;
	delete this->padCliente2;
	destruirLog(this->log);
	delete this->colorLinea;
	delete this->colorFondoEscenario;
	delete this->colorFondoFiguras;
	delete this->validador;

	delete this->arcoDerecha;
	delete this->arcoIzquierda;
	delete this->posicionInicialTejo;
	this->borrarListaFiguras();
	this->borrarListaTexturas();
	this->borrarListaBonus();
	 if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al destructor de Escenario"<<std::endl;


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

int Escenario::sizeListaBonus(){
	return this->listaBonus.size();
}

int Escenario::sizeListaTexturas(){
	return this->listaTexturas.size();
}

std::list<Figura*>::iterator Escenario::iteratorListaFiguras(){
	return this->listaFiguras.begin();
}
std::list<Bonus*>::iterator Escenario::iteratorListaBonus(){
	return this->listaBonus.begin();
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
			SDL_BlitSurface(this->fondoPantalla, NULL,this->buffer, &rect);

			// dibujo los arcos
			this->arcoDerecha->dibujar(this->buffer);
			this->arcoIzquierda->dibujar(this->buffer);
			int i = 1;
			Figura *figura;
			while(i<=this->sizeListaFiguras()){
				figura = *iter;
				figura->dibujar(this->buffer);
				iter++;
				i++;
			}
			GraficadorPuntajes* graficadorPuntajes=GraficadorPuntajes::obtenerInstancia();
			graficadorPuntajes->graficarPuntaje(this->buffer);
			graficadorPuntajes->graficarCantidadDeTejos(this->buffer);
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

Figura* Escenario::getFiguraPorId(std::string idFigura){
	std::list<Figura*>::iterator iter;
	Figura *figura = NULL;
	iter = this->iteratorListaFiguras();
	int i=1;

	while(i<=this->sizeListaFiguras()){
		figura = *iter;
		if(figura->getId().compare(idFigura) == 0){
			return figura;
		}
		else{
			i++;
			iter++;
		}
	}
	return figura;



}

Bonus* Escenario::obtenerBonusPorTipo(int tipo){

	std::list<Bonus*>::iterator iter;
	Bonus *bonus;
	iter = this->iteratorListaBonus();
	int i=1;
	while(i<=this->sizeListaBonus()){
		bonus = *iter;
		if(bonus->getTipoBonus() == tipo ){
			return bonus;
		}
		else{
			i++;
			iter++;
		}
	}

	return bonus;


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
	//seteamos el titulo a la barra
	SDL_WM_SetCaption("    Taller de Programacion Grupo Nro:3   GRAFICADOR  "," Taller de Programacion Grupo Nro:3   GRAFICADOR ");
	//SDL_WM_SetIcon(icono, NULL); // Compatible con MS Windows

	this->screen = SDL_SetVideoMode(this->getAncho(),this->getAlto(),16, SDL_SWSURFACE | SDL_DOUBLEBUF );
	this->buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, this->getAncho(), this->getAlto(), 16,
					     0,0,0,0);

	if(!this->screen){
		std::cout<<"No se pudo iniciar la pantalla: %s"<<SDL_GetError();
		std::string aux = SDL_GetError();
		escribirMensajeLog(this->log,"No se pudo iniciar la pantalla: " + aux );
		exit(1);
	}
	return 0;

}



int Escenario::graficar(){
	SDL_Rect rect;
			rect.x =0;
			rect.y =0;
			rect.w = this->getAncho();
			rect.h = this->getAlto();
	
		Pad* pad;

		
		// Actualización lógica de la posición
		pad = this->getPadJugador();

		if (!primerPintada){
		this->pintarPantalla();
			primerPintada = true;
		}

		SDL_BlitSurface(this->buffer, NULL,this->screen, &rect);

		this->getPadCliente1()->dibujar(this->screen);
		this->getPadCliente2()->dibujar(this->screen);


		this->getTejo()->dibujar(this->screen);


		SDL_Flip(this->getScreen());
		SDL_FreeSurface(this->screen);


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

int Escenario::getTejosRestantes(){
	return this->tejosRestantes;
}

void Escenario::decrementarTejosRestantes(){
	this->tejosRestantes--;
}
bool Escenario::getCorriendo(){
	return this->corriendo;
}
void Escenario::setCorriendo(bool corriendo){
	this->corriendo = corriendo;
}
void Escenario::setTejosRestantes(int cantTejos){
	this->tejosRestantes = cantTejos;
}
int Escenario::getNumeroNivel(){
	return this->numeroNivel;
}

void Escenario::incrementarNivel(){
	this->numeroNivel++;
}
std::string Escenario::getNumeroNivelEnString(){
		std::string cadena;
		char num[10];
		char* pNum = num;
		char aux1[5];
		char* paux1 = aux1;
		memset(paux1,0,sizeof(char)*5);
		memset(pNum,0,sizeof(char)*10);
		itoa(this->numeroNivel,paux1,10);
		strcat(pNum,paux1);
		cadena = pNum;
		return cadena;

}
void Escenario::borrarListaFiguras(){
	list<Figura*>::iterator iterFiguras;
	Figura* figura;
	iterFiguras=this->listaFiguras.begin();
	while(iterFiguras !=this->listaFiguras.end()){
		figura=*iterFiguras;
		delete figura;
		iterFiguras++;
	}
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al borrarListaFiguras"<<endl<<endl;
	this->listaFiguras.clear();
}

void Escenario::borrarListaTexturas(){
	list<Textura*>::iterator iterTextura;
	Textura* textura;
	iterTextura=this->listaTexturas.begin();
	while(iterTextura !=this->listaTexturas.end()){
		textura=*iterTextura;
		delete textura;
		iterTextura++;
	}
	if(DEBUG_DESTRUCTOR==1)
		std::cout<<" entro al borrarListaTexturas"<<endl<<endl;
	this->listaTexturas.clear();

}

void Escenario::borrarListaBonus(){
	list<Bonus*>::iterator iterBonus;
	Bonus* bonus;
		iterBonus=this->listaBonus.begin();
		while(iterBonus !=this->listaBonus.end()){
			bonus=*iterBonus;
			delete bonus;
			iterBonus++;
		}
		if(DEBUG_DESTRUCTOR==1)
			std::cout<<" entro al borrarListaBonus"<<endl<<endl;
	this->listaBonus.clear();

}

void Escenario::setearImagenesEnNull(){
		this->fondoPantalla = NULL;
		this->tejo->setImagen(NULL);
		this->padCliente1->setImagen(NULL);
		this->padCliente2->setImagen(NULL);
		this->arcoDerecha->setImagen(NULL);
		this->arcoIzquierda->setImagen(NULL);
		GraficadorPuntajes::obtenerInstancia()->setImagen(NULL);

}
int Escenario::getPosicionYPad(){
	return this->posicionYPad;
}
void Escenario::setPosicionYPad(int pos){
	this->posicionYPad = pos;

}
void Escenario::setGolDe(std::string pad){
	this->golDe = pad;
}
std::string Escenario::getGolDe(){
	return this->golDe;
}
void Escenario::setBonusActual(Bonus* bonus){
	this->bonusActual = bonus;
}
Bonus* Escenario::getBonusActual(){
	return this->bonusActual;
}
void Escenario::setFiguraConBonus(Figura*  figura){
	this->figuraConBonus = figura;
}
Figura* Escenario::getFiguraConBonus(){
	return this->figuraConBonus;
}
void Escenario::setPrimerPintada(bool primerPintada){
	this->primerPintada = primerPintada;

}
bool Escenario::getPrimerPintada(){
	return this->primerPintada;
}
