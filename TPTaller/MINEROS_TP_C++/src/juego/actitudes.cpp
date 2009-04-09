#include "Actitudes.h"

void crear(Actitudes &actitudes)
{
    asignarProcesarOro(actitudes, 0);
    asignarProcesarCobre(actitudes, 0);
    asignarProcesarPlata(actitudes, 0);
    asignarConstruirConducto(actitudes, 0);
    asignarDestruirConducto(actitudes, 0);
    asignarDestruirPerforadora(actitudes, 0);
}
void destruir(Actitudes &actitudes)
{
    asignarProcesarOro(actitudes, -1);
    asignarProcesarCobre(actitudes, -1);
    asignarProcesarPlata(actitudes, -1);
    asignarConstruirConducto(actitudes, -1);
    asignarDestruirConducto(actitudes, -1);
    asignarDestruirPerforadora(actitudes, -1);
}
void asignarProcesarOro(Actitudes &actitudes, prioridadActitud valor)
{
    actitudes.procesarOro = valor;
}
prioridadActitud obtenerProcesarOro(const Actitudes &actitudes)
{
        return actitudes.procesarOro;
}
void asignarProcesarPlata(Actitudes &actitudes, prioridadActitud valor)
{
    actitudes.procesarPlata = valor;
}
prioridadActitud obtenerProcesarPlata(const Actitudes &actitudes)
{
        return actitudes.procesarPlata;
}
void asignarProcesarCobre(Actitudes &actitudes, prioridadActitud valor)
{
    actitudes.procesarCobre = valor;
}
prioridadActitud obtenerProcesarCobre(const Actitudes &actitudes)
{
        return actitudes.procesarCobre;
}
void asignarConstruirConducto(Actitudes &actitudes, prioridadActitud valor)
{
    actitudes.construirConducto = valor;
}
prioridadActitud obtenerConstruirConducto(const Actitudes &actitudes)
{
        return actitudes.construirConducto;
}
void asignarDestruirConducto(Actitudes &actitudes, prioridadActitud valor)
{
    actitudes.destruirConducto = valor;
}
prioridadActitud obtenerDestruirConducto(const Actitudes &actitudes)
{
        return actitudes.destruirConducto;
}
void asignarDestruirPerforadora(Actitudes &actitudes, prioridadActitud valor)
{
    actitudes.destruirPerforadora = valor;
}
prioridadActitud obtenerDestruirPerforadora(const Actitudes &actitudes)
{
        return actitudes.destruirPerforadora;
}

