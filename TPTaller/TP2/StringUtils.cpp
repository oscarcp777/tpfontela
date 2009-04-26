#include <string>
#include "StringUtils.h"
#include <iostream>
#include <list>
using namespace std;
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
 		std::cout<<"vector ooooooooooooooooooo \n "<<" "<<valor<<endl;
 		if(valor.compare(nombretag)==0){
 			++the_iterator;
 			valorTag=*the_iterator;
 			return valorTag;
 		}
 		++the_iterator;


 	}
 	return valorTag;
 }

string StringUtils::trim(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;
 bool isTag=false;
    while ( It != cadena.end() )
    {


		if(*It == '<'||isTag||*It == '>'){
				isTag=true;
		if(*It == '>'){isTag=false;}
	        	cadenaSinEspacios+=*It;
				It++;
		}
		else{
			It++;
		}


    }
// 	std::cout<<cadenaSinEspacios<< endl;

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
