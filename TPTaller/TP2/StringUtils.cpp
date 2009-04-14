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
