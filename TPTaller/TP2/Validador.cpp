//#include <iostream>
//#include <list>
//#include <string>

#include "Validador.h"
#include "archivoTexto.h"
#include "StringUtils.h"
#include "Escenario.h"
#include "Textura.h"
#include "Hidratar.h"
#include "Tag.h"
using namespace std;
const char MARCADOR_TAG = '-';

bool dentroDeCuadrado= false;
bool dentroDeCirculo= false;
bool dentroDeSegmento= false;
bool dentroDeTriangulo= false;
bool dentroDeRectangulo= false;
std::string todosLosValues;

Validador::Validador(std::string nombreArchivoTags,std::string nombreArchivoAtributos){
	ArchivoTexto miArchivoTags(nombreArchivoTags);
	ArchivoTexto miArchivoAtributos(nombreArchivoAtributos);
	string linea1, linea2;
	miArchivoTags.irAlPrincipio();
	bool encontro = false;
	Tag *tagActual;
	while (miArchivoTags.leerLinea(linea1)) {
		// std::cout << linea << std::endl;
		//leo la linea y la guardo en la Lista
		tagActual = new Tag(linea1);
		miArchivoAtributos.irAlPrincipio();
		encontro = false;
		while(miArchivoAtributos.leerLinea(linea2) && encontro == false){
			if(linea2.at(0)== MARCADOR_TAG){
				linea2 = linea2.substr(1,linea2.size());
				if (linea2.compare(linea1) == 0){
					encontro = true;
					while (linea2.at(0)!= MARCADOR_TAG  && miArchivoAtributos.leerLinea(linea2))
						tagActual->addAtributo(linea2);

				}
			}
		}
		Validador::ListaTagsValidos.push_back(tagActual);
	}


}
int Validador::validarCantidadTag(std::string atributo,vector<string>& listaClave,std::string cadenaTag){
	vector<string>::iterator the_iterator;
	string valorTag="sinValor";
	string valor ;
	int cont=0;
	int contTriX=0;
	int contTriY=0;
	int contSegX=0;
	int contSegY=0;
	std::cout<<"atributo "<<atributo<<"tag :"<<cadenaTag<<endl;
	the_iterator = listaClave.begin();
	while( the_iterator != listaClave.end() ) {
		valor = *the_iterator;
		valor =StringUtils::trimPalabra(valor);
		if(atributo.compare("x")==0&&valor.compare(atributo)==0){
			if(cadenaTag.compare("triangulo")==0){
				contTriX++;
				std::cout<<"entro x triangulo"<<atributo<<"tag :"<<contTriX<<endl;
				if(contTriX==4)
					return -1;
			}
			if(cadenaTag.compare("segmento")==0){
				contSegX++;
				std::cout<<"entro x segmento"<<atributo<<"tag :"<<contSegX<<endl;
				if(contSegX==3)
					return -1;
			}
			if(cadenaTag.compare("segmento")!=0&&cadenaTag.compare("triangulo")!=0){

				cont++;
				std::cout<<"otros  x"<<atributo<<"tag :"<<cont<<endl;
			}
		}else{
			if(atributo.compare("y")==0&&valor.compare(atributo)==0){
				if(cadenaTag.compare("triangulo")==0){
					contTriY++;
					std::cout<<"entro y triangulo"<<atributo<<"tag :"<<cadenaTag<<endl;
					if(contTriY==4)
						return -1;
				}
				if(cadenaTag.compare("segmento")==0){
					contSegY++;
					std::cout<<"segmento y "<<atributo<<"tag :"<<cadenaTag<<endl;
					if(contSegY==3)
						return -1;
				}
				if(cadenaTag.compare("segmento")!=0&&cadenaTag.compare("triangulo")!=0){
					std::cout<<"otros y"<<atributo<<"tag :"<<cadenaTag<<endl;
								cont++;
							}
			}else{
				if(valor.compare(atributo)==0){
					std::cout<<"todos menos x "<<atributo<<"tag :"<<cadenaTag<<endl;
					cont++;
				}

			}
		}

		++the_iterator;


	}
	if(cont<=1)
		return 0;
	else
		return -1;
}
Validador::~Validador(){
	list<Tag*>::iterator iter;
	Tag* nombreTag;
	iter=Validador::ListaTagsValidos.begin();

	while(iter != Validador::ListaTagsValidos.end()){
		nombreTag=*iter;
		delete nombreTag;
		iter++;
	}
}
void Validador::setLog(Log* log){
	this->log = log;

}


