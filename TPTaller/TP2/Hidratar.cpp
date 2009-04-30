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
static const std::string ALTURA="ALTURA";
static const std::string PATH="path";
static const std::string TEXTURA="textura";
static const std::string CUADRADO="cuadrado";
static const std::string RECTANGULO="rectangulo";
static const std::string TRIANGULO="triangulo";
static const std::string CIRCULO="circulo";
static const std::string DELIMITADOR="\"";
static const std::string GENERAL="General";
static const std::string TEXTURA_FIG="texturaFig";
static const std::string TEXTURA_ESC="texturaEsc";
static const std::string RESOLUCION="resolucion";
static const std::string COLOR_FONDO_FIG="colorFondoFig";
static const std::string COLOR_FONDO_ESC="colorFondoEsc";
static const std::string COLOR_LINEA="colorLinea";
static const std::string SEGMENTO="segmento";
static const std::string COLOR_FIGURA="colorFigura";
static const std::string ID_TEXTURA="id_textura";
int obtenerResolucion(string resolucion){
	int resInt=atoi(resolucion.c_str());
	if(resInt==640||resInt==800||resInt==1024||resInt==1280){
		return resInt;
	}else{
		return -1;
	}
}
int validarNumeroRGB(string numero){
static const std::string CUADRADO="cuadrado";
static const std::string RECTANGULO="rectangulo";
static const std::string TRIANGULO="triangulo";
static const std::string CIRCULO="circulo";

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

			if(valor.compare(">")!=0){
			std::cout<<"clave del tag "<<valor<<endl;
			listaClave.push_back(valor);
			}
		}else{
		std::cout<<"valor del atributo "<<valor<<endl;
		}
		the_iterator++;

	}
}

int Hidratar::hidratarCuadrado(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;
	string valueId;
	int lado;
	Cuadrado *cuadrado;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConVectorAtributosValidos(CUADRADO,listaClave)==0){
	cuadrado = new Cuadrado();
	valueId = StringUtils::getValorTag(ID,vec);
	lado = atoi((StringUtils::getValorTag(LADO,vec)).c_str());
	cuadrado->setIdTextura(valueId);
	cuadrado->setLado(lado);
	escenario->addFigura(cuadrado);
     	std::cout<<"exito AL CREAR EL CUADRADO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL CUADRADO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;

	return -1;



}

int Hidratar::hidratarCirculo(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;
	string valueId;
	int radio;
	Circulo *circulo;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConVectorAtributosValidos(CIRCULO,listaClave)==0){
	circulo = new Circulo();
	valueId = StringUtils::getValorTag(ID,vec);
	radio = atoi((StringUtils::getValorTag(RADIO,vec)).c_str());
	circulo->setIdTextura(valueId);
	circulo->setRadio(radio);
	escenario->addFigura(circulo);
     	std::cout<<"exito AL CREAR EL CIRCULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL CIRCULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;

	return -1;
}

int Hidratar::hidratarRectangulo(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	vector<string> listaClave;
	vector<string> vec;
	string valueId;
	int base,altura;
	Rectangulo *rectangulo;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConVectorAtributosValidos(RECTANGULO,listaClave)==0){
	rectangulo = new Rectangulo();
	valueId = StringUtils::getValorTag(ID,vec);
	base = atoi((StringUtils::getValorTag(BASE,vec)).c_str());
	altura = atoi((StringUtils::getValorTag(ALTURA,vec)).c_str());
	rectangulo->setIdTextura(valueId);
	rectangulo->setBase(base);
	rectangulo->setAltura(altura);
	escenario->addFigura(rectangulo);
     	std::cout<<"exito AL CREAR EL RECTANGULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL RECTANGULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;

	return -1;
}

