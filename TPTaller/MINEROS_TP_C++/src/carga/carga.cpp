#include "carga.h"
#include <iostream>

using namespace std;
int obtenerCantBots(indiceEquipos::Lista &lista)
{
    int acumulador=0;
    indiceEquipos::PtrNodoLista pNodo;
    indiceEquipos::Dato dato;

    pNodo = indiceEquipos::primero(lista);
    while (pNodo != indiceEquipos::fin() )
    {
        indiceEquipos::obtenerDato(lista, dato, pNodo);
        acumulador+=dato.cantBots;
        pNodo = indiceEquipos::siguiente(lista, pNodo);
    }
    return acumulador;
}
int obtenerId( Carga &carga)
{
    indiceEquipos::PtrNodoLista ptrNodo;
    indiceEquipos::Dato dato;

    ptrNodo = indiceEquipos::ultimo(*getIndiceEquipos(carga));
    if(ptrNodo != indiceEquipos::fin())
    {
        indiceEquipos::obtenerDato(*getIndiceEquipos(carga), dato, ptrNodo);
        return  dato.id + 1;
    }
    else
        return 1;

}
int obtenerIdBot( Carga &carga)
{
    indiceBots::PtrNodoLista ptrNodo;
    indiceBots::Dato dato;

    ptrNodo = indiceBots::ultimo(*getIndiceBots(carga));
    if(ptrNodo != indiceBots::fin())
    {
        indiceBots::obtenerDato(*getIndiceBots(carga), dato, ptrNodo);
        return  dato.id + 1;
    }
    else
        return 1;

}
bool existeCaracterPerforadora(Carga &carga,ArchivoRegistros &archivo, char caracter)
{
    indiceEquipos::PtrNodoLista ptrNodo;
    indiceEquipos::Dato dato;
    bool existe = false;
    regEquipos regAux;

    ptrNodo = indiceEquipos::primero(*getIndiceEquipos(carga));
    while(ptrNodo != indiceEquipos::fin() && existe == false)
    {
        indiceEquipos::obtenerDato(*getIndiceEquipos(carga), dato, ptrNodo);
        posicionarse(archivo, dato.prr);
        leer(archivo,(void*)&regAux);
        ptrNodo = indiceEquipos::siguiente(*getIndiceEquipos(carga), ptrNodo);
        if (regAux.caracterPerforadora == caracter)
            existe = true;
    }
    return existe;
}
bool existeCaracterTuberia(Carga &carga,ArchivoRegistros &archivo, char caracter)
{
    indiceEquipos::PtrNodoLista ptrNodo;
    indiceEquipos::Dato dato;
    bool existe = false;
    regEquipos regAux;

    ptrNodo = indiceEquipos::primero(*getIndiceEquipos(carga));
    while(ptrNodo != indiceEquipos::fin() && existe == false)
    {
        indiceEquipos::obtenerDato(*getIndiceEquipos(carga), dato, ptrNodo);
        posicionarse(archivo, dato.prr);
        leer(archivo,(void*)&regAux);
        ptrNodo = indiceEquipos::siguiente(*getIndiceEquipos(carga), ptrNodo);
        if (regAux.caracterSeccionCamino == caracter)
            existe = true;
    }
    return existe;

}
bool existeEquipo(Carga &carga, int idEquipo)
{
    indiceEquipos::PtrNodoLista ptrNodo;
    indiceEquipos::Dato dato;
    bool existe = false;

    ptrNodo = indiceEquipos::primero(*getIndiceEquipos(carga));
    while(ptrNodo != indiceEquipos::fin() && existe == false)
    {
        indiceEquipos::obtenerDato(*getIndiceEquipos(carga), dato, ptrNodo);
        if (dato.id == idEquipo)
            existe=true;
        ptrNodo = indiceEquipos::siguiente(*getIndiceEquipos(carga), ptrNodo);
    }
    return existe;
}

