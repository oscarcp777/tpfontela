#include "equipo.h"

void crearEquipo(TDA_Equipo* tda){
	tda->atajadas=0;
	tda->goles=0;
	tda->puntos=0;


}


void destruirEquipo(TDA_Equipo* tda){
	tda->atajadas=-1;
	tda->goles=-1;
	tda->puntos=-1;
}
