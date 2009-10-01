package vista.manejadores;

import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import controlador.ControladorPersistencia;

public class ManejadorBotonGuardar extends MouseAdapter implements
		MouseListener {

	
	private ControladorPersistencia controladorPersistencia;
	
	public ManejadorBotonGuardar(ControladorPersistencia controladorPersistencia){
		this.controladorPersistencia  = controladorPersistencia;
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		this.controladorPersistencia.guardar();
	}
	
}