void crear(Carga &carga)
{
    setRutaTablero(carga,"tablero.txt");
    setRutaEquipos(carga,"equipos.dat");
    setRutaBots(carga,"bots.dat");
    setRutaResultados(carga,"resultado.xml");
    setCantRondas(carga, 50);
    indiceEquipos::crearLista(*getIndiceEquipos(carga));
    indiceBots::crearLista(*getIndiceBots(carga));

}
void destruir(Carga &carga)
{
    ArchivoTexto archivo;
    Cadena cadena;

    crear(cadena);
    convertirIntAString(cadena, getCantRondas(carga));
    crear(archivo, "partida.txt");
    escribirCadena(archivo, "partida.rondas="+getValor(cadena));
    bajarDeLinea(archivo);
    escribirCadena(archivo, "partida.tablero="+getRutaTablero(carga));
    bajarDeLinea(archivo);
    escribirCadena(archivo, "partida.equipos="+getRutaEquipos(carga));
    bajarDeLinea(archivo);
    escribirCadena(archivo, "partida.bots="+getRutaBots(carga));
    bajarDeLinea(archivo);
    escribirCadena(archivo, "partida.resultado="+getRutaResultados(carga));
    bajarDeLinea(archivo);
    destruir(archivo);
    indiceEquipos::eliminarLista(*getIndiceEquipos(carga));
    indiceBots::eliminarLista(*getIndiceBots(carga));
}

