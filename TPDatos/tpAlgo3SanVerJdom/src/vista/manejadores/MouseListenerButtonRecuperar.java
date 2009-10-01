package vista.manejadores;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import vista.PruebaFlujoVentanas;

import controlador.ControladorPersistencia;


	

public class MouseListenerButtonRecuperar implements ActionListener{

	
	private ControladorPersistencia controladorPersistencia;
	
	public MouseListenerButtonRecuperar(ControladorPersistencia controladorPersistencia){
		this.controladorPersistencia  = controladorPersistencia;
	}
	
	public void actionPerformed(ActionEvent e) {
			
			int idNivel = 0;
			boolean nivelGuardado = true;
			try {
				idNivel = Niveles.recuperarIdNivel("XMLPersistencia/NroNivel.prs"); 
			} catch (Exception f) {
				nivelGuardado = false;
				
			}
		
			if (nivelGuardado)
				this.controladorPersistencia.recuperar(idNivel);
			
	}

	



	
	
}
