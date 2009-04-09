
#include "juego.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main()
{
    //Declaro variables
    ArchivoTexto aPartida;
    Juego juego;

    srand(time(NULL)); //Crea la semilla para el dado tomando la hora del sistema

    cout << "Mineros v1.0" << endl<< endl;
    crear(aPartida, "partida.txt"); //Creo el archivo de partidas
    crear(juego, aPartida); //Creo el juego
    /* Si la cant de rondas es <= 0 entonces hay un error en juego */
    if (cantidadRondas(juego) > 0) {
        cout << "Comenzando partida...." << endl;
        comenzar(juego); //Comienzo el juego
        cout << "Partida terminada satisfactoriamente" << endl;
    } else {
        cout << "Error durante la ejecucion del juego" << endl;
    }
        destruir(juego); //Destruyo el juego
        std::cout << "Para ver los resultados dirijase al archivo de salida"<< endl<< endl;

    system("pause");

    return 0;
}
