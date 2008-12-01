package modelo.mapaDeJuego;


import modelo.elementosDelMapa.Nave;
import modelo.elementosDelMapa.Poogling;
import modelo.nivelDeJuego.ColPooglins;
import modelo.nivelDeJuego.ColTerreno;
import modelo.nivelDeJuego.InfoNivel;





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
		
	public ColTerreno obtenerTerrenosDelMapa(){
		return mapa.getColTerreno();
	}
	
	public Nave obtenerNaveIngreso(){
		return mapa.getNaveIngreso();
	}
	
	public Nave obtenerNaveEscape(){
		return mapa.getNaveEscape();
	}
	
	public Mapa obtenerMapaDeJuego(){
		return mapa;
	}
	
	
} 
