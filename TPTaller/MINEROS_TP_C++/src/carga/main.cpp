#include "carga.h"
#include <iostream>

using namespace std;
int main()
{
    char caracter;
    bool seGenero;
    Carga carga;

    crear(carga);

    do
    {
        cout<< "Desea generar un tablero? (S/N)";
        cin >>caracter;
    }while((caracter != 'S') && (caracter != 's') && (caracter != 'N') && (caracter != 'n'));
    if ((caracter == 'S') || (caracter == 's'))
    {
        int filas;
        int columnas;
        cin.ignore();
        do
        {
            cout<<"Ingrese la cantidad de filas (mayor a 0): ";
            cin >>filas;
        }while(filas <= 0);
        do
        {
            cout<<"Ingrese la cantidad de columnas (mayor a la cantidad de bots): ";
            cin >>columnas;
        }while(columnas <= 0);
        seGenero = generarArchivoTablero(carga,filas,columnas);
        cout<<endl;
        if (seGenero)
            cout << "Se genero satisfactoriamente el tablero"<<endl;
        else
            cout << "Hubo problemas al generar el tablero"<<endl;
    }
    do
    {
        cout<< "Desea cargar los equipos? (S/N)";
        cin >>caracter;
    }while((caracter != 'S') && (caracter != 's') && (caracter != 'N') && (caracter != 'n'));
    if ((caracter == 'S') || (caracter == 's'))
    {
        seGenero = generarArchivoEquipos(carga);
        if (seGenero)
            cout << "Se generaron satisfactoriamente los equipos"<<endl;
        else
            cout << "Hubo problemas al generar los equipos"<<endl;
    }
    do
    {
        cout<< "Desea cargar los bots? (S/N)";
        cin >>caracter;
    }while((caracter != 'S') && (caracter != 's') && (caracter != 'N') && (caracter != 'n'));
    if ((caracter == 'S') || (caracter == 's'))
    {
        seGenero =     generarArchivoBots(carga);
        if (seGenero)
            cout << "Se generaron satisfactoriamente los bots"<<endl;
        else
            cout << "Hubo problemas al generar los bots"<<endl;
    }
    system("pause");
    destruir(carga);

    return 0;
}