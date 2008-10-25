package mapaDeJuego;


import java.util.Iterator;

import nivelDeJuego.ColPooglins;
import nivelDeJuego.ColTerreno;
import nivelDeJuego.InfoNivel;

import elementosDelMapa.Nave;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;

import propiedadesDeElementos.Posicion;


import utilitarios.Constants;













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
		mapaTerreno = new MapaTerreno();
		naveIngreso = new Nave (infoNivel.getPosicionNaveIngreso());
	    naveEscape = new Nave(infoNivel.getPosicionNaveEscape());
	    naveIngreso.cargarPooglings(infoNivel.getColPooglins());
	}
	
	public ColPooglins obtenerPooglinsNaveIngreso(){
		return naveIngreso.obtenerPooglings();
	}
	
	public ColPooglins obtenerPooglinsNaveEscape(){
		return naveEscape.obtenerPooglings();
	}
	
	public Posicion obtenerPosicionNaveIngreso(){
		return naveIngreso.obtenerPosicion();
	}
	
	public Posicion obtenerPosicionNaveEscape(){
		return naveEscape.obtenerPosicion();
	}
	
	public boolean isPooglinLlegoANaveEscape(Poogling poogling){
		if (poogling.getMovimiento().getPosicion().compareTo(this.naveEscape.obtenerPosicion())==Constants.ValorComparador.IGUAL)
		return true;
		else 
			return false;
	}
	
	public void subirPooglinNaveEscape(Poogling pooglin){
		//Cuando las posiciones coinciden el pooglin se sube a la nave
		//para pasar al 2do nivel
		naveEscape.colisionarPoogling(pooglin);
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
