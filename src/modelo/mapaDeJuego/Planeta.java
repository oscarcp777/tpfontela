package modelo.mapaDeJuego;


import java.util.Iterator;



import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.habilidadesPooglins.ContenedorHabilidades;
import modelo.nivelDeJuego.ColPooglins;
import modelo.nivelDeJuego.InfoNivel;
import modelo.propiedadesDeElementos.Posicion;
import modelo.utilitarios.Constants;





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
