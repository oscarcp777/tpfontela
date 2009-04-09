/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA RONDA                                      *
 ******************************************************************************/

/********************************HEADERS***************************************/

#include "ronda.h"

/*******************************PRIMITIVAS*************************************/

//Funcion que se encarga de hacer un cierto numero de tabulados en el archivo
void tabulararchivo (ArchivoTexto &arch1, char canttab){
    for (char contador = 0; contador <=canttab; contador++)
            tabular(arch1);
}

/*Aca definimos las funciones del grafo*/
void desmarcar  (Vertice* Vertice) {
	// Casteo para Simplificar operatoria posterior
	DatoVertice* infoVertice = static_cast<DatoVertice*> ( Vertice!=NULL?getInfo( Vertice ):NULL );

	// Desmarcar es setear en false marcado
	if (infoVertice != NULL) infoVertice->marcado = false;
}
//esta funcion debe recibir un vertice con info, de lo contrario devuelve
//false por defecto

bool debeMarcarse (Vertice* Vertice ) {
	// Casteos para Simplificar operatoria posterior

	DatoVertice* infoVertice = static_cast<DatoVertice*> ( Vertice!=NULL?getInfo ( Vertice ):NULL );

	//si marcado es igual a false devuelve true
	if (infoVertice != NULL)
        if (!infoVertice->marcado)
            return true;

    return false;//devuelve esto por defecto si no hay info en el vertice
}

void marcar (Vertice* Vertice ) {
	// Casteos para Simplificar operatoria posterior
	DatoVertice* infoVertice = static_cast<DatoVertice*> ( Vertice!=NULL?getInfo ( Vertice ):NULL );

	//si marcado es igual a false devuelve true
	if (infoVertice != NULL)
        infoVertice->marcado = true;
}

/* Ronda Crear */

void crear(Ronda &ronda1, int nroronda)
{
    ronda1.nroronda = nroronda;
    Pturnos::crearPila(ronda1.turnos);
}

/* Ronda Destruir */

void destruir(Ronda &ronda1){
    ronda1.nroronda = -1;
    Pturnos::eliminarPila(ronda1.turnos); /* Los turnos se destruyen dentro de la
                                    implementacion del TDA pila */
}

/* Get Nro */

int getnro(const Ronda &ronda1){
    return ronda1.nroronda;
}

/* Realizar Turno */

void realizarTurno(Ronda &ronda1, Tablero &tablero1, ArchivoTexto &archsalida,
                            ListaDeBots::Lista &listabots, int Cantidad, int Recurso){
    //Declaro variables
    ListaDeBots::PtrNodoLista puntero1;
    Pturnos::Dato turno1;
    //Valor Recurso, Cantidad;
    Bot* Pbot = NULL;
    Perforadora* Pperforadora;
    CargaPerforadora* Pcargaperforadora;

    crear(turno1, 0, *Pbot); //Creo un turno vacio para llenar

    Pturnos::desapilar(ronda1.turnos, turno1); //Obtengo el primer turno de la pila

    Pbot = getBot(turno1); //Obtengo el bot del turno extraido

    puntero1 = ListaDeBots::localizarDato(listabots, Pbot); //Se fija si el bot fue destruido
    //Si el bot sigue vivo en esta ronda
    if (puntero1 != ListaDeBots::fin()){

        Pperforadora = get_Perforadora(*Pbot); //Obtengo la perforadora de ese bot
        Pcargaperforadora = getCarga(*Pperforadora); //Obtengo la carga de esa perforadora
        //Segun el valor de recurso obtenido, incremento la cantidad del mismo al principio del turno


        switch (Recurso) {
            case 1: setEnergia(*Pcargaperforadora, getEnergia(*Pcargaperforadora) + Cantidad); break;
            case 2: setHierro(*Pcargaperforadora, getHierro(*Pcargaperforadora) + Cantidad); break;
            case 3: setMadera(*Pcargaperforadora, getMadera(*Pcargaperforadora) + Cantidad); break;
        }
        jugar(turno1, tablero1, archsalida, listabots); //Se juega el turno
    } //sino no hace nada
    destruir(turno1); //Se destruye el turno extraido de la pila
}

/* Llenar Ronda */