int Validador::validarValues(std::string tipo,std::string values){
	//el tipo puede ser (<posicion,<textura,<ver1,<ver2,<ver3,<inicio,<fin y cualquier tipo de figura
	//valida que esten bien los datos que llegan en value (porque el tipo ya fue validado, devuelve 0 si esta todo OK, sino devuelve -1
	int exito = 0;
	std::string cadena;

	if(tipo.compare("<textura ")==0){
		//obtengo el ultimo caracter, se supone que deben ser >
		cadena = values.substr(values.length()-1,values.length());

		//si no es el caracter > devuelvo -1
		if(cadena.compare(">") != 0){
			exito = -1;
		}

		//si es el caracter > esta todo OK parseo
		else{
			//std::cout<<"values: "<<values<<endl;
			//con la siguiente funcion se crea la textura y se agrega al escenario
			exito=Hidratar::hidratartextura(values.substr(0,values.size()-1));

		}
	}

	else if(tipo.compare("<General ")==0){
		//obtengo el ultimo caracter, se supone que deben ser >
		cadena = values.substr(values.length()-1,values.length());

		//si no es el caracter > devuelvo -1
		if(cadena.compare(">") != 0){
			exito = -1;
		}

		//si es el caracter > esta todo OK parseo
		else{
			//std::cout<<"values: "<<values<<endl;
			//con la siguiente funcion se setean en escenario todos los atributos que vienen en <General>
			exito=Hidratar::hidratarEscenario(values);
			//exito=0;
		}
	}
	else if((tipo.compare("<cuadrado ")==0) || (dentroDeCuadrado)){

		if(!dentroDeCuadrado){
			//obtengo el ultimo caracter, se supone que deben ser >
			cadena = values.substr(values.length()-1,values.length());

			//si no es el caracter > o si values contiene "<" devuelvo -1
			if((cadena.compare(">") != 0) || (values.find("<")<values.size())){
				exito = -1;
			}

			//si es el caracter > esta todo OK parseo
			else{
				//std::cout<<"values: "<<values<<endl;
				//copio los values "solamente" borro el ultimo caracter >
				todosLosValues = values.substr(0,values.size()-1)+" ";
				dentroDeCuadrado = true;
			}
		}
		else{
			std::cout<<"DENTRO de CUADRADO"<<endl;
			//si entro por segunda vez dentro de cuadrado
			if(tipo.compare("<posicion ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					//copio los values "solamente" borro los ultimos caracteres />
					todosLosValues += values.substr(0,values.size()-2);
					//std::cout<<"TODOS LOS VALUESSSs "<<todosLosValues<<endl;
					exito=Hidratar::hidratarCuadrado(todosLosValues);
					dentroDeCuadrado = false;
				}
			}
			std::cout<<"FIN de CUADRADO"<<endl;
		}

	}

	else if((tipo.compare("<circulo ")==0) || (dentroDeCirculo)){

		if(!dentroDeCirculo){
			//obtengo el ultimo caracter, se supone que deben ser >
			cadena = values.substr(values.length()-1,values.length());

			//si no es el caracter > o si values contiene "<" devuelvo -1
			if((cadena.compare(">") != 0) || (values.find("<")<values.size())){
				exito = -1;
			}

			//si es el caracter > esta todo OK parseo
			else{
				//std::cout<<"values: "<<values<<endl;
				//copio los values "solamente" borro el ultimo caracter >
				todosLosValues = values.substr(0,values.size()-1)+" ";
				dentroDeCirculo = true;
			}
		}
		else{
			std::cout<<"DENTRO de Circulo"<<endl;
			//si entro por segunda vez dentro de cuadrado
			if(tipo.compare("<posicion ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					//copio los values "solamente" borro los ultimos caracteres />
					todosLosValues += values.substr(0,values.size()-2);
					//std::cout<<"TODOS LOS VALUESSSs "<<todosLosValues<<endl;
					exito=Hidratar::hidratarCirculo(todosLosValues);
					dentroDeCirculo = false;
				}
			}
			std::cout<<"FIN de CIRCULO"<<endl;
		}
	}
	else if((tipo.compare("<rectangulo ")==0)||(dentroDeRectangulo)){

		if(!dentroDeRectangulo){
			//obtengo el ultimo caracter, se supone que deben ser >
			cadena = values.substr(values.length()-1,values.length());

			//si no es el caracter > o si values contiene "<" devuelvo -1
			if((cadena.compare(">") != 0) || (values.find("<")<values.size())){
				exito = -1;
			}

			//si es el caracter > esta todo OK parseo
			else{
				//std::cout<<"values: "<<values<<endl;
				//copio los values "solamente" borro el ultimo caracter >
				todosLosValues = values.substr(0,values.size()-1)+" ";
				dentroDeRectangulo = true;
			}
		}
		else{
			std::cout<<"DENTRO de Rectangulo"<<endl;
			//si entro por segunda vez dentro de cuadrado
			if(tipo.compare("<posicion ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					//copio los values "solamente" borro los ultimos caracteres />
					todosLosValues += values.substr(0,values.size()-2);
					//std::cout<<"TODOS LOS VALUESSSs "<<todosLosValues<<endl;
					exito=Hidratar::hidratarRectangulo(todosLosValues);

					dentroDeRectangulo = false;
				}
			}
			std::cout<<"FIN de Rectangulo"<<endl;
		}
	}
	else if((tipo.compare("<triangulo ")==0) || (dentroDeTriangulo)){

		if(!dentroDeTriangulo){
			//obtengo el ultimo caracter, se supone que deben ser >
			cadena = values.substr(values.length()-1,values.length());

			//si no es el caracter > o si values contiene "<" devuelvo -1
			if((cadena.compare(">") != 0) || (values.find("<")<values.size())){
				exito = -1;
			}

			//si es el caracter > esta todo OK parseo
			else{
				//std::cout<<"values: "<<values<<endl;
				todosLosValues = values.substr(0,values.size()-1)+" ";
				dentroDeTriangulo = true;
			}
		}
		else{
			std::cout<<"DENTRO de triangulo"<<endl;

			if(tipo.compare("<ver1 ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					todosLosValues += values.substr(0,values.size()-2)+" ";
				}
			}

			else if(tipo.compare("<ver2 ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					todosLosValues += values.substr(0,values.size()-2)+" ";
				}
			}

			else if(tipo.compare("<ver3 ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					todosLosValues += values.substr(0,values.size()-2);
					//std::cout<<"TODOS LOS VALUESSSs "<<todosLosValues<<endl;
					exito=Hidratar::hidratarTriangulo(todosLosValues);
					//si llega a vertice3 sale
					dentroDeTriangulo = false;
				}
			}


			std::cout<<"FIN de triangulo"<<endl;
		}
	}
	else if((tipo.compare("<segmento ")==0) || (dentroDeSegmento)){

		if(!dentroDeSegmento){
			//obtengo el ultimo caracter, se supone que deben ser >
			cadena = values.substr(values.length()-1,values.length());

			//si no es el caracter > o si values contiene "<" devuelvo -1
			if((cadena.compare(">") != 0) || (values.find("<")<values.size())){
				exito = -1;
			}

			//si es el caracter > esta todo OK parseo
			else{
				//std::cout<<"values: "<<values<<endl;
				todosLosValues = values.substr(0,values.size()-1)+" ";
				dentroDeSegmento = true;
			}
		}
		else{
			std::cout<<"DENTRO de segmento"<<endl;
			if(tipo.compare("<inicio ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					todosLosValues += values.substr(0,values.size()-2)+" ";
				}
			}

			else if(tipo.compare("<fin ")==0){
				//obtengo los dos ultimos caracteres, se supone que deben ser />
				cadena = values.substr(values.length()-2,values.length());

				//si no son /> devuelvo -1
				if(cadena.compare("/>") != 0){
					exito = -1;
				}

				//si son /> esta todo OK parseo
				else{
					//std::cout<<"values: "<<values<<endl;
					todosLosValues += values.substr(0,values.size()-2);
					//std::cout<<"TODOS LOS VALUESSSs "<<todosLosValues<<endl;
					exito=Hidratar::hidratarSegmento(todosLosValues);
					dentroDeSegmento= false;
				}
			}

			std::cout<<"FIN de segmento"<<endl;
		}
	}
	return exito;
}