bool generarArchivoTablero(Carga &carga, int cantFilas, int cantColumnas)
{
    bool creado = false;
    int cantBots;
    char charAuxiliar;

    //me fijo que las filas y columnas sean numeros validos
    if ((cantColumnas>0) && (cantFilas-1 > 0))
    {
        cantBots = obtenerCantBots(*getIndiceEquipos(carga));
        //me fijo que la cantidad de bots ingresados sea menor que las
        //columnas
        if (cantBots < cantColumnas)
        {
            Dado dado;
            int numero;

            ArchivoTexto archivo;

            creado = true;
            crear(dado, 12);
            crear(archivo,getRutaTablero(carga));
            for(int indiceFilas = 1; indiceFilas < cantFilas; indiceFilas++)
            {
                for(int indiceColumnas = 0; indiceColumnas < cantColumnas; indiceColumnas++)
                {
                    //elijo un numero al azar
                    numero = tirar(dado);
                    //si es mayor a nueve, convierto a caracter especial
                    if (numero >9)
                    {
                        switch (numero)
                        {
                            case 10: charAuxiliar = 'z';
                                     break;
                            case 11: charAuxiliar = 'y';
                                     break;
                            case 12: charAuxiliar = 'x';
                                     break;
                        }
                    }
                    else
                        charAuxiliar=(char)numero+48;

                        //escribo el caracter en el archivo

                    escribirCaracter(archivo,charAuxiliar);
                }
                if (indiceFilas < cantFilas-1)
                    bajarDeLinea(archivo);
            }
            creado = true;
            destruir(dado);
            destruir(archivo);
        }
    }
    return creado;
}
bool mayorACero(int valor)
{
    if (valor > 0)
        return true;
    else
        return false;
}
int pedirIntMayorACero(string mensaje)
{
    int valor;
    do
    {
        cout<<mensaje;
        cin>> valor;
    }while(!mayorACero(valor));
    return valor;
}
long int cargarIndiceEquipos(indiceEquipos::Lista &lista, ArchivoRegistros &archivo)
{
    indiceEquipos::Dato dato;
    long int contador = 0;

    regEquipos registroEquipos;
    posicionarse(archivo,0);
    while (!fin(archivo))
    {
        leer(archivo, (void*)&registroEquipos);
        dato.cantBots = 0;
        dato.id = registroEquipos.id;
        dato.nombre = registroEquipos.nombre;
        dato.prr = contador;
        indiceEquipos::insertarDato(lista, dato);
        contador++;
    }
    return contador;
}
long int cargarIndiceBots(Carga &carga, ArchivoRegistros &archivo)
{
    indiceBots::Dato dato;
    indiceEquipos::Dato datoEquipos;
    indiceEquipos::PtrNodoLista ptrNodoEquipos;
    long int contador = 0;

    regBots registroBots;
    posicionarse(archivo,0);
    while (!fin(archivo))
    {
        leer(archivo, (void*)&registroBots);
        dato.id = registroBots.idBot;
        dato.prr = contador;
        contador++;
        indiceBots::insertarDato(*getIndiceBots(carga), dato);
        //busco el equipo e incremento en 1 su cant de bots
        datoEquipos.id = registroBots.idEquipo;
        ptrNodoEquipos = indiceEquipos::localizarDato(*getIndiceEquipos(carga) ,datoEquipos);
        indiceEquipos::obtenerDato(*getIndiceEquipos(carga) ,datoEquipos, ptrNodoEquipos);
        datoEquipos.cantBots++;
        indiceEquipos::colocarDato(*getIndiceEquipos(carga),datoEquipos, ptrNodoEquipos);
    }
    return contador;
}
bool generarArchivoBots(Carga &carga)
{
    bool creado = false;
    long int pos;
    bool salida = true;
    regBots registro;
    indiceBots::PtrNodoLista ptrNodo;
    indiceBots::Dato dato;
    indiceEquipos::PtrNodoLista ptrNodoEquipos;
    indiceEquipos::Dato datoEquipos;
    ArchivoRegistros archivo;

    crear(archivo,getRutaBots(carga),sizeof(registro));
    //si no esta cargado el indice de equipos lo cargo

    if(indiceEquipos::listaVacia(*getIndiceEquipos(carga)))
    {
        ArchivoRegistros archivoEquipos;
        regEquipos registroEquipos;
        crear(archivoEquipos,getRutaEquipos(carga),sizeof(registroEquipos));

        cargarIndiceEquipos(*getIndiceEquipos(carga), archivoEquipos);
    }

    pos = cargarIndiceBots(carga, archivo);
    do
    {
        cout<<"Los equipos posibles son: "<<endl;
        ptrNodoEquipos = indiceEquipos::primero(*getIndiceEquipos(carga));
        while( ptrNodoEquipos != indiceEquipos::fin())
        {

            indiceEquipos::obtenerDato(*getIndiceEquipos(carga),datoEquipos, ptrNodoEquipos);
            cout <<datoEquipos.id<<")" <<datoEquipos.nombre << " - ";
            ptrNodoEquipos = indiceEquipos::siguiente(*getIndiceEquipos(carga), ptrNodoEquipos);
        }
        cout<<endl;
        do
        {
            cout<<"Ingrese el numero del equipo: ";
            cin>>registro.idEquipo;
        }while(!mayorACero(registro.idEquipo) || (!existeEquipo(carga, registro.idEquipo)));

        registro.idBot = obtenerIdBot(carga);
        int valor;
        valor = pedirIntMayorACero("Ingrese la prioridad para moverse arriba (mayor a 0): ");
        registro.arriba = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para moverse abajo (mayor a 0): ");
        registro.abajo = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para moverse derecha (mayor a 0): ");
        registro.derecha = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para moverse izquierda (mayor a 0): ");
        registro.izquierda = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para no moverse (mayor a 0): ");
        registro.esperar = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para procesar oro (mayor a 0): ");
        registro.procesarOro = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para procesar plata (mayor a 0): ");
        registro.procesarPlata = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para procesar cobre (mayor a 0): ");
        registro.procesarCobre = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para construir conducto (mayor a 0): ");
        registro.construirConducto = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para destruir conducto (mayor a 0): ");
        registro.destruirConducto = char(valor);
        valor = pedirIntMayorACero("Ingrese la prioridad para destruir una perforadora (mayor a 0): ");
        registro.destruirPerforadora = char(valor);
        posicionarse(archivo, pos);
        escribir(archivo, (void*)&registro);
        dato.id = registro.idBot;
        dato.prr = pos;
        pos++;
        indiceBots::insertarDato(*getIndiceBots(carga), dato);
        string strAuxiliar;
        char caracter;
        do
        {
            cout<<"Desea ingresar otro bot? (S/N): ";
            cin>>strAuxiliar;
            caracter = strAuxiliar[0];
            if ((caracter != 'S') && (caracter != 's') && (caracter != 'N') && (caracter != 'n'))
                cout<<"Opcion invalida";
        }while((caracter != 'S') && (caracter != 's') && (caracter != 'N') && (caracter != 'n'));
        if ( (caracter == 'N') || (caracter == 'n'))
            salida =false;

        cout<<endl;
    }while(salida == true);
    return true;
}


