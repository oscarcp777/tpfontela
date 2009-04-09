/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                             TDA Tablero                                    *
 ******************************************************************************/

/********************************HEADERS***************************************/

#include "tablero.h"


using namespace std;
/*******************************PRIMITIVAS*************************************/
/*----------------------------------------------------------------------------*/
// funciones adicionales para la implementacion de las primitivas
int CantidadFilas(ArchivoTexto &aTablero){
    int cont=0;
    std::string cadena;
    irAlComienzo(aTablero);
    while (leerLinea(aTablero,cadena))
      cont++;
    return cont;

}
char DeMineralAChar(Mineral mineral)
{
    if (obtenerTipo(mineral) == roca)
    {
        switch (obtenerPuntos(mineral))
        {
            case 1: return '1';
                    break;
            case 2: return '2';
                    break;
            case 3: return '3';
                    break;
            case 4: return '4';
                    break;
            case 5: return '5';
                    break;
            case 6: return '6';
                    break;
            case 7: return '7';
                    break;
            case 8: return '8';
                    break;
            case 9: return '9';
                    break;
        }
        } else {
            switch(obtenerTipo(mineral))
            {
               case oro: return 'z';
                         break;
               case plata: return 'y';
                           break;
               case cobre: return 'x';
                           break;
            }
        }
    }
EnumMinerales Get_TipoMineral(char mineral){
    switch (mineral) {

        case 'z': return oro;
        case 'y': return plata;
        case 'x': return cobre;
        default: return roca;
    }
}
Puntos Get_PuntosMineral(char mineral){
    switch (mineral) {
        case '1':  return 1;
        case '2':  return 2;
        case '3':  return 3;
        case '4':  return 4;
        case '5':  return 5;
        case '6':  return 6;
        case '7':  return 7;
        case '8':  return 8;
        case '9':  return 9;
        default: return 0;
    }
}

bool aristasSonIguales (void* dato1, void* dato2)
{
    DatoArista* arista1;
    DatoArista* arista2;

    arista1 = static_cast<DatoArista *>(dato1);
    arista2 = static_cast<DatoArista *>(dato2);

    if (arista1->Id == arista2->Id)
        return true;
    else
        return false;

}

/*----------------------------------------------------------------------------*/


void Crear(Tablero &tablero, ArchivoTexto &aTablero){
    int columnas =0;
    int filas =0;
    Casillero* casillero;
    Mineral mineral;
    Cadena cadena;
    std::string stringAuxiliar;
    bool leida=false;
    int numeroCasillero = 1;


    crear(cadena);
    irAlComienzo(aTablero);
    leerLinea(aTablero,stringAuxiliar);
    setValor(cadena,stringAuxiliar);
    columnas= cantidadCaracteres(cadena);
    filas= CantidadFilas(aTablero)+1;
    Crear(*getMatriz(tablero),columnas,filas);
    destruir(cadena);
    tablero.grafo =nuevoGrafo();
    (getEntrada(tablero))->dondeSeCargo=agregarVertice(getGrafo(tablero),getEntrada(tablero));
    for(int i=0; i<columnas; i++){
        casillero = new Casillero;
        crear(*casillero, numeroCasillero);
        numeroCasillero++;
        setDato(*getMatriz(tablero),casillero,0,i);
    }
    irAlComienzo(aTablero);
    for (int i = 1; i < filas; i++) {              // escribo en cada campo
        leida= leerLinea(aTablero,stringAuxiliar);
        for (int j = 0; j < columnas; j++){
            casillero=new Casillero;
            if (Get_PuntosMineral(stringAuxiliar[j]) == 0)
                crear(mineral, Get_TipoMineral(stringAuxiliar[j]));
            else
                crear(mineral, Get_TipoMineral(stringAuxiliar[j]), Get_PuntosMineral(stringAuxiliar[j]));
            crear(*casillero, numeroCasillero);
            numeroCasillero++;

            asignarBot(*casillero, SinBot());
            asignarMineral(*casillero, mineral);
            destruir(mineral);
            setDato(*(getMatriz(tablero)),casillero,i,j);
        }

}
}
/*---------------------------------------------------------------------------*/

