package modelo.fabricaTerrenos;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;

import modelo.elementosDelMapa.Fuego;
import modelo.elementosDelMapa.Terreno;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Vida;
import modelo.utilitarios.Constants;
import modelo.xml.DatosTerreno;

public class MapeoTerrenos {
	private List terrenos = new ArrayList(); //se uso un arrayList y no un mapa (no se pudo hacer los mismo que en la clase ContenedorHabilidades)
											 //porque la lista que se le pasa por parametro al metodo que cargaria al mapa de terrenos contiene claves repetidas.	
	private Hashtable mapTerrenosDisponibles = new Hashtable();
	
	private static MapeoTerrenos instance = new MapeoTerrenos();
	
	private MapeoTerrenos(){
		cargarFabricaMapaTerrenosDisponibles();
	}
	
	public static MapeoTerrenos getInstance(){
		return instance;
	}
	
	private void cargarFabricaMapaTerrenosDisponibles(){
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.AIRE, new FabricaAire());
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.AGUJERO_NEGRO, new FabricaAgujeroNegro());
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.FUEGO, new FabricaFuego());
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.HIELO, new FabricaHielo());
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.ROCA, new FabricaRoca());
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.TIERRA, new FabricaTierra());
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.TUNEL_DERECHA, new FabricaTunelDerecha());
		mapTerrenosDisponibles.put(Constants.NombreTerrenos.TUNEL_IZQUIERDA, new FabricaTunelIzquierda());
	}
	
	//con este metodo solo se cargaran en el mapa los terrenos que esten en el nivel de juego
	//se filtrara el resto.
	public void cargarMapaTerrenos(List datosTerrenos){
	
		
		for(Iterator it = datosTerrenos.iterator();it.hasNext();){
			DatosTerreno datoTerreno = (DatosTerreno)it.next();
			Posicion posicion=new Posicion(Integer.parseInt(datoTerreno.getCoordenadaX()),Integer.parseInt(datoTerreno.getCoordenadaY()));
			Terreno terreno = ((FabricaTerrenos)mapTerrenosDisponibles.get(datoTerreno.getNombreTerreno())).crear();
			terreno.asignarPosicion(posicion);
			terreno.setVida(new Vida(Integer.parseInt(datoTerreno.getCantVidas())));
			terrenos.add(terreno);
		}
	}
	
	public Terreno obtenerTerreno(String nombre){
		return (Terreno)mapTerrenosDisponibles.get(nombre);
	}
	
	public List obtenerColeccionTerrenos(){
		return terrenos;
	}
	
}
