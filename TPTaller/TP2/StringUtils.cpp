#include <string>
#include "StringUtils.h"
#include <iostream>
#include <list>
using namespace std;
 StringUtils::StringUtils(){
}


string StringUtils::trim(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;
    while ( It != cadena.end() )
    {
    	if ( *It != ' ' )
    	cadenaSinEspacios+=*It;
 /* 		std::cout <<*/It++;
    }
 //	std::cout<<cadenaSinEspacios << endl;
   
	return cadenaSinEspacios;
}