void Destruir(Tablero &tablero){
    Casillero* auxCasillero;
    for (int i = 0; i < getCantFilas(*getMatriz(tablero)); i++)               // escribo en cada campo
      for (int j = 0; j < getCantColumnas(*getMatriz(tablero)); j++){
          //tomo el dato , lo destruyo y lo pongo en el mismo lugar.
          auxCasillero = getDato(*getMatriz(tablero), i, j);
          destruir(*auxCasillero);
          //libero la memoria ocupada por el casillero
          delete ( getDato(*getMatriz(tablero), i, j));
      }

    Destruir(*getMatriz(tablero));
    eliminarGrafo(getGrafo(tablero));
}
/*---------------------------------------------------------------------------*/

void UbicarBotsIniciales(Tablero &tablero,ListaDeBots::Lista &botInicialesOriginales){

    //creo la otra lista
    ListaDeBots::Lista botIniciales;
    ListaDeBots::crearLista(botIniciales);

    ListaDeBots::PtrNodoLista ptrNodoCorriente=ListaDeBots::primero(botInicialesOriginales);
     //variable aux
     ListaDeBots::PtrNodoLista ptrNodoListaAux;
     //creo un puntero a bot
     Bot* ptrBot1;
     while (ptrNodoCorriente!=ListaDeBots::fin()){
         //obtengo el "punero a Bot" apuntado por ptrNodoCorriente
         ListaDeBots::obtenerDato(botInicialesOriginales,ptrBot1, ptrNodoCorriente);
         //adiciono al final de la lista de salida
         ptrNodoListaAux=ListaDeBots::adicionarFinal(botIniciales,ptrBot1);
         //apunto al siguiente nodo a ptrcorriente, si es fin salgo del ciclo
         ptrNodoCorriente=ListaDeBots::siguiente(botInicialesOriginales,ptrNodoCorriente);
     }

    int CantBots=0;
    int columna;
    ListaDeBots::PtrNodoLista ptrNodo= ListaDeBots::primero(botIniciales);
    ListaDeBots::Dato ptrBot;
    Casillero *casilleroAuxiliar;
    Dado dado;


    while (ptrNodo!=ListaDeBots::fin()){
        CantBots++;
        ptrNodo=ListaDeBots::siguiente(botIniciales,ptrNodo);
    }

    crear(dado,getCantColumnas(*getMatriz(tablero)));

    while(!ListaDeBots::listaVacia(botIniciales))
    {

        obtenerDato(botIniciales, ptrBot, primero(botIniciales));

        columna = tirar(dado);
        casilleroAuxiliar = getDato(*getMatriz(tablero),0, columna-1);
        if (obtenerBot(*casilleroAuxiliar) == SinBot())
        {
            asignarBot(*casilleroAuxiliar, ptrBot);
            ActualizarEntorno(tablero,*ptrBot);
            ListaDeBots::eliminarNodo(botIniciales,primero(botIniciales));
        }
    }
    destruir(dado);
}
//Elimina todos los enlaces entre un vertice y todos a los que apunta,
//eliminando sus aristas
void eliminarEnlaces(Casillero *casilleroDestino)
{
    Arista* aristaAux;
    Vertice* verticeAux;
    Conjunto* PtrConjunto;
    PtrConjunto = getAristasSalientes(obtenerPunteroTuberia(*casilleroDestino)->dondeSeCargo);
    IteradorConjunto* Ptriterador = nuevoIterador(PtrConjunto);
    DatoArista* aristaEntrante=new DatoArista;
    while (!fin(Ptriterador))
    {
        aristaAux = static_cast<Arista*> (obtenerElemento(Ptriterador));
        verticeAux = getVerticeDestino(aristaAux);
        aristaEntrante->Id = obtenerId(*casilleroDestino);

        aristaAux = buscarAristaSaliente(verticeAux,aristaEntrante,&aristasSonIguales);
        if (aristaAux != NULL)
        {
            DatoArista * datoAristaAux;
            datoAristaAux = static_cast<DatoArista*>(getInfo (aristaAux));
            delete datoAristaAux;
            quitarAristaSaliente(verticeAux, aristaAux);
        }
        irAlSiguiente(Ptriterador);
    }
    eliminarIterador(Ptriterador);
    eliminarConjunto(PtrConjunto);
    PtrConjunto = nuevoConjunto ();
}
//Funcion interna que se encarga de enlazar un vertice con todos los salientes
void enlazar(Tablero &tablero,Casillero *ptrCasilleroAux, DatoVertice *datoDestino, DatoVertice *ptrDatoVertice)
{
    DatoArista *datoArista;
    datoArista = new DatoArista;;
    datoArista->Id = obtenerId(*ptrCasilleroAux);
    if(buscarAristaSaliente(datoDestino->dondeSeCargo,datoArista,&aristasSonIguales) == NULL)
    {
        agregarAristaDirigida(getGrafo(tablero),datoDestino->dondeSeCargo, ptrDatoVertice->dondeSeCargo, datoArista);

    }
    datoArista = new DatoArista;
    datoArista->Id = datoDestino->Id;
    if(buscarAristaSaliente(ptrDatoVertice->dondeSeCargo,datoArista,&aristasSonIguales) == NULL)
    {
        agregarAristaDirigida(getGrafo(tablero),ptrDatoVertice->dondeSeCargo,datoDestino->dondeSeCargo, datoArista);
    }
    else
        delete datoArista;
}
//Funcion interna para crear un vertice nuevo
void crearVerticeNuevo(Tablero &tablero, Casillero* casilleroDestino,Casillero* casilleroOrigen, DatoVertice &datoDestino)
{
    Vertice* verticeAux;

            datoDestino.Id = obtenerId(*casilleroDestino);
            datoDestino.marcado = false;
            datoDestino.tuberia = get_Equipo(*obtenerBot(*casilleroOrigen));
            datoDestino.dondeSeCargo =NULL;
            verticeAux = agregarVertice(getGrafo(tablero),&datoDestino);
            datoDestino.dondeSeCargo = verticeAux;
            DatoVertice* auxiliar = obtenerPunteroTuberia(*casilleroDestino);
            DatoVertice** ptrDatoAux = &auxiliar;
            *ptrDatoAux = &datoDestino;
            (*ptrDatoAux)->dondeSeCargo = verticeAux;
}
/*---------------------------------------------------------------------------*/
void moverBot(Tablero &tablero,Bot* punteroBot,EnumMovimiento movimiento){

    int PosFila;
    int PosColum;

    Casillero* casilleroAux;
    Casillero* casilleroOrigen;
    DatoVertice* datoDestino;
    DatoVertice* datoOrigen;
    Vertice* verticeAux;

    //busco el casillero desde donde me muevo
    buscarCasillero(tablero,*punteroBot, PosFila,PosColum);
    //obtengo sus datos
    casilleroOrigen=getDato(*getMatriz(tablero),PosFila,PosColum);
    //Calculo la posicion del casillero al que hay que moverse
    switch(movimiento){
        case arriba: PosFila--;
                     break;
        case abajo: PosFila++;
                    break;
        case derecha: PosColum++;
                      break;
        case izquierda: PosColum--;
                        break;
    }
    //si me tengo que mover
    if (movimiento!=nada)
    {
        //obtengo el casillero de destino
        Casillero* casilleroDestino = getDato(*getMatriz(tablero),PosFila, PosColum);
        //quito su mineral
        quitarMineral(*casilleroDestino);
        //le asigno el bot a mover
        asignarBot(*casilleroDestino, obtenerBot(*casilleroOrigen));
        //actualizo el entorno del bot movido para que vea los cambios
        ActualizarEntorno(tablero,*obtenerBot(*casilleroDestino));
        //si hay alguna tuberia, saco los enlaces
        if (obtenerTuberia(*casilleroDestino) != -1)
        {
            //solo saco las que no son de mi equipo
            if (obtenerTuberia(*casilleroDestino) != get_Equipo(*obtenerBot(*casilleroOrigen)))
                eliminarEnlaces(casilleroDestino);
            //enlazo el destino con el origen, formando asi la seccion de la
            //tuberia
            datoDestino = obtenerPunteroTuberia(*casilleroDestino);
            datoOrigen = obtenerPunteroTuberia(*casilleroOrigen);
            datoDestino->tuberia = datoOrigen -> tuberia;
        }
        else
        {
            //si no hay tuberia, creo el vertice y armo el enlace
            datoDestino = new DatoVertice;
            crearVerticeNuevo(tablero,casilleroDestino,casilleroOrigen, *datoDestino);
        }
        //se quita el bot del origen
        quitarBot(*casilleroOrigen);
        //aca se actualizan los enlaces con los casillero del entorno
        int fila;
        int columna;
        DatoVertice* ptrDatoVertice;
        Casillero* ptrCasilleroAux;
        buscarCasillero(tablero,*punteroBot,fila,columna);
        //Aca se actualizan los enlaces con el entorno, no se realiza todo
        //en alguna funcion, debido a que son cuatro casos muy especificos
        //y varian
        if ( (fila-1) > 0 )
        {
            //obtengo el casillero
            ptrCasilleroAux = getDato(*getMatriz(tablero),fila-1,columna);
            if (ptrCasilleroAux != NULL)
            {
                //saco el dato de su vertice
                ptrDatoVertice = obtenerPunteroTuberia(*ptrCasilleroAux);
                //armo los enlaces
                if(obtenerTuberia(*ptrCasilleroAux) == datoDestino->tuberia)
                    enlazar(tablero,ptrCasilleroAux, datoDestino,ptrDatoVertice);
                asignarTuberia(*casilleroDestino, datoDestino);
            }
        }
        else
        {
            //si se esta en la fila de arriba se agrega una coneccion con
            //el vertice de entrada
            DatoArista *arista = new DatoArista;
            arista->Id = obtenerId(*casilleroDestino);
            if(buscarAristaSaliente(tablero.entrada.dondeSeCargo,arista,&aristasSonIguales) == NULL)
                agregarAristaDirigida(getGrafo(tablero),tablero.entrada.dondeSeCargo,datoDestino->dondeSeCargo,arista);
            else
                delete arista;
        }
        if (fila+1 < getCantFilas(*getMatriz(tablero)))
        {
            ptrCasilleroAux = getDato(*getMatriz(tablero),fila+1,columna);
            if (ptrCasilleroAux != NULL)
            {
                ptrDatoVertice = obtenerPunteroTuberia(*ptrCasilleroAux);
                if(obtenerTuberia(*ptrCasilleroAux) == datoDestino->tuberia)
                    enlazar(tablero,ptrCasilleroAux, datoDestino,ptrDatoVertice);
                asignarTuberia(*casilleroDestino, datoDestino);
            }
        }
        if (columna-1>=0)
        {
            ptrCasilleroAux = getDato(*getMatriz(tablero),fila,columna-1);
            if (ptrCasilleroAux != NULL)
            {
                ptrDatoVertice = obtenerPunteroTuberia(*ptrCasilleroAux);
                if(obtenerTuberia(*ptrCasilleroAux) == datoDestino->tuberia)
                    enlazar(tablero,ptrCasilleroAux, datoDestino,ptrDatoVertice);
                asignarTuberia(*casilleroDestino, datoDestino);
            }
        }
        if (columna+1<getCantColumnas(*getMatriz(tablero)))
        {
            ptrCasilleroAux = getDato(*getMatriz(tablero),fila,columna+1);
            if (ptrCasilleroAux != NULL)
            {
                ptrDatoVertice = obtenerPunteroTuberia(*ptrCasilleroAux);
                if(obtenerTuberia(*ptrCasilleroAux) == datoDestino->tuberia)
                    enlazar(tablero,ptrCasilleroAux, datoDestino,ptrDatoVertice);
                asignarTuberia(*casilleroDestino, datoDestino);
            }
        }
    }
}

