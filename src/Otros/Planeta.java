package Otros;

import java.util.Iterator;

import TipoPosicion.Mapa;


public class Planeta{
	
	private Mapa mapa;
		
	public Planeta(InfoNivel infoNivel){
		mapa = new Mapa(infoNivel);
		mapa.cargarTerrenoDeJuego();
	}
	
	public void moverPooglin(Poogling pooglin){
		pooglin.mover(mapa);
	}
	
	public ColPooglins obtenerPooglins(){
		return mapa.obtenerPooglins();
	}
	
	
	
} 
