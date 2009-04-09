/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA GrupoEquipos

 */

#include "grupoequipos.h"

/******************************************************************************/
/* Implementación de Primitivas */
/*------------------------------*/


void crearGrupoEquipos(GrupoEquipos &grupoequip,ArchivoRegistros &Aequipos,ArchivoRegistros &Abots){
    //creo la lista de equipos
    lequipos::crearLista(grupoequip.ListaEquipos);
    ////////////// CARGA ARCHIVO EQUIPOS////////////////
    regEquipos registro1;
    //pos dentro del archivo
    long int posEquipos=0;
    //puntero a equipo
    Equipo* ptrequipo;
    //me posiciono en la primer posicion del archivo
    posicionarse(Aequipos,0);
    //mientras no se puedan leer mas registros
    while (!fin(Aequipos)){
        //cargo el registro del equipo a agregar
        leer(Aequipos,static_cast<void*>(&registro1));
        //creo una variable equipo en el heap
        ptrequipo=new Equipo;
        //creo el tda equipo con los valores del registros leidos del archivo
        crearEquipo(*ptrequipo,registro1.id, registro1.nombre,
                            registro1.caracterPerforadora,registro1.caracterSeccionCamino);
        //agrego el equipo al grupo de equipos
        agregarEquipo(grupoequip,ptrequipo);
        //incremento la posicion
        posEquipos++;
        //avanzo una posicion en el archivo
        posicionarse(Aequipos,posEquipos);
    }

    ////////////// CARGA ARCHIVO BOTS////////////////

    //puntero a registroDeEquipo
    regBots registro2;
    //pos dentro del archivo
    long int posBots=0;
    //puntero a equipo
    Equipo* ptrequipo1;
    Bot* ptrBot1;

    //me posiciono en la primer posicion del archivo
    posicionarse(Abots,0);
    //mientras no se puedan leer mas registros
    while (!fin(Abots)){
        //obtengo un void pointer con el registro del Bot a agregar

        leer(Abots,static_cast<void*> (&registro2));

        //obtengo el equipo del Bot a Agregar
        ptrequipo1=ObtenerEquipo(grupoequip,registro2.idEquipo);
        //creo un bot en el heap
        ptrBot1=new Bot;
        //creo el tda bot con los valores del registros leidos del archivo
        crear(*ptrBot1,registro2.idBot,registro2.idEquipo, ptrequipo1);
        //obtengo la estrategia del bot para setearla con los valores del reg
        Estrategia* ptrEstrategia=get_Estrategia(*ptrBot1);
        //obtengo los movimientos de la estrategia del bot para setearla con los valores del reg
        Movimientos* ptrMovimientos=obtenerMovimientos(*ptrEstrategia);
        //obtengo las actitudes de la estrategia del bot para setearla con los valores del reg
        Actitudes* ptrActitudes=obtenerActitudes(*ptrEstrategia);
        //seteo los movimientos
        asignarArriba(*ptrMovimientos,registro2.arriba);
        asignarAbajo(*ptrMovimientos,registro2.abajo);
        asignarIzquierda(*ptrMovimientos,registro2.izquierda);
        asignarDerecha(*ptrMovimientos,registro2.derecha);
        asignarNada(*ptrMovimientos,registro2.esperar);
        //seteo las actitudes
        asignarProcesarOro(*ptrActitudes,registro2.procesarOro);
        asignarProcesarPlata(*ptrActitudes,registro2.procesarPlata);
        asignarProcesarCobre(*ptrActitudes,registro2.procesarCobre);
        asignarConstruirConducto(*ptrActitudes,registro2.construirConducto);
        asignarDestruirConducto(*ptrActitudes,registro2.destruirConducto);
        asignarDestruirPerforadora(*ptrActitudes,registro2.destruirPerforadora);
        //agrega el bot a la lista de bots del equipo
        cargarBotaEquip(*ptrequipo1,ptrBot1);
        //incremento la posicion
        posBots++;
        //avanzo una posicion en el archivo
        posicionarse(Abots,posBots);
    }


}

void agregarEquipo(GrupoEquipos &grupoequip,ptrEquipo ptrequip){
    lequipos::PtrNodoLista puntero1;
    puntero1 = lequipos::insertarDato(grupoequip.ListaEquipos,ptrequip);
}

void obtenerlistaBotsGrupoEquipos(GrupoEquipos &grupoequip,ListaDeBots::Lista &listaBotsGrupo){
    Equipo* ptrEquip;
    //apunto al primer elemento de la lista de equipos
    lequipos::NodoLista* ptrNodoCorriente=lequipos::primero(grupoequip.ListaEquipos);

    while (ptrNodoCorriente!=lequipos::fin()){
         //obtengo un equipo apuntado por ptrNodoCorriente

         lequipos::obtenerDato(grupoequip.ListaEquipos,ptrEquip, ptrNodoCorriente);
         //agrego de ese equipo los Bots q tenga en su listadebots a la lista general
         ObtenerListaBots(*ptrEquip,listaBotsGrupo);
         //apunto al siguiente equipo en caso de ser fin() sale del ciclo
         ptrNodoCorriente=lequipos::siguiente(grupoequip.ListaEquipos,ptrNodoCorriente);
    }
}

