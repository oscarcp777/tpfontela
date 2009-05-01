
#include "StringUtils.h"

 StringUtils::StringUtils(){
}
 
 std::string  StringUtils::getValorTag(std::string nombretag,vector<string>& tokens){
 	vector<string>::iterator the_iterator;
 	string valorTag="error";
 	string valor ;
 	the_iterator = tokens.begin();
 	while( the_iterator != tokens.end() ) {
 		valor = *the_iterator;
 		valor =trimPalabra(valor);
 		int posicionCaracterIgual = valor.find_first_of("=");
 		valor= valor.substr(0,posicionCaracterIgual);
 		if(valor.compare(nombretag)==0){
 			++the_iterator;
 			valorTag=*the_iterator;
 			return valorTag;
 		}
 		++the_iterator;


 	}
 	return valorTag;
 }

string StringUtils::actualizarCadena(string cadena,char char_reemplazable){
	 //nueva cadena donde se reemplazaran los valores no deseados por los que quiero que contenga la cadena
	 std::string nueva_cadena;

	 int cant_veces = 0;
	 int inc = 0;

	 //tipo ostringstream que se utiliza para ingresar un string, char, int para despues poder pasarselo a la nueva_cadena
	 //sirve mas que nada para que no tome como un ascii al asignarle a nueva_cadena un valor entero.
	 std::ostringstream ostr;
     	 
	 while(inc<=cadena.length()){
		 
		 //Se obtiene el valor de cada posicion de cadena y se compara en la misma con el caracter que se desea reemplazar
		 //En caso de que el caracter a reemplazar coincida con el de la posicion inc en la cadena, a nueva_cadena le 
		 //asigno el caracter_reemplazable mas un entero que diferencia al resto de los caracteres. 
		 //Ej: x="2" x="3" x="4" se reemplazara por x1="2" x2="3" x3="4" copiando esto en nueva_cadena.
		 if(cadena[inc]==char_reemplazable){
			 cant_veces++;
			 ostr << cant_veces<<endl;
			 ostr.str("");
			 nueva_cadena+=char_reemplazable;
			 nueva_cadena+=ostr.str();
		 }else
		 
		  nueva_cadena+=cadena[inc];	
		  inc++;
	}
	
	 return nueva_cadena;

 }

string StringUtils::trim(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;

   
	while ( It != cadena.end() ){
		if((*It == ' ') || (*It == '\n')){
			//si el caracter es un espacio leo el siguiente
			It++;
			if((*It == ' ') || (*It == '\n')){
				//si es otro espacio, itero hasta que sea distinto de espacio
	        	//cadenaSinEspacios+=*It;
				while((*It == ' ') || (*It == '\n')){
				It++;
				}
				cadenaSinEspacios+=*It;
				//std::cout<<"despues del while"<<endl;
				//std::cout<<"caracter "<<*It<<endl;
				//system("PAUSE");
				It++;
				
			}
			else{
				//si lei un  espacio y el siguiente no es espacio vuelvo al primer espacio
				It--;
				//si no era otro espacio copio el caracter
				cadenaSinEspacios+=*It;
				//std::cout<<"1er else"<<endl;
				//std::cout<<"caracter "<<*It<<endl;
				//system("PAUSE");
				It++;
				}
		}
		else{
			//si no es un espacio directamente se la asigno a la cadena
			cadenaSinEspacios+=*It;
			//std::cout<<"2do else"<<endl;
			//std::cout<<"caracter "<<*It<<endl;
			//system("PAUSE");
			It++;
		}
	//std::cout<<"CADENA TEMPORAL: "<<endl;
	//std::cout<<cadenaSinEspacios<<endl;	
    }
 	
	return cadenaSinEspacios;
}
void StringUtils::Tokenize(const string& str, vector<string>& tokens, const string& delimiters ){
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

std::string StringUtils::trimPalabra(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;

    while ( It != cadena.end() )
    {
 		if(*It != ' '){
			cadenaSinEspacios+=*It;
				It++;
		}
		else{
			It++;
		}
  }
    return cadenaSinEspacios;
}
