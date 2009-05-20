#include "Hidratar.h"
#include "Escenario.h"
#include "StringUtils.h"
#include "Validador.h"
#include "Segmento.h"
#include <vector>
#include <map>
#include <string>
static const std::string ID="id";
static const std::string RADIO="radio";
static const std::string LADO="lado";
static const std::string BASE="base";
static const std::string ALTURA="altura";
static const std::string VELOCIDAD="velocidad";
static const std::string PATH="path";
static const std::string TEXTURA="textura";
static const std::string CUADRADO="cuadrado";
static const std::string RECTANGULO="rectangulo";
static const std::string TRIANGULO="triangulo";
static const std::string TEJO="tejo";
static const std::string PAD="pad";
static const std::string CIRCULO="circulo";
static const std::string DELIMITADOR="\"";
static const std::string GENERAL="General";
static const std::string TEXTURA_FIG="texturaFig";
static const std::string TEXTURA_ESC="texturaEsc";
static const std::string RESOLUCION="resolucion";
static const std::string COLOR_FONDO_FIG="colorFondoFig";
static const std::string COLOR_FONDO_ESC="colorFondoEsc";
static const std::string COLOR_LINEA="colorLinea";
static const std::string POS_X="x";
static const std::string POS_Y="y";
static const char POSICION_X='x';
static const char POSICION_Y='y';
static const std::string POS_X1="x1";
static const std::string POS_Y1="y1";
static const std::string POS_X2="x2";
static const std::string POS_Y2="y2";
static const std::string POS_X3="x3";
static const std::string POS_Y3="y3";
static const std::string SEGMENTO="segmento";
static const std::string COLOR_FIGURA="colorFigura";
static const std::string ID_TEXTURA="idTextura";
static const std::string X1="x1";
static const std::string X2="x2";
static const std::string Y1="y1";
static const std::string Y2="y2";
static const std::string SINVALOR="sinValor";
static const int POS_TEJO_X_INICIAL = 690;
static const int POS_TEJO_Y_INICIAL = 300;
static const int POS_PAD1_X_INICIAL = 710;
static const int POS_PAD1_Y_INICIAL = 240;
static const int POS_PAD2_X_INICIAL = 56;
static const int POS_PAD2_Y_INICIAL = 240;

void escribirErrorIDLog(std::string nombreTag,std::string id){
	Escenario* escenario=Escenario::obtenerInstancia();
	if(id.compare(SINVALOR)==0){
		std::cout<<"NO SE ENCONTRO EL ATRIBUTO id EN : "+nombreTag<<endl;
		escribirMensajeLog(*(escenario->getLog()),"NO SE ENCONTRO EL ATRIBUTO id EN : "+nombreTag);
	}
}
int validarNumero(string numero){
	for ( int pos = 0; pos < numero.length(); ++pos ){
		std::cout<<isdigit(numero.at(pos))<<endl;
		if(isdigit(numero.at(pos))){
			return -1;
		}
	}
	return 0;
}

int obtenerResolucion(string resolucion){
	int resInt=atoi(resolucion.c_str());
	if(resInt==640||resInt==800||resInt==1024||resInt==1280){
		return resInt;
	}else{
		return -1;
	}
}
int validarNumeroRGB(string numero){
	for ( int pos = 0; pos < numero.length(); ++pos )
		if(isdigit(numero.at(pos)==0)){
			return -1;
		}

	if(atoi(numero.c_str())>255){

		return -1;
	}

	return 0;

}


int hidratarColor(std::string cadena,Color* color){

	if(cadena.size()!=9){

		return -1;
	}else{

		string r= cadena.substr(0,3);
		string g= cadena.substr(3,3);
		string b= cadena.substr(6,3);

		if(validarNumeroRGB(r)==0&&validarNumeroRGB(g)==0&&validarNumeroRGB(b)==0){

			SDL_Color sdlColor;
			sdlColor.r=atoi(r.c_str());
			sdlColor.g=atoi(g.c_str());
			sdlColor.b=atoi(b.c_str());
			color->setColor(sdlColor);
		}else{
			return -1;
		}
	}

	return 0;
}

/**
 * este metodo agrega los atributos opcionales a las figuras que son si los encuentra los agrega sino
 * escribe en el log el error
 * COLOR_FIGURA
 * COLOR_LINEA
 * ID_TEXTURA
 */
