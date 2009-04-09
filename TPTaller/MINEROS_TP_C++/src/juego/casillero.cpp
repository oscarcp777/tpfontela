#include "Casillero.h"
#include <iostream>


void crear(Casillero &casillero, int id)
{
    casillero.IdCasillero = id;
    casillero.mineral = SinMineral();
    asignarBot(casillero, SinBot());
    casillero.datoVertice = SinTuberia();
}
void destruir(Casillero &casillero)
{
    quitarBot(casillero);
    quitarMineral(casillero);
    delete (casillero.datoVertice);
}
void asignarBot(Casillero &casillero, Bot* bot)
{
    //si no hay mineral lo agrega
    if( obtenerMineral(casillero) == SinMineral() )
        casillero.bot = bot;
}

Bot* obtenerBot(const Casillero &casillero)
{
    return casillero.bot;
}
void quitarBot(Casillero &casillero)
{
    asignarBot(casillero, SinBot());
}

void asignarMineral(Casillero &casillero, Mineral mineral)
{

    //si no hay bot
    if(obtenerBot(casillero) == SinBot() )
    {
        //si no tiene mineral, reservo un lugar de memoria para el mineral
        //y si tenia uno, lo quito
        if (casillero.mineral == SinMineral())
            casillero.mineral = new Mineral;
        else
            quitarMineral(casillero);
        //asigno el nuevo mineral
        *(casillero.mineral) = mineral;
    }
}
Mineral* obtenerMineral(Casillero &casillero)
{
    return casillero.mineral;
}
void quitarMineral(Casillero &casillero)
{
    if (casillero.mineral != SinMineral())
        delete(casillero.mineral);
    casillero.mineral = SinMineral();
}
void asignarTuberia(Casillero &casillero, DatoVertice* dato)
{
    casillero.datoVertice = dato;
}

DatoVertice* obtenerPunteroTuberia(Casillero &casillero)
{
    return casillero.datoVertice;
}

Tuberia obtenerTuberia(Casillero &casillero)
{
    DatoVertice* datoAuxiliar;

    datoAuxiliar = obtenerPunteroTuberia(casillero);
    if (datoAuxiliar != NULL)
        return datoAuxiliar->tuberia;
    else
        return -1;
}

Bot* SinBot(){
    return NULL;
}

DatoVertice* SinTuberia(){
    return NULL;
}

Mineral* SinMineral(){
    return NULL;
}
void obtenerPuntosNecesarios(Casillero& casillero, tId_Equipo equipoBot, Energia &energia, Madera &madera, Hierro &hierro)
{
    energia = 0;
    madera = 0;
    hierro = 0;

    //sumo puntos necesarios por construir un conducto y destruir el enemigo de
    //ser necesario
    if(obtenerTuberia(casillero) == -1)
    {
        madera += MADERA_CONDUCTO;
        hierro += HIERRO_CONDUCTO;
        energia++;
    } else  {
        if(obtenerTuberia(casillero) != equipoBot)
        {
            energia+= DESTRUIR_TUBERIA;
            madera += MADERA_CONDUCTO;
            hierro += HIERRO_CONDUCTO;
        }
    }
    //suma los puntos por ser un mineral
    if(obtenerMineral(casillero) != SinMineral() )
        energia+= obtenerPuntos(*obtenerMineral(casillero));
    //suma los puntos por destruir otra perforadora
    if(obtenerBot(casillero) != SinBot())
        if(get_Equipo(*obtenerBot(casillero)) != equipoBot)
        {    energia+=DESTRUIR_BOT;
        }
}
int obtenerId(Casillero &casillero)
{
    return casillero.IdCasillero;
}
