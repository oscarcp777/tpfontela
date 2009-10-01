package controlador;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import vista.PruebaFlujoVentanas;
import vista.manejadores.LevantaMapas;
import vista.utilitarias.IniciadorDeImagenes;
import modelo.control.Nivel;
import modelo.entornoDeJuego.ControladorEstadoPooglin;
import modelo.entornoDeJuego.EstadoPooglin;
import modelo.entornoDeJuego.Mapa;
import modelo.entornoDeJuego.ServiciosTerreno;
import modelo.persistencia.Persistidor;
import modelo.persistencia.SerializableJDOM;
import modelo.pooglins.Posicion;

public class ControladorPersistencia {

	private Mapa controladorPoglin;
	private ControladorEstadoHabilidades controladorHabilidades;
	
	public ControladorPersistencia(Mapa controladorPoglin) {
		this.controladorPoglin = controladorPoglin;
		this.controladorHabilidades = ControladorEstadoHabilidades.getIntence();
		
	}
	
	public void guardar(){
		try {
			Persistidor.guardar("XMLPersistencia/nivelEnJuego.xml", (SerializableJDOM)this.controladorPoglin);
		} catch (Exception e) {
			System.out.println("NO FUNCIONA");
		}
		
	}
	
	public Mapa recuperar(int nroNivel){
		Mapa mapa = null;
		try {
			
			mapa = LevantaMapas.getIntance().cargarMapa(nroNivel);
			Persistidor.recuperar("XMLPersistencia/nivelEnJuego.xml", (SerializableJDOM)mapa);
			List<EstadoPooglin> list = (List)((LinkedList)mapa.getEstadoPooglins()).clone();
			for (EstadoPooglin e : list) {
				mapa.agregarPooglinPorEstado(e);
			}
		} catch (Exception e) {
			System.out.println("NO FUNCIONA");
		}
	return mapa;	
	
	}
	
	
	

}
