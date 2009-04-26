#include "Hidratar.h"
#include "Escenario.h"


	void Hidratar::hidratarEscenario(std::string atributos){
		Escenario* escenario = Escenario::obtenerInstancia();
		//atributos

	}
	Textura* Hidratar::hidratartextura(std::string atributos){
     return new Textura("pocoyo4","pocoyo4.jpg");
}