void obtenerlistaEquipos(GrupoEquipos &grupoequip,lequipos::Lista &listaEquiposSalida){
    Equipo* ptrEquip;
    //apunto al primer elemento de la lista de equipos
    lequipos::NodoLista* ptrNodoCorriente=lequipos::primero(grupoequip.ListaEquipos);
    lequipos::NodoLista* ptrNodoAux;
    while (!(ptrNodoCorriente==lequipos::fin())){
         //obtengo un equipo apuntado por ptrNodoCorriente
         lequipos::obtenerDato(grupoequip.ListaEquipos,ptrEquip, ptrNodoCorriente);
         //adiciono en la lista de salida
         ptrNodoAux=lequipos::adicionarPrincipio(listaEquiposSalida,ptrEquip);
         //apunto al siguiente equipo en caso de ser fin() sale del ciclo
         ptrNodoCorriente=lequipos::siguiente(grupoequip.ListaEquipos,ptrNodoCorriente);
    }
}

void destruirGrupoEquipos(GrupoEquipos &grupoequip){
    lequipos::eliminarLista(grupoequip.ListaEquipos);
}
int cantidadEquipos (GrupoEquipos &grupoequip){
    //apunto al primer elemento de la lista de equipos
    lequipos::NodoLista* ptrNodoCorriente=lequipos::primero(grupoequip.ListaEquipos);
    int cant=0;
    while (!(ptrNodoCorriente==lequipos::fin())){
         cant++;
         //apunto al siguiente equipo en caso de ser fin() sale del ciclo
         ptrNodoCorriente=lequipos::siguiente(grupoequip.ListaEquipos,ptrNodoCorriente);
    }
    return cant;
}
int cantidadBotsTotales(GrupoEquipos &grupoequip){
    //apunto al primer elemento de la lista de equipos
    lequipos::NodoLista* ptrNodoCorriente=lequipos::primero(grupoequip.ListaEquipos);
    int cant=0;
    Equipo* ptrEquipo;

    while (!(ptrNodoCorriente==lequipos::fin())){

         lequipos::obtenerDato(grupoequip.ListaEquipos,ptrEquipo, ptrNodoCorriente);

         cant+=cantBots(*ptrEquipo);

         //apunto al siguiente equipo en caso de ser fin() sale del ciclo
         ptrNodoCorriente=lequipos::siguiente(grupoequip.ListaEquipos,ptrNodoCorriente);
    }
    return cant;
}

Equipo* EquipoMayorPuntaje(GrupoEquipos &grupoequip){
    //apunto al primer elemento de la lista de equipos
    lequipos::NodoLista* ptrNodoCorriente=lequipos::primero(grupoequip.ListaEquipos);
    //El Equipo con mayor puntaje inicialmente es el 1ro
        Equipo* ptrEquipoMayorPuntaje;
        lequipos::obtenerDato(grupoequip.ListaEquipos,ptrEquipoMayorPuntaje, ptrNodoCorriente);

    //Variable para recorrer la lista de equipos
    Equipo* ptrEquipo = ptrEquipoMayorPuntaje;

    //Apunto al siguiente Nodo
    ptrNodoCorriente=lequipos::siguiente(grupoequip.ListaEquipos,ptrNodoCorriente);

    while (!(ptrNodoCorriente==lequipos::fin())){
         //obtengo el equipo apuntado por el ptrNodoCorriente
         lequipos::obtenerDato(grupoequip.ListaEquipos,ptrEquipo,ptrNodoCorriente);
         //si el puntaje del equipo corriente es mayor q el del Equipo con Mayor Puntaje hasta el momento
         if (GetPuntosEquipo(*ptrEquipo) > GetPuntosEquipo(*ptrEquipoMayorPuntaje)) {
            //ahora el equipo con mayor puntaje es el Equipo corriente
            ptrEquipoMayorPuntaje=ptrEquipo;
         }
         //apunto al siguiente Nodo en caso de ser fin() sale del ciclo
         ptrNodoCorriente=lequipos::siguiente(grupoequip.ListaEquipos,ptrNodoCorriente);
    }
    return ptrEquipoMayorPuntaje;
}

Equipo* ObtenerEquipo(GrupoEquipos &grupoequip,tId_Equipo ID){
    Equipo* ptrEquip;
    bool encontrado=false;
    //apunto al primer elemento de la lista de equipos
    lequipos::NodoLista* ptrNodoCorriente=lequipos::primero(grupoequip.ListaEquipos);
    while ((!(ptrNodoCorriente==lequipos::fin()))&& (!encontrado)){
         //obtengo un equipo apuntado por ptrNodoCorriente
         lequipos::obtenerDato(grupoequip.ListaEquipos,ptrEquip, ptrNodoCorriente);
         //si el id del equipo apuntado por ptrEquipo es el id q buscaba salgo del siclo
         encontrado = (getid(*ptrEquip)==ID);
         //apunto al siguiente equipo en caso de ser fin() o encontrado sale del ciclo
         ptrNodoCorriente=lequipos::siguiente(grupoequip.ListaEquipos,ptrNodoCorriente);
    }

    //se considera q el id ingresado pertence a un equipo
return ptrEquip;
}

