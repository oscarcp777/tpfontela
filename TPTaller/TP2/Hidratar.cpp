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
static const std::string ID_TEXTURA="idTextura";
static const std::string X1="x1";
static const std::string X2="x2";
static const std::string Y1="y1";
static const std::string Y2="y2";
static const char POSICION_X='x';
static const char POSICION_Y='y';

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
			std::cout<<"clave del tag "<<valor.size()<<endl;
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
	std::string valueId;
	int lado;
	Cuadrado *cuadrado;
	Validador* validador=escenario->getValidador();
	StringUtils::Tokenize(atributos,vec,DELIMITADOR);
	cargarListaClaves(listaClave,vec);

    if(validador->compararConVectorAtributosValidos(CUADRADO,listaClave)==0){
	cuadrado = new Cuadrado();
	valueId = StringUtils::getValorTag(ID,vec);
	std::cout<<"********************VALOOOOOOOOORRRRRRRRRR valueId: "<<valueId<<endl;
	lado = atoi((StringUtils::getValorTag(LADO,vec)).c_str());
	
	// LA SIGUIENTE LINEA ESTABA MAL seteaba el id a la textura en vez de al id de la figura
	//cuadrado->setIdTextura(valueId);
	//la que va es:
	cuadrado->setId(valueId);
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
	
	// LA SIGUIENTE LINEA ESTABA MAL seteaba el id a la textura en vez de al id de la figura
	//circulo->setIdTextura(valueId);
	//la que va es:
	circulo->setId(valueId);
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
	// LA SIGUIENTE LINEA ESTABA MAL seteaba el id a la textura en vez de al id de la figura
	//rectangulo->setIdTextura(valueId);
	//la que va es:
	rectangulo->setId(valueId);
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
	// LA SIGUIENTE LINEA ESTABA MAL seteaba el id a la textura en vez de al id de la figura
	//triangulo->setIdTextura(valueId);
	//la que va es:
	triangulo->setId(valueId);
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


		}else{
			std::cout<<"ERROR AL AGREGAR EL ATRIBUTO "<<valorClave<<" AL ESCENARIO"<<endl;
			escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG "+valorClave+" AL ESCENARIO" );
			return -1;
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
	Color* colorFigura=new Color();
		Color* colorLinea=new Color();
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
				valorAtributo=StringUtils::getValorTag(COLOR_FIGURA,tokens);
				std::cout<<"valor de la clave COLOR_FIGURA"<<" "<<valorAtributo<<endl;
				if(hidratarColor(valorAtributo,colorFigura)!=-1&&valorAtributo.compare("error") != 0){
					figura->setColorFigura(colorFigura);

					std::cout<<"EXITO AL AGREGAR EL TAG OPCIONAL COLOR_FIGURA A LA FIGURA"<<endl;
				}else{
					std::cout<<"ERROR AL AGREGAR EL TAG OPCIONAL COLOR_FIGURA A LA FIGURA "<<endl;
					escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR EL TAG OPCIONAL COLOR_FIGURA A LA FIGURA "+id);
				}
			}

			if(valorClave.compare(COLOR_LINEA)==0){
				valorAtributo=StringUtils::getValorTag(COLOR_LINEA,tokens);
				std::cout<<"valor de la clave COLOR_LINEA "<<" "<<valorAtributo<<endl;
				if(hidratarColor(valorAtributo,colorLinea)!=-1&&valorAtributo.compare("error") != 0){
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
            std::cout<<"atributos modificados "<<"("<<x1<<","<<y1<<")"<<"("<<y1<<","<<y2<<")"<<endl;
		if(validador->validarNumero(x1)==-1||validador->validarNumero(y1)==-1){
			std::cout<<"ERROR AL AGREGAR TAG INICIO AL SEGMENTO "<<endl;
			escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG INICIO AL SEGMENTO : "+id);
			return -1;
		}
		if(validador->validarNumero(x2)==-1||validador->validarNumero(y2)==-1){
			std::cout<<"ERROR AL AGREGAR TAG FIN AL SEGMENTO "<<endl;
			escribirMensajeLog(*(escenario->getLog()),"ERROR AL AGREGAR TAG INICIO AL SEGMENTO : "+id);
			return -1;
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
		return -1;
	}

























}


