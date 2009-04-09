#include "estrategia.h"

void crear(Estrategia &estrategia)
{
    Movimientos* movimientos = obtenerMovimientos(estrategia);
    crear(*movimientos);
    Actitudes* actitudes = obtenerActitudes(estrategia);
    crear(*actitudes);
}
void destruir(Estrategia &estrategia)
{
    Movimientos* movaux= obtenerMovimientos(estrategia);
    Actitudes* actaux= obtenerActitudes(estrategia);
    destruir(*movaux);
    destruir(*actaux);
}
void asignarMovimientos(Estrategia &estrategia, Movimientos &movimientosNuevos)
{
    estrategia.movimientos = movimientosNuevos;
}
void asignarActitudes(Estrategia &estrategia, Actitudes &actitudesNuevas)
{
    estrategia.actitudes = actitudesNuevas;
}
Movimientos* obtenerMovimientos(Estrategia &estrategia)
{
    return &estrategia.movimientos;
}
Actitudes* obtenerActitudes(Estrategia &estrategia)
{
    return &estrategia.actitudes;
}


EnumMovimiento calcularMovimiento(Estrategia &estrategia, Perforadora &perforadora, tId_Equipo equipoBot)
{
    Casillero* auxiliarCasillero;
    CargaPerforadora* auxiliarCarga;
    Entorno* entorno;
    Mineral* auxiliarMineral;
    Bot* auxiliarBot;
    Tuberia auxiliarTuberia;
    Movimientos auxiliarMovimientos;
    Actitudes auxiliarActitudes;
    Energia energiaNecesaria;
    Madera maderaNecesaria;
    Hierro hierroNecesario;

    //obtengo el entorno del bot
    entorno = getEntorno(perforadora);
    //obtengo los recursos del bot
    auxiliarCarga = getCarga(perforadora);
    //obtengo una copia de los movimientos y las actitudes
    auxiliarMovimientos = *obtenerMovimientos(estrategia);
    auxiliarActitudes = *obtenerActitudes(estrategia);

    //Aca obtengo los cuatro casilleros para procesar y etcs//
    //<---- obtengo el casillero de arriba del entorno----->
        auxiliarCasillero = getArriba(*entorno);
        //obtengo los puntos necesarios para realizar el movimiento, si no
        //alcanzan directamente no hace nada
        if (auxiliarCasillero != Vacio())
        {
            obtenerPuntosNecesarios(*auxiliarCasillero, equipoBot, energiaNecesaria,maderaNecesaria, hierroNecesario);

            if( getEnergia(*auxiliarCarga) < energiaNecesaria ||
                getMadera(*auxiliarCarga) < maderaNecesaria ||
                getHierro(*auxiliarCarga) < hierroNecesario)
            {

                asignarArriba(auxiliarMovimientos,0);
            }
            else//si no calcula prioridades
            {
                auxiliarMineral = obtenerMineral(*auxiliarCasillero);
                //si tiene mineral, calcula cual es la prioridad de procesarlo
                if ( auxiliarMineral != SinMineral() )
                {
                    //multiplico por la prioridad
                    EnumMinerales tipomineralaux=obtenerTipo(*auxiliarMineral);
                    switch(tipomineralaux)
                    {
                        case oro:   asignarArriba(auxiliarMovimientos,obtenerProcesarOro(auxiliarActitudes)*obtenerArriba(auxiliarMovimientos));
                                    break;
                        case plata: asignarArriba(auxiliarMovimientos,obtenerProcesarPlata(auxiliarActitudes)*obtenerArriba(auxiliarMovimientos));
                                    break;
                        case cobre: asignarArriba(auxiliarMovimientos,obtenerProcesarCobre(auxiliarActitudes)*obtenerArriba(auxiliarMovimientos));
                                    break;
                        case roca: asignarArriba(auxiliarMovimientos,obtenerConstruirConducto(auxiliarActitudes)*obtenerArriba(auxiliarMovimientos));
                                   break;
                    }
                }
                //chequeo si en vez de mineral hay un bot
                else
                {
                    auxiliarBot = obtenerBot(*auxiliarCasillero);
                    if ( auxiliarBot != SinBot())
                    {
                        tId_Equipo Equipoaux = get_Equipo(*auxiliarBot);
                        if( equipoBot != Equipoaux )
                            asignarArriba(auxiliarMovimientos,obtenerDestruirPerforadora(auxiliarActitudes)*obtenerArriba(auxiliarMovimientos));
                        else
                            asignarArriba(auxiliarMovimientos,0);
                    }
                }
            }
        }
        else
            asignarArriba(auxiliarMovimientos,0);
    //<---- obtengo el casillero de Abajo del entorno----->
        auxiliarCasillero = getAbajo(*entorno);
        //obtengo los puntos necesarios para realizar el movimiento, si no
        //alcanzan directamente no hace nada
        if (auxiliarCasillero != Vacio())
        {
            obtenerPuntosNecesarios(*auxiliarCasillero, equipoBot, energiaNecesaria,maderaNecesaria, hierroNecesario);
           if( getEnergia(*auxiliarCarga) < energiaNecesaria ||
                getMadera(*auxiliarCarga) < maderaNecesaria ||
                getHierro(*auxiliarCarga) < hierroNecesario)
            {
                asignarAbajo(auxiliarMovimientos,0);
            }
            else//si no calcula prioridades
            {
                auxiliarMineral = obtenerMineral(*auxiliarCasillero);
                //si tiene mineral, calcula cual es la prioridad de procesarlo
                if ( auxiliarMineral != SinMineral() )
                {
                    //multiplico por la prioridad
                    EnumMinerales tipomineralaux=obtenerTipo(*auxiliarMineral);
                    switch(tipomineralaux)
                    {
                        case oro:   asignarAbajo(auxiliarMovimientos,obtenerProcesarOro(auxiliarActitudes)*obtenerAbajo(auxiliarMovimientos));
                                    break;
                        case plata: asignarAbajo(auxiliarMovimientos,obtenerProcesarPlata(auxiliarActitudes)*obtenerAbajo(auxiliarMovimientos));
                                    break;
                        case cobre: asignarAbajo(auxiliarMovimientos,obtenerProcesarCobre(auxiliarActitudes)*obtenerAbajo(auxiliarMovimientos));
                                    break;
                        case roca: asignarAbajo(auxiliarMovimientos,obtenerConstruirConducto(auxiliarActitudes)*obtenerAbajo(auxiliarMovimientos));
                                   break;
                    }
                }
                //chequeo si en vez de mineral hay un bot
                else
                {
                    auxiliarBot = obtenerBot(*auxiliarCasillero);
                    if ( auxiliarBot != SinBot())
                    {
                        tId_Equipo Equipoaux = get_Equipo(*auxiliarBot);
                        if( equipoBot != Equipoaux )
                            asignarAbajo(auxiliarMovimientos,obtenerDestruirPerforadora(auxiliarActitudes)*obtenerAbajo(auxiliarMovimientos));
                        else
                            asignarAbajo(auxiliarMovimientos,0);
                    }
                }
            }
        }
        else
            asignarAbajo(auxiliarMovimientos,0);
        //<---- obtengo el casillero de la Derecha del entorno----->
        auxiliarCasillero = getDerecha(*entorno);
        if (auxiliarCasillero != Vacio())
        {
            //obtengo los puntos necesarios para realizar el movimiento, si no
            //alcanzan directamente no hace nada

            obtenerPuntosNecesarios(*auxiliarCasillero, equipoBot, energiaNecesaria,maderaNecesaria, hierroNecesario);
           if( getEnergia(*auxiliarCarga) < energiaNecesaria ||
                getMadera(*auxiliarCarga) < maderaNecesaria ||
                getHierro(*auxiliarCarga) < hierroNecesario)
            {
                asignarDerecha(auxiliarMovimientos,0);
            }
            else//si no calcula prioridades
            {
                auxiliarMineral = obtenerMineral(*auxiliarCasillero);
                //si tiene mineral, calcula cual es la prioridad de procesarlo
                if ( auxiliarMineral != SinMineral() )
                {
                    //multiplico por la prioridad
                    EnumMinerales tipomineralaux=obtenerTipo(*auxiliarMineral);
                    switch(tipomineralaux)
                    {
                        case oro:   asignarDerecha(auxiliarMovimientos,obtenerProcesarOro(auxiliarActitudes)*obtenerDerecha(auxiliarMovimientos));
                                    break;
                        case plata: asignarDerecha(auxiliarMovimientos,obtenerProcesarPlata(auxiliarActitudes)*obtenerDerecha(auxiliarMovimientos));
                                    break;
                        case cobre: asignarDerecha(auxiliarMovimientos,obtenerProcesarCobre(auxiliarActitudes)*obtenerDerecha(auxiliarMovimientos));
                                    break;
                        case roca: asignarDerecha(auxiliarMovimientos,obtenerConstruirConducto(auxiliarActitudes)*obtenerDerecha(auxiliarMovimientos));
                                   break;
                    }
                }
                //chequeo si en vez de mineral hay un bot
                else
                {
                    auxiliarBot = obtenerBot(*auxiliarCasillero);
                    if ( auxiliarBot != SinBot())
                    {
                        tId_Equipo Equipoaux = get_Equipo(*auxiliarBot);
                        if( equipoBot != Equipoaux )
                            asignarDerecha(auxiliarMovimientos,obtenerDestruirPerforadora(auxiliarActitudes)*obtenerDerecha(auxiliarMovimientos));
                        else
                            asignarDerecha(auxiliarMovimientos,0);
                    }
                }
            }
        }
        else
            asignarDerecha(auxiliarMovimientos,0);
        //<---- obtengo el casillero de la Izquierda del entorno----->
        auxiliarCasillero = getIzquierda(*entorno);
        if (auxiliarCasillero != Vacio())
        {
            //obtengo los puntos necesarios para realizar el movimiento, si no
            //alcanzan directamente no hace nada
            obtenerPuntosNecesarios(*auxiliarCasillero, equipoBot, energiaNecesaria,maderaNecesaria, hierroNecesario);
            if( getEnergia(*auxiliarCarga) < energiaNecesaria ||
                getMadera(*auxiliarCarga) < maderaNecesaria ||
                getHierro(*auxiliarCarga) < hierroNecesario)
            {
                asignarIzquierda(auxiliarMovimientos,0);
            }
            else//si no calcula prioridades
            {
                auxiliarMineral = obtenerMineral(*auxiliarCasillero);
                //si tiene mineral, calcula cual es la prioridad de procesarlo
                if ( auxiliarMineral != SinMineral() )
                {
                    //multiplico por la prioridad
                    EnumMinerales tipomineralaux=obtenerTipo(*auxiliarMineral);
                    switch(tipomineralaux)
                    {
                        case oro:   asignarIzquierda(auxiliarMovimientos,obtenerProcesarOro(auxiliarActitudes)*obtenerIzquierda(auxiliarMovimientos));
                                    break;
                        case plata: asignarIzquierda(auxiliarMovimientos,obtenerProcesarPlata(auxiliarActitudes)*obtenerIzquierda(auxiliarMovimientos));
                                    break;
                        case cobre: asignarIzquierda(auxiliarMovimientos,obtenerProcesarCobre(auxiliarActitudes)*obtenerIzquierda(auxiliarMovimientos));
                                    break;
                        case roca: asignarIzquierda(auxiliarMovimientos,obtenerConstruirConducto(auxiliarActitudes)*obtenerIzquierda(auxiliarMovimientos));
                                   break;
                    }
                }
                //chequeo si en vez de mineral hay un bot
                else
                {
                    auxiliarBot = obtenerBot(*auxiliarCasillero);
                    if ( auxiliarBot != SinBot())
                    {
                        tId_Equipo Equipoaux = get_Equipo(*auxiliarBot);
                        if( equipoBot != Equipoaux )
                            asignarIzquierda(auxiliarMovimientos,obtenerDestruirPerforadora(auxiliarActitudes)*obtenerIzquierda(auxiliarMovimientos));
                        else
                            asignarIzquierda(auxiliarMovimientos,0);
                    }
                }
            }
        }
        else
            asignarIzquierda(auxiliarMovimientos,0);
        //devuelvo el que tiene mayor puntos

       return (obtenerMayorPrioridad(auxiliarMovimientos));
}
