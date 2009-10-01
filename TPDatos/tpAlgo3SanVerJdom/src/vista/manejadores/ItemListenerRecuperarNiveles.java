package vista.manejadores;

import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import controlador.ControladorPersistencia;

import vista.PruebaFlujoVentanas;

public class ItemListenerRecuperarNiveles implements ItemListener  {
	
	private ControladorPersistencia controladorPersistencia;
	
	public ItemListenerRecuperarNiveles(ControladorPersistencia controladorPersistencia){
		this.controladorPersistencia  = controladorPersistencia;
	}
	
	public void itemStateChanged(ItemEvent e) {
		
		Niveles nivel = (Niveles)e.getItem(); 
		if(e.getStateChange() != 2){	
			
			int idNivel = 0;
			boolean nivelGuardado = true;
			try {
				idNivel = Niveles.recuperarIdNivel("XMLPersistencia/NroNivel.prs"); 
			} catch (Exception f) {
				nivelGuardado = false;
			}
		
			if (nivelGuardado)
			PruebaFlujoVentanas.cargarJuego(this.controladorPersistencia.recuperar(idNivel));		
		}		
	}
}