/*---------------------------------------------------------------------------*/

void ActualizarEntorno(Tablero &tablero,Bot &bot){

    int ContFila;
    int ContColum;
    int filaDestino;
    int columnaDestino;
    Entorno* entornoAux;


    entornoAux=getEntorno(*get_Perforadora(bot));

    buscarCasillero(tablero,bot,ContFila,ContColum);

    //cambio arriba

    filaDestino = ContFila-1;
    if(filaDestino >= 1)
    {
        setArriba(*entornoAux, getDato(*getMatriz(tablero),filaDestino,ContColum));

    }
    else
    {
        setArriba(*entornoAux, Vacio());
        setIzquierda(*entornoAux, Vacio());
        setDerecha(*entornoAux, Vacio());
    }

    //cambio laterales
    if(filaDestino >= 0)  {
        //cambio izquierda
        columnaDestino = ContColum-1;
        if(columnaDestino >= 0)
            setIzquierda(*entornoAux, getDato(*getMatriz(tablero),ContFila,columnaDestino));
        else
            setIzquierda(*entornoAux, Vacio());
        //cambio derecha
        columnaDestino = ContColum+1;
        if(columnaDestino < getCantColumnas(*getMatriz(tablero))-1)
            setDerecha(*entornoAux, getDato(*getMatriz(tablero),ContFila,columnaDestino));
        else
            setDerecha(*entornoAux, Vacio());
    }
    //cambio abajo
    filaDestino = ContFila+1;
    if(filaDestino < getCantFilas(*getMatriz(tablero))-1)
        setAbajo(*entornoAux, getDato(*getMatriz(tablero),filaDestino,ContColum));
    else
        setAbajo(*entornoAux, Vacio());
}

