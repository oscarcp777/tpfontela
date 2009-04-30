#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>

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
	static std::string actualizarCadena(string cadena,char char_reemplazable);
	static void Tokenize(const string& str, vector<string>& tokens, const string& delimiters );

private:

};
#endif
