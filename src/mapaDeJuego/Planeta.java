package mapaDeJuego;

import habilidadesPooglins.ContenedorHabilidades;

import java.util.Iterator;

import nivelDeJuego.ColPooglins;
import nivelDeJuego.InfoNivel;

import elementosDelMapa.Poogling;




public class Planeta{
	
	private Mapa mapa;
		
	public Planeta(InfoNivel infoNivel){
		mapa = new Mapa(infoNivel);
		mapa.cargarTerrenoDeJuego();
		ContenedorHabilidades.getInstance().mapearHabilidades(infoNivel.getFabricaHabilidades());
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