void ActualizarSalida(Tablero&tablero,ArchivoTexto &archsalida, GrupoEquipos* grupo)
{
    Casillero* casillero;
    bajarDeLinea(archsalida);
    Equipo* equipo;
    Bot* bot;

    for (int i = 1; i < getCantFilas(*getMatriz(tablero)); i++)
    {
        //Tabulo
        for (char contador = 0; contador <=5; contador++)
            tabular(archsalida);
        //escribirCadena(archsalida, "<l> "); //escribo el comienzo de linea
        for (int j =0 ; j < getCantColumnas(*getMatriz(tablero)); j++)
        {
            casillero = getDato(*getMatriz(tablero),i,j);
            bot = obtenerBot(*casillero);
            if ( bot != SinBot()  )
            {
                equipo = get_PtrEquipo(*bot);
                escribirCaracter(archsalida,getCaracterPerforadora(*equipo));
            }
            else
            {
                if ( obtenerTuberia(*casillero) != -1)
                {
                    equipo = ObtenerEquipo(*grupo,obtenerTuberia(*casillero) );
                    escribirCaracter(archsalida, getCaracterCamino(*equipo));
                }
                else
                {
                    if ( obtenerMineral(*casillero) != SinMineral())
                    {
                        escribirCaracter(archsalida,DeMineralAChar(*obtenerMineral(*casillero)));
                    }
                }
            }
        }
        //escribirCadena(archsalida, " </l>"); //escribo el fin de linea
        bajarDeLinea(archsalida);
    }
 }

