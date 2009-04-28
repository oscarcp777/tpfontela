#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
class StringUtils{

public:
	 StringUtils();
	/**
	* Este metodo quita los espacios en blanco entre los tag
	* de una cadena de caracteres
	*
	*/
    static std::string getValorTag(std::string nombretag,vector<string>& tokens);
	string trim(std::string cadena);
	static std::string trimPalabra(std::string cadena);
	static void Tokenize(const string& str, vector<string>& tokens, const string& delimiters );

private:

};
#endif
