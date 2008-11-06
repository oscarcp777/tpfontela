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
		//En este constructor se cargan los atributos del mapa de acuerdo a la informacion recibida por el planeta,
		//que seria nuestro nivel de juego.
			 
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
	
	public boolean llegoPooglinANaveEscape(Poogling poogling){
		if (poogling.obtenerPosicion().compareTo(this.naveEscape.obtenerPosicion())==Constants.ValorComparador.IGUAL)
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
	
	//Si la clave posicion del terreno se encuentra en el mapa, borra el terreno actual
	//y lo cambia por el terreno que se le pasa por parametro, en caso contrario no hace dicho cambio. 
	public void cambiarTerreno(Terreno terreno){
		if(mapaTerreno.eliminarTerreno(terreno.obtenerPosicion()))
		mapaTerreno.agregarTerreno(terreno);	
	}
	
	public Terreno obtenerTerreno(Posicion posicionKey){
		return (Terreno)mapaTerreno.obtenerTerreno(posicionKey);
	}
	
	private void agregarAcolTerrenoBloqueContiguo(ColTerreno colTerrenoContiguos,Terreno terrenoContiguo){
		if(terrenoContiguo!=null)
			colTerrenoContiguos.agregarTerreno(terrenoContiguo);
	}
	
	public ColTerreno obtenerBloquesContiguosAlPooglin(Poogling pooglin){
		Posicion posicionActualPooglin = pooglin.obtenerPosicion();
		ColTerreno colTerrenoContiguos = new ColTerreno();
		
		Terreno terrenoArriba=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteArriba());
		Terreno terrenoAbajo=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteAbajo());
		Terreno terrenoDerecha=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteIzquierda());
		Terreno terrenoIzquierda=(Terreno)obtenerTerreno(posicionActualPooglin.obtenerPosicionSiguienteDerecha());
	
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoArriba);	
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoAbajo);
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoDerecha);
		agregarAcolTerrenoBloqueContiguo(colTerrenoContiguos,terrenoIzquierda);
	
		return colTerrenoContiguos;
	}
	
	
}
