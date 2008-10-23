package Otros;

import java.util.Iterator;

import TipoPosicion.Mapa;


public class Planeta{
	
	private Mapa mapa;
		
	public Planeta(InfoNivel infoNivel){
		mapa = new Mapa(infoNivel);
		mapa.cargarTerrenoDeJuego();
	}
	
	public boolean moverPooglin(Poogling pooglin){
		return pooglin.mover(mapa);
	}
	
	public ColPooglins obtenerPooglinsNaveIngreso(){
		return mapa.obtenerPooglinsNaveIngreso();
	}
	
	public ColPooglins obtenerPooglinsNaveEscape(){
		return mapa.obtenerPooglinsNaveEscape();
	}
	
} 