int Validador::compararConTagsValidos(string cadena){
	list<Tag*>::iterator i;
	int exito=-1;
	Tag* nombreTag;
	i=Validador::ListaTagsValidos.begin();

	while(i != Validador::ListaTagsValidos.end()){
		//exito = cadena.compare(*i);
		nombreTag = *i;
		exito = cadena.compare(nombreTag->getNombreTag());

		//std::cout << *i<< " "<<endl;
		//std::cout <<"exito"<<exito<<endl;
		if(exito == 0){
			return 0;
		}
		i++;
	}

	return exito;
}
int Validador::compararConVectorAtributosValidos(string cadenaTag,std::vector<string> listaAtributos){
	std::vector<string>::iterator iter;
	std::string tagRepetido;
	iter = listaAtributos.begin();
	std::string mensaje="EN EL TAG "+cadenaTag+" EL SIGUIENTE ATRIBUTO SE ENCUENTRA REPETIDO: ";
	Escenario* escenario=Escenario::obtenerInstancia();
	while( iter != listaAtributos.end() ) {
		std::string tag=*iter;
		if(validarCantidadTag(*iter,listaAtributos,cadenaTag)==-1&&tagRepetido.compare(tag)!=0){
			tagRepetido=tag;
			escribirMensajeLog(*(escenario->getLog()),mensaje+tag);
		}

		if(Validador::compararConAtributosValidos(cadenaTag,*iter)==-1){

			return -1;
		}
		++iter;
	}
	return 0;
}
int Validador::compararConAtributosValidos(string cadenaTag, string cadenaAtributo){
	list<Tag*>::iterator i;
	int exito=-1;
	Tag* tag;
	i=Validador::ListaTagsValidos.begin();
	int atributoValido = -1;

	while(i != Validador::ListaTagsValidos.end()){
		//exito = cadena.compare(*i);
		tag = *i;
		exito = cadenaTag.compare(tag->getNombreTag());

		//std::cout << *i<< " "<<endl;
		//std::cout <<"exito"<<exito<<endl;
		if(exito == 0){

			atributoValido =tag->chequearAtributo(cadenaAtributo);

			return atributoValido;
		}
		i++;
	}

	return atributoValido;
}


