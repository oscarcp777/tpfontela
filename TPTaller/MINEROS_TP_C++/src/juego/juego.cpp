
#include "Juego.h"

using namespace std;

void crear(Juego &juego, ArchivoTexto &partida)
{
    ArchivoRegistros aEquipos;
    ArchivoRegistros aBots;
    ArchivoTexto aTablero;
    string cadenaAuxiliar;
    string parametro;
    string valor;
    Cadena cadena;
    bool fin = false;

    juego.rondaActual = 0;
    //creo la cadena
    crear(cadena);
    //creo la lista de bots en juego
    ListaDeBots::crearLista(*(obtenerBotsEnJuego(juego)));
    //voy al comienzo del archivo
    irAlComienzo(partida);
    fin = !leerLinea(partida, cadenaAuxiliar);
    while ( !fin )
    {
        setValor(cadena, cadenaAuxiliar);
        //busco que parametro esta entre el punto y el igual
        parametro = buscarParametro(cadena,'.','=');
        //obtengo el valor que va despues del igual
        valor = obtenerValor(cadena,'=');
        setValor(cadena, valor);
        //cargo los bots, equipos, tablero, asigno la cant de rondas y
        //creo el archivo de resultados. Hago un if ya que no puedo hacer
        //un switch de un string
        if(parametro == "rondas")
            juego.cantRondas = convertirStringAInt(cadena);
        if(parametro == "tablero")
            // creo archivo tablero
            crear(aTablero,valor);
        if(parametro == "bots")
            //creo archivo bots
            crear(aBots, valor, sizeof(regBots));
        if(parametro == "equipos")
            //creo archivo equipos
            crear(aEquipos, valor, sizeof(regEquipos));
        if(parametro == "resultado")
            //creo archivo resultados
            crear(*(obtenerAResultados(juego)),valor);
        fin = !leerLinea(partida, cadenaAuxiliar);
    }
        //creo los equipos
        crearGrupoEquipos(*obtenerEquipos(juego), aEquipos, aBots);
        //cargo el tablero
        Crear(*obtenerTablero(juego),aTablero);
        //Si hay mas bots que columnas, no se pueden ubicar en el tablero al principio

        if (getCantColumnas(*getMatriz(*obtenerTablero(juego))) < cantidadBotsTotales(*obtenerEquipos(juego))){
            cout << "Error: Hay mas bots que casilleros en una fila del tablero" << endl;
            juego.cantRondas = -1; //coloco el juego en un estado inválido
        }
        destruir(cadena);
        destruir(aEquipos);
        destruir(aBots);
        destruir(aTablero);
   }

void destruir(Juego &juego)
{
    Destruir(*obtenerTablero(juego));
    destruirGrupoEquipos(*obtenerEquipos(juego));
    ListaDeBots::eliminarLista(*(obtenerBotsEnJuego(juego)));
    destruir(*obtenerAResultados(juego));
}

void comenzar(Juego &juego)
{

    irAlComienzo(*(obtenerAResultados(juego)));
    escribirCadena(*(obtenerAResultados(juego)), "<partida>");
    bajarDeLinea(*(obtenerAResultados(juego)));
    tabular(*(obtenerAResultados(juego)));
    escribirCadena(*(obtenerAResultados(juego)), "<rondas>");
    bajarDeLinea(*(obtenerAResultados(juego)));
    //cargo todos los bots del equipo

    asignarBotsEnJuego(juego);
    UbicarBotsIniciales(*obtenerTablero(juego),*obtenerBotsEnJuego(juego));
    while ( rondaActual(juego) <= cantidadRondas(juego) )
    {
        crear(*(obtenerRonda(juego)),rondaActual(juego) );
            jugar(*(obtenerRonda(juego)),*(obtenerTablero(juego)) ,*(obtenerAResultados(juego)), *obtenerBotsEnJuego(juego), obtenerEquipos(juego));
            juego.rondaActual++;
        destruir(*obtenerRonda(juego));
    }
    terminar(juego);
}
void terminar(Juego &juego)
{
    Equipo* auxiliarEquipo;

    bajarDeLinea(*(obtenerAResultados(juego)));
    tabular(*(obtenerAResultados(juego)));
    escribirCadena(*(obtenerAResultados(juego)), "</rondas>");
    bajarDeLinea(*(obtenerAResultados(juego)));
    tabular(*(obtenerAResultados(juego)));
    escribirCadena(*(obtenerAResultados(juego)), "<ganador>");
    auxiliarEquipo = equipoConMasPuntos(juego);
    escribirCadena(*(obtenerAResultados(juego)), getnombre(*auxiliarEquipo)),
    escribirCadena(*(obtenerAResultados(juego)), "</ganador>");
    bajarDeLinea(*(obtenerAResultados(juego)));
    escribirCadena(*(obtenerAResultados(juego)), "</partida>");
}

tRondas cantidadRondas(Juego &juego)
{
    return juego.cantRondas;
}
tRondas rondaActual(Juego &juego)
{
    return juego.rondaActual;
}
Equipo* equipoConMasPuntos(Juego &juego)
{
    return EquipoMayorPuntaje(*obtenerEquipos(juego));
}
Ronda* obtenerRonda(Juego &juego)
{
    return &(juego.ronda);
}
ArchivoTexto* obtenerAResultados(Juego &juego)
{
    return &(juego.aResultado);
}
Tablero* obtenerTablero(Juego &juego)
{
    return &(juego.tablero);
}
GrupoEquipos* obtenerEquipos(Juego &juego)
{
    return &(juego.equipos);
}
ListaDeBots::Lista* obtenerBotsEnJuego(Juego &juego)
{
    return &(juego.botsEnjuego);
}
void asignarBotsEnJuego(Juego &juego)
{
    obtenerlistaBotsGrupoEquipos(*(obtenerEquipos(juego)),*(obtenerBotsEnJuego(juego)));
}
