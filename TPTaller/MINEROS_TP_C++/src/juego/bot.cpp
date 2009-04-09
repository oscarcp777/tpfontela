/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                               TDA BOT                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/
#include "bot.h"

/*******************************PRIMITIVAS*************************************/

/* Crear */

void crear(Bot &Bot1,tId_Bot ID_bot,tId_Equipo ID_equipo, Equipo* Ptrequipo){
    Bot1.ID_bot = ID_bot; //Coloca el id recibido como parámetro
    Bot1.ID_equipo = ID_equipo; //Coloca el id de equipo recibido como parámetro
    Bot1.ptrequipo = Ptrequipo; //Asigna el puntero a equipo
    crear(Bot1.estrategia); //Crea la estrategia del bot
    Entorno entorno1;
    crear(entorno1, Vacio(), Vacio(), Vacio(), Vacio() );
    crear(Bot1.perforadora, ID_bot, entorno1); //Crea la perforadora del bot
}

/* Destruir */

void destruir(Bot &Bot1){
    Bot1.ID_bot = -1; //Coloca el id como inválido
    destruir(Bot1.estrategia); //Destruye la estrategia asignada
    destruir(Bot1.perforadora); //Destruye la perforadora asignada
}

/* Get Estrategia */
Estrategia* get_Estrategia(Bot &Bot1){
    return &Bot1.estrategia;
}

/* Get ID */

tId_Bot get_ID(const Bot &Bot1){
    return Bot1.ID_bot; //Devuelve el id actual
}

/* Get Equipo */

tId_Equipo get_Equipo(const Bot &Bot1){
    return Bot1.ID_equipo; //Devuelve el equipo actual
}

/* Get PtrEquipo */

Equipo* get_PtrEquipo(const Bot &Bot1){
    return Bot1.ptrequipo; //Devuelve el puntero al equipo
}

/* Get Perforadora */
Perforadora* get_Perforadora(Bot &Bot1){
    return &Bot1.perforadora;
}

/* Realizar Movimiento */

EnumMovimiento realizar_Movimiento(Bot &Bot1){
 Estrategia estrategiaaux = *get_Estrategia(Bot1);
 Perforadora perforadoraaux = *get_Perforadora(Bot1);
 tId_Equipo equipoaux = get_Equipo(Bot1);
 return calcularMovimiento(estrategiaaux, perforadoraaux, equipoaux); //Devuelve la estrategia calculada
}