bool generarArchivoEquipos(Carga &carga)
{
    bool creado = false;
    bool salida = true;
    indiceEquipos::Lista *lista;
    indiceEquipos::Dato dato;
    regEquipos registro;
    ArchivoRegistros archivo;
    string strAuxiliar;
    long int pos;

    crear(archivo,getRutaEquipos(carga),sizeof(registro));
    lista = getIndiceEquipos(carga);
    pos = cargarIndiceEquipos(*lista, archivo);
    //system("clear");

        //busco en el indice el ultimo codigo, asi asigno el otro auto-
        //maticamente. Si la lista esta vacia le asigno 1
    do
    {
        cout<<"Ingrese el nombre del equipo por favor: ";
        cin>>registro.nombre;
        registro.id = obtenerId(carga);
        //agrego el caracter perforadora
        bool existe;
        do
        {
            cout<<"Ingrese el caracter de perforadora: ";
            cin >> strAuxiliar;
            registro.caracterPerforadora = strAuxiliar[0];
            existe = existeCaracterPerforadora(carga, archivo, registro.caracterPerforadora);
            if (existe)
                cout<<"El caracter '"<<registro.caracterPerforadora<<"' ya existe, elija otro"<<endl;
        }while(existe);
        do
        {
            cout<<"Ingrese el caracter de sección de camino: ";
            cin >> strAuxiliar;
            registro.caracterSeccionCamino = strAuxiliar[0];
            existe = existeCaracterTuberia(carga, archivo, registro.caracterSeccionCamino);
            if (existe)
                cout<<"El caracter '"<<registro.caracterSeccionCamino<<"' ya existe, elija otro"<<endl;
        }while(existe);
        posicionarse(archivo, pos);
        escribir(archivo, (void*)&registro);
        creado = true;

        dato.id = registro.id;
        dato.cantBots = 0;
        dato.nombre = registro.nombre;
        dato.prr = pos;
        pos++;
        indiceEquipos::insertarDato(*lista, dato);
        char caracter;
        do
        {
            cout<<"Desea ingresar otro equipo? (S/N): ";
            cin>>strAuxiliar;
            caracter = strAuxiliar[0];
            if ((caracter != 'S') && (caracter != 's') && (caracter != 'N') && (caracter != 'n'))
                cout<<"Opcion invalida";
        }while((caracter != 'S') && (caracter != 's') && (caracter != 'N') && (caracter != 'n'));
        if ( (caracter == 'N') || (caracter == 'n'))
            salida =false;

        cout<<endl;
    }while(salida == true);
    destruir(archivo);
    return creado;
}

tCantRondas getCantRondas(Carga &carga)
{
    return carga.cantRondas;
}
void setCantRondas(Carga &carga, tCantRondas cantidad)
{
    if (cantidad >0)
    {
        carga.cantRondas = cantidad;
    }
}
string getRutaTablero(Carga &carga)
{
    return carga.rutaTablero;
}

void setRutaTablero(Carga &carga, string cadena)
{
    carga.rutaTablero = cadena;
}
string getRutaEquipos(Carga &carga)
{
    return carga.rutaEquipos;
}
void setRutaEquipos(Carga &carga, string cadena)
{
    carga.rutaEquipos = cadena;
}
string getRutaResultados(Carga &carga)
{
    return carga.rutaResultado;
}
void setRutaResultados(Carga &carga, string cadena)
{
    carga.rutaResultado =cadena;
}
indiceEquipos::Lista* getIndiceEquipos(Carga &carga)
{
    return &(carga.equipos);
}
indiceBots::Lista* getIndiceBots(Carga &carga)
{
    return &(carga.bots);
}
string getRutaBots(Carga &carga)
{
    return carga.rutaBots;
}
void setRutaBots(Carga &carga, string cadena)
{
    carga.rutaBots = cadena;
}

