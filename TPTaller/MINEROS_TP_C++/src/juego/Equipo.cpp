/******************************************************************************
 *                   Algoritmos y Programación II - 75.41                     *
 *                        Cátedra Ing. Mandrafina                             *
 *            Facultad de Ingeniería - Universidad de Buenos Aires            *
 ******************************************************************************/

/* TDA Equipo
 * Archivo : Equipo.cpp
 */

#include "Equipo.h"


/******************************************************************************/
/* Implementación de Primitivas */
/*------------------------------*/

void crearEquipo(Equipo &equip, tId_Equipo id, std::string nom, char perChar, char camChar){
     ListaDeBots::crearLista(equip.listBots);
     equip.id=id;
     equip.nombre=nom;
     equip.perfoChar=perChar;
     equip.caminChar=camChar;
     }

/******************************************************************************/


std::string getnombre(Equipo &equip){
       return equip.nombre;
}
/******************************************************************************/

tId_Equipo getid(Equipo &equip){
       return equip.id;
}
/******************************************************************************/

char getCaracterCamino(Equipo &equip){
       return equip.caminChar;
}
/******************************************************************************/

char getCaracterPerforadora(Equipo &equip){
       return equip.perfoChar;
}
/******************************************************************************/
void cargarBotaEquip (Equipo &equip, Pbot pbot){

    ListaDeBots::adicionarFinal(equip.listBots,pbot);

}
/******************************************************************************/
void sacarBot (Equipo &equip,Pbot pbot){
    ListaDeBots::eliminarDato(equip.listBots,pbot);

}
/******************************************************************************/

int cantBots(Equipo &equip){
     ListaDeBots::NodoLista* ptrNodoCorriente=ListaDeBots::primero(equip.listBots);
     int cant=0;
     while (!(ptrNodoCorriente==ListaDeBots::fin())){
        ptrNodoCorriente=ListaDeBots::siguiente(equip.listBots,ptrNodoCorriente);
        cant++;
     }
    return cant;
}

/******************************************************************************/

void destruirequipo(Equipo &equip){
     equip.id=0;
     ListaDeBots::eliminarLista(equip.listBots);
}
/******************************************************************************/

BodegaPuntos GetPuntosEquipo(Equipo &equip){
    //apunto al primer nodo q apunta al Bot
    ListaDeBots::NodoLista* ptrNodoCorriente=ListaDeBots::primero(equip.listBots);
    Pbot ptrBot;
    Perforadora* ptrPerforadora;
    BodegaPuntos PuntosEquipo=0;
    while (!(ptrNodoCorriente==ListaDeBots::fin())){
         //obtengo el "punero a Bot" apuntado por ptrNodoCorriente
         ListaDeBots::obtenerDato(equip.listBots,ptrBot, ptrNodoCorriente);

         ptrPerforadora=get_Perforadora(*ptrBot);
         //Si tiene salida a la superficie
         if (getSalida(*ptrPerforadora) == true)
            PuntosEquipo+=getBodegaPuntos(*ptrPerforadora);
         //apunto al siguiente nodo a ptrcorriente, si es fin salgo del ciclo
         ptrNodoCorriente=ListaDeBots::siguiente(equip.listBots,ptrNodoCorriente);
     }
    return PuntosEquipo;
}

/******************************************************************************/

void ObtenerListaBots(Equipo &equip,ListaDeBots::Lista &listabotsalida){
     //apunto al nodo del puntero al primer Bot
     ListaDeBots::PtrNodoLista ptrNodoCorriente=ListaDeBots::primero(equip.listBots);
     //variable aux
     ListaDeBots::PtrNodoLista ptrNodoListaAux;
     //creo un puntero a bot
     Bot* ptrBot;
     while (ptrNodoCorriente!=ListaDeBots::fin()){
         //obtengo el "punero a Bot" apuntado por ptrNodoCorriente
         ListaDeBots::obtenerDato(equip.listBots,ptrBot, ptrNodoCorriente);
         //adiciono al final de la lista de salida
         ptrNodoListaAux=ListaDeBots::adicionarFinal(listabotsalida,ptrBot);
         //apunto al siguiente nodo a ptrcorriente, si es fin salgo del ciclo
         ptrNodoCorriente=ListaDeBots::siguiente(equip.listBots,ptrNodoCorriente);
     }
}

/*----------------------------------------*/