void agregarAtributosOpcionales(vector<string>& tokens,Figura* figura,vector<string>& listaClave){
	Escenario* escenario=Escenario::obtenerInstancia();
	std::string id;
	id=StringUtils::getValorTag(ID,tokens);
	std::string valorAtributo;
	std::string valorClave;
	std::string idtextura;
	std::vector<string>::iterator iter;
	iter = listaClave.begin();
	while( iter != listaClave.end() ) {
		valorClave=*iter;
		std::cout<<"valor de la clave \n "<<" "<<valorClave<<endl;
		if(valorClave.compare(ID_TEXTURA)==0){
			idtextura=StringUtils::getValorTag(ID_TEXTURA,tokens);
			figura->setIdTextura(idtextura);
			std::cout<<"valor de la clave ID_TEXTURA"<<" "<<idtextura<<endl;
			std::cout<<"EXITO AL AGREGAR EL TAG OPCIONAL ID_TEXTURA A LA FIGURA "<<endl;
		}
		if(valorClave.compare(COLOR_FIGURA)==0){
			Color* colorFigura=new Color();
			valorAtributo=StringUtils::getValorTag(COLOR_FIGURA,tokens);
			std::cout<<"valor de la clave COLOR_FIGURA"<<" "<<valorAtributo<<endl;
			if(hidratarColor(valorAtributo,colorFigura)!=-1&&valorAtributo.compare("sinValor") != 0){
				figura->setColorFigura(colorFigura);

				std::cout<<"EXITO AL AGREGAR EL TAG OPCIONAL COLOR_FIGURA A LA FIGURA"<<endl;
			}else{
				std::cout<<"ERROR AL AGREGAR EL TAG OPCIONAL COLOR_FIGURA A LA FIGURA "<<endl;
				escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR EL TAG OPCIONAL COLOR_FIGURA A LA FIGURA "+id);
			}
		}

		if(valorClave.compare(COLOR_LINEA)==0){
			valorAtributo=StringUtils::getValorTag(COLOR_LINEA,tokens);
			Color* colorLinea=new Color();
			std::cout<<"valor de la clave COLOR_LINEA "<<" "<<valorAtributo<<endl;
			if(hidratarColor(valorAtributo,colorLinea)!=-1&&valorAtributo.compare("sinValor") != 0){
				figura->setColorLinea(colorLinea);
				std::cout<<"EXITO AL AGREGAR EL TAG OPCIONAL COLOR_LINEA A LA FIGURA"<<endl;
			}else{
				std::cout<<"ERROR AL AGREGAR EL TAG OPCIONAL COLOR_LINEA A LA FIGURA"<<endl;
				escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR EL TAG OPCIONAL COLOR_LINEA A LA FIGURA"+id);
			}
		}

		++iter;
	}
}

void cargarListaClaves(std::vector<std::string>& listaClave,std::vector<std::string>& tokens){
	std::vector<std::string>::iterator the_iterator;
	the_iterator = tokens.begin();
	std::string valor;
	for (int var = 0; var < tokens.size(); ++var) {
		valor =StringUtils::trimPalabra(*the_iterator);
		if((var%2)==0){
			int posicionCaracterIgual = valor.find_first_of("=");
			if(posicionCaracterIgual!=0){
				valor= valor.substr(0,posicionCaracterIgual);
			}

			if(valor.compare(">")!=0&&valor.size()!=0){
				std::cout<<"clave del tag "<<valor<<endl;
				listaClave.push_back(valor);
			}
		}else{
			std::cout<<"valor del atributo "<<valor<<endl;
		}
		the_iterator++;

	}
}



void escribirErrorEnLog(Escenario*escenario, int errorPosicion, int propiedad,int errorAtributosValidos,std::string id){

	if(errorPosicion==-1){
		escribirMensajeLog(*(escenario->getLog()),"Se ha producido un error en el tag posicion x o y del: "+id);

	}

	if(errorAtributosValidos==-1)
		escribirMensajeLog(*(escenario->getLog()),"Se ha producido un error de escritura en uno de los valores de los tags del: "+id);

	if(propiedad==-1)
		escribirMensajeLog(*(escenario->getLog()),"Se ha producido un error en el tag de una de las propiedades del: "+id);
}


