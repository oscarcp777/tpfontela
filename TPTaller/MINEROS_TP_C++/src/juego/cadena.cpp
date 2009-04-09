


//Funcion interna para procesamiento de la cadena de entrada
//busca lo que esta ente el punto y el igual, ej: partida.rondas=100,
//retorna rondas
#include "cadena.h"


using namespace std;
void crear(Cadena &cadena)
{
    setValor(cadena,"");
}
void destruir(Cadena &cadena)
{
}
void setValor(Cadena &cadena, string parametro)
{
    cadena.valor = parametro;
}
string getValor(const Cadena &cadena)
{
    return cadena.valor;
}
string buscarParametro(Cadena &cadena, char charInicio, char charFin)
{
    int posInicial;
    int posFinal;
    string cadenaAuxiliar;

    cadenaAuxiliar = getValor(cadena);
    if( cadenaAuxiliar != "")
    {
        posInicial = cadenaAuxiliar.find(charInicio) + 1;
        posFinal = cadenaAuxiliar.find(charFin);
        return cadenaAuxiliar.substr(posInicial, posFinal - posInicial);
    }
    else
        return "";
}
//busca lo que hay despues del igual y lo retorna, ej: partida.rondas=100
//devuelve 100
string obtenerValor(Cadena &cadena, char charInicial)
{
    int posInicial;
    string cadenaAuxiliar;

    cadenaAuxiliar = getValor(cadena);

    if( cadenaAuxiliar != "")
    {
        posInicial = cadenaAuxiliar.find(charInicial) + 1;
        return getValor(cadena).substr(posInicial, cantidadCaracteres(cadena));
    }
    else
        return "";
}

int convertirStringAInt(const Cadena &cadena)
{
    int valorRetorno=0;

    istringstream entrada(getValor(cadena));

    if(!entrada.eof())
        entrada>>valorRetorno;
    return valorRetorno;
}
void convertirIntAString(Cadena &cadena, int numero)
{
    stringstream stream;

    stream << numero;
	setValor(cadena, stream.str());
}
int cantidadCaracteres(Cadena &cadena)
{
    return getValor(cadena).length();
}
