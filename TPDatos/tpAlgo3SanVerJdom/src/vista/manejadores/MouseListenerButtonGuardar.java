package vista.manejadores;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import modelo.constantes.Constantes;

import vista.componentes.Actor;

import controlador.ControladorDePooglin;
import controlador.ControladorPersistencia;
import controlador.excepciones.HabilidadInactivaException;


public class MouseListenerButtonGuardar implements ActionListener{
	
	
	private ControladorPersistencia controladorPersistencia;
	
	public MouseListenerButtonGuardar(ControladorPersistencia controladorPersistencia){
		this.controladorPersistencia  = controladorPersistencia;
	}
	
	public void actionPerformed(ActionEvent e) {
			this.controladorPersistencia.guardar();
		
	}

	

}