void buscarCasillero(Tablero &tablero,Bot &bot, int &ContFilas, int &ContColum)
{
    bool encontrado=false;
    Casillero* auxCasillero;
    ContFilas = 0;

    while( (ContFilas<getCantFilas(*getMatriz(tablero)))&&(!encontrado) )
    {
        ContColum = 0;
        while ((ContColum < getCantColumnas(*getMatriz(tablero)))    &&  (!encontrado))
        {
            auxCasillero = (getDato((*getMatriz(tablero)),ContFilas,ContColum));
            if (obtenerBot(*auxCasillero) != SinBot() )
            {
                if (get_ID(*obtenerBot(*auxCasillero)) == get_ID(bot))
                {
                    encontrado=true;
                }
            }
            if(!encontrado)
                ContColum++;
        }
        if(!encontrado)
            ContFilas++;
    }
    }

/*---------------------------------------------------------------------------*/

MatrizDinamica* getMatriz(Tablero &tablero){
    return &(tablero.Matriz);
}
Grafo* getGrafo(Tablero &tablero)
{
    return tablero.grafo;
}
Casillero* buscarCasilleroPorId(Tablero &tablero,int id)
{
    bool encontrado=false;
    Casillero* auxCasillero;
    int ContFilas = 0;
    int ContColum;

    while( (ContFilas<getCantFilas(*getMatriz(tablero)))&&(!encontrado) )
    {
        ContColum = 0;
        while ((ContColum < getCantColumnas(*getMatriz(tablero)))    &&  (!encontrado))
        {
            auxCasillero = (getDato((*getMatriz(tablero)),ContFilas,ContColum));
            if (obtenerId(*auxCasillero) == id)
                encontrado = true;

            if(!encontrado)
                ContColum++;
        }
        if(!encontrado)
            ContFilas++;
    }
    if (encontrado)
        return auxCasillero;
    else
        return NULL;
}
DatoVertice* getEntrada(Tablero &tablero)
{
    return &(tablero.entrada);
}
