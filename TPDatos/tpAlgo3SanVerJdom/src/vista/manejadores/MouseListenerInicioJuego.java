package vista.manejadores;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import vista.paneles.PanelDeNiveles;
import vista.paneles.PanelPrincipal;
import vista.paneles.VentanaPrincipal;
import vista.utilitarias.NavegadorDeVentanas;


public class MouseListenerInicioJuego extends MouseAdapter {
	
	public MouseListenerInicioJuego(){
		
	}

	public void mouseClicked(MouseEvent e) {
		
		NavegadorDeVentanas.getInstance().crearPanelDeNiveles();
	}
}
