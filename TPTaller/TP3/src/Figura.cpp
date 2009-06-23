#include "Figura.h"
#include "Escenario.h"
#include "Define.h"

Figura::Figura(){
	this->colorFigura = NULL;
	this->colorLinea = NULL;
	this->setIdTextura("NULL");
	this->imagen = NULL;
	this->imagenBonus = NULL;

}
SDL_Surface* Figura::getImagenBonus()
   {
       return this->imagenBonus;
   }

void Figura::setImagenBonus(SDL_Surface *imagenBonus)
   {
       this->imagenBonus = imagenBonus;
   }
int Figura::getX(){
  return this->pos->getX();
}
/**
	 * si el bonus esta activo le seteo la imagendel bonus al dispersor
	 */
void Figura::verificarBonusActivo(int base,int altura){
	if(this->imagenBonus!=NULL){
		this->imagenBonus=ScaleSurface(this->imagenBonus, base, altura);

	}
}
std::string Figura::getTipo()
    {
        return tipo;
    }

    void Figura::setTipo(std::string tipo)
    {
        this->tipo = tipo;
    }
int Figura::getY(){
	 return this->pos->getY();
}
int Figura::getXInfluencia()
{
	return xInfluencia;
}

void Figura::setXInfluencia(int xInfluencia)
{
	this->xInfluencia = xInfluencia;
}

int Figura::getYInfluencia()
{
	return yInfluencia;
}

void Figura::setYInfluencia(int yInfluencia)
{
	this->yInfluencia = yInfluencia;
}

int Figura::getAnchoInfluencia()
{
	return anchoInfluencia;
}
void Figura::setTieneBonus(bool tiene){
	this->tieneBonus = tiene;	
}
bool Figura::getTieneBonus(){
	return this->tieneBonus;	
}
void Figura::setAnchoInfluencia(int anchoInfluencia)
{
	this->anchoInfluencia = anchoInfluencia;
}

int Figura::getAltoInfluencia()
{
	return altoInfluencia;
}

void Figura::setAltoInfluencia(int altoInfluencia)
{
	this->altoInfluencia = altoInfluencia;
}

Posicion* Figura::getPosicion(){
	return this->pos;
}

std::list<RectanguloInfluencia*>::iterator Figura::iteratorRectangulosDeInfluencia(){
	return this->rectangulosDeInfluencia.begin();
}
void Figura::addRectanguloInfluencia(RectanguloInfluencia *rectanguloInfluencia){
	this->rectangulosDeInfluencia.push_back(rectanguloInfluencia);

}
void Figura::setEscalada(bool escalada){
	this->escalada = escalada;
}
bool Figura::getEscalada(){
	return this->escalada;
}
int Figura::sizeListaRectangulos(){
	return this->rectangulosDeInfluencia.size();
}
void Figura::setPosicion(Posicion*posicion){
	this->pos = posicion;
}
Figura::~Figura(){
	delete this->colorFigura;
	delete this->colorLinea;

}
std::string Figura::getId(){
	return this->id;
}
void Figura::setId(std::string id){
	this->id = id;
}

void Figura::setIdTextura(std::string idTextura){
	this->idTextura = idTextura;
}
std::string Figura::getIdTextura(){
	return this->idTextura;
}
Color* Figura::getColorLinea()

{
	if (this->colorLinea == NULL)
		return Escenario::obtenerInstancia()->getColorLinea();
	else
		return this->colorLinea;
}

void Figura::setColorLinea(Color *colorLinea)
{
	this->colorLinea = colorLinea;
}

void Figura::setImagen(SDL_Surface *imagen){

	this->imagen = imagen;
}


Color* Figura::getColorFigura()
{
	if (this->colorFigura == NULL)
		return Escenario::obtenerInstancia()->getColorFondoFiguras();
	else
		return this->colorFigura;
}

