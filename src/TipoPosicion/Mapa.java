package TipoPosicion;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import fabricas.FabricaTerreno;

import fabricas.MapaTerreno;



import Otros.ColPooglins;
import Otros.Dimension;

import Otros.ColTerreno;
import Otros.DimensionTerreno;
import Otros.InfoNivel;
import Otros.Nave;
import Otros.Poogling;
import TipoTerrenos.Aire;
import TipoTerrenos.Terreno;
import TipoTerrenos.Tierra;
import Utilidades.Constants;


public class Mapa {
	
	//La matriz del terreno tendra como posicion superior izquierda 00
	//y como posicion inferior derecha Ymax(filaMax) y Xmax(columnaMax)
	
	private ColTerreno colTerreno;
	private MapaTerreno mapaTerreno;
	private Nave naveIngreso;
	private Nave naveEscape;
		
	public Mapa(InfoNivel infoNivel){
		//En este constructor se cargan los atributos del mapa de acuerdo a la información recibida por el planeta,
		//que sería nuestro nivel de juego.
			 
		colTerreno = infoNivel.getColTerreno();
		mapaTerreno = new MapaTerreno(infoNivel.getDimensionTerreno());
		naveIngreso = new Nave (infoNivel.getPosicionNaveIngreso());
	    naveEscape = new Nave(infoNivel.getPosicionNaveEscape());
	    naveIngreso.cargarPooglings(infoNivel.getColPooglins());
	}
	
	public ColPooglins obtenerPooglins(){
		return naveIngreso.obtenerPooglings();
	}
	
	public Posicion obtenerPosicionNaveIngreso(){
		return naveIngreso.obtenerPosicion();
	}
	
	public Posicion obtenerPosicionNaveEscape(){
		return naveEscape.obtenerPosicion();
	}
	
	public void subirPooglinNaveEscape(Poogling pooglin){
		//Cuando las posiciones coinciden el pooglin se sube a la nave
		//para pasar al 2do nivel
		naveEscape.colisionPoogling(pooglin);
	}
	
	public void cargarTerrenoDeJuego(){
		for(Iterator itColTerreno=colTerreno.iterator();itColTerreno.hasNext();){
			Terreno terreno = (Terreno)itColTerreno.next();
			mapaTerreno.agregarTerreno(terreno);
		}
	}
	
	public Terreno obtenerTerreno(Posicion posicionKey){
		return (Terreno)mapaTerreno.obtenerTerreno(posicionKey);
	}
	
}