int Validador::validarArchivoXML(int i,string cadena){
	int exito = 0;
	int exitoValues;
	string subCadena,values;
	char caracter = NULL;
	//std::cout<<"caracter cuando inicia la func "<<caracter<<endl;
	//std::cout<<"cadena "<<cadena<<endl;
	//std::cout<<"valor de i cuando se llama a la fun "<<i<<endl;
	// le asigno el caracter "<" a subCadena
	if(i==1){
		subCadena += '<';
	}
	//leo el string cadena mientras que no encuntre un " "(espacio) o un ">"
	while((caracter != ' ') && (caracter != '>') && (i<cadena.length())){
		//std::cout<<"valor de i en el while "<<i<<endl;
		caracter = cadena.at(i);
		//std::cout<<caracter<<endl;
		subCadena += caracter;
		//std::cout<<subCadena<<endl;
		i++;
		//std::cout<<"valor de i en el while "<<i<<endl;

	}
	//system("PAUSE");
	//si el ultimo caracter es ">" es un cierre de etiqueta
	if(caracter == '>'){

		if(subCadena.at(1) == '/'){

			//en la siguiente linea con "substr" borro los </> y comparo con los tags validos
			if(Validador::compararConTagsValidos(subCadena.substr(2,subCadena.length()-3))!=0){
				//si es distinto de 0 es porque no es un tag valido
				std::cout<<"error de sintaxis, no se esperaba "<<subCadena<<endl;
				//escribo el error en el archivo de errores
				escribirMensajeLog(*this->log,"error de sintaxis, no se esperaba "+subCadena);
				//destruirLog(log);
				return -1;
			}
			else{
				std::cout<<"se encontro un cierre  "<<subCadena<<endl;
				Validador::ListaTagsArchivo.push_back(subCadena);
				//si es correcta la sintaxis agregar a una listahi de tags o algo para comparar
				//cierres y aperturas correctamente
			}

		}
		else{
			//en la siguiente linea con substr borro los <> y comparo con los tags validos
			if(Validador::compararConTagsValidos(subCadena.substr(1,subCadena.length()-2))!=0){
				std::cout<<"error de sintaxis, no se esperaba "<<subCadena<<endl;
				//escribo el error en el archivo de errores
				escribirMensajeLog(*this->log,"error de sintaxis, no se esperaba "+subCadena);
				//destruirLog(log);
				return -1;
			}
			else{
				//si es correcta la sintaxis agregar a una lista de tags o algo para comparar
				//cierres y aperturas correctamente
				std::cout<<"se encontro una apertura "<<subCadena<<endl;
				Validador::ListaTagsArchivo.push_back(subCadena);
			}

		}
		//se llama nuevamente con el ultimo valor de i, si i es menor que el tamaño de la cadena
		if(i<cadena.length()){
			exito = Validador::validarArchivoXML(i,cadena);
		}
	}
	//si el ultimo caracter es " "(espacio) lo que sigue en cadena son campos y luego viene el cierre
	else if (caracter == ' '){
		int posicionEspacio = subCadena.find_first_of(' ');
		//en la siguiente linea obtengo la cadena hasta antes del espacio y sin el "<" y la comparo con los tags validos
		if(Validador::compararConTagsValidos(subCadena.substr(1,posicionEspacio-1))!=0){
			std::cout<<"error de sintaxis, no se esperaba "<<subCadena<<endl;
			//escribo el error en el archivo de errores
			escribirMensajeLog(*this->log,"error de sintaxis, no se esperaba "+subCadena);
			//destruirLog(log);
			return -1;
		}
		else{
			std::cout<<"se encontro un espacio luego de la apertura "<<subCadena<<endl;

			//como existe espacio, tengo que comparar la cadena despues de "<" hasta antes del espacio " " con los TAGS Validos
			//TODO comparar la cadena con TAGS validos y parciar lo que sigue luego del espacio
			caracter = NULL;
			// i tiene el valor del while anterior (cuando salio)
			while((caracter != '>') &&(i<cadena.length())){
				caracter = cadena.at(i);
				values += caracter;
				i++;
			}

			if(values.at(values.length()-1) != '>'){
				//si no termina en ">" es un error de sintaxis
				std::cout<<"error de sintaxis, se esperaba cierre >"<<endl;
				//escribo el error en el archivo de errores
				escribirMensajeLog(*this->log,"error de sintaxis, se esperaba cierre >");
				//destruirLog(log);
				return -1;
			}
			else{
				//si entra aca es porque values termina en ">" asique agrego el tag en la linea siguiente
				Validador::ListaTagsArchivo.push_back(subCadena.substr(0,posicionEspacio)+='>');
				exitoValues = Validador::validarValues(subCadena,values);
				//si exitoValues  es -1 (hay un error en values) imprimo en log y salgo, si es 0 sigue todo como antes
				if(exitoValues != 0){
					escribirMensajeLog(*this->log,"error de sintaxis, verifique la linea: "+subCadena+values);
					//destruirLog(log);
					return -1;
				}

			}
		}

		//se llama nuevamente con el ultimo valor de i, si i es menor que el tamaño de la cadena
		if(i<cadena.length()){
			exito = Validador::validarArchivoXML(i,cadena);
		}
	}
	//si no encuentro ni " "(espacio) ni ">" error en sintaxis
	else{
		std::cout<<"error de sintaxis, "<<subCadena<<endl;
		//escribo el error en el archivo de errores
		escribirMensajeLog(*this->log,"error de sintaxis,  verifique la linea: "+subCadena);
		//destruirLog(log);
		return -1;
	}
	//destruirLog(log);
	return exito;
}