void Figura::setColorFigura(Color *colorFigura)
{
	this->colorFigura = colorFigura;
}
void Figura::putpixel(SDL_Surface *screen, int x, int y, SDL_Color color)
{
	// Convertimos color
	Uint32 col=SDL_MapRGB(screen->format, color.r, color.g, color.b);
	// Determinamos posición de inicio
	char *buffer=(char*) screen->pixels;
	// Calculamos offset para y
	buffer+=screen->pitch*y;
	// Calculamos offset para x
	buffer+=screen->format->BytesPerPixel*x;
	// Copiamos el pixel
	memcpy(buffer, &col, screen->format->BytesPerPixel);
}

SDL_Color Figura::getpixel(SDL_Surface *imagen, int x, int y)
{
	SDL_Color color;
	Uint32 col;
	// Determinamos posición de inicio
	char *buffer=(char *) imagen->pixels;
	// Calculamos offset para y
	buffer+=imagen->pitch*y;
	// Calculamos offset para x
	buffer+=imagen->format->BytesPerPixel*x;
	// Obtenemos el pixel
	memcpy(&col, buffer, imagen->format->BytesPerPixel);
	// Descomponemos el color
	SDL_GetRGB(col, imagen->format, &color.r, &color.g, &color.b);
	// Devolvemos el color
	return color;
}
//PARA EXPANDIR Y CONTRAER IMAGENES

Uint32 Figura::ReadPixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	//Aqui p es la direccion del pixel que nosotros queremos recuperar
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;

	case 2:
		return *(Uint16 *)p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32 *)p;

	default:
		return 0;       /* por descarte devuelvo 0 */
	}
}

void Figura::DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	//Aqui la direccion del pixel que nosotros queremos setear
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

//Esta es la funcion que usamos para expandir y contraer una imagen
//Esta funcion invoca a readPixel y drawPixel

SDL_Surface* Figura::ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height)
{
	if (!Surface || !Width || !Height)
		return 0;

	SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
			Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

	double  _stretch_factor_x = (static_cast<double>(Width)  / static_cast<double>(Surface->w)),
	_stretch_factor_y = (static_cast<double>(Height) / static_cast<double>(Surface->h));

	for (Sint32 y = 0; y < Surface->h; y++)
		for (Sint32 x = 0; x < Surface->w; x++)
			for (Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
				for (Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
					DrawPixel(_ret, static_cast<Sint32>(_stretch_factor_x * x) + o_x,
							static_cast<Sint32>(_stretch_factor_y * y) + o_y, ReadPixel(Surface, x, y));

	return _ret;
}


void Figura::dibujarLinea(SDL_Color color,SDL_Surface *screen ,int x1, int y1, int x2, int y2){

	this->color = color;
	bool steep = abs(y2-y1) > abs(x2-x1);
	if( steep )
	{
		int t = x1;
		x1 = y1;
		y1 = t;
		t = x2;
		x2 = y2;
		y2 = t;
	}
	if( x1 > x2 )
	{
		int t = x1;
		x1 = x2;
		x2 = t;
		t = y1;
		y1 = y2;
		y2 = t;
	}
	int dx = x2 - x1;
	int dy = abs(y2-y1);
	int error = 0;
	int ystep = 0;
	int y = y1;
	if( y1 < y2 ) ystep = 1; else ystep = -1;
	for(int x = x1; x < x2; x++ )
	{
		if( steep )
		{
			plot(screen, y, x, color );
		}
		else
		{
			plot( screen, x, y, color );
		}
		error = error + dy;
		if( 2*error >= dx )
		{
			y = y + ystep;
			error = error - dx;
		}
	}
}

void Figura::plot( SDL_Surface* surface, int x, int y, SDL_Color color )
{
	if( x >= 0 && x < surface->w && y >= 0 && y < surface->h )
	{
		unsigned int* p = (unsigned int*) surface->pixels;
		p[(y*(surface->pitch/4))+x] = SDL_MapRGB(surface->format, color.r, color.g, color.b);
	}
}
