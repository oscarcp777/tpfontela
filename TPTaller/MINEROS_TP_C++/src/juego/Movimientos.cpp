#include "movimientos.h"

void crear(Movimientos &movimientos)
{
    asignarArriba(movimientos,0);
    asignarAbajo(movimientos,0);
    asignarDerecha(movimientos,0);
    asignarIzquierda(movimientos,0);
    asignarNada(movimientos,1);
}

void destruir(Movimientos &movimientos)
{
    asignarArriba(movimientos,-1);
    asignarAbajo(movimientos,-1);
    asignarDerecha(movimientos,-1);
    asignarIzquierda(movimientos,-1);
    asignarNada(movimientos,1);
}
prioridadMovimiento obtenerArriba(const Movimientos &movimientos)
{
    return movimientos.arriba;
}
void asignarArriba(Movimientos &movimientos, prioridadMovimiento valor)
{
    movimientos.arriba = valor;
}
prioridadMovimiento obtenerAbajo(const Movimientos &movimientos)
{
    return movimientos.abajo;
}
void asignarAbajo( Movimientos &movimientos, prioridadMovimiento valor)
{
    movimientos.abajo = valor;
}
prioridadMovimiento obtenerDerecha(const Movimientos &movimientos)
{
    return movimientos.derecha;
}
void asignarDerecha(Movimientos &movimientos, prioridadMovimiento valor)
{
    movimientos.derecha = valor;
}
prioridadMovimiento obtenerIzquierda(const Movimientos &movimientos)
{
    return movimientos.izquierda;
}

void asignarIzquierda(Movimientos &movimientos, prioridadMovimiento valor)
{
    movimientos.izquierda = valor;
}
prioridadMovimiento obtenerNada(const Movimientos &movimientos)
{
    return movimientos.nada;
}
void asignarNada(Movimientos &movimientos, prioridadMovimiento valor)
{
    if(valor <1)
        movimientos.nada = 1;
    else
        movimientos.nada = valor;
}
EnumMovimiento obtenerMayorPrioridad(const Movimientos &movimientos)
{
    prioridadMovimiento mayorValor;
    EnumMovimiento mayor;
    Dado dado;//lo uso para sortear cual de los dos movimientos con igual valor se hacen

    mayorValor = obtenerNada(movimientos);
    mayor = nada;
    crear(dado,2);
    if( obtenerArriba(movimientos) >= mayorValor )
    {
        //si es mayor lo asigno directamente
        if(obtenerArriba(movimientos) > mayorValor)
        {
            mayor = arriba;
            mayorValor = obtenerArriba(movimientos);
        }
        else
        {
            //si no sorteo, si sale 1 le asigno el nuevo, si no mantengo el viejo
            if(tirar(dado) == 1)
            {
                    mayor = arriba;
                    mayorValor = obtenerArriba(movimientos);
            }
        }
    }
    if( obtenerAbajo(movimientos) >= mayorValor )
    {
        //si es mayor lo asigno directamente
        if(obtenerAbajo(movimientos) > mayorValor)
        {
            mayor = abajo;
            mayorValor = obtenerAbajo(movimientos);
        }
        else
        {
            //si no sorteo, si sale 1 le asigno el nuevo, si no mantengo el viejo
            if(tirar(dado) == 1)
            {
                    mayor = abajo;
                    mayorValor = obtenerAbajo(movimientos);
            }
        }
    }
    if( obtenerDerecha(movimientos) >= mayorValor )
    {
        //si es mayor lo asigno directamente
        if(obtenerDerecha(movimientos) > mayorValor)
        {
            mayor = derecha;
            mayorValor = obtenerDerecha(movimientos);
        }
        else
        {
            //si no sorteo, si sale 1 le asigno el nuevo, si no mantengo el viejo
            if(tirar(dado) == 1)
            {
                    mayor = derecha;
                    mayorValor = obtenerDerecha(movimientos);
            }
        }
    }
    if( obtenerIzquierda(movimientos) >= mayorValor )
    {
        //si es mayor lo asigno directamente
        if(obtenerIzquierda(movimientos) > mayorValor)
        {
            mayor = izquierda;
            mayorValor = obtenerIzquierda(movimientos);
        }
        else
        {
            //si no sorteo, si sale 1 le asigno el nuevo, si no mantengo el viejo
            if(tirar(dado) == 1)
            {
                    mayor = izquierda;
                    mayorValor = obtenerIzquierda(movimientos);
            }
        }
    }
    return mayor;
}

