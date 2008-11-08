package mapaDeJuego;

import habilidadesPooglins.ContenedorHabilidades;

import java.util.Iterator;

import propiedadesDeElementos.Posicion;

import utilitarios.Constants;

import nivelDeJuego.ColPooglins;
import nivelDeJuego.InfoNivel;

import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;




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
	
	public boolean cambioAirePorHielo(Posicion posicion){
		Terreno terreno=mapa.obtenerTerreno(posicion);
		return (terreno.obtenerNombre().equals(Constants.NombreTerrenos.HIELO));
	}
	
	
} 