int Validador::borrarDeTagsNoNecesariosDeListaTagsArchivo(){
	int exito = 0;
	list<string>::iterator itAux;
	list<string>::iterator it = Validador::ListaTagsArchivo.begin();
	string cadena;

	while(it != Validador::ListaTagsArchivo.end()){

		cadena = *it;
		if(cadena.compare("<posicion>")==0){
			itAux =it;
			it++;
			Validador::ListaTagsArchivo.erase(itAux);
		}
		else if(cadena.compare("<ver1>")==0){
			itAux =it;
			it++;
			Validador::ListaTagsArchivo.erase(itAux);
		}
		else if(cadena.compare("<ver2>")==0){
			itAux =it;
			it++;
			Validador::ListaTagsArchivo.erase(itAux);
		}
		else if(cadena.compare("<ver3>")==0){
			itAux =it;
			it++;
			Validador::ListaTagsArchivo.erase(itAux);
		}
		else if(cadena.compare("<inicio>")==0){
			itAux =it;
			it++;
			Validador::ListaTagsArchivo.erase(itAux);
		}
		else if(cadena.compare("<fin>")==0){
			itAux =it;
			it++;
			Validador::ListaTagsArchivo.erase(itAux);
		}
		else{
			it++;
		}

	}
	return exito;
}





