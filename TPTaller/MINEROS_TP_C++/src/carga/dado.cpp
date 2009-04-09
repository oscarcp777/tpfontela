/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Mandrafina                             *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 ******************************************************************************/

/******************************************************************************
 *                               TDA DADO                                     *
 ******************************************************************************/

/********************************HEADERS***************************************/

#include "dado.h"

/*******************************PRIMITIVAS*************************************/

/* Crear */

void crear(Dado &dado1, int cantidadcaras){
    srand(time(NULL)); //Crea la semilla para el dado tomando la hora del sistema
    if ((cantidadcaras > 0) && (cantidadcaras < 10000)){ //Valida la cantidad de caras
        ListaDeCaras::crearLista(dado1.ListaCaras); //Crea la lista de caras
        dado1.CantidadCaras = cantidadcaras; //Asigna la cantidad de caras al dado
        //Bucle repetitivo que asigna los valores y las caras al dado.
        //El valor de una cara esta dado seg�n su n�mero de cara.
        for(int contador = 1; contador <= obtenerCantDeCaras(dado1); contador++){
            Cara cara1; //Crea una variable de tipo cara
            crear(cara1, contador); //Crea la cara
            ListaDeCaras::NumCara numerocara1 = contador; /*Crea y asigna una variable
                                                            con el n�mero de caras */
            ListaDeCaras::Dato DatoLista; //Crea una variable de tipo dato de la lista
            DatoLista.numerocara = numerocara1; //Asigna el numero de cara al dato de la lista
            DatoLista.cara = cara1; //Le asigna la cara
            ListaDeCaras::PtrNodoLista Puntero = NULL; //Crea un puntero a nodo de la lista
            //Adiciona el dato al final de la lista para mantener el orden
            Puntero = ListaDeCaras::adicionarFinal(dado1.ListaCaras, DatoLista);
        }
    } else {
        dado1.CantidadCaras = -1; //Sino invalida el dado
    }
}

/* Destruir */

void destruir(Dado &dado1){
    if (obtenerCantDeCaras(dado1) > 0) { //Verifica que el dado ya no sea inv�lido
        ListaDeCaras::eliminarLista(dado1.ListaCaras); //Elimina la lista de caras
        dado1.CantidadCaras = -1; //Invalida el dado
    }
}

/* Obtener Cara */

Valor obtenerCara(Dado &dado1, ListaDeCaras::NumCara numero){
    if ((obtenerCantDeCaras(dado1) > 0) && (numero > 0) &&
    (numero <=  obtenerCantDeCaras(dado1))){ /* Valida la cantidad de caras
                                                    y el n�mero pasado como par�metro */
        ListaDeCaras::PtrNodoLista Puntero = NULL; // Crea un puntero a nodo de la lista
        ListaDeCaras::Dato DatoLista; //Crea un dato de la lista
        Cara caraaux; //Crea una variable cara auxiliar para la b�squeda
        crear(caraaux,1); /*Crea la cara asignando un n�mero arbitrario 1
                                 para el n�mero de caras (podr�a ser cualquiera) */
        DatoLista.numerocara = numero; //Asigna el n�mero de la cara al dato
        DatoLista.cara = caraaux; //Asigna la cara auxiliar al dato
        /* Asigna un puntero al nodo donde est� el dato con el n�mero de cara a
        obtener el valor */
        Puntero = ListaDeCaras::localizarDato(dado1.ListaCaras, DatoLista);
        destruir(caraaux); // Destruye la cara auxiliar
        return get_Valor(Puntero -> dato.cara); /* Devuelve el valor de la
                                                     cara encontrada */
    } else {
        return -1; // Sino devuelve valor -1
    }
}

/* Obtener Cantidad de Caras */

int obtenerCantDeCaras(Dado &dado1){
    return dado1.CantidadCaras; //Devuelve la cantidad de caras del dado
}

/* Tirar */

Valor tirar(Dado &dado1){
    if ((obtenerCantDeCaras(dado1) > 0)) { //Valida la cantidad de caras del dado
        int numerocara; //Crea una variable del n�mero de cara a obtener el valor
        numerocara = (rand() % obtenerCantDeCaras(dado1)) + 1; /* Asigna un
        n�mero de cara v�lido del dado al azar */
        return obtenerCara(dado1, numerocara); /* Devuelve el valor de la cara
                                                       con ese n�mero */
    } else {
        return -1; //Sino devuelve valor -1
    }
}