void llenarRonda(Ronda &ronda1, ListaDeBots::Lista &listaorig){
    //creo la otra lista
    ListaDeBots::Lista listabots;
    ListaDeBots::crearLista(listabots);

    ListaDeBots::PtrNodoLista ptrNodoCorriente=ListaDeBots::primero(listaorig);
     //variable aux
     ListaDeBots::PtrNodoLista ptrNodoListaAux;
     //creo un puntero a bot
     Bot* ptrBot;
     while (ptrNodoCorriente!=ListaDeBots::fin()){
         //obtengo el "punero a Bot" apuntado por ptrNodoCorriente
         ListaDeBots::obtenerDato(listaorig,ptrBot, ptrNodoCorriente);
         //adiciono al final de la lista de salida
         ptrNodoListaAux=ListaDeBots::adicionarFinal(listabots,ptrBot);
         //apunto al siguiente nodo a ptrcorriente, si es fin salgo del ciclo
         ptrNodoCorriente=ListaDeBots::siguiente(listaorig,ptrNodoCorriente);
     }

    //Declaro variables
    ListaDeBots::PtrNodoLista puntero1;

    int CantDeBots = 0; //Inicializo cantidad de bots en 0.
    int NroTurno = 1; //Digo que el primer turno es el nro 1.
    Valor valor;
    Dado dado1;
    ListaDeBots::Dato dato1;
    //Recorro la lista de bots y cuento la cantidad
    puntero1 = ListaDeBots::primero(listabots);
    while (puntero1 != ListaDeBots::fin()){
        CantDeBots++;
        puntero1 = ListaDeBots::siguiente(listabots, puntero1);
    }
    /*A medida que lleno la pila al azar, elimino el bot de la lista y descuento
      1 a la cantidad de bots. Luego incremento el nro de turno */
    while (CantDeBots > 0) {
        crear(dado1, CantDeBots); /*Creo un dado para obtener el valor al azar.
        La cantidad de caras es la cantidad de bots que hay disponibles en la lista */
        valor = tirar(dado1); //Obtengo el valor al azar
        //Busco el bot en la lista que esta en la posicion del valor al azar obtenido.
        puntero1 = ListaDeBots::primero(listabots);
        int contador = 1;
        while ( contador < valor) {
            puntero1 = ListaDeBots::siguiente(listabots, puntero1);
            contador++;
        }
        ListaDeBots::obtenerDato(listabots, dato1, puntero1); //Obtengo el dato en esa posicion
        turno turno1;
        crear(turno1, NroTurno, *dato1); //Creo un turno para ese bot(dato)
        Pturnos::apilar(ronda1.turnos, turno1); //Lo apilo
        destruir(turno1); //Lo destruyo
        destruir(dado1); //Destruyo el dado porque ya no lo necesito
        ListaDeBots::eliminarNodo(listabots, puntero1); /* Elimino el bot de la lista
        porque ya esta en la pila */
        CantDeBots--; //Descuento un bot
        NroTurno++; //Incremento el numero del turno
    }
}

/* Agregar Encabezado */

void agregarEncabezado(Ronda &ronda1, ArchivoTexto &archsalida){
    //Declaro variables
    std::string buffer;
    Cadena snroronda;
    int nroronda;
    crear(snroronda); //Creo cadena
    //Acomodo el cursor
    //irAlFinal(archsalida);
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 2);
    nroronda = getnro(ronda1); //Obtengo el nro de ronda
    convertirIntAString(snroronda, nroronda); //Lo transformo a string
    buffer = "<ronda numero=\"" + getValor(snroronda) + "\">"; //Lleno el buffer con los datos
    escribirCadena(archsalida, buffer); //Escribo el archivo
    destruir(snroronda); //Destruyo la cadena
}

/* Agregar Perforadora */

void agregarPerforadora(Ronda &ronda1, Bot &bot1, ArchivoTexto &archsalida){
    //Declaro variables necesarias
    std::string buffer, salida;
    Cadena sId_bot, sId_equipo, senergia, smadera, shierro, spuntos;
    Perforadora* Pperforadora;
    CargaPerforadora* Pcargaperforadora;
    tId_Bot Id_bot;
    tId_Equipo Id_equipo;
    Energia energia;
    Madera madera;
    Hierro hierro;
    BodegaPuntos puntos;
    //Creo cadenas
    crear(sId_bot);
    crear(sId_equipo);
    crear(senergia);
    crear(smadera);
    crear(shierro);
    crear(spuntos);
    //Obtengo los datos a escribir en el archivo
    Id_bot = get_ID(bot1); //Obtengo el id del bot pasado como parametro
    Id_equipo = get_Equipo(bot1); //Obtengo su id de equipo
    Pperforadora = get_Perforadora(bot1); //Obtengo la perforadora de ese bot
    Pcargaperforadora = getCarga(*Pperforadora); //Obtengo la carga de la perforadora
    energia = getEnergia(*Pcargaperforadora); //Obtengo la energia de la perforadora
    madera = getMadera(*Pcargaperforadora); //Obtengo la madera
    hierro = getHierro(*Pcargaperforadora); //Obtengo el hierro
    puntos = getBodegaPuntos(*Pperforadora); //Obtengo los puntos que tiene acumulados
    if (getSalida(*Pperforadora) == true)
        salida = "si";
    else
        salida = "no";
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 4);
    convertirIntAString(sId_bot, Id_bot); //transformo a string
    convertirIntAString(sId_equipo, Id_equipo); //transformo a string
    //Lleno el buffer con los datos convertidos a string
    buffer = "<perforadora id=\"" + getValor(sId_bot) + "\"  equipo=\""
    + getValor(sId_equipo) + "\">";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 5);
    convertirIntAString(senergia, energia); //transformo a string
    //Lleno el buffer con los datos convertidos a string
    buffer = "<energia> " + getValor(senergia) + " </energia>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 5);
    convertirIntAString(shierro, hierro); //transformo a string
    //Lleno el buffer con los datos convertidos a string
    buffer = "<hierro> " + getValor(shierro) + " </hierro>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 5);
    convertirIntAString(smadera, madera); //transformo a string
    //Lleno el buffer con los datos convertidos a string
    buffer = "<madera> " + getValor(smadera) + " </madera>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 5);
    convertirIntAString(spuntos, puntos); //transformo a string
    //Lleno el buffer con los datos convertidos a string
    buffer = "<puntos-totales> " + getValor(spuntos) + " </puntos-totales>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 5);
    //Lleno el buffer
    buffer = "<conducto-salida> " + salida + " </conducto-salida>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 4);
    //Lleno el buffer
    buffer = "</perforadora>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Destruyo cadenas
    destruir(sId_bot);
    destruir(sId_equipo);
    destruir(senergia);
    destruir(smadera);
    destruir(shierro);
    destruir(spuntos);
}