int Validador::validarAperturaYCierreTags(){
	int exito=-1;
	bool primerIngresoAlIf = true;
	bool primerIngresoAlIfTexturas = true;
	bool dentroListaTexturas = false;
	bool dentroListaElementos = false;
	string cadena;
	list<string>::iterator iterAux1,iterAux2, iterAux3, iterAux4, iterAux5;
	list<string>::iterator iter = Validador::ListaTagsArchivo.begin();

	//verifico que el primer elemento sea <escenario>
	cadena = *iter;//contiene el primer tag del archivo
	if(cadena.compare("<escenario>") != 0){
		std::cout<<"no se esperaba "<<cadena<<"en el comienzo del archivo"<<endl;
		//escribo el error en el archivo de errores
		escribirMensajeLog(*this->log,"no se esperaba "+cadena+" en el comienzo del archivo");
		exito = -2;
	}

	//verifico que el ultimo elemento sea </escenario>
	iterAux1= Validador::ListaTagsArchivo.end();
	iterAux1--;
	cadena = *iterAux1;//contiene el ultimo tag del archivo
	if(cadena.compare("</escenario>") != 0){
		std::cout<<"no se esperaba "<<cadena<<" en el fin del archivo"<<endl;
		//escribo el error en el archivo de errores
		escribirMensajeLog(*this->log,"no se esperaba "+cadena+" en el fin del archivo");
		exito = -2;

	}
	//empieza en el segundo elemento;
	iter++;
	//std::cout<<"contenido iter"<<*iter<<endl;

	while(Validador::ListaTagsArchivo.size()!=2 && (exito==-1)){

		cadena = *iter;
		//std::cout<<"contenido de iter al iniciar el while"<<*iter<<endl;

		if(cadena.compare("<General>")==0){
			//si la cadena es <General> se supone que la siguiente tiene que ser </General>, lo verifico
			iterAux1 =iter;
			iterAux2 = ++iter;
			cadena = *iterAux2;
			if(cadena.compare("</General>")==0){
				//si encuentro <General> seguido de </General> los borro
				iter++;
				Validador::ListaTagsArchivo.erase(iterAux1);
				Validador::ListaTagsArchivo.erase(iterAux2);

			}
			else{
				//sino es un error de sintaxis
				std::cout<<"se espera <General> cerrado por </General>"<<endl;
				//escribo el error en el archivo de errores
				escribirMensajeLog(*this->log,"se espera <General> cerrado por </General>");
				//para que salga del while hago lo siguiente
				exito=-2;

			}
		}
		else if(cadena.compare("<ListadoDeTexturas>")==0 || dentroListaTexturas==true){
			//utilizo dentroListaTexturas para trabajar entre <ListadoDeTexturas> y </ListadoDeTexturas>
			dentroListaTexturas = true;
			//si la cadena es <ListadoDeTexturas> pueden pasar dos cosas, que el siguiente sea </ListadoDeTexturas> o
			//que tenga mas elementos (texturas) dentro
			iterAux1 =iter;
			iterAux2 = iter;
			if(primerIngresoAlIfTexturas == true){
				//lo uso porque si entra por primera vez tengo que incrementar, pero si entra por segunda vez para borrar
				//alguna textura no se tiene que incrementar
				iterAux2++;
			}
			primerIngresoAlIfTexturas=false;
			cadena = *iterAux2;
			if(cadena.compare("<textura>")==0){
				//si encuentro <textura> verifico que el siguiente sea </textura> y los borro, sino error sintaxis
				iterAux1=iterAux2;
				iterAux1++;
				cadena = *iterAux1;

				if(cadena.compare("</textura>")==0){
					iter=iterAux1;
					iter++;
					Validador::ListaTagsArchivo.erase(iterAux1);
					Validador::ListaTagsArchivo.erase(iterAux2);

				}
				else{
					//sino es un error de sintaxis
					std::cout<<"se espera <textura> cerrado por </textura>"<<endl;
					//escribo el error en el archivo de errores
					escribirMensajeLog(*this->log,"se espera <textura> cerrado por </textura>");
					//para que salga del while hago lo siguiente
					exito=-2;

				}


			}
			else if(cadena.compare("</ListadoDeTexturas>")==0){
				//si encuentro <ListadoDeTexturas> seguido de </ListadoDeTexturas> los borro
				//decremento el puntero para que apunte a <ListadoDeTexturas> y iterAux2 apunta a </ListadoDeTexturas>
				iterAux1--;
				if(Validador::ListaTagsArchivo.size() != 3){
					iter++;
				}
				else{
					exito =-2;
				}
				Validador::ListaTagsArchivo.erase(iterAux1);
				Validador::ListaTagsArchivo.erase(iterAux2);

				dentroListaTexturas=false;


			}
			else{
				//sino es un error de sintaxis
				std::cout<<"se espera <ListadoDeTexturas> cerrado por </ListadoDeTexturas>"<<endl;
				//escribo el error en el archivo de errores
				escribirMensajeLog(*this->log,"no se esperaba"+cadena+" en  <ListadoDeTexturas>");
				//para que salga del while hago lo siguiente
				dentroListaTexturas=false;
				exito=-2;

			}


		}

		else if(cadena.compare("<ListadoDeElementos>")==0 || dentroListaElementos==true){
			//utilizo dentroListaElementos para trabajar entre <ListadoDeElementos> y </ListadoDeElementos>
			dentroListaElementos = true;
			//si la cadena es <ListadoDeElementos> pueden pasar dos cosas, que el siguiente sea </ListadoDeElementos> o
			//que tenga mas elementos (figuras) dentro
			iterAux1 =iter;
			iterAux2 = iter;
			if(primerIngresoAlIf == true){
				//lo uso porque si entra por primera vez tengo que incrementar, pero si entra por segunda vez para borrar
				//alguna figura no se tiene que incrementar
				iterAux2++;
			}
			primerIngresoAlIf=false;
			cadena = *iterAux2;

			if(cadena.compare("</ListadoDeElementos>")==0){

				//si encuentro <ListadoDeElementos> seguido de </ListadoDeElementos> los borro
				//decremento el puntero para que apunte a <ListadoDeElementos> y iterAux2 apunta a </ListadoDeElementos>
				iterAux1--;
				iter++;
				Validador::ListaTagsArchivo.erase(iterAux1);
				Validador::ListaTagsArchivo.erase(iterAux2);
				dentroListaElementos=false;

			}
			else if(cadena.compare("<cuadrado>")==0){
				//si encuentro <cuadrado> verifico que el siguiente sea </cuadrado> y los borro, sino error sintaxis
				iterAux1=iterAux2;
				iterAux1++;
				iterAux3 = iterAux1;
				cadena = *iterAux1;
				if(cadena.compare("<posicion>") == 0){
					iterAux3++;
					cadena = *iterAux3;
					if(cadena.compare("</cuadrado>")==0){
						iter=iterAux3;
						iter++;
						Validador::ListaTagsArchivo.erase(iterAux1);
						Validador::ListaTagsArchivo.erase(iterAux2);
						Validador::ListaTagsArchivo.erase(iterAux3);

					}
					else{
						//sino es un error de sintaxis
						std::cout<<"verifique los tags de cuadrado"<<endl;
						//escribo el error en el archivo de errores
						escribirMensajeLog(*this->log,"error, verifique los tags de cuadrado");
						//para que salga del while hago lo siguiente
						exito=-2;

					}
				}


			}
			else if(cadena.compare("<triangulo>")==0){
				//si encuentro <triangulo> verifico que el siguiente sea </triangulo> y los borro, sino error sintaxis
				iterAux1=iterAux2;
				iterAux1++;
				cadena = *iterAux1;
				if(cadena.compare("</triangulo>")==0){
					iter=iterAux1;
					iter++;
					Validador::ListaTagsArchivo.erase(iterAux1);
					Validador::ListaTagsArchivo.erase(iterAux2);


				}
				else{
					//sino es un error de sintaxis
					std::cout<<"se espera <triangulo> cerrado por </triangulo>"<<endl;
					//escribo el error en el archivo de errores
					escribirMensajeLog(*this->log,"se espera <triangulo> cerrado por </triangulo>");

					//para que salga del while hago lo siguiente
					exito= -2;

				}


			}
			else if(cadena.compare("<segmento>")==0){
				//si encuentro <triangulo> verifico que el siguiente sea </triangulo> y los borro, sino error sintaxis
				iterAux1=iterAux2;
				iterAux1++;
				iterAux3 = iterAux1;
				cadena = *iterAux1;

				if(cadena.compare("<inicio>") == 0){
					iterAux3++;
					iterAux4 = iterAux3;
					cadena = *iterAux3;
					if(cadena.compare("<fin>") == 0){
						iterAux4++;
						cadena = *iterAux4;
						if(cadena.compare("</segmento>")==0){
							iter=iterAux4;
							iter++;
							Validador::ListaTagsArchivo.erase(iterAux1);
							Validador::ListaTagsArchivo.erase(iterAux2);
							Validador::ListaTagsArchivo.erase(iterAux3);
							Validador::ListaTagsArchivo.erase(iterAux4);

						}
						else{
							//sino es un error de sintaxis
							std::cout<<"verifique los tags de segmento"<<endl;
							//escribo el error en el archivo de errores
							escribirMensajeLog(*this->log,"error, verifique los tags de segmento");
							//para que salga del while hago lo siguiente
							exito=-2;

						}
					}
				}


			}
			else if(cadena.compare("<rectangulo>")==0){
				//si encuentro <rectangulo> verifico que el siguiente sea </rectangulo> y los borro, sino error sintaxis
				iterAux1=iterAux2;
				iterAux1++;
				iterAux3 = iterAux1;
				cadena = *iterAux1;
				if(cadena.compare("<posicion>") == 0){
					iterAux3++;
					cadena = *iterAux3;
					if(cadena.compare("</rectangulo>")==0){
						iter=iterAux3;
						iter++;
						Validador::ListaTagsArchivo.erase(iterAux1);
						Validador::ListaTagsArchivo.erase(iterAux2);
						Validador::ListaTagsArchivo.erase(iterAux3);

					}
					else{
						//sino es un error de sintaxis
						std::cout<<"verifique los tags de rectangulo"<<endl;
						//escribo el error en el archivo de errores
						escribirMensajeLog(*this->log,"error, verifique los tags de rectangulo");
						//para que salga del while hago lo siguiente
						exito=-2;

					}
				}
			}

			else if(cadena.compare("<circulo>")==0){
				//si encuentro <circulo> verifico que el siguiente sea </circulo> y los borro, sino error sintaxis
				iterAux1=iterAux2;
				iterAux1++;
				iterAux3 = iterAux1;
				cadena = *iterAux1;
				if(cadena.compare("<posicion>") == 0){
					iterAux3++;
					cadena = *iterAux3;
					if(cadena.compare("</circulo>")==0){
						iter=iterAux3;
						iter++;
						Validador::ListaTagsArchivo.erase(iterAux1);
						Validador::ListaTagsArchivo.erase(iterAux2);
						Validador::ListaTagsArchivo.erase(iterAux3);

					}
					else{
						//sino es un error de sintaxis
						std::cout<<"verifique los tags de circulo"<<endl;
						//escribo el error en el archivo de errores
						escribirMensajeLog(*this->log,"error, verifique los tags de circulo");
						//para que salga del while hago lo siguiente
						exito=-2;

					}
				}


			}
			else{
				//sino es un error de sintaxis
				std::cout<<"no se esperaba"<<cadena<<endl;
				//escribo el error en el archivo de errores
				escribirMensajeLog(*this->log,"no se esperaba "+cadena+" en ListadoElementos");
				//para que salga del while hago lo siguiente
				dentroListaElementos=false;
				exito=-2;

			}
		}
		else{
			//sino es un error de sintaxis
			std::cout<<"no se esperaba "<<cadena<<endl;
			//escribo el error en el archivo de errores
			escribirMensajeLog(*this->log,"no se esperaba "+cadena);
			//para que salga del while hago lo siguiente
			exito=-2;
		}


	}

	//si sale del while sin error en el while(es decir exito igual a -1) en la lista de tagsArchivo debe haber solo dos elementos
	//<escenario> y </escenario>
	if((exito==-1) && (Validador::ListaTagsArchivo.size()==2)){
		iterAux1 = Validador::ListaTagsArchivo.begin();//este debe contener <escenario>
		iterAux2 = iterAux1;
		iterAux2++;//este debe contener </escenario>
		cadena = *iterAux1;

		if(cadena.compare("<escenario>")==0){
			//si la cadena es <escenario> se supone que la siguiente tiene que ser <escenario> (si llega hasta aca sin tirar error
			//es porque solo quedan dos elementos (<escenario> y </escenario>), lo verifico
			cadena = *iterAux2;
			if(cadena.compare("</escenario>")==0){
				//si encuentro <escenario> seguido de </escenario> los borro
				Validador::ListaTagsArchivo.erase(iterAux1);
				Validador::ListaTagsArchivo.erase(iterAux2);

			}
			else{
				//sino es un error de sintaxis
				std::cout<<"se espera <escenario> cerrado por </escenario>"<<endl;
				//escribo el error en el archivo de errores
				escribirMensajeLog(*this->log,"se espera <escenario> cerrado por </escenario>");
				//para que salga del while hago lo siguiente
				exito=-2;

			}
		}
	}
	else if((exito==-1) && Validador::ListaTagsArchivo.size()!=2){
		//sino es un error de sintaxis
		std::cout<<"se espera <escenario> cerrado por </escenario>"<<endl;
		//escribo el error en el archivo de errores
		escribirMensajeLog(*this->log,"se espera <escenario> cerrado por </escenario>");
		//para que salga del while hago lo siguiente
		exito=-2;

	}
	if(Validador::ListaTagsArchivo.empty()==true){
		//si se borraron todos los tags es porque estaban bien
		exito=0;
	}

	return exito;
}


