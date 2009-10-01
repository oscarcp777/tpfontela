package controlador;

import java.util.HashMap;

import vista.manejadores.ManejadorEventosBotonesHabilidad;

import modelo.pooglins.HabilidadesDisponibles;

public class ControladorDeDisponibilidadHabilidades {
	
	public HabilidadesDisponibles oficios;
	public static ControladorDeDisponibilidadHabilidades instance;
	
	public static ControladorDeDisponibilidadHabilidades getInstance(HabilidadesDisponibles inVO) {
		if (ControladorDeDisponibilidadHabilidades.instance == null) ControladorDeDisponibilidadHabilidades.instance = new ControladorDeDisponibilidadHabilidades(inVO);
		return ControladorDeDisponibilidadHabilidades.instance;
	}

	private ControladorDeDisponibilidadHabilidades(HabilidadesDisponibles inVO) {

		oficios = inVO;
		
	}
	
	public void descontarUno(Integer idOficio){
		oficios.descontarUno(idOficio);
	}
	
	public boolean tieneDisponibles(Integer idOficio) {
		return 	oficios.tieneDisponibles(idOficio);
	}
	
	public int obtenerDiponibles(Integer idOficio){
		return oficios.obtenerDisponiblesPorIdDeNivel(idOficio);
	}
	

}
