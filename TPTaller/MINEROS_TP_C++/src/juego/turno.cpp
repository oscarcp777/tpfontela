/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA TURNO                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/

#include "turno.h"

/*******************************PRIMITIVAS*************************************/

/* Funciones adicionales */

//Funcion que se encarga de hacer un cierto numero de tabulados en el archivo
void Tabulararchivo (ArchivoTexto &arch1, char canttab){
    for (char contador = 0; contador <=canttab; contador++)
            tabular(arch1);
}

//Funcion que transforma de enummovimiento a string
std::string MovaString(EnumMovimiento movimiento){
    switch (movimiento) {
        case arriba: return "arriba";
        case abajo: return "abajo";
        case izquierda: return "izquierda";
        case derecha: return "derecha";
        case nada: return "espera";
    }
}

//Función que se encarga de devolver un casillero del entorno segun el movimiento
Casillero* obtenercasillerocorresp(Bot &bot, EnumMovimiento movimiento){
    Entorno* Pentorno;
    Perforadora* Pperf;

    Pperf = get_Perforadora(bot);
    Pentorno = getEntorno(*Pperf);
    switch (movimiento) {
        case arriba: return getArriba(*Pentorno);
        case abajo: return getAbajo(*Pentorno);
        case izquierda: return getIzquierda(*Pentorno);
        case derecha: return getDerecha(*Pentorno);
        case nada: return Vacio();
    }

}

/* Turno Crear */

void crear(turno &turno1, int nro, Bot &botaasignar){
    turno1.nro = nro;
    turno1.botasignado = &botaasignar;
}

/* Turno destruir */

void destruir(turno &turno1){
    turno1.nro = -1;
    turno1.botasignado = SinBot();
}

/* Set Bot */

void setBot(turno &turno1, Bot &botaasignar){
    turno1.botasignado = &botaasignar;
}

/* Get Bot */

Bot* getBot(const turno &turno1){
    return turno1.botasignado;
}

/* Get Nro */

int getNro(const turno &turno1)
{
    return turno1.nro;
}

/* Jugar */

