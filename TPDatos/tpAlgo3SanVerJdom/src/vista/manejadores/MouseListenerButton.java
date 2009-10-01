package vista.manejadores;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import controlador.ControladorDePooglin;
public class MouseListenerButton extends MouseAdapter {
	
	private ControladorDePooglin controladorDePooglin;
	private int id;
	
	public MouseListenerButton(ControladorDePooglin controladorDePooglin,int id){
		this.controladorDePooglin  = controladorDePooglin;
		this.id = id;
	}

	public void mouseClicked(MouseEvent e) {
		System.out.println("CLICK SOBRE BOTON");
		this.controladorDePooglin.activarHabilidad(this.id);
		
	}
	
	

}
