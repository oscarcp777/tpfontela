package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import controlador.ControladorPersistencia;

import vista.PruebaFlujoVentanas;

public class ManejadorBotonCargar extends MouseAdapter implements MouseListener {

	
	private ControladorPersistencia controladorPersistencia;
	
	public ManejadorBotonCargar(ControladorPersistencia controladorPersistencia){
		this.controladorPersistencia  = controladorPersistencia;
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
	PruebaFlujoVentanas.flujo.pausar();
		int idNivel = 0;
		boolean nivelGuardado = true;
		try {
			idNivel = Niveles.recuperarIdNivel("XMLPersistencia/NroNivel.prs"); 
		} catch (Exception f) {
			nivelGuardado = false;
		}
	
		if (nivelGuardado)
			PruebaFlujoVentanas.mapa = this.controladorPersistencia.recuperar(idNivel);
		PruebaFlujoVentanas.flujo.play();
	}
	
	
}