void jugar(turno &turno1, Tablero &tablero1, ArchivoTexto &archsalida,
                ListaDeBots::Lista &listabots){

    //Declaro variables
    EnumMovimiento movimiento;
    Bot* Pbot;
    Bot* Pbot2;
    Perforadora* Pperf1;
    Perforadora* Pperf2;
    CargaPerforadora* Pcar1;
    BodegaPuntos Puntos1, Puntos2;
    Casillero* Pcas;
    Mineral* Pmineral;
    EnumMinerales tipo;
    Hierro hieraux;
    Energia energaux;
    Madera madaux;

    Pbot = getBot(turno1); //Obtengo el bot asignado al turno
    ActualizarEntorno(tablero1,*Pbot);
    movimiento = realizar_Movimiento(*Pbot); /* Le pido al bot que me de
    el movimiento que quiere realizar */
    ActualizarEntorno(tablero1,*Pbot);

    Pcas = obtenercasillerocorresp(*Pbot, movimiento); /* Devuelvo el casillero
    al que se va a mover el bot */;
    /* Si el casillero no es nulo y el bot se mueve */
    int ContFilas, ContColum;
    Casillero* cA;
    buscarCasillero(tablero1,*Pbot, ContFilas, ContColum);
    cA = getDato(tablero1.Matriz, ContFilas,ContColum);

    if (Pcas != Vacio()){
        /* Obtengo los recursos necesarios para moverse a ese casillero */
        obtenerPuntosNecesarios(*Pcas, get_Equipo(*Pbot), energaux, madaux, hieraux);
        Pperf1=get_Perforadora(*Pbot); /* Obtengo la perforadora del bot */
        Pcar1 = getCarga(*Pperf1); /* Obtengo la carga de la perf */
        Puntos1=getBodegaPuntos(*Pperf1); /* Obtengo los puntos de la perf */
        /* Si el casillero tiene un bot */

        if (obtenerBot(*Pcas) != SinBot()){
            Pbot2= obtenerBot(*Pcas); /* Obtengo ese bot */
            Pperf2=get_Perforadora(*Pbot2); /* Obtengo su perforadora */
            Puntos2=getBodegaPuntos(*Pperf2); /* Obtengo su puntaje */

            /* Si es enemigo */
           if (get_Equipo(*Pbot)!=get_Equipo(*Pbot2)){
                /* Le doy los puntos de la perforadora a destruir, a la perf que
                    se esta moviendo */
                setBodegaPuntos(*Pperf1, Puntos1 + Puntos2);
                /* Elimino el bot a destruir de la lista de actuales */
                ListaDeBots::eliminarDato(listabots, Pbot2);
            } //Si es aliado no hace nada
        }
        Puntos1=getBodegaPuntos(*Pperf1); /* Obtengo los puntos de la perf */
        /* Si el casillero tiene un mineral */
        if (obtenerMineral(*Pcas) != SinMineral()) {
            Pmineral = obtenerMineral(*Pcas); //Lo obtengo
            tipo = obtenerTipo(*Pmineral); //Obtengo el tipo del mineral

            /* Segun el tipo, asigno los puntos de recompensa */
            switch(tipo)
            {
                case oro:   setBodegaPuntos(*Pperf1, Puntos1 + RECOMPENSAORO);
                            break;
                case plata: setBodegaPuntos(*Pperf1, Puntos1 + RECOMPENSAPLATA);
                            break;
                case cobre: setBodegaPuntos(*Pperf1, Puntos1 + RECOMPENSACOBRE);
                            break;
            }
        }
        /* Actualizo los recursos */

        setEnergia(*Pcar1, getEnergia(*Pcar1) - energaux);
        setMadera(*Pcar1, getMadera(*Pcar1) - madaux);
        setHierro(*Pcar1, getHierro(*Pcar1) - hieraux);
    } /* Si el casillero esta vacio o el bot espera, no hace nada */
    moverBot(tablero1, Pbot, movimiento); //Le digo al tablero que mueva al bot
    registrar(turno1, movimiento, archsalida); //Registro los datos
}

/* Registrar */

void registrar(turno &turno1, EnumMovimiento movimiento, ArchivoTexto &archsalida){
    //Declaro variables necesarias
    std::string buffer, strmov;
    Cadena snroturno, sIdBot;
    int nroturno;
    tId_Bot IdBot;
    Bot* pbot;

    //Creo cadenas necesarias
    crear(snroturno);
    crear(sIdBot);
    strmov = MovaString(movimiento); //Convierto el movimiento a un string
    //Acomodo el cursor en el archivo
    //irAlFinal(archsalida);
    bajarDeLinea(archsalida);
    Tabulararchivo(archsalida, 4);
    nroturno = getNro(turno1); //Obtengo el numero del turno actual
    convertirIntAString(snroturno, nroturno); //Lo convierto a string
    //Lleno el buffer con los datos
    buffer = "<turno numero=\"" + getValor(snroturno) + "\">";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    Tabulararchivo(archsalida, 5);
    pbot = getBot(turno1); //Obtengo el bot asignado al turno
    IdBot = get_ID(*pbot); //Obtengo su id
    convertirIntAString(sIdBot, IdBot); //Lo convierto a string
    //Lleno el buffer con los datos
    buffer = "<IDbot> " + getValor(sIdBot) + " </IDbot>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    Tabulararchivo(archsalida, 5);
    //Lleno el buffer con los datos
    buffer = "<Movimiento> " + strmov + " </Movimiento>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    Tabulararchivo(archsalida, 4);
    //Lleno el buffer con los datos
    buffer = "</turno>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Destruyo cadenas
    destruir(snroturno);
    destruir(sIdBot);
}

