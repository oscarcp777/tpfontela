#include "minerales.h"

void crear(Mineral &mineral, EnumMinerales contenido, Puntos valor)
{
    asignarMineral(mineral, contenido, valor);
}
void destruir(Mineral &mineral)
{
    //En este caso, la primitiva no realiza accion alguna.
}
void crear(Mineral &mineral, EnumMinerales contenido)
{
    asignarMineral(mineral, contenido);
}
EnumMinerales obtenerTipo(const Mineral &mineral)
{
    return mineral.tipo;
}
Puntos obtenerPuntos(const Mineral &mineral)
{
    return mineral.puntos;
}

void asignarMineral(Mineral &mineral, EnumMinerales contenido, Puntos valor)
{
        //chequeo por las dudas que mande un valor de puntos valido, si no no
        //hace nada
        if ((valor >=1) && (valor<=9))
        {
            mineral.tipo = contenido;
            if (contenido != roca)
            {
                switch(contenido)
                {
                    case oro: mineral.puntos = DUREZAORO;
                              break;
                    case plata: mineral.puntos = DUREZAPLATA;
                                break;
                    case cobre: mineral.puntos = DUREZACOBRE;
                                break;
               }
            }
            else
                mineral.puntos = valor;
        }
}
void asignarMineral(Mineral &mineral, EnumMinerales contenido)
{
    asignarMineral(mineral, contenido, 1);
}