int Hidratar::hidratarTriangulo(std::string atributos){
		Escenario* escenario=Escenario::obtenerInstancia();
		vector<string> listaClave;
	vector<string> vec;
	string valueId;
	Triangulo *triangulo;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConVectorAtributosValidos(TRIANGULO,listaClave)==0){
	triangulo = new Triangulo();
	valueId = StringUtils::getValorTag(ID,vec);
	triangulo->setIdTextura(valueId);
	escenario->addFigura(triangulo);
     	std::cout<<"exito AL CREAR EL TRIANGULO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
     	return 0;
	}else
		std::cout<<"ERROR AL CREAR EL TRIANGULO NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;

	return -1;
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
   	system("PAUSE");
	 /**################################################################################################*/
		/**###############                    ACA AGRAGO LOS TAG OPCIONALES    #################################*/
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
				if(obtenerResolucion(valorAtributo)!=-1&&valorAtributo.compare("error") != 0){
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
				if(hidratarColor(valorAtributo,colorFondoFiguras)!=-1&&valorAtributo.compare("error") != 0){
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
				if(hidratarColor(valorAtributo,colorFondoEscenario)!=-1&&valorAtributo.compare("error") != 0){
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
				if(hidratarColor(valorAtributo,colorLinea)!=-1&&valorAtributo.compare("error") != 0){
					escenario->setColorLinea(colorLinea);
					std::cout<<"EXITO AL AGREGAR TAG COLOR_LINEA AL ESCENARIO "<<endl;
				}else{
					std::cout<<"ERROR AL AGREGAR TAG COLOR_LINEA AL ESCENARIO "<<endl;
					escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG colorLinea AL ESCENARIO ");
				}
			}


		}
		++iter;
	}
	system("PAUSE");
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
	if(validador->compararConVectorAtributosValidos(TEXTURA,listaClave)==0){
		id=StringUtils::getValorTag(ID,tokens);
		path=StringUtils::getValorTag(PATH,tokens);
		Textura *textura = new Textura(id,path);
		escenario->addTextura(textura);
		std::cout<<"exito AL CREAR LA TEXTURA  SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		return 0;
	}else{
		std::cout<<"ERROR AL CREAR LA TEXTURA NO SE LA AGREGO A LA LISTA DE ESCENARIO"<<endl;
		return -1;
	}
}
int Hidratar::hidratarSegmento(std::string atributos){
	Escenario* escenario=Escenario::obtenerInstancia();
	Segmento *segmento;
	Color* colorFigura=new Color();
	Color* colorLinea=new Color();
	std::string valorAtributo;
	std::string valorClave;
	std::string id;
	std::string idtextura;
	vector<string> listaClave;
	vector<string> tokens;
	StringUtils::Tokenize(atributos, tokens,DELIMITADOR);
	cargarListaClaves(listaClave,tokens);
	std::cout<<"tamanio del vector"<<tokens.size()<<endl;
	std::cout<<"tamanio de la lista"<<listaClave.size()<<endl;
	Validador* validador=escenario->getValidador();
	if(validador->compararConVectorAtributosValidos(SEGMENTO,listaClave)==0){
		id=StringUtils::getValorTag(ID,tokens);


        /**################################################################################################*/
		/**###############                    ACA AGRAGO LOS TAG OPCIONALES    #################################*/
		/**################################################################################################*/

		std::vector<string>::iterator iter;
		iter = listaClave.begin();
		while( iter != listaClave.end() ) {
			valorClave=*iter;
			std::cout<<"valor de la clave \n "<<" "<<valorClave<<endl;
				if(valorClave.compare(ID_TEXTURA)==0){
					idtextura=StringUtils::getValorTag(ID_TEXTURA,tokens);
					segmento->setIdTextura(idtextura);
					std::cout<<"valor de la clave COLOR_FIGURA"<<" "<<idtextura<<endl;
					std::cout<<"EXITO AL AGREGAR TAG ID_TEXTURA AL SEGMENTO "<<endl;
				}
				if(valorClave.compare(COLOR_FIGURA)==0){
					valorAtributo=StringUtils::getValorTag(COLOR_FIGURA,tokens);
					std::cout<<"valor de la clave COLOR_FIGURA"<<" "<<valorAtributo<<endl;
					if(hidratarColor(valorAtributo,colorFigura)!=-1&&valorAtributo.compare("error") != 0){
						segmento->setColorFigura(colorFigura);

						std::cout<<"EXITO AL AGREGAR TAG COLOR_FIGURA AL SEGMENTO "<<endl;
					}else{
						std::cout<<"ERROR AL AGREGAR TAG COLOR_FIGURA AL SEGMENTO "<<endl;
						escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG COLOR_FIGURA AL SEGMENTO "+id);
					}
				}

				if(valorClave.compare(COLOR_LINEA)==0){
					valorAtributo=StringUtils::getValorTag(COLOR_LINEA,tokens);
					std::cout<<"valor de la clave COLOR_LINEA "<<" "<<valorAtributo<<endl;
					if(hidratarColor(valorAtributo,colorLinea)!=-1&&valorAtributo.compare("error") != 0){
						segmento->setColorLinea(colorLinea);
						std::cout<<"EXITO AL AGREGAR TAG COLOR_LINEA AL SEGMENTO "<<endl;
					}else{
						std::cout<<"ERROR AL AGREGAR TAG COLOR_LINEA AL SEGMENTO "<<endl;
						escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG COLOR_LINEA AL SEGMENTO "+id);
					}
				}

			++iter;
		}
		std::cout<<"exito AL CREAR EL SEGMENTO  SE LA AGREGO A LA LISTA DE fIGURAS"<<endl;
		return 0;
	}else{
		std::cout<<"ERROR AL CREAR EL SEGMENTO  NO SE LA AGREGO A LA LISTA DE fIGURAS"<<endl;
		return -1;
	}

























}