int Hidratar::hidratarCuadrado(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;
	string valueId;
	int lado;
	int errorNumeroPosX;
	int errorNumeroPosY;
	int errorNumeroPos;
	int errorPropiedad;
	int errorAtributosValidos;
	Posicion*posicion;
	Cuadrado *cuadrado;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

	string posicionX = (StringUtils::getValorTag(POS_X,vec)).c_str();
	string posicionY = (StringUtils::getValorTag(POS_Y,vec)).c_str();
	errorNumeroPosX = validador->validarNumero(posicionX);
	errorNumeroPosY = validador->validarNumero(posicionY);
	errorPropiedad = validador->validarNumero((StringUtils::getValorTag(LADO,vec)).c_str());
	errorAtributosValidos = validador->compararConVectorAtributosValidos(CUADRADO,listaClave);
	valueId = StringUtils::getValorTag(ID,vec);
	escribirErrorIDLog("CUADRADO :"+atributos,valueId);
	if(errorNumeroPosY==-1 || errorNumeroPosX==-1){
		std::cout<<"ERROR AL AGREGAR LA POSICION  AL CUADRADO "+valueId<<endl;
		escribirMensajeLog(*(escenario->getLog())," ERROR AL AGREGAR LA POSICION  AL CUADRADO : "+valueId);
		errorNumeroPos=-1;
	}else
		errorNumeroPos = 0;

	if(errorPropiedad==-1 ){
		std::cout<<"ERROR AL AGREGAR EL TAG lado AL CUADRADO"+valueId<<endl;
		escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR EL TAG lado AL CUADRADO"+valueId);

	}

	std::cout<<"Error atributos validos"<<errorAtributosValidos<<endl;

	if(errorNumeroPos==0&&errorAtributosValidos==0&&errorPropiedad==0){
		cuadrado = new Cuadrado();
		posicion = new Posicion(atoi((StringUtils::getValorTag(POS_X,vec)).c_str()),atoi((StringUtils::getValorTag(POS_Y,vec)).c_str()));

		lado = atoi((StringUtils::getValorTag(LADO,vec)).c_str());
		cuadrado->setId(valueId);
		cuadrado->setLado(lado);
		cuadrado->setPosicion(posicion);
		escenario->addFigura(cuadrado);
		std::cout<<"exito AL CREAR EL CUADRADO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		/**################################################################################################*/
		/**###############                    ACA AGREGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/
		agregarAtributosOpcionales(vec, cuadrado, listaClave);
		return 0;
	}else{
		//	escribirErrorEnLog(escenario, errorNumeroPos, errorPropiedad, errorAtributosValidos,StringUtils::getValorTag(ID,vec));
		std::cout<<"ERROR AL CREAR EL CUADRADO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		escribirMensajeLog(*(escenario->getLog()),"ERROR NO SE PUDO AGREGAR  A LA LISTA DE FIGURAS DEL  ESCENARIO EL CUADRADO : "+valueId);
	}
	return 0;
}

int Hidratar::hidratarCirculo(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;
	string valueId;
	Posicion* posicion;
	Circulo *circulo;
	int errorNumeroPosX, errorNumeroPosY, errorNumeroPos, radio, errorAtributosValidos, errorNumeroRadio;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);
	valueId = StringUtils::getValorTag(ID,vec);
	string posicionX = (StringUtils::getValorTag(POS_X,vec)).c_str();
	string posicionY = (StringUtils::getValorTag(POS_Y,vec)).c_str();
	errorNumeroPosX = validador->validarNumero(posicionX);
	errorNumeroPosY = validador->validarNumero(posicionY);
	errorNumeroRadio = validador->validarNumero((StringUtils::getValorTag(RADIO,vec)).c_str());
	errorAtributosValidos = validador->compararConVectorAtributosValidos(CIRCULO,listaClave);
	escribirErrorIDLog("CIRCULO :"+atributos,valueId);
	if(errorNumeroPosX==-1 || errorNumeroPosY==-1){
		std::cout<<"ERROR AL AGREGAR LA POSICION  AL CIRCULO  :"+valueId<<endl;
		escribirMensajeLog(*(escenario->getLog())," ERROR AL AGREGAR LA POSICION  AL CIRCULO : "+valueId);
		errorNumeroPos=-1;

	}else
		errorNumeroPos=0;

	if(errorNumeroRadio==-1){
		std::cout<<"ERROR AL AGREGAR EL TAG radio AL CIRCULO"+valueId<<endl;
		escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR EL TAG radio AL CIRCULO"+valueId);

	}

	std::cout<<"Error atributos validos"<<errorAtributosValidos<<endl;

	if(errorNumeroPos==0&&errorNumeroRadio==0&&errorAtributosValidos==0){
		circulo = new Circulo();
		posicion = new Posicion(atoi(posicionX.c_str()),atoi(posicionY.c_str()));

		radio = atoi((StringUtils::getValorTag(RADIO,vec)).c_str());
		circulo->setId(valueId);
		circulo->setRadio(radio);
		circulo->setPosicion(posicion);
		escenario->addFigura(circulo);
		std::cout<<"exito AL CREAR EL CIRCULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		/**################################################################################################*/
		/**###############                    ACA AGREGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/
		agregarAtributosOpcionales(vec, circulo, listaClave);
		return 0;
	}else{
		std::cout<<"ERROR AL CREAR EL CIRCULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		//	escribirErrorEnLog(escenario, errorNumeroPos, errorNumeroRadio, errorAtributosValidos, StringUtils::getValorTag(ID,vec));
		escribirMensajeLog(*(escenario->getLog()),"ERROR NO SE PUDO AGREGAR  A LA LISTA DE FIGURAS DEL  ESCENARIO EL CIRCULO : "+valueId);
	}
	return 0;
}

int Hidratar::hidratarRectangulo(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;
	string valueId;
	string errorAEscribir;
	int base,altura;
	int errorNumeroPosX,errorNumeroPosY,errorNumeroPos,errorAtributosValidos,errorPropiedad,errorBase,errorAltura;
	Rectangulo *rectangulo;
	Posicion* posicion;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	std::cout<<"atributos "<<atributos<<endl;
	cargarListaClaves(listaClave,vec);
	string posicionX = (StringUtils::getValorTag(POS_X,vec)).c_str();
	string posicionY = (StringUtils::getValorTag(POS_Y,vec)).c_str();
	std::cout<<"posicionX "<<posicionX<<endl;
	std::cout<<"posicionY "<<posicionY<<endl;
	errorNumeroPosX = validador->validarNumero(posicionX);
	errorNumeroPosY = validador->validarNumero(posicionY);
	errorBase = validador->validarNumero((StringUtils::getValorTag(BASE,vec)).c_str());
	errorAltura = validador->validarNumero((StringUtils::getValorTag(ALTURA,vec)).c_str());
	errorAtributosValidos = validador->compararConVectorAtributosValidos(RECTANGULO,listaClave);
	valueId = StringUtils::getValorTag(ID,vec);
	escribirErrorIDLog("RECTANGULO :"+atributos,valueId);
	if(errorAltura==-1){
		errorAEscribir="ERROR AL AGREGAR EL TAG altura AL RECTANGULO :";
		std::cout<<errorAEscribir+valueId<<endl;
		escribirMensajeLog(*(escenario->getLog()),errorAEscribir+valueId);
		errorPropiedad = -1;
	}else
		errorPropiedad = 0;

	if(errorBase==-1){
		errorAEscribir="ERROR AL AGREGAR EL TAG base AL RECTANGULO  :";
		std::cout<<errorAEscribir+valueId<<endl;
				escribirMensajeLog(*(escenario->getLog()),errorAEscribir+valueId);
		errorPropiedad = -1;
	}else
		errorPropiedad = 0;

	if(errorNumeroPosX==-1 || errorNumeroPosY==-1){
		std::cout<<"ERROR AL AGREGAR LA POSICION  AL RECTANGULO  "+valueId<<endl;
		escribirMensajeLog(*(escenario->getLog())," ERROR AL AGREGAR LA POSICION  AL RECTANGULO : "+valueId);
		errorNumeroPos=-1;
	}else
		errorNumeroPos = 0;


	std::cout<<"Error atributos validos"<<errorAtributosValidos<<endl;

	if(errorNumeroPos==0&&errorPropiedad==0&&errorAtributosValidos==0){
		rectangulo = new Rectangulo();
		posicion = new Posicion(atoi(posicionX.c_str()),atoi(posicionY.c_str()));

		base = atoi((StringUtils::getValorTag(BASE,vec)).c_str());
		altura = atoi((StringUtils::getValorTag(ALTURA,vec)).c_str());
		rectangulo->setId(valueId);
		rectangulo->setBase(base);
		rectangulo->setAltura(altura);
		rectangulo->setPosicion(posicion);
		escenario->addFigura(rectangulo);
		std::cout<<"exito AL CREAR EL RECTANGULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		/**################################################################################################*/
		/**###############                    ACA AGREGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/
		agregarAtributosOpcionales(vec, rectangulo, listaClave);
		return 0;
	}else{
		std::cout<<"ERROR AL CREAR EL RECTANGULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		//escribirErrorEnLog(escenario, errorNumeroPos, errorPropiedad, errorAtributosValidos, StringUtils::getValorTag(ID,vec));
		escribirMensajeLog(*(escenario->getLog()),"ERROR NO SE PUDO AGREGAR  A LA LISTA DE FIGURAS DEL  ESCENARIO EL RECTANGULO : "+valueId);
	}
	return 0;
}

int Hidratar::hidratarTriangulo(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> listaClaveOriginal;
	vector<string> vec;
	string valueId;
	string nueva_cadena;
	Triangulo *triangulo;
	int errorVerticePosX1,errorVerticePosY1,errorVerticePosX2,errorVerticePosY2,errorVerticePosX3,errorVerticePosY3, errorVertice, errorAtributosValidos;
	Posicion* vertice1;
	Posicion* vertice2;
	Posicion* vertice3;
	Validador* validador=escenario->getValidador();
	vector<string> tokens;
	StringUtils::Tokenize(atributos, tokens,DELIMITADOR);
	cargarListaClaves(listaClaveOriginal,tokens);
	nueva_cadena=StringUtils::actualizarCadena(StringUtils::actualizarCadena(atributos,POSICION_X),POSICION_Y);
	StringUtils::Tokenize(nueva_cadena,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);
	string posicionX1 = (StringUtils::getValorTag(POS_X1,vec)).c_str();
	string posicionY1 = (StringUtils::getValorTag(POS_Y1,vec)).c_str();
	string posicionX2 = (StringUtils::getValorTag(POS_X2,vec)).c_str();
	string posicionY2 = (StringUtils::getValorTag(POS_Y2,vec)).c_str();
	string posicionX3 = (StringUtils::getValorTag(POS_X3,vec)).c_str();
	string posicionY3 = (StringUtils::getValorTag(POS_Y3,vec)).c_str();
	errorVerticePosX1 = validador->validarNumero(posicionX1);
	errorVerticePosX2 = validador->validarNumero(posicionX2);
	errorVerticePosX3 = validador->validarNumero(posicionX3);
	errorVerticePosY1 = validador->validarNumero(posicionY1);
	errorVerticePosY2 = validador->validarNumero(posicionY2);
	errorVerticePosY3 = validador->validarNumero(posicionY3);
	errorAtributosValidos = validador->compararConVectorAtributosValidos(TRIANGULO,listaClaveOriginal);
	valueId = StringUtils::getValorTag(ID,vec);
	escribirErrorIDLog("TRIANGULO :"+atributos,valueId);
	if(errorVerticePosX1==-1||errorVerticePosX2==-1||errorVerticePosX3==-1||errorVerticePosY1==-1||errorVerticePosY2==-1||errorVerticePosY3==-1){
		errorVertice = -1;
	     std::cout<<"ERROR AL AGREGAR LOS VERTICES  AL TRIANGULO  "+valueId<<endl;
		escribirMensajeLog(*(escenario->getLog())," ERROR AL AGREGAR LOS VERTICES   AL TRIANGULO : "+valueId);

	}else
		errorVertice = 0;



	std::cout<<"Error atributos validos"<<errorAtributosValidos<<endl;

	if(errorVertice==0&&errorAtributosValidos==0){
		triangulo = new Triangulo();
		vertice1 = new Posicion(atoi(posicionX1.c_str()),atoi(posicionY1.c_str()));
		vertice2 = new Posicion(atoi(posicionX2.c_str()),atoi(posicionY2.c_str()));
		vertice3 = new Posicion(atoi(posicionX3.c_str()),atoi(posicionY3.c_str()));

		triangulo->setId(valueId);
		triangulo->setVertice1(vertice1);
		triangulo->setVertice2(vertice2);
		triangulo->setVertice3(vertice3);

		escenario->addFigura(triangulo);
		std::cout<<"exito AL CREAR EL TRIANGULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;

		/**################################################################################################*/
		/**###############                    ACA AGRAGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/
		agregarAtributosOpcionales(vec, triangulo, listaClave);
		return 0;
	}else{
		std::cout<<"ERROR AL CREAR EL TRIANGULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
	//	escribirErrorEnLog(escenario, errorVertice, 0, errorAtributosValidos,StringUtils::getValorTag(ID,vec)); //en la propiedad le pongo 0 porque no tiene una propiedad definida como rectangulo (base y altura).
		escribirMensajeLog(*(escenario->getLog()),"ERROR NO SE PUDO AGREGAR  A LA LISTA DE FIGURAS DEL  ESCENARIO EL TRIANGULO : "+valueId);
	}
	return 0;
}

int Hidratar::hidratarTejo(std::string atributos){
    Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;
	Circulo *circulo;
	int errorRadio, errorVelocidad, errorAtributosValidos, error;
	Posicion* posicion;

	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos, vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);
	string radio = (StringUtils::getValorTag(RADIO,vec)).c_str();
	string velocidad = (StringUtils::getValorTag(VELOCIDAD,vec)).c_str();

	errorRadio = validador->validarNumero(radio);
	errorVelocidad = validador->validarNumero(velocidad);
	errorAtributosValidos = validador->compararConVectorAtributosValidos(TEJO,listaClave);

	if(errorRadio==-1||errorVelocidad==-1||errorAtributosValidos==-1){
		error=-1;
	     std::cout<<"ERROR AL CREAR EL TEJO  "<<endl;
		escribirMensajeLog(*(escenario->getLog())," ERROR AL CREAR EL TEJO: ");

	}else
		error = 0;



	std::cout<<"Error atributos validos"<<errorAtributosValidos<<endl;

	if(error==0&&errorAtributosValidos==0){
		Posicion *p = new Posicion(POS_TEJO_X_INICIAL,POS_TEJO_Y_INICIAL);
		circulo= new Circulo("tejo",atoi((StringUtils::getValorTag(RADIO,vec)).c_str()),p);

		/**################################################################################################*/
		/**###############                    ACA AGRAGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/
	    agregarAtributosOpcionales(vec,circulo, listaClave);
	    Tejo* tejo = new Tejo(circulo);
	    tejo->setVelocidad(atoi((StringUtils::getValorTag(VELOCIDAD,vec)).c_str()));
		escenario->setTejo(tejo);
		std::cout<<"exito AL CREAR EL TEJO SE LO AGREGO AL ESCENARIO"<<endl;

		return 0;
	}else{
		std::cout<<"ERROR AL CREAR EL TEJO NO SE LO AGREGO AL ESCENARIO"<<endl;
		escribirMensajeLog(*(escenario->getLog()),"ERROR NO SE PUDO AGREGAR  AL ESCENARIO EL TEJO : ");
	}
	return 0;
}

int Hidratar::hidratarPads(std::string atributos){
	std::cout<<"veo que trae "<<atributos<<endl;
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;

	int errorBase, errorAltura, errorAtributosValidos=0, error;
	Posicion* posicion;

	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos, vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);
	string base = (StringUtils::getValorTag(BASE,vec)).c_str();
	string altura = (StringUtils::getValorTag(ALTURA,vec)).c_str();
	std::cout<<"veo que trae "<<base<<altura<<endl;
	errorBase = validador->validarNumero(base);
	errorAltura = validador->validarNumero(altura);

	errorAtributosValidos = validador->compararConVectorAtributosValidos(PAD,listaClave);

	if(errorBase==-1||errorAltura==-1||errorAtributosValidos==-1){
		error=-1;
	     std::cout<<"ERROR AL CREAR LOS PAD  "<<endl;
		escribirMensajeLog(*(escenario->getLog())," ERROR AL CREAR LOS PAD: ");

	}else
		error = 0;



	std::cout<<"Error atributos validos"<<errorAtributosValidos<<endl;

	if(error==0&&errorAtributosValidos==0){
		Posicion *posPadInicialCliente1 = new Posicion(POS_PAD1_X_INICIAL,POS_PAD1_Y_INICIAL);
		Posicion *posPadInicialCliente2 = new Posicion(POS_PAD2_X_INICIAL,POS_PAD2_Y_INICIAL);
		Rectangulo* rectangulo1 = new Rectangulo("padCliente1",atoi((StringUtils::getValorTag(BASE,vec)).c_str()),atoi((StringUtils::getValorTag(ALTURA,vec)).c_str()),posPadInicialCliente1);
		Rectangulo* rectangulo2 = new Rectangulo("padCliente2",atoi((StringUtils::getValorTag(BASE,vec)).c_str()),atoi((StringUtils::getValorTag(ALTURA,vec)).c_str()),posPadInicialCliente2);
		/**################################################################################################*/
		/**###############                    ACA AGRAGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/
				agregarAtributosOpcionales(vec,rectangulo1, listaClave);
			    agregarAtributosOpcionales(vec,rectangulo2, listaClave);


		Pad* padCliente1 = new Pad(rectangulo1);
		Pad* padCliente2 = new Pad(rectangulo2);
		escenario->setPadCliente1(padCliente1);
		escenario->setPadCliente2(padCliente2);
		std::cout<<"exito AL CREAR LOS PAD SE LO AGREGARON AL ESCENARIO"<<endl;

		return 0;
	}else{
		std::cout<<"ERROR AL CREAR LOS PAD NO SE AGREGARON AL ESCENARIO"<<endl;
		escribirMensajeLog(*(escenario->getLog()),"ERROR NO SE PUDO AGREGAR AL ESCENARIO LOS PAD : ");
	}
	return 0;
}

int Hidratar::hidratarEscenario(std::string atributos){
	Escenario* escenario = Escenario::obtenerInstancia();

	std::string texturaFig;
	std::string texturaEsc;
	int resolucion;
	Color* colorFondoEscenario = new Color();
	Color* colorFondoFiguras= new Color();
	Color* colorLinea= new Color();
	std::string valorAtributo;
	std::string valorClave;
	vector<string> listaClave;
	vector<string> tokens;
	std::cout<<"atributos"<<atributos<<endl;
	StringUtils::Tokenize(atributos, tokens,DELIMITADOR);
	cargarListaClaves(listaClave,tokens);
	std::cout<<"tamanio del vector"<<tokens.size()<<endl;
	std::cout<<"tamanio de la lista"<<listaClave.size()<<endl;
	Validador* validador=escenario->getValidador();

	/**################################################################################################*/
	/**###############                    ACA AGREGO LOS TAG OPCIONALES    #################################*/
	/**################################################################################################*/

	std::vector<string>::iterator iter;
	iter = listaClave.begin();
	std::cout<<"llego aca  "<<" "<<*iter<<endl;
	while( iter != listaClave.end() ) {
		std::cout<<"claves de la lista "<<" "<<*iter<<endl;
		valorClave=*iter;
		std::cout<<"valor de la clave"<<" "<<valorClave<<endl;
		std::cout<<"validaddor"<<" "<<(validador->compararConAtributosValidos("General",valorClave))<<endl;
		if(validador->compararConAtributosValidos(GENERAL,valorClave)==0){

			if(valorClave.compare(TEXTURA_ESC)==0){
				texturaEsc=StringUtils::getValorTag(TEXTURA_ESC,tokens);
				escenario->setTexturaEsc(texturaEsc);
				std::cout<<"valor de la clave"<<" "<<texturaEsc<<endl;
				std::cout<<"EXITO AL AGREGAR TAG TEXTURA_ESC AL ESCENARIO "<<endl;
			}

			if(valorClave.compare(TEXTURA_FIG)==0){
				texturaFig=StringUtils::getValorTag(TEXTURA_FIG,tokens);
				escenario->setTexturaFig(texturaFig);
				std::cout<<"valor de la clave"<<" "<<texturaFig<<endl;
				std::cout<<"EXITO AL AGREGAR TAG TEXTURA_FIG AL ESCENARIO "<<endl;
			}

			if(valorClave.compare(RESOLUCION)==0){
				valorAtributo=StringUtils::getValorTag(RESOLUCION,tokens);
				if(obtenerResolucion(valorAtributo)!=-1&&valorAtributo.compare("sinValor") != 0){
					escenario->setResolucion(obtenerResolucion(valorAtributo));
					std::cout<<"valor de la clave"<<" "<<obtenerResolucion(valorAtributo)<<endl;
					std::cout<<"EXITO AL AGREGAR TAG RESOLUCION AL ESCENARIO "<<endl;
				}else{
					std::cout<<"ERROR AL AGREGAR TAG RESOLUCION AL ESCENARIO "<<endl;
					escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG RESOLUCION AL ESCENARIO ");
				}
			}

			if(valorClave.compare(COLOR_FONDO_FIG)==0){
				valorAtributo=StringUtils::getValorTag(COLOR_FONDO_FIG,tokens);
				std::cout<<"valor de la clave COLOR_FONDO_FIG"<<" "<<valorAtributo<<endl;
				if(hidratarColor(valorAtributo,colorFondoFiguras)!=-1&&valorAtributo.compare("sinValor") != 0){
					escenario->setColorFondoFiguras(colorFondoFiguras);

					std::cout<<"EXITO AL AGREGAR TAG COLOR_FONDO_FIG AL ESCENARIO "<<endl;
				}else{
					std::cout<<"ERROR AL AGREGAR TAG COLOR_FONDO_FIG AL ESCENARIO "<<endl;
					escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG colorFondoFig AL ESCENARIO ");
				}
			}

			if(valorClave.compare(COLOR_FONDO_ESC)==0){
				valorAtributo=StringUtils::getValorTag(COLOR_FONDO_ESC,tokens);
				std::cout<<"valor de la clave"<<" "<<valorAtributo<<endl;
				if(hidratarColor(valorAtributo,colorFondoEscenario)!=-1&&valorAtributo.compare("sinValor") != 0){
					escenario->setColorFondoEscenario(colorFondoEscenario);
					std::cout<<"EXITO AL AGREGAR TAG COLOR_FONDO_ESC AL ESCENARIO "<<endl;
				}else{
					std::cout<<"ERROR AL AGREGAR TAG COLOR_FONDO_ESC AL ESCENARIO "<<endl;
					escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG colorFondoEsc AL ESCENARIO ");
				}
			}

			if(valorClave.compare(COLOR_LINEA)==0){
				valorAtributo=StringUtils::getValorTag(COLOR_LINEA,tokens);
				std::cout<<"valor de la clave"<<" "<<valorAtributo<<endl;
				if(hidratarColor(valorAtributo,colorLinea)!=-1&&valorAtributo.compare("sinValor") != 0){
					escenario->setColorLinea(colorLinea);
					std::cout<<"EXITO AL AGREGAR TAG COLOR_LINEA AL ESCENARIO "<<endl;
				}else{
					std::cout<<"ERROR AL AGREGAR TAG COLOR_LINEA AL ESCENARIO "<<endl;
					escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG colorLinea AL ESCENARIO ");
				}
			}


		}else{
			std::cout<<"ERROR AL AGREGAR EL ATRIBUTO "<<valorClave<<" AL ESCENARIO"<<endl;
			escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG "+valorClave+" AL ESCENARIO" );

		}
		++iter;
	}

	return 0;
}
int Hidratar::hidratartextura(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	std::string id;
	std::string path;
	vector<string> listaClave;
	vector<string> tokens;
	StringUtils::Tokenize(atributos, tokens,DELIMITADOR);
	cargarListaClaves(listaClave,tokens);
	std::cout<<"tamanio del vector"<<tokens.size()<<endl;
	std::cout<<"tamanio de la lista"<<listaClave.size()<<endl;
	Validador* validador=escenario->getValidador();
	id=StringUtils::getValorTag(ID,tokens);
	escribirErrorIDLog("TEXTURA  :"+atributos,id);
	if(validador->compararConVectorAtributosValidos(TEXTURA,listaClave)==0&&id.compare("sinValor")!=0){
		path=StringUtils::getValorTag(PATH,tokens);
		Textura *textura = new Textura(id,path);
		escenario->addTextura(textura);
		std::cout<<"exito AL CREAR LA TEXTURA  SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		return 0;
	}else{
		std::cout<<"ERROR AL CREAR LA TEXTURA NO SE LA AGREGO A LA LISTA DE ESCENARIO :"+id<<endl;
		escribirMensajeLog(*(escenario->getLog()),"ERROR AL CREAR LA TEXTURA NO SE LA AGREGO A LA LISTA DE ESCENARIO :"+id);
		return 0;
	}
}



int Hidratar::hidratarSegmento(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	Segmento *segmento;
	Posicion *inicio;
	Posicion* fin;
	std::string id;
	std::string x1;
	std::string x2;
	std::string y1;
	std::string y2;
	string atributosModificados=StringUtils::actualizarCadena(StringUtils::actualizarCadena(atributos,POSICION_X),POSICION_Y);
	vector<string> listaClave;
	vector<string> tokens;
	vector<string> tokensModificado;
	StringUtils::Tokenize(atributos, tokens,DELIMITADOR);
	cargarListaClaves(listaClave,tokens);
	std::cout<<"tamanio del vector"<<tokens.size()<<endl;
	std::cout<<"tamanio de la lista"<<listaClave.size()<<endl;
	Validador* validador=escenario->getValidador();
	if(validador->compararConVectorAtributosValidos(SEGMENTO,listaClave)==0){
		StringUtils::Tokenize(atributosModificados, tokensModificado,DELIMITADOR);
		std::cout<<"atributos modificados "<<atributosModificados<<endl;
		id=StringUtils::getValorTag(ID,tokens);
		x1=StringUtils::getValorTag(X1,tokensModificado);
		x2=StringUtils::getValorTag(X2,tokensModificado);
		y1=StringUtils::getValorTag(Y1,tokensModificado);
		y2=StringUtils::getValorTag(Y2,tokensModificado);
		escribirErrorIDLog("SEGMENTO :"+atributos,id);
		std::cout<<"atributos modificados "<<"("<<x1<<","<<y1<<")"<<"("<<y1<<","<<y2<<")"<<endl;
		if(validador->validarNumero(x1)==-1||validador->validarNumero(y1)==-1){
			std::cout<<"ERROR AL AGREGAR TAG INICIO AL SEGMENTO "<<endl;
			escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG INICIO AL SEGMENTO : "+id);
			return 0;
		}
		if(validador->validarNumero(x2)==-1||validador->validarNumero(y2)==-1){
			std::cout<<"ERROR AL AGREGAR TAG FIN AL SEGMENTO "<<endl;
			escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG INICIO AL SEGMENTO : "+id);
			return 0;
		}

		// si no hay errores instancio y agrego le segmento
		inicio= new Posicion(atoi(x1.c_str()),atoi(y1.c_str()));
		fin= new Posicion(atoi(x2.c_str()),atoi(y2.c_str()));
		segmento= new Segmento(id,inicio,fin);
		escenario->addFigura(segmento);
		/**################################################################################################*/
		/**###############                    ACA AGREGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/
		agregarAtributosOpcionales(tokens, segmento, listaClave);
		std::cout<<"exito AL CREAR EL SEGMENTO  SE LA AGREGO A LA LISTA DE FIGURAS"<<endl;
		return 0;
	}else{
		std::cout<<"ERROR AL CREAR EL SEGMENTO  NO SE LA AGREGO A LA LISTA DE FIGURAS"<<endl;
		return 0;
	}

}


