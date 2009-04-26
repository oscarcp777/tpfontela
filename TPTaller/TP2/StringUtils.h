#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
class StringUtils{
private:
public:
	 StringUtils();
	/**
	* Este metodo quita los espacios en blanco entre los tag
	* de una cadena de caracteres
	*
	*/
	string trim(std::string cadena);
	std::string trimPalabra(std::string cadena);
	void Tokenize(const string& str, vector<string>& tokens, const string& delimiters );
};