/* Agregar Pie */

void agregarPie(Ronda &ronda1, Tablero &tablero1, ArchivoTexto &archsalida,
                        ListaDeBots::Lista &listabots, GrupoEquipos* grupo){
    //Declaro variables
    std::string buffer;
    ListaDeBots::PtrNodoLista puntero1;
    ListaDeBots::Dato dato1;
    //Acomodo el cursor en el archivo
    //irAlFinal(archsalida);
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 3);
    //Lleno el buffer
    buffer = "<tablero>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Llamo al tablero para que se imprima en el archivo
    ActualizarSalida(tablero1, archsalida, grupo);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 3);
    //Lleno el buffer
    buffer = "</tablero>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 3);
    //Lleno el buffer
    buffer = "<perforadoras>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Recorro toda la lista de bots y agrego los datos de la perforadora en el archivo
    puntero1 = ListaDeBots::primero(listabots);
    while (puntero1!=ListaDeBots::fin()){
        ListaDeBots::obtenerDato(listabots, dato1, puntero1);
        //Llamo al agregar datos de la perforadora
        agregarPerforadora(ronda1, *dato1, archsalida);
        puntero1 = ListaDeBots::siguiente(listabots, puntero1);
    }
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 3);
    //Lleno el buffer
    buffer = "</perforadoras>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 2);
    //Lleno el buffer
    buffer = "</ronda>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
}

/* Verificar Salidas */

void VerificarSalidas(Ronda &ronda1, Tablero &tablero1, ListaDeBots::Lista &listabots){
    ListaDeBots::PtrNodoLista puntero1;
    //Cada ronda reinicio las salidas para volver a buscarlas
    puntero1 = ListaDeBots::primero(listabots);
    while (puntero1 != ListaDeBots::fin()){
        Perforadora* Pperf = get_Perforadora(*puntero1->dato);
        setSalida(*Pperf, false);
        puntero1 = ListaDeBots::siguiente(listabots, puntero1);
    }
    recorrido(tablero1, &desmarcar, &debeMarcarse, &marcar, listabots);
}

/* Jugar */

void jugar(Ronda &ronda1, Tablero &tablero1, ArchivoTexto &archsalida,
                    ListaDeBots::Lista &listabots, GrupoEquipos* grupo){
    //Declaro variables necesarias
    std::string buffer;

    llenarRonda(ronda1, listabots); //Lleno la ronda de turnos, de forma azarosa
    agregarEncabezado(ronda1, archsalida); //Imprimo el encabezado en el archivo
    //Acomodo el cursor en el archivo

    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 3);
    //Lleno el buffer
    buffer = "<turnos>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Realizo todos los turnos contenidos en la ronda
    Dado dadorecurso;
    Dado dadocantidad;
    int Cantidad;
    int Recurso;

    crear(dadorecurso, 4); //Creo el dado de recursos
    crear(dadocantidad, 8); //Creo el dado que determina la cantidad de recursos

    while (!Pturnos::pilaVacia(ronda1.turnos))
    {
        Recurso = tirar(dadorecurso); //Obtengo un recurso al azar
        Cantidad = tirar(dadocantidad); //Obtengo una cantidad de recurso al azar

        realizarTurno(ronda1, tablero1, archsalida, listabots, Cantidad, Recurso);


    }
    destruir(dadorecurso); //Como ya tengo el valor que quería, destruyo el dado
    destruir(dadocantidad); //Idem anterior
    //Acomodo el cursor en el archivo
    bajarDeLinea(archsalida);
    tabulararchivo(archsalida, 3);
    //Lleno el buffer
    buffer = "</turnos>";
    //Escribo los datos en el archivo
    escribirCadena(archsalida, buffer);
    //Verfico las salidas de las perforadoraas
    VerificarSalidas(ronda1, tablero1, listabots);
    //Agrego los datos finales de la ronda en el archivo de salida
    agregarPie(ronda1, tablero1, archsalida, listabots, grupo);
}


