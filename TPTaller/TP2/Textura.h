#include <iostream>

class Textura {
	
	public:
		Textura(std::string id, std::string path);
		std::string getId();
		std::string getPath();

	private:
		std::string id;
		std::string path;


};