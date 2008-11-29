package modelo.habilidadesPooglins;


import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;

import modelo.FabricaHabilidades.FabricaCongelamiento;
import modelo.FabricaHabilidades.FabricaHabilidades;
import modelo.FabricaHabilidades.FabricaPlatilloVolador;
import modelo.FabricaHabilidades.FabricaRayoLaser;
import modelo.FabricaHabilidades.FabricaTaladroUltrasonico;
import modelo.FabricaHabilidades.FabricaTeletransportacion;
import modelo.FabricaHabilidades.FabricaTunelElectromagnetico;
import modelo.utilitarios.Constants;
import modelo.xml.DatosHabilidades;


public class ContenedorHabilidades {

	private List habilidades = new ArrayList();
	private Hashtable mapaHabilidadesDisponibles = new Hashtable();
	
	private static ContenedorHabilidades instance = new ContenedorHabilidades();
	
	private ContenedorHabilidades(){
		cargarHabilidadesDisponibles();
	}
	
	public static ContenedorHabilidades getInstance(){
		return instance;
	}
	
	private void cargarHabilidadesDisponibles(){
		mapaHabilidadesDisponibles.put(Constants.NombreHabilidades.CONGELAMIENTO,new FabricaCongelamiento());
		mapaHabilidadesDisponibles.put(Constants.NombreHabilidades.PLATILLO_VOLADOR,new FabricaPlatilloVolador());
		mapaHabilidadesDisponibles.put(Constants.NombreHabilidades.RAYO_LASER,new FabricaRayoLaser());
		mapaHabilidadesDisponibles.put(Constants.NombreHabilidades.TALADRO_ULTRASONICO,new FabricaTaladroUltrasonico());
		mapaHabilidadesDisponibles.put(Constants.NombreHabilidades.TELETRANSPORTACION,new FabricaTeletransportacion());
		mapaHabilidadesDisponibles.put(Constants.NombreHabilidades.TUNEL_ELECTROMAGNETICO,new FabricaTunelElectromagnetico());
	}
	
	//se cargan las habilidades disponibles en el nivel de juego
	//el resto se filtra
	public void cargarMapaHabilidades(List nombreHabilidades){
		 
		for(Iterator it = nombreHabilidades.iterator();it.hasNext();){
			DatosHabilidades datosHabilidades = (DatosHabilidades)it.next();
			Habilidad habilidad=((FabricaHabilidades)mapaHabilidadesDisponibles.get(datosHabilidades.getNombreHabilidad())).crear();
			if(Boolean.parseBoolean(datosHabilidades.getEstadoHabilidad()))
				habilidad.activarHabilidad();
			else
				habilidad.desactivarHabilidad();
			habilidades.add(habilidad);
		}
		
	}
		
	public List obtenerColeccionHabilidades(){
		return habilidades;
	}
	
	public Habilidad obtenerHabilidad(String nombre){
	/*	FabricaHabilidades fabricaHabilidad = (FabricaHabilidades)mapaHabilidadesDisponibles.get(nombre);
		Habilidad habilidad = fabricaHabilidad.crear();
		return (habilidades.contains(habilidad))? habilidad: null; //si existe la habilidad en la lista de habilidades
																				   //disponibles, la retorna sino devuelve null	
	*/
		//Dejar lo anterior, ver como cargar la lista habilidades disponibles segun el nivel de juego
		//mediante el metodo cargarMapaHabilidades
		return ((FabricaHabilidades)mapaHabilidadesDisponibles.get(nombre)).crear();
		
	}
}