int Validador::validarSintaxis(std::string nombreArchivo){

	string cadena,linea,subCadena,values;
	char caracter;
	int i,exito;
	//Log log;
	//inicializarLog(log, "errores.err");
	ArchivoTexto miArchivo(nombreArchivo);
	miArchivo.irAlPrincipio();

	while (miArchivo.leerLinea(linea)) {
		//std::cout << linea << std::endl;
		cadena += linea;

	}
	//
	int cant=StringUtils::contadorTag(cadena);

	//if((cant%2)==0){
	//		cadena=StringUtils::trimPorTag(cadena);
	//}else{

	cadena=StringUtils::trim(cadena);
	//}

	////	std::cout <<"INICIO CONTENIDO DE ARCHIVO XML.xml (con espacios y tabs borrados)"<<endl;
	//	std::cout<<cadena<<endl;
	//	std::cout <<"FIN CONTENIDO DE ARCHIVO XML.xml (con espacios y tabs borrados)"<<endl;
	//    system("PAUSE");
	//obtengo primer caracter de la cadena
	caracter = cadena.at(0);
	//si el primer caracter es "<" sigo
	if( caracter == '<'){
		i=1;
		exito = Validador::validarArchivoXML(i,cadena);
		//std::cout<<"exito"<<exito<<endl;

		if(exito == 0){
			//entra a este if si se validaron los tags correctamente del archivo,en las siguientes lineas se verifica si
			//los tags se abrieron <> y se cerraron </> correctamentes (que no se abra uno antes de cerrar otro
			list<string>::iterator iter = Validador::ListaTagsArchivo.begin();


			std::cout<<"TAGS"<<endl;
			while(iter != this->ListaTagsArchivo.end()){
				std::cout<<*iter<<endl;
				iter++;

			}
			std::cout<<"FIN TAGS"<<endl;

			//Validador::borrarDeTagsNoNecesariosDeListaTagsArchivo();
			exito = Validador::validarAperturaYCierreTags();

		}

	}
	//si el primer caracter es DISTINTO de "<" error en sintaxis
	else{
		std::cout<<"error de sintaxis, no comienza con < "<<endl;
		//escribo el error en el archivo de errores
		escribirMensajeLog(*this->log,"error de sintaxis, no comienza con <");
		//destruirLog(log);
		return -1;
	}

	return exito;
}

int Validador::validarNumero(std::string numero){
	for ( int pos = 0; pos < numero.length(); ++pos ){
		if(!isdigit(numero.at(pos))){
			return -1;
		}
	}
	return 0;
}







