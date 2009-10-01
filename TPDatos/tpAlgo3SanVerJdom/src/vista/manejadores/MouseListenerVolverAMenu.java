package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import vista.utilitarias.NavegadorDeVentanas;

public class MouseListenerVolverAMenu  extends MouseAdapter {

	public void mouseClicked(MouseEvent e) {
		
		NavegadorDeVentanas.getInstance().crearPanelPrincipal();
	}
}
